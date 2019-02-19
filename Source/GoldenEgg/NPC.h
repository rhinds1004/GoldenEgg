// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "NPC.generated.h"


UCLASS()
class GOLDENEGG_API ANPC : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	ANPC(const FObjectInitializer& ObjectInitializer);

	//Message told to the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCSettings")
		FString NPCMessage;

	//Sphere volume around the NPC that will trigger NPC to react to the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPCSettings")
		USphereComponent* ProxSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCSettings")
		FString NPCName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCSettings")
		UTexture2D* NPCFace;

	//Body of this function belongs to ANPC::Prox_Implementation not ANPC::Prox because function is flagged as a blueprintNativeEvent
	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
		void Prox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherOverlappedComp,
			int32 OtherBodyInde, bool bFromSweep, const FHitResult& SweepResult);
			virtual int Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherOverlappedComp,
			int32 OtherBodyInde, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
