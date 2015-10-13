// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGameEnhanced.h"
#include "itemsSpawning.h"

#include "inventory.h"
#include "itemBasic.h"
#include <random>

AitemBasic **allItems;

// Sets default values
AitemsSpawning::AitemsSpawning()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    //PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AitemsSpawning::BeginPlay()
{
    
    Super::BeginPlay();
}

// Called every frame
void AitemsSpawning::Tick( float DeltaTime )
{
    
    Super::Tick( DeltaTime );
}

FVector* AitemsSpawning::spawn(int rows, int columns, float widthApart, FVector thisLoc)
{
    bool blocked;
    int i=0;
    AitemBasic *newItem;
    basicItemCount = ( (rows>columns)?rows:columns ) - 2;
    FVector *allTheItems;
    allTheItems = new FVector[basicItemCount];
    for(i=0; i<basicItemCount; i++)
        allTheItems[i] = FVector(-1, -1, -1);
    i=0;
    int blockID;
    int colNum, rowNum;
    std::random_device rd;
    
    //get array of all of the items
    allItems = new AitemBasic*[basicItemCount];
    
    while(i<basicItemCount){
        blocked = false;
        // choose a random block [0..rows*columns-1]
        blockID = rd() % (rows * columns);
        // get the col# and row# of that block
        colNum = blockID % columns ;
        rowNum = blockID / columns ;
        for(int j=0; j<basicItemCount; j++)
            if((int)(allTheItems[j].X+.5) == rowNum && (int)(allTheItems[j].Y+.5) == colNum)
                blocked = true;
        if(!blocked){
            allTheItems[i] = FVector(rowNum, colNum, 0);
            // spawn at ( (col#+.5)*widthApart, (row#+.5)*widthApart, offTheGround )
            newItem = GetWorld()->SpawnActor<AitemBasic>
            ( thisLoc + FVector( ((float)colNum+.5)*widthApart, ((float)rowNum+.5)*widthApart, 75.f+50 ), FRotator(0,0,0) );
            newItem->mazeLocation = FVector2D (rowNum, colNum);
            
            //add each newly created item to the array of all items
            allItems[i] = newItem;
            
            i++;  
        }
    }
    return allTheItems;
}


/**
 Function called to check if all the items have been collected
 
 - parameter void:
 
*/
bool AitemsSpawning::allItemsFound(){
    
    for(int i = 0; i<basicItemCount; i++){
        if(!allItems[i]->found){
            return false;
        }
    }
    
    return true;
}