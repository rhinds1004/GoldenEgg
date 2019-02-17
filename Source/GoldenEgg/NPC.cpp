// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC.h"
#include "Avatar.h"
#include "MyHud.h"


// Sets default values
ANPC::ANPC(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Proximity Sphere"));	
	ProxSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	ProxSphere->SetSphereRadius(32.0f);
	//Code to make ANPC::Prox() run when this proximity sphere overlaps another actor
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox);
	NPCMessage = "Hi, I am Owen"; //Default NPC message can be changed in blueprint


}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int ANPC::Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherOverlappedComp,
	int32 OtherBodyInde, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return -1;
	}
	APlayerController* FPController = GetWorld()->GetFirstPlayerController();
	if(FPController)
	{
		AMyHUD* hud = Cast<AMyHUD>(FPController->GetHUD());
		hud->addMessage(Message(NPCMessage, 5.f, FColor::White));
	}
//	UE_LOG(LogTemp, Warning, TEXT("Prox impl"));
	return 0;
}