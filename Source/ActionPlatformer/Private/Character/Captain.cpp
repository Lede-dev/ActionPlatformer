// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Captain.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACaptain::ACaptain()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetWorldRotation(FRotator(-10, -90, 0));
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
}

void ACaptain::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	CameraBoom->SetAbsolute(false, true, false);
}

void ACaptain::BeginPlay()
{
	Super::BeginPlay();
}
