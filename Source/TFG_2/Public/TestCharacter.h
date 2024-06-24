// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"


#include "EnemyCharacter.h"
#include "LimbSkeletalMeshComponent.h"
#include "BodySkeletalMeshComponent.h"

#include "TestCharacter.generated.h"



UCLASS()
class TFG_2_API ATestCharacter : public ACharacter
{
	GENERATED_BODY()

	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		//USkeletalMeshComponent* body;

public:
	// Sets default values for this character's properties
	ATestCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UFUNCTION(BlueprintCallable)
		void ThrowRaycast();

	
	static inline int32 maxLimbs = 8;
	UPROPERTY(BlueprintReadWrite, Category = "EnemyModular")
		int32 limbsUsed = 0;
	UFUNCTION(BlueprintCallable)
		static int32 GetMaxLimbs() { return maxLimbs; };


	UFUNCTION(BlueprintCallable)
		void ResetLimbsToAttach() { limbsUsed = 0; };
};
