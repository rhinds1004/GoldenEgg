// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"


// Sets default values
AProjectile::AProjectile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
	SetRootComponent(ProxSphere);
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::Prox);
	Mesh->SetupAttachment(RootComponent);
	Damage = 1.f;
	LifeSpan = 7.f;
}



// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AProjectile::Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	//don't hit non root components
	if (OtherComp != OtherActor->GetRootComponent())
	{
		return -1;
	}
	DoDamage(OtherActor, OtherComp);
	Destroy();
	return 0;
}

int AProjectile::DoDamage(AActor * OtherActor, UPrimitiveComponent * OtherComp)
{
	if (!OtherActor || !OtherComp)
	{
		return -1;
	}
	OtherActor->TakeDamage(Damage, FDamageEvent(), NULL, this);
	return 0;
}