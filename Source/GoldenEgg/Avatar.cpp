// Fill out your copyright notice in the Description page of Project Settings.

#include "Avatar.h"
#include "Engine/Engine.h"


// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mouseSensitivity = 200.0f;
	maxHP = 100.0f;
	currentHP = 100.0f;
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
	PlayerInputComponent->BindAxis("LookX", this, &AAvatar::LookX);
	PlayerInputComponent->BindAxis("LookY", this, &AAvatar::LookY);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AAvatar::ToggleInventory);

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

//Player view looks along X axis
void AAvatar::LookX(float amt)
{
	AddControllerYawInput(mouseSensitivity * amt * GetWorld()->GetDeltaSeconds());
}

//Player view looks along Y axis
void AAvatar::LookY(float amt)
{
	AddControllerPitchInput(mouseSensitivity * amt * GetWorld()->GetDeltaSeconds());
}

float AAvatar::GetCurrentHp()
{
	
	return currentHP;
}

float AAvatar::GetMaxHp()
{
	return maxHP;
}

void AAvatar::PickUp(APickUpItem * Item)
{
}

void AAvatar::ToggleInventory()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Showing Inventory...");
	}
}

