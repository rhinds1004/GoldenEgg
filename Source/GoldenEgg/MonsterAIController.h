// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class GOLDENEGG_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMonsterAIController(const FObjectInitializer& ObjectInitializer);
	virtual void Possess(class APawn* InPawn) override;
	virtual void UnPossess() override;

	UBehaviorTreeComponent* BehaviorTreeCmp;
	UBlackboardComponent* BlackboardCmp;
	class AMonsterBase* Possessed;
	//start following the player
	void StartFollowingPlayer();
	void SetFollowRange(bool val);
	void SetAttackRange(bool val);
	void GetDead();
/*	void SetTimeSinceLastStrike(float val);
	void SetAttackTimeout(float val);
	float GetTimeSinceLastStrike();
	float GetAttackTimeout();
	*/
	
	
	


};
