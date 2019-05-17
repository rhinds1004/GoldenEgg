// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Spell.generated.h"

UCLASS()
class GOLDENEGG_API ASpell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpell(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Spell)
		UBoxComponent* ProxBox;
	//particle visualization of the spell
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Spell)
		UParticleSystemComponent* Particles;

	//How much damage the spell does per second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell)
		float DamagePerSecond;

	//How long the spell does lasts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell)
		float Duration;

	//Length of the time spell has been alive in the level
	float TimeAlive;

	//caster of the spell
	AActor* Caster;

	//Parents this spell to a caster actor
	void SetCaster(AActor* caster);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
