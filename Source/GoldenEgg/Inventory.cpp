// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory.h"
#include "PickUpItem.h"


// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	inventoryShowing = false;

	// ...
}


// Called when the game starts
/*
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
} */


// Called every frame
/*
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
} */

void UInventory::AddInventoryItem(APickUpItem* item)
{
	if (inventory.Find(item->Name))
	{
		inventory[item->Name]->Quantity += item->Quantity;
	}
	else
	{
		APickUpItem* newItem = NewObject<APickUpItem>(item);
		newItem->Name = item->Name;
		newItem->Quantity = item->Quantity;
		newItem->Mesh = item->Mesh;
		newItem->ProxSphere = item->ProxSphere;
		newItem->Icon = item->Icon;
		inventory.Emplace(item->Name, newItem);
	}
}

int32 UInventory::itemQuantity(FString itemName)
{
	if (inventory.Find(itemName))
	{
		return	inventory[itemName]->Quantity;
	}
	return -1;
}

/*Gives count of items in the inventory. Does not give the total amount of items in the inventory.*/
int32 UInventory::numberOfSlotsUsed()
{
	return inventory.Num();
}

void UInventory::DisplayInventory()
{
	
}

TMap<FString, APickUpItem*>::TIterator UInventory::CreateIterator()
{
	return inventory.CreateIterator();
}

TArray<APickUpItem*> UInventory::InventoryList()
{
	
	TArray<APickUpItem*> tempList;
	for (auto it =
		inventory.CreateIterator(); it; ++it)
	{
		tempList.Add(it->Value);
	}
	return tempList;
}

