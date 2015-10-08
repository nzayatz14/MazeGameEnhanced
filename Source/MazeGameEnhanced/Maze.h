// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Wall.h"
#include "itemsSpawning.h"
#include "inventory.h"

#include "GameFramework/Actor.h"
#include "Maze.generated.h"


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
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
public:
    /** Returns DummyRoot subobject **/
    FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
    
private:
    void createMaze(float x, float y, int numWallsX, int numWallsY);
    bool inOneSet(int array[], int size);
    int findLeader(int array[], int start);
    
};
