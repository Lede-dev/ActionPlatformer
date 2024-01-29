// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Notifies/PaperZDAnimNotifyState.h"
#include "AttackAnimNotifyState.generated.h"

class AActionZDCharacter;
/**
 * 
 */
UCLASS()
class ACTIONPLATFORMER_API UAttackAnimNotifyState : public UPaperZDAnimNotifyState
{
	GENERATED_BODY()

protected:
	TWeakObjectPtr<AActionZDCharacter> PaperCharacter;

protected:
	virtual void OnNotifyBegin_Implementation(UPaperZDAnimInstance* OwningInstance) override;
	virtual void OnNotifyEnd_Implementation(UPaperZDAnimInstance* OwningInstance) override;

	virtual FName GetDisplayName_Implementation() const override;
	
};
