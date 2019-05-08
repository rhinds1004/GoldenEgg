// Fill out your copyright notice in the Description page of Project Settings.

#include "Avatar.h"
#include "Engine/Engine.h"
//#include "Inventory.h"
#include "MyHUD.h"
#include "MyDamageType.h"
#include "PickUpItem.h"


// Sets default values
AAvatar::AAvatar(const FObjectInitializer& ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mouseSensitivity = 200.0f;
	maxHP = 100.0f;
	currentHP = 100.0f;

	//ObjectInitializer.CreateDefaultSubobject<UInventory>(this, TEXT("Storage"));
	myInventory = CreateDefaultSubobject<UInventory>( TEXT("Storage"));
	
	//AddOwnedComponent(CreateDefaultSubobject<UInventory>(this, TEXT("Storage")));
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
	//apply knockback vector
	AddMovementInput(1 * knockback, 1.f);

	//half the size of the knockback each frame 
	knockback *= 0.5f;
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
	PlayerInputComponent->BindAction("MouseClickedLMB", IE_Pressed, this, &AAvatar::MouseClicked);

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
	
	if (myInventory->inventoryShowing)
	{
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		hud->MouseMoved();
		return;
	}
	else
	{
		AddControllerYawInput(mouseSensitivity * amt * GetWorld()->GetDeltaSeconds());
	}
}

//Player view looks along Y axis
void AAvatar::LookY(float amt)
{
	if (myInventory->inventoryShowing)
	{
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		hud->MouseMoved();
		return;
	}
	else
	{
		AddControllerPitchInput(mouseSensitivity * amt * GetWorld()->GetDeltaSeconds());
	}
}

void AAvatar::MouseClicked()
{
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	hud->MouseClicked();
}

float AAvatar::GetCurrentHp()
{
	
	return currentHP;
}

float AAvatar::GetMaxHp()
{
	return maxHP;
}

/*Add the item to the players inventory. If item is picked up while the players inventory screen is open,
* a call to the player's hud is made and the newly picked up item will be displayed within the inventory
* screen.
*/
void AAvatar::PickUp(APickUpItem* item)
{
	
	myInventory->AddInventoryItem(item);

	if (myInventory->inventoryShowing)
	{
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		// Combine string name of the item, with qty eg Cow x 5 
		FString fs = item->Name + FString::Printf(TEXT(" x %d"), item->Quantity);
		UTexture2D* tex;
		if (item->Icon)
		{
			tex = item->Icon;
			hud->addWidget(Widget(Icon(fs, tex)));
		}
	}
}

/*Toggles if the player's inventory is to be displayed or not. */

void AAvatar::ToggleInventory()
{
	if (GEngine)
	{
		
		// Get the controller & hud 
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());

		// If inventory is displayed, undisplay it. 
		if (myInventory->inventoryShowing)
		{
			hud->clearWidgets();
			myInventory->inventoryShowing = false;
			PController->bShowMouseCursor = false;
			return;
		}

		// Otherwise, display the player's inventory 
		myInventory->inventoryShowing = true;
		PController->bShowMouseCursor = true;
		for (auto it =
			myInventory->CreateIterator(); it; ++it)
		{
			// Combine string name of the item, with qty eg Cow x 5 
			FString fs = it->Key + FString::Printf(TEXT(" x %d"), it->Value->Quantity);
			UTexture2D* tex;
			if (it->Value->Icon)
			{
				tex = it->Value->Icon;
				hud->addWidget(Widget(Icon(fs, tex)));
			}
		}
	}

}

//determine damage done and then subtract that amount from current hp
float AAvatar::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	// Call the base class - this will tell us how much damage to apply  
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	//add some knockback that gets applied over a few frames
	//TODO make some kind of damagetype
//	UE_LOG(LogTemp, Warning, TEXT("DamageEvent ID: %d"), DamageEvent.GetTypeID());
//	UE_LOG(LogTemp, Warning, TEXT("ClassEvent ID: %d"), DamageEvent.ClassID());
	DamageEvent.DamageTypeClass.GetDefaultObject();
	//TODO works because the class is derived from base Udamamgetype ?? is this the way to do it though??
	if (Cast<UMyDamageType>(DamageEvent.DamageTypeClass.GetDefaultObject()))
	{
		knockback = GetActorLocation() - DamageCauser->GetActorLocation();
		knockback.Normalize();
		knockback *= Damage * 500;
	}
	if (ActualDamage > 0.f)
	{
		currentHP -= ActualDamage;
	}
	return AActor::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}


/*
void AAvatar::ToggleInventory()
{
	if (GEngine)
	{

		// Get the controller & hud 
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());

		// If inventory is displayed, undisplay it. 
		if (myInventory->inventoryShowing)
		{
			hud->clearWidgets();
			myInventory->inventoryShowing = false;
			PController->bShowMouseCursor = false;
			return;
		}

		// Otherwise, display the player's inventory 
		inventoryList = myInventory->InventoryList();
		myInventory->inventoryShowing = true;
		PController->bShowMouseCursor = true;
		for (auto& inventoryItem : inventoryList)
		{
			// Combine string name of the item, with qty eg Cow x 5 
			FString fs = inventoryItem->Name + FString::Printf(TEXT(" x %d"), inventoryItem->Quantity);
			UTexture2D* tex;
			if (inventoryItem)
			{
				tex = inventoryItem->Icon;
				hud->addWidget(Widget(Icon(fs, tex)));
			}
		}

	}
}
*/