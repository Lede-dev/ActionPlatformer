// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/ActionZDCharacter.h"
#include "Kismet/KismetMathLibrary.h"

AEnemyAIController::AEnemyAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (EnemyBehaviorTree)
	{
		RunBehaviorTree(EnemyBehaviorTree);
	}

	Character = MakeWeakObjectPtr(Cast<AActionZDCharacter>(InPawn));
	if (Character.IsValid())
	{
		Character->OnStunStateChanged.AddUObject(this, &AEnemyAIController::OnStunStateChanged);
	}
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AActionZDCharacter* Player = Cast<AActionZDCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter()))
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyAIController( %s ) found target player character."), *GetName())
		SetAttackTarget(Player);
	}
}

void AEnemyAIController::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateFocusDirection();
}

void AEnemyAIController::SetAttackTarget(AActionZDCharacter* NewAttackTarget)
{
	AttackTarget = NewAttackTarget;
	
	if (GetBlackboardComponent())
	{
		GetBlackboardComponent()->SetValueAsObject(FName("AttackTarget"), NewAttackTarget);
	}
}

void AEnemyAIController::UpdateFocusDirection()
{
	if (AttackTarget.IsValid() && Character.IsValid())
	{
		if (Character->IsDead())
		{
			SetFocalPoint(Character->GetActorLocation() + Character->GetActorForwardVector());
		}
		else
		{
			const FVector MoveDirection = AttackTarget->GetActorLocation() - Character->GetActorLocation();
			SetFocalPoint(Character->GetActorLocation() + FVector(MoveDirection.X, 0, 0));
		}
	}
}

void AEnemyAIController::OnStunStateChanged(const bool IsStunned)
{
	if (GetBlackboardComponent())
	{
		GetBlackboardComponent()->SetValueAsBool(FName("IsStunned"), IsStunned);
	}
}
