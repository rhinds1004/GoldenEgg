// Fill out your copyright notice in the Description page of Project Settings.

#include "MeleeWeapon.h"
#include "MonsterBase.h"
#include "Components/StaticMeshComponent.h"




// Sets default values
AMeleeWeapon::AMeleeWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AttackDamage = 1.f;
	Swinging = false;
	WeaponHolder = NULL;

	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	SetRootComponent(Mesh);

	ProxBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this,TEXT("ProxBox"));
	ProxBox->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::Prox);
	ProxBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	
}

// Called when the game starts or when spawned
void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AMeleeWeapon::Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//don't hit non root components
	if (OtherComp != OtherActor->GetRootComponent()) 
	{
		return -1;
	}
	//only hit if swinging
	//don't register a hit if it is actor holding this weapon
	//only hit once
	if (Swinging && OtherActor != (AActor *)WeaponHolder && !ThingsHit.Contains(OtherActor))
	{
		OtherActor->TakeDamage(AttackDamage + WeaponHolder->BaseAttackDamage, FDamageEvent(), NULL, this);
		ThingsHit.Add(OtherActor);
	}
	return 0;
}

void AMeleeWeapon::Swing()
{
	ThingsHit.Empty();
	Swinging = true;
}

void AMeleeWeapon::Rest()
{
	ThingsHit.Empty();
	Swinging = false;
}
