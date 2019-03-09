// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpItem.h"
#include "Kismet/GameplayStatics.h"
#include "MyHUD.h"
#include "Avatar.h"
#include "Engine/World.h"


// Sets default values
APickUpItem::APickUpItem(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Name = "Unknown Item";
	Quantity = 0;
	ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &APickUpItem::Prox); //overlap delgate to proxshpere
	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);

	
																			  
	/**Important! This line tells you to make sure the pickup item's ProxSphere component is attached to the Mesh root component.
	This means that when the mesh moves in the level, ProxSphere follows.**/

	ProxSphere->AttachToComponent(Mesh, FAttachmentTransformRules::KeepWorldTransform);


}



// Called when the game starts or when spawned
void APickUpItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int APickUpItem::Prox_Implementation(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return -1;
	}
	//gets the first player controller
	//AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	AAvatar* avatar = Cast<AAvatar>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	//Let player pickup this item
	avatar->PickUp(this);
	//get the hud for the first player controller
	AMyHUD* hud = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	//hud->addMessage(Message(FString("Picked up: ") + FString::FromInt(Quantity) + FString(" ") + Name, 5.f, FColor::White, Icon));
	
	Destroy();

	return 0;
}

