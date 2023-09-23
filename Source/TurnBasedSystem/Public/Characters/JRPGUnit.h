// Copyright (c) 2023, Me&Myself. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UnitBase.h"
#include "JRPGUnit.generated.h"

class AAIController;

struct FAIRequestID;
struct FPathFollowingResult;

UCLASS()
class TURNBASEDSYSTEM_API ATurnBasedJRPGUnit : public ATurnBasedUnitBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	FText GetName() { return Name; }
	
	float GetCurrentHealth() const { return CurrentHealth; }
	float GetMaxHealth() const { return MaxHealth; }
	
	float GetCurrentMana() const { return CurrentMana; }
	float GetMaxMana() const { return MaxMana; }

	float GetStrength() const { return Strength; }
	float GetAccuracy() const { return Accuracy; }
	float GetStamina() const { return Stamina; }
	float GetHaste() const { return Haste; }
	float GetWisdom() const { return Wisdom; }

protected:
	virtual void BeginBattle() override;
	
	virtual void AttackCommand() override;

	UFUNCTION(BlueprintImplementableEvent)
	void BP_Attack();
	
private:
	void OnUnitReachTarget(FAIRequestID RequestID, const FPathFollowingResult& Result);
	UFUNCTION(BlueprintCallable)
	void OnUnitFinishedAttack();
	void OnUnitBackToBattlePosition(FAIRequestID RequestID, const FPathFollowingResult& Result);
	
	UPROPERTY(EditDefaultsOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;
	float CurrentHealth;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxMana;
	float CurrentMana;

	UPROPERTY(EditDefaultsOnly)
	float Strength;
	UPROPERTY(EditDefaultsOnly)
	float Accuracy;
	UPROPERTY(EditDefaultsOnly)
	float Stamina;
	UPROPERTY(EditDefaultsOnly)
	float Haste;
	UPROPERTY(EditDefaultsOnly)
	float Wisdom;

	FTimerHandle ActionTimerHandle;

	const float MinActionTime = 1;
	const float MaxActionTime = 3;

	bool bIsRange;

	UPROPERTY()
	AAIController* AIController;
	FDelegateHandle AIMoveDelegate;
};
