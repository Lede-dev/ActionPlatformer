// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "ActionZDCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStunStateChanged, bool IsStunned)

class UPaperZDAnimSequence;
class UBoxComponent;

UENUM()
enum class EFaction
{
	Player UMETA(DisplayName="Player"),
	Enemy UMETA(DisplayName="Enemy"),
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	FName DeathAnimationName;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sound")
	USoundBase* DamageSound;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Faction")
	EFaction Faction;

protected:
	UPROPERTY(VisibleAnywhere, Category="HitBox")
	bool bIsHitBoxActive;

	UPROPERTY(VisibleAnywhere, Category="Attack")
	bool bIsAttacking;

	UPROPERTY(VisibleAnywhere, Category="Attack")
	bool bIsStunned;

	UPROPERTY(VisibleAnywhere, Category="Attack")
	bool bIsDeath;

	UPROPERTY(VisibleAnywhere, Category="Attack")
	bool bIsInHitStop;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	int32 MaxHealth;

	UPROPERTY(VisibleAnywhere, Category="Health")
	int32 CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	float HitStopDelaySeconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	FVector ShakeOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	float ShakeRepeatPeriodSeconds;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack")
	float ShakeStopDelaySeconds;
	
private:
	FTimerHandle DeathTimer;
	FTimerHandle HitStopTimer;
	FTimerHandle ShakeTimer;
	FTimerHandle ShakeStopTimer;

	bool FlipShake;
	FVector ShakeStartLocation;

	//Delegates
public:
	FOnStunStateChanged OnStunStateChanged;
	
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
	bool CanMove() const { return !bIsAttacking && !bIsStunned; }
	
	UFUNCTION(BlueprintCallable, Category="ActionCharacter")
	bool IsAttacking() const { return bIsAttacking; }

	UFUNCTION(BlueprintCallable, Category="ActionCharacter")
	bool IsStunned() const { return bIsStunned; }

	UFUNCTION(BlueprintCallable, Category="ActionCharacter")
	bool IsDead() const { return bIsDeath; }

	UFUNCTION(BlueprintCallable, Category="ActionCharacter")
	bool IsInHitStop() const { return bIsInHitStop; }
	
	void AttackBasic();
	void AttackSpecial();
	void Damage();

	UFUNCTION(BlueprintCallable, Category="ActionCharacter")
	void PlayHitStop();

	UFUNCTION(BlueprintCallable, Category="ActionCharacter")
	void ShakeSprite();
	
	virtual void OnDeath() {}
	
	// Factions
public:
	EFaction GetFaction() const { return Faction; }
	
private:
	UFUNCTION()
	virtual void OnHitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {}
	
};
