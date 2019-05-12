// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "MonsterBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AMonsterAIController::AMonsterAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BehaviorTreeCmp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("MonsterBT"));
	BlackboardCmp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("MonsterBlackboard"));
}



void AMonsterAIController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);
	AMonsterBase* Monster = Cast<AMonsterBase>(InPawn);
	if (Monster)
	{
		if (Monster->BehaviorTree->BlackboardAsset)
		{
			BlackboardCmp->InitializeBlackboard(*Monster->BehaviorTree->BlackboardAsset);
		}
	}
}

void AMonsterAIController::UnPossess()
{
	Super::UnPossess();

	BehaviorTreeCmp->StopTree();
}


void AMonsterAIController::StartFollowingPlayer()
{
	AActor* player = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	FVector playerPos = player->GetActorLocation();
	MoveToLocation(playerPos);
}

void AMonsterAIController::SetFollowRange(bool val)
{
	BlackboardCmp->SetValueAsBool("IsInFollowRange", val);  //Needs to be the same as the key found in the blueprint of the blackboard
}

void AMonsterAIController::SetAttackRange(bool val)
{
	BlackboardCmp->SetValueAsBool("IsInAttackRange", val);  //Needs to be the same as the key found in the blueprint of the blackboard
}



