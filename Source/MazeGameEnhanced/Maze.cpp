// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGameEnhanced.h"
#include "Maze.h"

#include "Wall.h"
#include "itemsSpawning.h"
#include "inventory.h"
#include "AvatarGameMode.h"

AWall **myWalls;

// Sets default values
AMaze::AMaze()
{
   // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
   PrimaryActorTick.bCanEverTick = true;
    
    // Create dummy root scene component
    DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
    RootComponent = DummyRoot;

}

// Called when the game starts or when spawned
void AMaze::BeginPlay()
{
   Super::BeginPlay();
   maxX = WALL_SIZE * numCols;
   maxY = WALL_SIZE * numRows;
   createMaze(maxX,maxY,numRows,numCols);
}

// Called every frame
void AMaze::Tick( float DeltaTime )
{

   Super::Tick( DeltaTime );
}


/**
Function that generates a (rows x cols) maze
 
 - parameter x: the size of the floor in the x direction
 - parameter y: the size of the floor in the y direction
 - parameter rows: the number of walls desired in the x direction
 - parameter cols: the number of walls desired in the y direction
 - returns: void
*/
void AMaze::createMaze(float x, float y, int rows, int cols){
    float spaceBetweenBorders = x / rows;
    int numSpaces = rows*cols;
    int numBorders = rows*(cols+1) + cols*(rows+1);
    int verticals = 0;
    FVector BlockLocation = FVector(0,0,0);
    mazeDimensions = FVector2D(rows, cols);
    myWalls = new AWall*[numBorders];
    allTheWalls = new bool[numBorders];

    // when the walls spawn, spawn all the items distributed to fit rows, columns, spaceBetween
    AitemsSpawning *allItems = GetWorld()->SpawnActor<AitemsSpawning>(FVector(-100,-100,-500), FRotator(0,0,0));
    allTheItems = allItems->spawn(rows, cols, spaceBetweenBorders, BlockLocation );

    //generate the horizontal walls
    for (int i = 0; i<=cols; i++){
        for (int j = 0; j<rows; j++){
            
            BlockLocation = FVector(spaceBetweenBorders*i, spaceBetweenBorders*j, 0.f);
            
            AWall* NewWall = GetWorld()->SpawnActor<AWall>(BlockLocation, FRotator(0,90,0));
            NewWall->setMeshSize(spaceBetweenBorders, WALL_HEIGHT);
            
            if (i == 0 || i == cols){
                NewWall->setIsBorder(true);
            }
            
            verticals++;
            
            //add wall to array
            myWalls[i*rows + j] = NewWall;
        }
    }
    
    
    //generate the vertical walls
    for (int i = 0; i<=rows; i++){
        for (int j = 0; j<cols; j++){
            
            BlockLocation = FVector(spaceBetweenBorders*j, spaceBetweenBorders*i, 0.f);
            
            AWall* NewWall = GetWorld()->SpawnActor<AWall>(BlockLocation, FRotator(0,0,0));
            NewWall->setMeshSize(spaceBetweenBorders, 400);
            NewWall->isHorizontal = true;
            
            if (i == 0 || i == rows){
                NewWall->setIsBorder(true);
            }
            
            //add wall to array
            myWalls[(cols+1)*rows + i*cols + j] = NewWall;
        }
    }
    
    
    //initialize the array for the disjoint sets
    int *disjointSets = new int[numSpaces];
    
    for(int i = 0;i<numSpaces;i++){
        disjointSets[i] = -1;
    }
    for(int i=0; i<numBorders; i++)
        allTheWalls[i] = true;
    
    int wall;
    int space1;
    int space2;
    int aboveRow, aboveCol;
    int leader1;
    int leader2;
    
    //get the walls that are to be knocked down
    while(!inOneSet(disjointSets, numSpaces)){
        wall = rand()%numBorders;
        
        //if the wall is not already knocked down and is not a border
        if(!myWalls[wall]->getIsBorder() && myWalls[wall]->getIsStanding()){
            
            //check if the wall is horizontal or not, get the spaces the wall is seperating based on this fact
            if(!myWalls[wall]->getIsHorizontal()){
                space1 = wall-rows;
                space2 = wall;
            }else{
                aboveRow = (wall-(verticals+cols))/cols;
                aboveCol = (wall-(verticals+cols))%cols;
                space1 = aboveCol*rows+aboveRow;
                space2 = space1+1;
            }
            
            //join the 2 sets
            leader1 = findLeader(disjointSets,space1);
            leader2 = findLeader(disjointSets,space2);
            
            if(!(leader1 == leader2 && leader1 != -1)){
                disjointSets[leader1] = space2;
                myWalls[wall]->setIsStanding(false);
                allTheWalls[wall] = false;
            }
        }
    }
    
    
    //generate the beginning opening
    //start opening
    wall = rand()%rows;
    
    if(myWalls[wall]->getIsBorder() && myWalls[wall]->getIsStanding()){
        myWalls[wall]->setIsStanding(false);
        allTheWalls[wall] = false;
        
        //move player start to that location
        TActorIterator<AAvatarGameMode> ActorItr =TActorIterator<AAvatarGameMode>(GetWorld());
        
        if (ActorItr) {
            ActorItr->movePlayerStart(myWalls[wall]->GetActorLocation());
        }
    }
}


/**
 Opens the exit when the user has collected all of the items.
 
 - parameter void:
 - returns: void
*/
void AMaze::openExit(){
    int numSpaces = numRows*numCols;
    int wall = rand()%numRows + (numSpaces);
    
    FString cross = FString::FromInt(wall);
    //GEngine->AddOnScreenDebugMessage(3, 1.0f, FColor::Green, *cross);
    
    if(myWalls[wall]->getIsBorder() && myWalls[wall]->getIsStanding()){
        myWalls[wall]->setIsStanding(false);
        allTheWalls[wall] = false;
        
        finishingLocation = myWalls[wall]->GetActorLocation();
    }
}


/** 
 Takes in the array of connections checks to see whether or not all of the elements in the array are in 1 set
 
 - parameter array: the array of connections made
 - parameter size: the size of the array
 - returns: a boolean representing whether or not all of the elements in the array are in 1 set
*/
bool AMaze::inOneSet(int array[], int size){
    
    //only one element is allowed to have a -1 as its component
    int one = 0;
    for(int i = 0;i<size;i++){
        if (array[i] == -1 && one == 1){
            return false;
        }else if (array[i] == -1){
            one++;
        }
    }
    
    return true;
}


/**
 Takes in an array and a start value and finds the "leader" if the line that start value is in
 
 - parameter array: the array of connections made
 - parameter start: the starting position of the lineage you wish to find the start of
 - returns: the "leader" of that line
 */
int AMaze::findLeader(int array[], int start){
    int prev = start;
    int leader = array[start];
    while (leader != -1) {
        prev = leader;
        leader = array[leader];
    }
    
    return prev;
}