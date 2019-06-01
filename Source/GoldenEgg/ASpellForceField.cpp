// Fill out your copyright notice in the Description page of Project Settings.

#include "ASpellForceField.h"
#include "Components/SphereComponent.h"
#include "MonsterBase.h"

//TODO add a clamp so the radius can only get so big, but the duration can keep increasing.


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
			float diff = BoundSphere->GetUnscaledSphereRadius() - PreviousRadius;
			//monster->AddActorLocalOffset(FVector(diff * 150, diff * 15, 0)); // spins avvatar and mosnter around each other

			FVector monsterFwdVector = monster->GetActorForwardVector();
			monsterFwdVector.Normalize();
			FVector casterFwdVector = Caster->GetActorForwardVector();
			casterFwdVector.Normalize();
			float dotProdResult = FVector::DotProduct(casterFwdVector, monsterFwdVector);
			if (dotProdResult < 0) // ensures monster is pushed away even if not facing caster.
			{
				monsterFwdVector.X *= -1;
				monsterFwdVector.Y *= -1;
				monsterFwdVector.Z *= -1;
			}
			monster->AddActorWorldOffset(FVector(monsterFwdVector.X * diff * 5, monsterFwdVector.Y * diff * 5, monsterFwdVector.Z * diff * 5)); //TODO pushes but only pushes in +x direction. 
			
		}
	}
	
}


void AASpellForceField::BeginPlay()
{
	Super::BeginPlay();
}
