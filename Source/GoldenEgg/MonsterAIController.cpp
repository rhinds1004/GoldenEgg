// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"



void AMonsterAIController::StartFollowingPlayer()
{
	AActor* player = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	FVector playerPos = player->GetActorLocation();
	MoveToLocation(playerPos);
}

