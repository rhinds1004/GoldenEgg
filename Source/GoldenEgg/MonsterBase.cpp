// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SkeletalMeshComponent.h"
//#include "GameFramework/Character.h"



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
	SightSphere->SetupAttachment(RootComponent);

	AttackRangeSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("AttackRangeSphere"));
	AttackRangeSphere->SetupAttachment(RootComponent);
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
	AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!avatar) return;
	//since it is avatar loc - get this actor loc. we are creating a vector from this actor to the avatar.
	FVector toPlayer = avatar->GetActorLocation() - GetActorLocation();
	float distanceToPlayer = toPlayer.Size();
	if (distanceToPlayer > SightSphere->GetScaledSphereRadius())
	{
		//If the player is out of sight, then enemy cannot chase
		return;
	}
	toPlayer /= distanceToPlayer; // normalizes the vector
	//Actually move the monster towards the player a bit
	AddMovementInput(toPlayer, Speed*DeltaTime);

	//since we don't care about magnitude we can normalize vector
	toPlayer.Normalize();
	//move this actor towards the player avatar
	AddMovementInput(toPlayer, Speed*DeltaTime);
	//Get the rotator that looks in the 'toPlayer' direction
	FRotator toPlayerRotation = toPlayer.ToOrientationRotator();
	toPlayerRotation.Pitch = 0; //o off the pitch
	RootComponent->SetWorldRotation(toPlayerRotation);


}

// Called to bind functionality to input
void AMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonsterBase::PostInitializeComponents()
{
Super::PostInitializeComponents();
	//Instantiate the melee weapon if a bp was selected
	if(BP_MeleeWeapon)
	{
		MeleeWeapon = GetWorld()->SpawnActor<AMeleeWeapon>(BP_MeleeWeapon, FVector(), FRotator());
		
		if (MeleeWeapon)
		{
		
			const USkeletalMeshSocket* socket = GetMesh()->GetSocketByName(FName("RightHandSocket"));
			socket->AttachActor(MeleeWeapon, GetMesh());
			MeleeWeapon->WeaponHolder = this;
		}
	}
}

