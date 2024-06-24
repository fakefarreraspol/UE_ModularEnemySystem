// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"

#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"




// Sets default values
ATestCharacter::ATestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATestCharacter::ThrowRaycast()
{
	UCameraComponent* camera = FindComponentByClass<UCameraComponent>();

	if (camera)
	{
		UE_LOG(LogTemp, Warning, TEXT("true"));
	}
	else UE_LOG(LogTemp, Warning, TEXT("false"));

	FVector cameraForward = camera->GetForwardVector();
	//UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), cameraForward.X, cameraForward.Y, cameraForward.Z);


	float RaycastDistance = 1000.0f;
	FVector RaycastEnd = camera->GetComponentLocation() + (cameraForward * RaycastDistance);

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	// Perform line trace (raycast) and check for hits
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		camera->GetComponentLocation(),
		RaycastEnd,
		ECollisionChannel::ECC_Camera,
		CollisionParams
	);

	UE_LOG(LogTemp, Error, TEXT("%d"), bHit);

	if (bHit)
	{
		UClass* HitActorClass = HitResult.GetActor()->GetClass();
		if (HitActorClass && HitActorClass->IsChildOf(AEnemyCharacter::StaticClass()))
		{
			if (!Cast<UBodySkeletalMeshComponent>(HitResult.GetComponent())) return;
			// Hit an actor of class BaseBP
			DrawDebugLine(
				GetWorld(),
				camera->GetComponentLocation(),
				HitResult.ImpactPoint,
				FColor::Red,
				false, 10.0f, 0,
				1.0f
			);
			AEnemyCharacter& HitModularEnemy = *Cast<AEnemyCharacter>(HitResult.GetActor());
			
			if (limbsUsed >= maxLimbs)
			{
				return;
			}
			limbsUsed++;

			//UE_LOG(LogTemp, Warning, TEXT("hola %f %f %f"), HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, HitResult.ImpactPoint.Z);
			HitModularEnemy.AddLimb(HitResult.ImpactPoint);
			
		}
		else
		{
			// Hit something else
			DrawDebugLine(
				GetWorld(),
				camera->GetComponentLocation(),
				HitResult.ImpactPoint,
				FColor::Blue,
				false, 10.0f, 0,
				1.0f
			);
		}
	}
	
}




