// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "LimbSkeletalMeshComponent.h"
#include "BodySkeletalMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/CapsuleComponent.h"


#include "NiagaraSystem.h"
#include "NiagaraComponent.h"

#include "EnemyCharacter.generated.h"



//class UPhysicsConstraintComponent;
UCLASS()
class TFG_2_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditDefaultsOnly, Category = "Skeletal Mesh")
		TSubclassOf<ULimbSkeletalMeshComponent> meshAsset;

	void AddLimb(FVector Location);
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OnSpiderLimbDestroyed(ULimbSkeletalMeshComponent* DestroyedComponent);

	UFUNCTION()
		void ReceiveDamage(int32 damage);

	UFUNCTION(BlueprintImplementableEvent, Category = "BaseCharacter", BlueprintCallable)
		void ActivateEnemy();

	UFUNCTION(BlueprintImplementableEvent, Category = "BaseCharacter", BlueprintCallable)
		void OnLegRemoved();

	FName GetNearestBone(const FVector& HitLocation);

	UBodySkeletalMeshComponent* body;

	UPROPERTY(BlueprintReadWrite, Category = "EnemyModular")
		TArray<ULimbSkeletalMeshComponent*> SpiderLegs;
	UPROPERTY(BlueprintReadWrite, Category = "EnemyModular")
		TArray<UPhysicsConstraintComponent*> PhysConstraints;

	
	
public: 
	UPROPERTY(BlueprintReadWrite, Category = "EnemyModular")
		int32 hp = 100;
	UPROPERTY(BlueprintReadWrite, Category = "EnemyModular")
		int32 maxHP = 100;
	UPROPERTY(BlueprintReadWrite, Category = "EnemyModular")
		bool canBeEdited = true;

	UPROPERTY()
		UNiagaraComponent* NiagaraComponent;
	UPROPERTY()
		UNiagaraSystem* NiagaraSystem;
};
