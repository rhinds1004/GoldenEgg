// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "Engine/Texture2D.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Avatar.h"


void AMyHUD::DrawHUD()
{

	Super::DrawHUD();

	canvasSizeX = Canvas->SizeX;
	canvasSizeY = Canvas->SizeY;
	// dims only exist here in stock variable Canvas 
	// Update them so use in addWidget() 
	
	//dims.X = ViewportSize.X;
	//dims.Y = ViewportSize.Y;
	ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	DrawMessages();
	DrawWidgets();
	AAvatar* Avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	DrawHpBar(Avatar->GetCurrentHp(), Avatar->GetMaxHp());
	barMargin = 50.f;
		barPad = 12.f;
	barHeight = 50.f;
		barWidth = 200.f;
}

void AMyHUD::AddMessage(Message msg)
{
	messages.Add(msg);
}

void AMyHUD::DrawMessages()
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
		//UE_LOG(LogTemp, Warning, TEXT("Trying to do texture"));
		DrawTexture(msg.tex, x, y, messageH, messageH, 0, 0, 1, 1);
	}
	//black backing
	DrawRect(FLinearColor::Black, messageH + x, y, canvasSizeX, messageH);

	DrawText(msg.message, msg.color,  messageH + x + pad, y + pad, hudFont);

}

void AMyHUD::addWidget(Widget widget)
{
	// find the pos of the widget based on the grid. 
	// draw the icons.. 
	FVector2D start(200, 200), pad(12, 12);
	widget.size = FVector2D(100, 100);
	widget.pos = start;
	// compute the position here 
	for (int c = 0; c < widgets.Num(); c++)
	{
		// Move the position to the right a bit. 
		widget.pos.X += widget.size.X + pad.X;
		// If there is no more room to the right then 
		// jump to the next line 
		if (widget.pos.X + widget.size.X > ViewportSize.X)
		{
			widget.pos.X = start.X;
			widget.pos.Y += widget.size.Y + pad.Y;
		}
	}
	widgets.Add(widget);
}

void AMyHUD::clearWidgets()
{
	widgets.Empty();
}

void AMyHUD::DrawHpBar(float currentHp, float maxHp)
{
	float x = 0.f; 
	float percHp = currentHp / maxHp;

//	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	DrawRect(FLinearColor(0, 0, 0, 1), x, ( ViewportSize.Y - ViewportSize.Y / 4) - barHeight - barPad -
		barMargin, barWidth + 2 * barPad, barHeight + 2 * barPad);
	DrawRect(FLinearColor(1 - percHp, percHp, 0, 1), x, (ViewportSize.Y - ViewportSize.Y / 4) - barHeight - barMargin,
		barWidth*percHp, barHeight);
	//DrawRect(FLinearColor::Black, x, canvasSizeY - canvasSizeY / 4, Avatar->totalHP * 5, 50.f);
	//	DrawRect(FLinearColor::Red, x, canvasSizeY - canvasSizeY/4, Avatar->currentHP * 5, 50.f);
}

void AMyHUD::DrawWidgets()
{
	for (int i = 0; i < widgets.Num(); i++)
	{
		DrawTexture(widgets[i].icon.tex, widgets[i].pos.X, widgets[i].pos.Y, widgets[i].size.X, widgets[i].size.Y, 0, 0, 1, 1);
		DrawText(widgets[i].icon.name, FLinearColor::Yellow, widgets[i].pos.X, widgets[i].pos.Y, hudFont, .6f, false);
	}
}
