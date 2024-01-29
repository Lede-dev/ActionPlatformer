// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyState/AttackAnimNotifyState.h"

#include "Character/ActionZDCharacter.h"

void UAttackAnimNotifyState::OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance)
{
	Super::OnNotifyBegin_Implementation(OwningInstance);

	if (!PaperCharacter.IsValid())
	{
		if (OwningInstance)
		{
			if (APaperZDCharacter* Character = OwningInstance->GetPaperCharacter())
			{
				PaperCharacter = MakeWeakObjectPtr(Cast<AActionZDCharacter>(Character));
			}
		}
	}

	if (PaperCharacter.IsValid())
	{
		PaperCharacter->SetHitBoxActive(true);
	}
}

void UAttackAnimNotifyState::OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance)
{
	Super::OnNotifyEnd_Implementation(OwningInstance);
	
	if (PaperCharacter.IsValid())
	{
		PaperCharacter->SetHitBoxActive(false);
	}
}

FName UAttackAnimNotifyState::GetDisplayName_Implementation() const
{
	return FName("HitBox");
}
