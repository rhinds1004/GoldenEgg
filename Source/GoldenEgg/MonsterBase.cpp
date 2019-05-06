// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SkeletalMeshComponent.h"
#include "Projectile.h"
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

	//Get the rotator that looks in the 'toPlayer' direction
	FRotator toPlayerRotation = toPlayer.ToOrientationRotator();
	toPlayerRotation.Pitch = 0; //o off the pitch
	RootComponent->SetWorldRotation(toPlayerRotation);

	if (isInAttackRange(distanceToPlayer))
	{
		//Perform the attack
		if (!TimeSinceLastStrike)
		{
			Attack(avatar);
		}

		TimeSinceLastStrike += DeltaTime;
		if (TimeSinceLastStrike > AttackTimeout)
		{
			TimeSinceLastStrike = 0;
		}
		return;
	}
	else
	{
		//Actually move the monster towards the player a bit
		AddMovementInput(toPlayer, Speed*DeltaTime);
	}
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

//Checks if weapon is currently being swung
void AMonsterBase::SwordSwung()
{
	if (MeleeWeapon)
	{
		MeleeWeapon->Swing();
	}
}

void AMonsterBase::Attack(AActor * thing)
{
	if (MeleeWeapon)
	{
		MeleeWeapon->Swing();
	}
	else if (BP_Projectile)
	{
		FVector fwd = GetActorForwardVector();
		Nozzle = GetMesh()->GetBoneLocation("RightHand");
		Nozzle += fwd * MoveProjectileFwdAmount; // move it fwd of the monster so doesn't hit the mosnter model
		FVector toOpponent = thing->GetActorLocation() - Nozzle;
		toOpponent.Normalize();
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(BP_Projectile, Nozzle, RootComponent->GetComponentRotation());

		if (projectile)
		{
			projectile->Firer = this;
			projectile->ProxSphere->AddImpulse(toOpponent*ProjectileLaunchImpulse);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("monster: no projectile actor could be spawned. Is the bullet overlapping something"))
		}
	}
}

