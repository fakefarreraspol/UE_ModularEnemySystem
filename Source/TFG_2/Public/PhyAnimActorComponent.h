// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "LimbSkeletalMeshComponent.h"

#include "PhyAnimActorComponent.generated.h"


UCLASS(Blueprintable)
class TFG_2_API UPhyAnimActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPhyAnimActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "physanim", BlueprintCallable)
		void LimbHit(const FHitResult& Hit);
	UFUNCTION(BlueprintImplementableEvent, Category = "physanim", BlueprintCallable)
		void OnStart(const ULimbSkeletalMeshComponent* Limb);

	UFUNCTION(BlueprintImplementableEvent, Category = "physanim", BlueprintCallable)
		void OnDestroyed();
};
