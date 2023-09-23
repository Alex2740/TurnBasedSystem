// Copyright (c) 2023, Me&Myself. All Rights Reserved.

#include "Characters/UnitBase.h"

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
}

void ATurnBasedUnitBase::StartUnitTurn()
{
	AttackCommand();
}

void ATurnBasedUnitBase::RequestTurn()
{
	ATurnBasedGameMode* TurnBasedGameMode = Cast<ATurnBasedGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	TurnBasedGameMode->TurnRequest(this);
}

void ATurnBasedUnitBase::EndUnitTurn()
{
	OnTurnEndedDelegate.Broadcast();
	BeginBattle();
}

void ATurnBasedUnitBase::BeginBattle()
{
	RequestTurn();
}

void ATurnBasedUnitBase::AttackCommand()
{
}
