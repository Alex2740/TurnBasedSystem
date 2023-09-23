// Copyright (c) 2023, Me&Myself. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnitBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnEndedSignature);

UCLASS()
class TURNBASEDSYSTEM_API ATurnBasedUnitBase : public ACharacter
{
	GENERATED_BODY()

public:
	ATurnBasedUnitBase();
	
	virtual void BeginPlay() override;

	ATurnBasedUnitBase* GetTarget() const { return Target; }
	void SetTarget(ATurnBasedUnitBase* Unit) { Target = Unit; }
	
	void StartUnitTurn();

	void RequestTurn();
	
	UPROPERTY(BlueprintAssignable)
	FOnTurnEndedSignature OnTurnEndedDelegate;

protected:
	void EndUnitTurn();
	virtual void BeginBattle();
	virtual void AttackCommand();

	UPROPERTY()
	FTransform BattlePosition;

	UPROPERTY()
	ATurnBasedUnitBase* Target;
};
