// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Captain.h"

#include "Camera/CameraComponent.h"
#include "Character/Shark.h"
#include "GameFramework/SpringArmComponent.h"

ACaptain::ACaptain()
{
	Faction = EFaction::Player;
	
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

void ACaptain::OnHitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Skip Check if Other Actor is Current Actor
	if (OtherActor == this) { return; }
	
	// Check if Other Actor Faction is Enemy
	if (AActionZDCharacter* Enemy = Cast<AActionZDCharacter>(OtherActor))
	{
		if (Enemy->GetFaction() == EFaction::Enemy)
		{
			Enemy->Damage();
			// PlayHitStop();
		}
	}
}
