// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "Projectile.generated.h"

class AMonsterBase;

UCLASS()
class GOLDENEGG_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile(const FObjectInitializer& ObjectInitializer);

	//How much damage done by the projectile
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
		float Damage;

	//Life span of the projectile in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
		float LifeSpan;

	// The visible Mesh for the component, so we can see
	// the shooting object
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		UStaticMeshComponent* Mesh;

	// the sphere you collide with to do impact damage
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		USphereComponent* ProxSphere;


	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		virtual int Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
		// Who is firing the projectile
		AMonsterBase* Firer;
		
		UFUNCTION()
			virtual int DoDamage(AActor* OtherActor, UPrimitiveComponent* OtherComp);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
