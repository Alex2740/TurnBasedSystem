// Copyright (c) 2023, Me&Myself. All Rights Reserved.

#include "Core/TurnBasedGameMode.h"

#include "Characters/UnitBase.h"
#include "Core/TurnBasedPlayerController.h"

ATurnBasedGameMode::ATurnBasedGameMode()
{
	PlayerControllerClass = ATurnBasedPlayerController::StaticClass();

	bTurnHasStarted = false;
}

void ATurnBasedGameMode::TurnRequest(ATurnBasedUnitBase* Unit)
{
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

void ATurnBasedGameMode::ReadyNextTurn()
{
	bTurnHasStarted = false;

	if (TurnOrder.IsValidIndex(0))
	{
		StartTurn();
	}
}
