// Copyright (c) 2023, Me&Myself. All Rights Reserved.

#include "Core/TurnBasedDamageNotify.h"

#include "Core/TurnBasedUnitBase.h"

bool UTurnBasedDamageNotify::Received_Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                             const FAnimNotifyEventReference& EventReference) const
{
	ATurnBasedUnitBase* Unit = Cast<ATurnBasedUnitBase>(MeshComp->GetOwner());
	ATurnBasedUnitBase* Target = Unit->GetTarget();
	Target->ApplyDamage(Unit, Unit->CalculateDamage());

	return true;
}
