// Copyright (c) 2023, Me&Myself. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TurnBasedUnitBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnEndedSignature);

UCLASS()
class TURNBASEDSYSTEM_API ATurnBasedUnitBase : public ACharacter
{
	GENERATED_BODY()

public:
	ATurnBasedUnitBase();
	
	virtual void BeginPlay() override;

	FText GetName() { return Name; }
	
	float GetCurrentHealth() const { return CurrentHealth; }
	float GetMaxHealth() const { return MaxHealth; }
	int GetLevelUnit() const { return LevelUnit; }
	
	ATurnBasedUnitBase* GetTarget() const { return Target; }
	void SetTarget(ATurnBasedUnitBase* Unit) { Target = Unit; }

	FTimerHandle GetActionTimerHandle() const { return ActionTimerHandle; }
	
	void StartUnitTurn();

	void RequestTurn();

	virtual float CalculateDamage();

	float ApplyDamage(ATurnBasedUnitBase* DamageCauser, float BaseDamage);

	UFUNCTION(BlueprintImplementableEvent)
	void OnTakeDamage(float Damage);
	
	UPROPERTY(BlueprintAssignable)
	FOnTurnEndedSignature OnTurnEndedDelegate;

protected:
	void EndUnitTurn();
	virtual void BeginBattle();
	virtual void AITurn();
	virtual void AttackCommand();
	virtual float TakeDamage_Internal(float DamageAmount);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_StartUnitTurn();

	FTimerHandle ActionTimerHandle;
	
	UPROPERTY(EditDefaultsOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly)
	bool bIsPlayable;
	
	float MaxHealth;
	float CurrentHealth;

	int LevelUnit;
	
	UPROPERTY()
	FTransform BattlePosition;

	UPROPERTY()
	ATurnBasedUnitBase* Target;
};
