// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Avatar.generated.h"

UCLASS()
class GOLDENEGG_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAvatar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveForward(float amt);
	UFUNCTION()
	void StrafeLeft(float amt);
	UFUNCTION()
	void MoveBackward(float amt);
	UFUNCTION()
	void StrafeRight(float amt);
	UFUNCTION()
		void LookX(float amt);
	UFUNCTION()
		void LookY(float amt);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mouse)
		float mouseSensitivity;
	
};
