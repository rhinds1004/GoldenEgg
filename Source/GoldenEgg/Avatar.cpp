// Fill out your copyright notice in the Description page of Project Settings.

#include "Avatar.h"


// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
	PlayerInputComponent->BindAxis("StrafeLeft", this, &AAvatar::StrafeLeft);
	PlayerInputComponent->BindAxis("Backward", this, &AAvatar::MoveBackward);
	PlayerInputComponent->BindAxis("StrafeRight", this, &AAvatar::StrafeRight);

}

void AAvatar::MoveForward(float amt)
{
	if (Controller && amt)
	{
		AddMovementInput(GetActorForwardVector(), amt);
	}
}

void AAvatar::StrafeLeft(float amt)
{
	if (Controller && amt)
	{
		AddMovementInput(-(GetActorRightVector()), amt);
		
	}
}

void AAvatar::MoveBackward(float amt)
{
	if (Controller && amt) 
	{
		AddMovementInput(-(GetActorForwardVector()), amt);
	}
}

void AAvatar::StrafeRight(float amt)
{
	if (Controller && amt)
	{
		AddMovementInput(GetActorRightVector(), amt);
	}
}

