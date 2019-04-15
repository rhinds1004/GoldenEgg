// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "MeleeWeapon.h"
#include "MonsterBase.generated.h"

UCLASS()
class GOLDENEGG_API AMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterBase(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	// Movement speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float Speed;
	
	//Monster's hitpoints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float HitPoints;

	//Experience gained for defeating the monster
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		int32 Experience;

	//Blueprint of the type of item dropped by the monster
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		UClass *BPLoot;

	//base amount of damage monster attacks do
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float BaseAttackDamage;

	//Amount of time needed for monster to rest in between attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float AttackTimeout;

	//Time since last monster's attack. Blueprint readable only
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonsterProperties)
	float TimeSinceLastStrike;

	//Range of monster's sight
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
		USphereComponent* SightSphere;

	//Range for his attack. Visualizes as a sphere in editor
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
		USphereComponent* AttackRangeSphere;

	//The melee weapon class the monster uses. If not set, uses a melee attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		UClass* BP_MeleeWeapon;

	//The MeleeWeapon instance (set if the character is using a melee weapon)
	AMeleeWeapon* MeleeWeapon;

	inline bool isInSightRange( float d)
	{
		return d < SightSphere->GetScaledSphereRadius();
	}

	inline bool isInAttackRange (float d)
	{
		return d < AttackRangeSphere->GetScaledSphereRadius();
	}
};
