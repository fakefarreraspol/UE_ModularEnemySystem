// Fill out your copyright notice in the Description page of Project Settings.


#include "BodySkeletalMeshComponent.h"

UBodySkeletalMeshComponent::UBodySkeletalMeshComponent()
{
    SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    // Set collision response to all channels
    SetCollisionResponseToAllChannels(ECR_Block);
    
}
void UBodySkeletalMeshComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UBodySkeletalMeshComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    UE_LOG(LogTemp, Warning, TEXT("hola"));
}