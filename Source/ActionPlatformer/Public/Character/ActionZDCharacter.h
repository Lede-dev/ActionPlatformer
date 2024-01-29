// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "ActionZDCharacter.generated.h"

class UPaperZDAnimSequence;
class UBoxComponent;
/**
 * 
 */
UCLASS()
class ACTIONPLATFORMER_API AActionZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* HitBox;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	UPaperZDAnimSequence* AttackAnimationSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	UPaperZDAnimSequence* ThrowAnimationSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	UPaperZDAnimSequence* StunAnimationSequence;
	
protected:
	UPROPERTY(VisibleAnywhere, Category="HitBox")
	bool bIsHitBoxActive;

	UPROPERTY(VisibleAnywhere, Category="Attack")
	bool bIsAttacking;

	UPROPERTY(VisibleAnywhere, Category="Attack")
	bool bIsStunned;

public:
	AActionZDCharacter();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	// Hit Box
public:
	UFUNCTION(BlueprintCallable, Category="ActionCharacter")
	void SetHitBoxActive(const bool IsHitBoxActive);

	UFUNCTION(BlueprintCallable, Category="ActionCharacter")
	bool IsHitBoxActive() const { return bIsHitBoxActive; }
	
	// Attack and Damage
public:
	UFUNCTION(BlueprintCallable, Category="ActionCharacter")
	bool CanInput() const { return !bIsAttacking && !bIsStunned; }
	
	UFUNCTION(BlueprintCallable, Category="ActionCharacter")
	bool IsAttacking() const { return bIsAttacking; }

	UFUNCTION(BlueprintCallable, Category="ActionCharacter")
	bool IsStunned() const { return bIsStunned; }
	
	void AttackBasic();
	void AttackSpecial();
	void Damage();

private:
	UFUNCTION()
	virtual void OnHitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {}
	
};
