// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "BodySkeletalMeshComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TFG_2_API UBodySkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:
	int32 bodyHealth;


	UBodySkeletalMeshComponent();



	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


protected:
	virtual void BeginPlay() override;

};
