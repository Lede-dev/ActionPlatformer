// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ActionZDCharacter.h"
#include "Captain.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ACTIONPLATFORMER_API ACaptain : public AActionZDCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

public:
	ACaptain();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void OnHitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
};
