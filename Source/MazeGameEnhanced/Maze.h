// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Maze.generated.h"

#define WALL_SIZE 200
#define WALL_HEIGHT 400


UCLASS()
class MAZEGAMEENHANCED_API AMaze : public AActor
{
	GENERATED_BODY()
    /** Dummy root component */
    UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class USceneComponent* DummyRoot;
    
public:
    // Sets default values for this actor's properties
    AMaze();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    bool *allTheWalls;
    FVector *allTheItems;
    FVector2D mazeDimensions;
    
    FVector finishingLocation;

    int numRows=6, numCols=6;
    
    float maxX, maxY;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    void openExit();
    
public:
    /** Returns DummyRoot subobject **/
    FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
    FORCEINLINE bool* GetAllAWall(){return allTheWalls;}
    FORCEINLINE FVector2D GetMazeDimensions(){return mazeDimensions;}
    FORCEINLINE FVector* GetAllTheItems(){return allTheItems;}
    FORCEINLINE FVector2D GetMazeMeshMaxs() {return FVector2D(maxX, maxY);}
    
private:
    void createMaze(float x, float y, int numWallsX, int numWallsY);
    bool inOneSet(int array[], int size);
    int findLeader(int array[], int start);
};
