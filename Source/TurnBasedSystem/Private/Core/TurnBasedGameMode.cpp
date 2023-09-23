// Copyright (c) 2023, Me&Myself. All Rights Reserved.

#include "Core/TurnBasedGameMode.h"

#include "Core/TurnBasedUnitBase.h"
#include "Core/TurnBasedPlayerController.h"

ATurnBasedGameMode::ATurnBasedGameMode()
{
	PlayerControllerClass = ATurnBasedPlayerController::StaticClass();

	bTurnHasStarted = false;
}

void ATurnBasedGameMode::TurnRequest(ATurnBasedUnitBase* Unit)
{
	if (!Units.Contains(Unit))
	{
		return;
	}
	
	TurnOrder.AddUnique(Unit);
	StartTurn();
}

void ATurnBasedGameMode::StartTurn()
{
	if (bTurnHasStarted)
	{
		return;
	}

	bTurnHasStarted = true;
	for (ATurnBasedUnitBase* Unit : Units)
	{
		GetWorld()->GetTimerManager().PauseTimer(Unit->GetActionTimerHandle());
	}

	if (TurnOrder.IsValidIndex(0))
	{
		TurnOrder[0]->StartUnitTurn();
		TurnOrder[0]->OnTurnEndedDelegate.AddUniqueDynamic(this, &ATurnBasedGameMode::ReadyNextTurn);

		TurnOrder.RemoveAt(0);
	}
	else
	{
		ReadyNextTurn();
	}
}

void ATurnBasedGameMode::AddUnit(ATurnBasedUnitBase* Unit)
{
	Units.AddUnique(Unit);
}

void ATurnBasedGameMode::RemoveUnit(ATurnBasedUnitBase* Unit)
{
	Units.Remove(Unit);
}

void ATurnBasedGameMode::ReadyNextTurn()
{
	bTurnHasStarted = false;
	for (ATurnBasedUnitBase* Unit : Units)
	{
		GetWorld()->GetTimerManager().UnPauseTimer(Unit->GetActionTimerHandle());
	}

	if (TurnOrder.IsValidIndex(0))
	{
		StartTurn();
	}
}
