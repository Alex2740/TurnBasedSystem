// Copyright (c) 2023, Me&Myself. All Rights Reserved.

#include "JRPG/TurnBasedJRPGUnit.h"

#include "AIController.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Navigation/PathFollowingComponent.h"

void ATurnBasedJRPGUnit::BeginPlay()
{
	Super::BeginPlay();

	AIController = GetController<AAIController>();
	
	FName LevelName = FName(*FString::FromInt(LevelUnit));
	FTurnBasedJRPGStats* Row = BaseStatsDataTable->FindRow<FTurnBasedJRPGStats>(LevelName, "");
	BaseStats = *Row;
	
	MaxHealth = BaseStats.Health * StatsModifier.Health;
	CurrentHealth = MaxHealth;

	MaxMana = BaseStats.Mana * StatsModifier.Mana;
	CurrentMana = MaxMana;

	BeginBattle();
}

float ATurnBasedJRPGUnit::CalculateDamage()
{
	return BaseStats.Strength * StatsModifier.Strength * 5 * FMath::RandRange(.9f, 1.1f);
}

void ATurnBasedJRPGUnit::BeginBattle()
{
	Super::BeginBattle();
	
	const float NormalizedHaste = UKismetMathLibrary::NormalizeToRange(BaseStats.Haste, 0, 255);
	const float DeltaActionTime = MaxActionTime - MinActionTime;

	const float WaitTime = (1 - NormalizedHaste) * DeltaActionTime + MinActionTime;
	
	GetWorld()->GetTimerManager().SetTimer(ActionTimerHandle, this, &ATurnBasedUnitBase::RequestTurn, WaitTime);
}

void ATurnBasedJRPGUnit::AITurn()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATurnBasedJRPGUnit::StaticClass(), FoundActors);

	TArray<ATurnBasedJRPGUnit*> PossibleTargets;

	for (AActor* Actor : FoundActors)
	{
		ATurnBasedJRPGUnit* Unit = Cast<ATurnBasedJRPGUnit>(Actor);
		if (Unit->bIsPlayable)
		{
			PossibleTargets.Add(Unit);
		}
	}

	const int TargetIndex = FMath::RandRange(0, PossibleTargets.Num() - 1);
	Target = PossibleTargets[TargetIndex];

	AttackCommand();
}

void ATurnBasedJRPGUnit::AttackCommand()
{
	AIController->MoveToActor(Target, 100);
	AIMoveDelegate = AIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &ATurnBasedJRPGUnit::OnUnitReachTarget);
}

float ATurnBasedJRPGUnit::TakeDamage_Internal(float DamageAmount)
{
	float NewDamage = FMath::Pow(DamageAmount, 2) / (DamageAmount + BaseStats.Stamina * StatsModifier.Stamina);
	
	return Super::TakeDamage_Internal(NewDamage);
}

void ATurnBasedJRPGUnit::OnUnitReachTarget(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	BP_Attack();
}

void ATurnBasedJRPGUnit::OnUnitFinishedAttack()
{
	AIController->GetPathFollowingComponent()->OnRequestFinished.Remove(AIMoveDelegate);
	AIController->MoveToLocation(BattlePosition.GetLocation());
	AIMoveDelegate = AIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &ATurnBasedJRPGUnit::OnUnitBackToBattlePosition);
}

void ATurnBasedJRPGUnit::OnUnitBackToBattlePosition(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	AIController->GetPathFollowingComponent()->OnRequestFinished.Remove(AIMoveDelegate);
	SetActorRotation(BattlePosition.GetRotation());

	EndUnitTurn();
}
