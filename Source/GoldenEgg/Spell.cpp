// Fill out your copyright notice in the Description page of Project Settings.

#include "Spell.h"
#include "MonsterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ASpell::ASpell(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ProxBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ProxBox"));
	Particles = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("ParticleSystem"));
	// The Particles are the root component, and the ProxBox
	// is a child of the Particle system.
	// If it were the other way around, scaling the ProxBox
	// would also scale the Particles, which we don't want
	RootComponent = Particles;


	Duration = 3.f;
	DamagePerSecond = 1.f;
	TimeAlive = 0;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
	ProxBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// search the proxbox for all actors in the volume.
	TArray<AActor*> actors;
	ProxBox->GetOverlappingActors(actors);
	// damage each actor the box overlaps
	for (int c = 0; c < actors.Num(); c++)
	{
		// don't damage the spell caster
		if (actors[c] != Caster)
		{
			// Only apply the damage if the box is overlapping
			// the actors ROOT component.
			// This way damage doesn't get applied for simply
			// overlapping the SightSphere of a monster
			AMonsterBase *monster = Cast<AMonsterBase>(actors[c]);
			if (monster && ProxBox->IsOverlappingComponent(Cast<UPrimitiveComponent>(monster->GetCapsuleComponent())))
			{
				monster->TakeDamage(DamagePerSecond*DeltaTime,
					FDamageEvent(), 0, this);
			}
			// to damage other class types, try a checked cast
			// here..
		}
	}
	TimeAlive += DeltaTime;
	if (TimeAlive > Duration)
	{
		Destroy();
	}

}

void ASpell::SetCaster(AActor* caster)
{
	Caster = caster;
	RootComponent->AttachToComponent(caster->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

AActor * ASpell::GetCaster()
{
	return Caster;
}
