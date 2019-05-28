// Fill out your copyright notice in the Description page of Project Settings.

#include "ASpellForceField.h"
#include "Components/SphereComponent.h"
#include "MonsterBase.h"


AASpellForceField::AASpellForceField(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{	
	BoundSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Bounding Sphere"));
	BoundSphere->InitSphereRadius(32.f);
	ExpandBy = 1.001f;
	//breaks if in began play. why?
	PreviousRadius = BoundSphere->GetUnscaledSphereRadius();
	BoundSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	PrimaryActorTick.bCanEverTick = true;
}

void AASpellForceField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PreviousRadius = BoundSphere->GetUnscaledSphereRadius();
	BoundSphere->SetSphereRadius(BoundSphere->GetUnscaledSphereRadius()*ExpandBy , true);
	TArray<AActor*>OverlapActors;
	BoundSphere->GetOverlappingActors(OverlapActors);
	for (int i = 0; i < OverlapActors.Num(); i++)
	{
		if (AMonsterBase* monster = Cast<AMonsterBase>(OverlapActors[i]))
		{
			//FVector knockback = monster->GetActorLocation() - BoundSphere->GetComponentLocation();
			//knockback.Normalize();
			//knockback *= 1 * 1500;
			float diff = BoundSphere->GetUnscaledSphereRadius() - PreviousRadius;
			//monster->AddActorLocalOffset(FVector(diff * 150, diff * 15, 0)); // spins avvatar and mosnter around each other
			monster->AddActorWorldOffset(FVector(diff * 10, 0, 0)); //TODO pushes but only pushes in +x direction. 
			//monster->AddMovementInput(, 1, true);
		}
	}
	
}


void AASpellForceField::BeginPlay()
{
	Super::BeginPlay();
}
