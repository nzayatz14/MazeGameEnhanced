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


/**
 Function called to check if the user has lost
 
 - parameter void
 - returns: void
 */
bool AAvatarGameMode::checkLoss(int32 time){
    
    //player loses if time runs out or if the score runs out
    if (time == 0){
        return true;
    }
    
    return false;
}


/**
 Function called to check and see if the user has finished the maze
 
 - parameter void:
 - returns: void
 */
bool AAvatarGameMode::checkForWin(bool hasWon, FVector loc){
    
    TActorIterator<AMaze> ActorItr =TActorIterator<AMaze>(GetWorld());
    if(ActorItr){
        
        FVector difference = loc - ActorItr->finishingLocation;
        
        if((difference.Size() < WALL_SIZE + (WALL_SIZE/4)) && !hasWon){
            won = true;
        }
    }
    
    return won;
}