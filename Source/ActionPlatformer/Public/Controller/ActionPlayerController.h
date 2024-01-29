// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ActionPlayerController.generated.h"


class AActionZDCharacter;

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

UCLASS()
class ACTIONPLATFORMER_API AActionPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* ThrowAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	FVector ForwardDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	FVector RightDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float ForwardMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float RightMoveSpeed;
	
protected:
	TWeakObjectPtr<AActionZDCharacter> Player;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& Value);
	void Jump();
	void Attack();
	void Throw();
	
};
