// Fill out your copyright notice in the Description page of Project Settings.


#include "LimbSkeletalMeshComponent.h"

void ULimbSkeletalMeshComponent::ReceiveDamage(int Damage)
{
	UE_LOG(LogTemp, Warning, TEXT("damaged!!"))
	hP -= Damage;
	if (hP <= 0)
	{
		
		//Communicate to enemy character the destruction of this limb
		OnComponentDestroyedEvent.Broadcast(this);
		DettachAndDestroy();
	}

}
void ULimbSkeletalMeshComponent::DettachAndDestroy()
{
	//remove destroyed limb collision with player
	SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	
	

	//Fall to the ground
	SetSimulatePhysics(true);
}

