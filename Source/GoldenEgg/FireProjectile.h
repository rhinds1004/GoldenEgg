// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "MyDamageType.h"
#include "FireProjectile.generated.h"

/**
 * 
 */
UCLASS()
class GOLDENEGG_API AFireProjectile : public AProjectile
{
	GENERATED_BODY()
	
		//TODO so how make damagetypes work
		UPROPERTY(EditDefaultsOnly, Category = Properties)
		TSubclassOf<UMyDamageType> KnockbackDamageType = UMyDamageType::StaticClass();

public:
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual int Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Who is firing the projectile
	AMonsterBase* Firer;

	UFUNCTION()
		virtual int DoDamage(AActor* OtherActor, UPrimitiveComponent* OtherComp) override;
};
