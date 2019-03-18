// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

class APickUpItem; // Forward declare the APickUpItem class since will be "mentioned" in a member function decl below

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GOLDENEGG_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void AddInventoryItem(APickUpItem* item);
	//void GetInventoryItem(FString name);
	int32 itemQuantity(FString itemName);
	int32 numberOfSlotsUsed();
	void DisplayInventory();
	//Invetory being displayed currently?
	bool inventoryShowing;

	TMap<FString, APickUpItem*>::TIterator CreateIterator();

	UFUNCTION()
	TArray<APickUpItem*> InventoryList();

private:
	UPROPERTY(VisibleAnywhere, Category = Inventory)
		TMap<FString, APickUpItem*> inventory; //players inventory	
											 
};
