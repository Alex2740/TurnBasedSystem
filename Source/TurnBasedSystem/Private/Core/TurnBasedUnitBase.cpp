// Copyright (c) 2023, Me&Myself. All Rights Reserved.

#include "Core/TurnBasedUnitBase.h"

#include "Core/TurnBasedGameMode.h"
#include "Kismet/GameplayStatics.h"

ATurnBasedUnitBase::ATurnBasedUnitBase()
{
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ATurnBasedUnitBase::BeginPlay()
{
	Super::BeginPlay();

	BattlePosition = GetActorTransform();

	MaxHealth = 100;
	CurrentHealth = 100;
}

void ATurnBasedUnitBase::StartUnitTurn()
{
	if (bIsPlayable)
	{
		BP_StartUnitTurn();
		return;
	}

	AITurn();
}

void ATurnBasedUnitBase::RequestTurn()
{
	ATurnBasedGameMode* TurnBasedGameMode = Cast<ATurnBasedGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	TurnBasedGameMode->TurnRequest(this);
}

float ATurnBasedUnitBase::CalculateDamage()
{
	return 1;
}

float ATurnBasedUnitBase::ApplyDamage(ATurnBasedUnitBase* DamageCauser, float BaseDamage)
{
	return TakeDamage_Internal(BaseDamage);
}

void ATurnBasedUnitBase::EndUnitTurn()
{
	OnTurnEndedDelegate.Broadcast();
	BeginBattle();
}

void ATurnBasedUnitBase::BeginBattle()
{
	ATurnBasedGameMode* TurnBasedGameMode = Cast<ATurnBasedGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	TurnBasedGameMode->AddUnit(this);
}

void ATurnBasedUnitBase::AITurn()
{
}

void ATurnBasedUnitBase::AttackCommand()
{
}

float ATurnBasedUnitBase::TakeDamage_Internal(float DamageAmount)
{
	const float OldHealth = CurrentHealth;

	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0, MaxHealth);

	const float ActualDamage = OldHealth - CurrentHealth;
	
	OnTakeDamage(ActualDamage);
	
	return ActualDamage;
}
