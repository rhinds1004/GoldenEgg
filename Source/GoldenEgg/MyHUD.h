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
	UTexture2D* tex;

	//set default values
	Message()
	{
		time = 5.f;
		color = FColor::White;
		tex = nullptr;
	}

	Message(FString iMessage, float iTime, FColor iColor, UTexture2D* iTex)
	{
		message = iMessage;
		time = iTime;
		color = iColor;
		tex = iTex;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDSettings)
		float barWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDSettings)
		float barHeight; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDSettings)
		float barPad;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDSettings)
	 float barMargin;

	virtual void DrawHUD() override;
	
	void addMessage(Message msg);

	void drawMessages();


	void drawMessage(Message msg, int lineCount);

	void DrawHpBar(float currentHP, float maxHp);
	
};
