// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterBase.h"


// Sets default values
AMonsterBase::AMonsterBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Speed = 20;
	HitPoints = 20;
	Experience = 0;
	BPLoot = NULL;
	BaseAttackDamage = 1;
	AttackTimeout = 1.5f;
	TimeSinceLastStrike = 0;

	SightSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SightSphere"));
	SightSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	AttackRangeSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("AttackRangeSphere"));
	AttackRangeSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
}

// Called when the game starts or when spawned
void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

