// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGameEnhanced.h"
#include "Wall.h"


// Sets default values
AWall::AWall()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    //PrimaryActorTick.bCanEverTick = true;
    
    isHorizontal = false;
    isBorder = false;
    isStanding = true;
    isObstacle = false;
    
    // Structure to hold one-time initialization
    struct FConstructorStatics
    {
        ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
        ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> WallMaterial;
        FConstructorStatics()
        : PlaneMesh(TEXT("/Game/StarterContent/CustomStuff/WallMesh.WallMesh"))
        , WallMaterial(TEXT("/Game/StarterContent/CustomStuff/WallMaterial.WallMaterial"))
        {
        }
    };
    static FConstructorStatics ConstructorStatics;
    
    // Create dummy root scene component
    DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
    RootComponent = DummyRoot;
    
    // Create static mesh component
    WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMesh0"));
    WallMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
    WallMesh->SetRelativeScale3D(FVector(1.0f,1.0f,1.0f));
    WallMesh->SetMaterial(0, ConstructorStatics.WallMaterial.Get());
    WallMesh->AttachTo(DummyRoot);
    
    // Save a pointer to the orange material
    WallMaterial = ConstructorStatics.WallMaterial.Get();

}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWall::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


/**
 Sets the size of a mesh to the given parameters
 
 - parameter width: the width of the wall
 - parameter height: the height of the wall
 - returns: void
*/
void AWall::setMeshSize(float width, float height){
    float scaleX = width/400;
    float scaleZ = height/400;
    
    WallMesh->SetRelativeScale3D(FVector(scaleX,1.0f,scaleZ));
}


/**
 Sets whether or not the wall is horizontal
 
 - parameter maybe: whether or not the wall is horizontal
 - returns: void
 */
void AWall::setHorizontal(bool maybe){
    
    //turn the wall if it is necessary
    if (maybe == true && isHorizontal == false){
        WallMesh->SetRelativeRotation(FRotator(0,90,0));
    }else if (maybe == false && isHorizontal == true) {
        WallMesh->SetRelativeRotation(FRotator(0,0,0));
    }
    
    isHorizontal = maybe;
}


/**
 Returns whether or no the wall is horizontal
 
 - parameter void:
 - returns: void
 */
bool AWall::getIsHorizontal(){
    return isHorizontal;
}


/**
 Sets whether or not the wall is a border
 
 - parameter maybe: whether or not the wall is a border
 - returns: void
 */
void AWall::setIsBorder(bool maybe){
    isBorder = maybe;
}


/**
 Returns whether or no the wall is a border
 
 - parameter void:
 - returns: void
 */
bool AWall::getIsBorder(){
    return isBorder;
}


/**
 Sets whether or not the wall is standing
 
 - parameter maybe: whether or not the wall is standing
 - returns: void
 */
void AWall::setIsStanding(bool maybe){
    isStanding = maybe;
    
    if (maybe == false) {
        WallMesh->SetRelativeRotation(FRotator(0,0,180));
    }
}


/**
 Sets whether or not the wall is an obstacle
 
 - parameter maybe: whether or not the wall is an obstacle
 - returns: void
 */
void AWall::setIsObstacle(bool maybe){
    isObstacle = maybe;
    
    if (maybe == true) {
        
        WallMesh->SetRelativeLocation(FVector(0.f,0.f,-230.f));
        WallMesh->SetRelativeRotation(FRotator(0,0,0));
    
       
    }
}


/**
 Returns whether or not the wall is an obstacle
 
 - parameter void:
 - returns: void
 */
bool AWall::getIsObstacle(){
    return isObstacle;
}



/**
 Returns whether or no the wall is standing
 
 - parameter void:
 - returns: void
 */
bool AWall::getIsStanding(){
    return isStanding;
}

