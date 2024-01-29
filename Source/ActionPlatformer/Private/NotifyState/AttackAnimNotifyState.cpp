// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyState/AttackAnimNotifyState.h"

#include "Character/ActionZDCharacter.h"

void UAttackAnimNotifyState::OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance)
{
	Super::OnNotifyBegin_Implementation(OwningInstance);

	if (!PaperCharacter.IsValid())
	{
		PaperCharacter = MakeWeakObjectPtr(Cast<AActionZDCharacter>(OwningInstance->GetPaperCharacter()));
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
