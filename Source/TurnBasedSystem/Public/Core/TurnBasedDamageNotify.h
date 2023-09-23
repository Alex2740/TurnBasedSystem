// Copyright (c) 2023, Me&Myself. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "TurnBasedDamageNotify.generated.h"

UCLASS()
class TURNBASEDSYSTEM_API UTurnBasedDamageNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	bool Received_Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) const;
};
