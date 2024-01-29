// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ActionZDCharacter.h"

#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Controller/ActionPlayerController.h"
#include "Kismet/GameplayStatics.h"

AActionZDCharacter::AActionZDCharacter()
{
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);
	
	GetSprite()->CastShadow = true;
}

void AActionZDCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	CurrentHealth = MaxHealth;
	
	HitBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AActionZDCharacter::OnHitBoxBeginOverlap);
}

void AActionZDCharacter::SetHitBoxActive(const bool IsHitBoxActive)
{
	bIsHitBoxActive = IsHitBoxActive;
	HitBox->SetCollisionEnabled(bIsHitBoxActive ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}

void AActionZDCharacter::AttackBasic()
{
	if (AttackAnimationSequence)
	{
		bIsAttacking = true;
		
		FZDOnAnimationOverrideEndSignature OnDone = FZDOnAnimationOverrideEndSignature();
		OnDone.BindLambda([this](bool IsCompleted){ bIsAttacking = false; });
		GetAnimInstance()->PlayAnimationOverride(AttackAnimationSequence, "Attack", 1.0, 0.0, OnDone);
	}
}

void AActionZDCharacter::AttackSpecial()
{
	if (ThrowAnimationSequence)
	{
		bIsAttacking = true;
		
		FZDOnAnimationOverrideEndSignature OnDone = FZDOnAnimationOverrideEndSignature();
		OnDone.BindLambda([this](bool IsCompleted){ bIsAttacking = false; });
		GetAnimInstance()->PlayAnimationOverride(ThrowAnimationSequence, "Attack", 1.0, 0.0, OnDone);
	}
}

void AActionZDCharacter::Damage()
{
	CurrentHealth = FMath::Max(0, CurrentHealth - 1);

	// Play Hit Sound
	if (DamageSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DamageSound, GetActorLocation());
	}
	
	if (CurrentHealth == 0) // Death
	{
		bIsDeath = true;

		// Disable Collision
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// Play Animation
		GetAnimInstance()->JumpToNode(DeathAnimationName);

		// Call OnDeath
		OnDeath();
	}
	else // Hit
	{
		// Play Hit Animation
		if (StunAnimationSequence)
		{
			bIsStunned = true;
			FZDOnAnimationOverrideEndSignature OnDone = FZDOnAnimationOverrideEndSignature();
			OnDone.BindLambda([this](bool IsCompleted){ bIsStunned = false; });
			GetAnimInstance()->PlayAnimationOverride(StunAnimationSequence, "Attack", 1.0, 0.0, OnDone);
		}

		// Play HitStop
		PlayHitStop();
	}
}

void AActionZDCharacter::PlayHitStop()
{
	FTimerManager& Timer = GetWorld()->GetTimerManager();
	if (Timer.IsTimerActive(HitStopTimer))
	{
		Timer.ClearTimer(HitStopTimer);
	}

	bIsInHitStop = true;
	CustomTimeDilation = 0.0f;
	Timer.SetTimer(HitStopTimer, [this]
	{
		bIsInHitStop = false;
		CustomTimeDilation = 1.0f;
	}, HitStopDelaySeconds, false);
}
