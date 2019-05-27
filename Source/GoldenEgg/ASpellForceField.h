// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "Components/SphereComponent.h"
#include "ASpellForceField.generated.h"

/**
 * 
 */
UCLASS()
class GOLDENEGG_API AASpellForceField : public ASpell
{
	GENERATED_BODY()
public:
		AASpellForceField(const FObjectInitializer& ObjectInitializer);

		UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
		USphereComponent* BoundSphere;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
			float ExpandBy;

		
		virtual void Tick(float DeltaTime) override;
		virtual void BeginPlay() override;
	
};
