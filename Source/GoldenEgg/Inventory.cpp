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

void UInventory::AddInventoryItem(APickUpItem * item)
{
	if (inventory.Find(item->Name))
	{
		inventory[item->Name] += item->Quantity;
	}
	else
	{
		inventory.Add(item->Name, item);
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

