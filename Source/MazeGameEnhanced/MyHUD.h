// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class MAZEGAMEENHANCED_API AMyHUD : public AHUD
{
   GENERATED_BODY()
public:
   AMyHUD();
   AMyHUD(const class FObjectInitializer &PCIP);

	// Get a font
   UFont *HUDFont;

   // Override draw hud 
   //UPROPERTY()
   virtual void DrawHUD() override;

   void DrawLine(FVector Start, FVector End, FLinearColor TheColor, float Thick);
   void DrawRectangle( float X, float Y, float Width, float Height, const FLinearColor& Color);

   void DrawMinimap(bool*, FVector *, FVector2D, FVector2D);
   void DrawActor(FVector2D ScreenSize, int cols, int rows, float LineLength, FVector);

};