// Copyright (c) 2023, Me&Myself. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TurnBasedGameMode.generated.h"

class ATurnBasedUnitBase;

UCLASS()
class TURNBASEDSYSTEM_API ATurnBasedGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATurnBasedGameMode();

	void TurnRequest(ATurnBasedUnitBase* Unit);
	
	void StartTurn();

private:
	void ReadyNextTurn();
	
	UPROPERTY()
	TArray<ATurnBasedUnitBase*> TurnOrder;

	bool bTurnHasStarted;
};
