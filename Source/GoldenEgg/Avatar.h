// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Avatar.generated.h"

class APickUpItem; // Forward declare the APickUpItem class since will be "mentioned" in a member function decl below

UCLASS()
class GOLDENEGG_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAvatar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

/* Properties */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mouse)
		float mouseSensitivity;

	UPROPERTY()
		TMap<FString, int> Backpack; //players inventory

									 //Icons for the items in the backpack
	UPROPERTY()
		TMap<FString, UTexture2D*> Icons;

	//Invetory being displayed currently?
	bool inventoryShowing;

	/* FUNCTIONS */

	//Avatar Movement
	UFUNCTION()
	void MoveForward(float amt);
	UFUNCTION()
	void StrafeLeft(float amt);
	UFUNCTION()
	void MoveBackward(float amt);
	UFUNCTION()
	void StrafeRight(float amt);
	UFUNCTION()
		void LookX(float amt);
	UFUNCTION()
		void LookY(float amt);

	//Avatar status
	UFUNCTION()
		float GetCurrentHp();
	UFUNCTION()
		float GetMaxHp();


	//Avatar actions
	UFUNCTION()
		void PickUp(APickUpItem* Item);
	UFUNCTION()
		void ToggleInventory();

	

private:
	UPROPERTY(VisibleAnywhere, Category = "NPC stats")
		float maxHP;
	UPROPERTY(VisibleAnywhere,  Category = "NPC stats")
		float currentHP;
};
