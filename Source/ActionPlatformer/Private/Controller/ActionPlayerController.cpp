// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/ActionPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Character/ActionZDCharacter.h"


void AActionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	Player = MakeWeakObjectPtr(Cast<AActionZDCharacter>(GetCharacter()));
}

void AActionPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AActionPlayerController::Move);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &AActionPlayerController::Jump);
		EnhancedInput->BindAction(AttackAction, ETriggerEvent::Started, this, &AActionPlayerController::Attack);
		EnhancedInput->BindAction(ThrowAction, ETriggerEvent::Started, this, &AActionPlayerController::Throw);
	}
}

void AActionPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D Movement = Value.Get<FVector2D>();
	if (Player.IsValid() && Player->CanMove())
	{
		Player->AddMovementInput(ForwardDirection * Movement.Y * ForwardMoveSpeed);
		Player->AddMovementInput(RightDirection * Movement.X * RightMoveSpeed);

		if (Movement.X > 0)
		{
			SetControlRotation(FRotator::ZeroRotator);
		}
		else if (Movement.X < 0)
		{
			SetControlRotation(FRotator(0, 180, 0));
		}
	}
}

void AActionPlayerController::Jump()
{
	if (Player.IsValid() && Player->CanMove())
	{
		Player->Jump();
	}
}

void AActionPlayerController::Attack()
{
	if (Player.IsValid() && Player->CanMove())
	{
		Player->AttackBasic();
	}
}

void AActionPlayerController::Throw()
{
	if (Player.IsValid() && Player->CanMove())
	{
		Player->AttackSpecial();
	}
}
