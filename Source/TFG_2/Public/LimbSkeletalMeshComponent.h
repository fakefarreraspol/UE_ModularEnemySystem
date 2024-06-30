// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"


#include "LimbSkeletalMeshComponent.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComponentDestroyed, ULimbSkeletalMeshComponent*, DestroyedComponent);
UCLASS()
class TFG_2_API ULimbSkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
private:
	int hP = 100;

	FTimerHandle TimerHandle;
public:
	void ReceiveDamage(int Damage);
	void DettachAndDestroy();

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnComponentDestroyed OnComponentDestroyedEvent;




};
