// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LimbSkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "ModularEnemy.generated.h"




UCLASS(config = Game)
class TFG_2_API AModularEnemy : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	AModularEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:	
	UPROPERTY(EditDefaultsOnly, Category = "Skeletal Mesh")
		TSubclassOf<ULimbSkeletalMeshComponent> meshAsset;
	
	FName boneName = "BODY1";
	TArray<USkeletalMeshSocket*> socketNames;
		
	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//USkeletalMeshSocket* CreateSocket(USkeletalMesh* Skeleton, FVector Location);
	void AddLimb(FVector Location);
	//void AddLimb();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
