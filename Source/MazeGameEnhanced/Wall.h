// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Wall.generated.h"

UCLASS()
class MAZEGAMEENHANCED_API AWall : public AActor
{
	GENERATED_BODY()
    
    /** Dummy root component */
    UPROPERTY(Category = Wall, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class USceneComponent* DummyRoot;
    
    /** StaticMesh component for the clickable block */
    UPROPERTY(Category = Wall, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* WallMesh;
	
public:	
	// Sets default values for this actor's properties
	AWall();
    
    /** Pointer to orange material used on active blocks */
    UPROPERTY()
    class UMaterialInstance* WallMaterial;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
    void setMeshSize(float width, float height);
    
    bool isHorizontal;
    bool isBorder;
    bool isStanding;
    bool isObstacle;
    
    void setHorizontal(bool maybe);
    bool getIsHorizontal();
    void setIsBorder(bool maybe);
    bool getIsBorder();
    void setIsStanding(bool maybe);
    bool getIsStanding();
    void setIsObstacle(bool maybe);
    bool getIsObstacle();

public:
    /** Returns DummyRoot subobject **/
    FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
    /** Returns BlockMesh subobject **/
    FORCEINLINE class UStaticMeshComponent* GetBallMesh() const { return WallMesh; }	
	
};
