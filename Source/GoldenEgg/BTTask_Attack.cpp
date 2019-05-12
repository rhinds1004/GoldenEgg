// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Attack.h"
#include "MonsterAIController.h"

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetOwner());
	if (Controller == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	//TODO need a attack function in the monsterAI
	//Controller->StartFollowingPlayer();

	return EBTNodeResult::Succeeded;
}
