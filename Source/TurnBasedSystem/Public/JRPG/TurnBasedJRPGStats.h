// Copyright (c) 2023, Me&Myself. All Rights Reserved.

#pragma once

#include "Engine/DataTable.h"
#include "TurnBasedJRPGStats.generated.h"

USTRUCT(BlueprintType)
struct FTurnBasedJRPGStats : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	float Health;
	float Mana;
	float Strength;
	float Accuracy;
	float Stamina;
	float Haste;
	float Wisdom;
};
