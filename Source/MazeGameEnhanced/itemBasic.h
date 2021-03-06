// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "itemBasic.generated.h"


UCLASS()
class MAZEGAMEENHANCED_API AitemBasic : public AActor
{
	GENERATED_BODY()
	
	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ItemBasicMesh;

public:	
	// Sets default values for this actor's properties
	AitemBasic();

	bool found;
	char itemType;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector2D mazeLocation;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//testing
	void spinWithQuaternion();
	
	//UFUNCTION()
	//	void onHit(AActor *Self, AActor *neighbor, FVector NormalImpulse, const FHitResult &Hit);


public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetItemBasicMesh() const { return ItemBasicMesh; }
	FORCEINLINE FVector2D GetMazeLocation() const { return mazeLocation; }

};
