// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */


struct Message
{
	FString message;
	float time;
	FColor color;

	//set default values
	Message()
	{
		time = 5.f;
		color = FColor::White;
	}

	Message(FString iMessage, float iTime, FColor iColor)
	{
		message = iMessage;
		time = iTime;
		color = iColor;
	}

};

UCLASS()
class GOLDENEGG_API AMyHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
		UFont* hudFont;
	TArray<Message> messages;
	float canvasSizeX = 0.f;
	float canvasSizeY = 0.f;


	virtual void DrawHUD() override;
	
	void addMessage(Message msg);

	void drawMessages();


	void drawMessage(Message msg, int lineCount);
	
};
