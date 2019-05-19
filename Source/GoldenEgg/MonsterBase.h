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

	//Blueprint reference for the project used by the monster
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		UClass* BP_Projectile;

	//Thrust behind the projectile launches
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float ProjectileLaunchImpulse;

	//The vector of the point on the mesh where the projectile will be fired from 
	UPROPERTY(VisibleAnywhere, Category = MonsterProperties)
		FVector Nozzle;

	//distance to move projectile fwd of the monster so doesn't hit the mosnter model
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float MoveProjectileFwdAmount;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	//checkss if an object is within in the monster's sight sphere. 
	UFUNCTION(BlueprintCallable)
	inline bool isInSightRange( float d)
	{
		if (SightSphere)
		{
			return d < SightSphere->GetScaledSphereRadius();
		}
		return false;
	}

	//checks if an object is within the monster's melee attack range. 
	UFUNCTION(BlueprintCallable)
	inline bool isInAttackRange (float d)
	{
		if (AttackRangeSphere)
		{
			return d < AttackRangeSphere->GetScaledSphereRadius();
		}
		return false;
	}

	//Checks if weapon is currently being swung
	UFUNCTION(BlueprintCallable, Category = Collision)
		void SwordSwung();

	UFUNCTION()
		void Attack(AActor* thing);

	UFUNCTION()
		virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

};
