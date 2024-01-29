// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ActionZDCharacter.h"

#include "PaperFlipbookComponent.h"
#include "Character/Shark.h"
#include "Components/BoxComponent.h"
#include "Controller/ActionPlayerController.h"

AActionZDCharacter::AActionZDCharacter()
{
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);
	
	GetSprite()->CastShadow = true;
}

void AActionZDCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

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
	if (StunAnimationSequence)
	{
		bIsStunned = true;
		FZDOnAnimationOverrideEndSignature OnDone = FZDOnAnimationOverrideEndSignature();
		OnDone.BindLambda([this](bool IsCompleted){ bIsStunned = false; });
		GetAnimInstance()->PlayAnimationOverride(StunAnimationSequence, "Attack", 1.0, 0.0, OnDone);
	}
}
