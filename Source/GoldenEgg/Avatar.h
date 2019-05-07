// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Inventory.h"
//#include "PickUpItem.h"
#include "Avatar.generated.h"

class APickUpItem; // Forward declare the APickUpItem class since will be "mentioned" in a member function decl below

UCLASS()
class GOLDENEGG_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAvatar(const FObjectInitializer& ObjectInitializer);

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
		UInventory* myInventory;


									 //Icons for the items in the backpack
//	UPROPERTY()
//		TMap<FString, UTexture2D*> Icons;



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
	UFUNCTION()
		void MouseClicked();

	//Avatar status
	UFUNCTION()
		float GetCurrentHp();
	UFUNCTION()
		float GetMaxHp();


	//Avatar actions
//	UFUNCTION()
		void PickUp(APickUpItem* Item);
//	UFUNCTION()
		void ToggleInventory();

	

private:
	FVector knockback; // in class AAVatar

	UPROPERTY(VisibleAnywhere, Category = "Avatar stats")
		float maxHP;
	UPROPERTY(VisibleAnywhere,  Category = "Avatar stats")
		float currentHP;

	UPROPERTY()
		TArray<APickUpItem*> inventoryList;
	
	UFUNCTION()
		virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
};
