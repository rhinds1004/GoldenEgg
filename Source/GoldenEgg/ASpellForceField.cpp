// Fill out your copyright notice in the Description page of Project Settings.

#include "ASpellForceField.h"
#include "Components/SphereComponent.h"


AASpellForceField::AASpellForceField(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{	
	BoundSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Bounding Sphere"));
	BoundSphere->InitSphereRadius(32.f);
	ExpandBy = 1.001f;
	//breaks if in began play. why?
	BoundSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	PrimaryActorTick.bCanEverTick = true;
}

void AASpellForceField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BoundSphere->SetSphereRadius(BoundSphere->GetUnscaledSphereRadius()*ExpandBy , true);
}


void AASpellForceField::BeginPlay()
{
	Super::BeginPlay();
}
