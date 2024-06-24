// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "Projectile.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemAsset(TEXT("/EnemyCharacter/Blood.Blood"));

    if (NiagaraSystemAsset.Succeeded())
    {
        NiagaraSystem = NiagaraSystemAsset.Object;
        
    }
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
    body = Cast<UBodySkeletalMeshComponent>(GetComponentByClass(UBodySkeletalMeshComponent::StaticClass()));

    body->OnComponentHit.AddDynamic(this, &AEnemyCharacter::OnHit);

    SpiderLegs.Empty();
    PhysConstraints.Empty();

    SetCanBeDamaged(false);

}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::AddLimb(FVector Location)
{
    if (!canBeEdited) return;

    FTransform LocationTransform(FQuat::Identity, Location, FVector::OneVector);

    if (meshAsset)
    {
        //ULimbSkeletalMeshComponent* NewSkeletalMeshComponent; 
        
        ULimbSkeletalMeshComponent* NewSkeletalMeshComponent = Cast<ULimbSkeletalMeshComponent>(AddComponentByClass(meshAsset, false, LocationTransform, false));

        //NewSkeletalMeshComponent->RegisterComponent();

        NewSkeletalMeshComponent->SetWorldLocation(Location);

        //in case the model has to be rotated        
        FVector RootLocation = body->GetComponentLocation();
        FVector AttachedLocation = NewSkeletalMeshComponent->GetComponentLocation();
        FVector Direction = (AttachedLocation - RootLocation).GetSafeNormal();
        FRotator DesiredRotation = FRotator(0.0f, FMath::RadiansToDegrees(FMath::Atan2(Direction.Y, Direction.X)), 0.0f);

        // Add the desired angle to the Z-component of the rotator
        float NewZAngle = DesiredRotation.Yaw + 0;

        // Ensure the angle stays within the range [-180, 180] degrees
        NewZAngle = FMath::FindDeltaAngleDegrees(0.0f, NewZAngle);

                
        // Apply the rotation to the component's transform
        NewSkeletalMeshComponent->SetWorldRotation(FRotator(DesiredRotation.Pitch, NewZAngle, DesiredRotation.Roll));

        //Add Physics Constraint
        UPhysicsConstraintComponent* physComponent = Cast<UPhysicsConstraintComponent>(AddComponentByClass(UPhysicsConstraintComponent::StaticClass(), false, LocationTransform, false));
        physComponent->SetWorldLocation(Location);
        FName nearestBoneHit = GetNearestBone(Location);

        physComponent->SetConstrainedComponents(NewSkeletalMeshComponent, TEXT("Bone"), body, nearestBoneHit);

        NewSkeletalMeshComponent->OnComponentHit.AddDynamic(this, &AEnemyCharacter::OnHit);
        
        NewSkeletalMeshComponent->OnComponentDestroyedEvent.AddDynamic(this, &AEnemyCharacter::OnSpiderLimbDestroyed);
     

        //Add Leg and constraint to their arrays
        SpiderLegs.Add(NewSkeletalMeshComponent);
        PhysConstraints.Add(physComponent);

        //increase hp by leg number
        hp += 100;
        maxHP = hp;
    }
    
}

void AEnemyCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!CanBeDamaged())
    {
        UE_LOG(LogTemp, Warning, TEXT("cannotBeDamaged"));
        return;
    }
    else UE_LOG(LogTemp, Warning, TEXT("canBeDamaged"));
    UE_LOG(LogTemp, Warning, TEXT("Component Hit!"));

    ULimbSkeletalMeshComponent* limb = Cast<ULimbSkeletalMeshComponent>(HitComponent);
    //AActor* other = Cast<AProjectile>(OtherComp);
    if (limb && Cast<AProjectile>(OtherActor))
    {
        limb->ReceiveDamage(50);
    }
    else if (Cast<AProjectile>(OtherActor))
    {
        ReceiveDamage(50);
    }
}

void AEnemyCharacter::OnSpiderLimbDestroyed(ULimbSkeletalMeshComponent* DestroyedComponent)
{
    NiagaraComponent = Cast<UNiagaraComponent>(AddComponentByClass(UNiagaraComponent::StaticClass(), false, this->GetTransform(), false));
    //NiagaraComponent->SetupAttachment(DestroyedComponent, TEXT("Bone"));
    NiagaraComponent->AttachToComponent(DestroyedComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Bone"));
    NiagaraComponent->SetAsset(NiagaraSystem);
    NiagaraComponent->bAutoActivate = true;
    //DestroyedComponent
    // Handle the skeletal mesh component destruction
    int32 Index = SpiderLegs.IndexOfByKey(DestroyedComponent);
    if (Index != INDEX_NONE)
    {
        UE_LOG(LogTemp, Warning, TEXT("Skeletal mesh component has been destroyed %s"), *SpiderLegs[Index]->GetName());
        SpiderLegs.RemoveAt(Index);
         
        UE_LOG(LogTemp, Warning, TEXT("Constraint component has been destroyed %s"), *PhysConstraints[Index]->GetName());
        PhysConstraints[Index]->DestroyComponent();
        PhysConstraints.RemoveAt(Index);

        ReceiveDamage(200);

        OnLegRemoved();
    }
    

}



FName AEnemyCharacter::GetNearestBone(const FVector& HitLocation)
{
    if (!body)
    {
        return NAME_None;
    }

    float NearestDistance = FLT_MAX;
    FName NearestBoneName = NAME_None;

    for (const FName& BoneName : body->GetAllSocketNames())
    {
        if (BoneName == TEXT("SPineBackward_03") || BoneName == TEXT("SPineForward_03")) continue; //Bones with no physic asset shape
        FVector BoneLocation = body->GetSocketLocation(BoneName);
        float Distance = FVector::Dist(BoneLocation, HitLocation);
        if (Distance < NearestDistance)
        {
            NearestDistance = Distance;
            NearestBoneName = BoneName;
        }
    }

    return NearestBoneName;
}



void AEnemyCharacter::ReceiveDamage(int32 damage)
{
    hp -= damage;

    if (hp <= 0)
    {
        Cast<UCapsuleComponent>(GetRootComponent())->SetCollisionResponseToAllChannels(ECR_Ignore);
        
        body->SetSimulatePhysics(true);
        for (ULimbSkeletalMeshComponent* leg : SpiderLegs)
        {
            leg->DettachAndDestroy();
        }

        for (UPhysicsConstraintComponent* constraint : PhysConstraints)
        {
            UE_LOG(LogTemp, Warning, TEXT("Constraint component has been destroyed %s"), *constraint->GetName());
            constraint->RemoveFromRoot();
            
            //constraint->DestroyComponent();
            
        }
    }
}