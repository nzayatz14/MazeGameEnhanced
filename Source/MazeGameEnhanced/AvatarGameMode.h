// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyHud.h"

#include "GameFramework/GameMode.h"
#include "AvatarGameMode.generated.h"

/**
 *
 */
UCLASS()
class MAZEGAMEENHANCED_API AAvatarGameMode : public AGameMode
{
    GENERATED_BODY()
    
    AAvatarGameMode();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
public:
    void movePlayerStart(FVector position);
    
    bool checkLoss(int32 time);
    bool checkForWin(bool hasWon, FVector loc);
    bool won = false;
};
