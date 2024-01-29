// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class AActionZDCharacter;

UCLASS()
class ACTIONPLATFORMER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EnemyAI")
	UBehaviorTree* EnemyBehaviorTree;

protected:
	TWeakObjectPtr<AActionZDCharacter> Character;
	TWeakObjectPtr<AActionZDCharacter> AttackTarget;

public:
	AEnemyAIController();
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	void SetAttackTarget(AActionZDCharacter* NewAttackTarget);
	AActionZDCharacter* GetAttackTarget() const { return AttackTarget.Get(); }

private:
	void UpdateFocusDirection();
	
private:
	void OnStunStateChanged(const bool IsStunned);
	
};
