// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */


struct Icon
{
	FString name;
	UTexture2D* tex;
	Icon() { name = "Unknown Icon"; tex = 0; }
	Icon(FString& iName, UTexture2D* iTex)
	{
		name = iName;
		tex = iTex;
	}

};

struct Widget
{
	Icon icon;
	FVector2D pos, size;
	Widget(Icon iIcon)
	{
		icon = iIcon;
	}
	float left() { return pos.X; }
	float right() { return pos.X + size.X; }
	float top() { return pos.Y; }
	float bottom() { return pos.Y + size.Y; }
};

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
	//Holds array of widget structs
	TArray<Widget> widgets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDSettings)
		float barWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDSettings)
		float barHeight; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDSettings)
		float barPad;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDSettings)
	 float barMargin;

	virtual void DrawHUD() override;
	
	void AddMessage(Message msg);

	void DrawMessages();


	void drawMessage(Message msg, int lineCount);
	
	void addWidget(Widget widget);
	void clearWidgets();

	void DrawHpBar(float currentHP, float maxHp);
	
	UFUNCTION()
	void DrawWidgets();

	//holds screen dimensions
	FVector2D ViewportSize;
};
