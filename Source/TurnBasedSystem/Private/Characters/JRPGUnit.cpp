// Copyright (c) 2023, Me&Myself. All Rights Reserved.

#include "Characters/JRPGUnit.h"

#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Navigation/PathFollowingComponent.h"

void ATurnBasedJRPGUnit::BeginPlay()
{
	Super::BeginPlay();

	AIController = GetController<AAIController>();
}

void ATurnBasedJRPGUnit::BeginBattle()
{
	const float NormalizedHaste = UKismetMathLibrary::NormalizeToRange(Haste, 0, 255);
	const float DeltaActionTime = MaxActionTime - MinActionTime;

	const float WaitTime = (1 - NormalizedHaste) * DeltaActionTime + MinActionTime;
	
	GetWorld()->GetTimerManager().SetTimer(ActionTimerHandle, this, &ATurnBasedUnitBase::RequestTurn, WaitTime);
}

void ATurnBasedJRPGUnit::AttackCommand()
{
	AIController->MoveToActor(Target, 100);
	AIMoveDelegate = AIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &ATurnBasedJRPGUnit::OnUnitReachTarget);
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
