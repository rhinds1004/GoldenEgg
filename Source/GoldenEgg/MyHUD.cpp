// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "Engine/Texture2D.h"



void AMyHUD::DrawHUD()
{

	Super::DrawHUD();

	canvasSizeX = Canvas->SizeX;
	canvasSizeY = Canvas->SizeY;
	drawMessages();

}

void AMyHUD::addMessage(Message msg)
{
	messages.Add(msg);
}

void AMyHUD::drawMessages()
{
	//iterates array backwards to avoid issues if an element is removed
	for (int c = messages.Num() - 1; c >= 0; c--)
	{
		drawMessage(messages[c], c);
		//reduce message lifespan by the amount of time that has passed since the last frame
		messages[c].time -= GetWorld()->GetDeltaSeconds();

		//if lifespan is zero delete from messages array
		if (messages[c].time <= 0)
		{
			messages.RemoveAt(c);
		}
	}
}

void AMyHUD::drawMessage(Message msg, int lineCount)
{
	//Draws the text background box to the correct size
	float outputHeight, outputWidth, pad = 10.f;
	GetTextSize(msg.message, outputWidth, outputHeight, hudFont, 1.f);

	float messageH = outputHeight + 2.f * pad;
	float x = 0.f, y = lineCount * messageH;

	if (msg.tex != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to do texture"));
		DrawTexture(msg.tex, x, y, messageH, messageH, 0, 0, 1, 1);
	}
	//black backing
	DrawRect(FLinearColor::Black, messageH + x, y, canvasSizeX, messageH);

	DrawText(msg.message, msg.color,  messageH + x + pad, y + pad, hudFont);

}
