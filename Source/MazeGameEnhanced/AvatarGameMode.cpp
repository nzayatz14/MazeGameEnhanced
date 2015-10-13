// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGameEnhanced.h"
#include "AvatarGameMode.h"
#include "Avatar.h"
#include "Maze.h"




AAvatarGameMode::AAvatarGameMode(){
    
}


void AAvatarGameMode::BeginPlay(){
    Super::BeginPlay();
    
}


/**
Function called to move the players location based on where the starting wall was removed
 
 - parameter position: the position of the starting wall that was removed
 - returns: void
*/
void AAvatarGameMode::movePlayerStart(FVector position){
    TActorIterator<AAvatar> ActorItr =TActorIterator<AAvatar>(GetWorld());
    
    if (ActorItr) {
        ActorItr->SetActorLocation(FVector(position.X, position.Y + WALL_SIZE / 2, WALL_HEIGHT));
    }
}