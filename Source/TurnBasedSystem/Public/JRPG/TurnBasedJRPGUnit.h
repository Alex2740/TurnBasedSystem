// Copyright (c) 2023, Me&Myself. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TurnBasedJRPGStats.h"
#include "Core/TurnBasedUnitBase.h"
#include "TurnBasedJRPGUnit.generated.h"

class UDataTable;
class AAIController;

struct FAIRequestID;
struct FPathFollowingResult;

UCLASS()
class TURNBASEDSYSTEM_API ATurnBasedJRPGUnit : public ATurnBasedUnitBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual float CalculateDamage() override;

protected:
	virtual void BeginBattle() override;
	virtual void AITurn() override;
	virtual void AttackCommand() override;
	virtual float TakeDamage_Internal(float DamageAmount) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_Attack();
	
private:
	void OnUnitReachTarget(FAIRequestID RequestID, const FPathFollowingResult& Result);
	UFUNCTION(BlueprintCallable)
	void OnUnitFinishedAttack();
	void OnUnitBackToBattlePosition(FAIRequestID RequestID, const FPathFollowingResult& Result);
	
	UPROPERTY()
	UDataTable* BaseStatsDataTable;

	UPROPERTY()
	FTurnBasedJRPGStats BaseStats;
	
	UPROPERTY()
	FTurnBasedJRPGStats StatsModifier;
	
	float MaxMana;
	float CurrentMana;
	
	const float MinActionTime = 1;
	const float MaxActionTime = 3;

	bool bIsRange;

	UPROPERTY()
	AAIController* AIController;
	FDelegateHandle AIMoveDelegate;
};
