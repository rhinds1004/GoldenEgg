// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MeleeWeapon.generated.h"

class AMonsterBase;

UCLASS()
class GOLDENEGG_API AMeleeWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeleeWeapon(const FObjectInitializer& ObjectInitializer);

	//Amount of damage attacks of this weapon so
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeleeWeapon)
		float AttackDamage;

	//List of things melee weapon already hit this swing
	TArray<AActor*> ThingsHit;

	//Prevents damage from occuring in frames where the sword is not swing
	bool Swinging;

	//Check to see if weapon is hitting the melee weapon owner
	AMonsterBase* WeaponHolder;

	//bounding box that determines if melee weapon hit
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MeleeWeapon)
		UBoxComponent* ProxBox;

	


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MeleeWeapon)
		UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		virtual int Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	void Swing();
	void Rest();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
