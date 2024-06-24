// Fill out your copyright notice in the Description page of Project Settings.


#include "ModularEnemy.h"

// Sets default values
AModularEnemy::AModularEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
   // static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Assets/Mesh/Limb/TESTLIMB.TESTLIMB"));
    //meshAsset = MeshAsset.Object;
}

// Called when the game starts or when spawned
void AModularEnemy::BeginPlay()
{
	Super::BeginPlay();
    
}

// Called every frame
void AModularEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AModularEnemy::AddLimb(FVector Location)
{
    //// Create a socket dynamically
    //USkeletalMeshComponent* RootSkeletalMesh = Cast<USkeletalMeshComponent>(RootComponent);
    //
    //USkeletalMeshSocket* NewSocket = CreateSocket(RootSkeletalMesh->SkeletalMesh, Location);
    //// Create a new skeletal mesh component instance
    //UE_LOG(LogTemp, Error, TEXT("Name of socket: %s"), *NewSocket->SocketName.ToString());
    //if (meshAsset)
    //{
    //    ULimbSkeletalMeshComponent* NewSkeletalMeshComponent = NewObject<ULimbSkeletalMeshComponent>(this, meshAsset);
    //    if (NewSkeletalMeshComponent)
    //    {
    //        // Attach the skeletal mesh component to the root component
    //        //NewSkeletalMeshComponent->SetupAttachment(RootComponent, "Body_BoneSocket");
    //        NewSkeletalMeshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, NewSocket->SocketName);
    //        // Register the component
    //        NewSkeletalMeshComponent->RegisterComponent();

    //        NewSkeletalMeshComponent->SetWorldLocation({ Location.X, Location.Y, 0 });

    //        
    //        FVector RootLocation = RootComponent->GetComponentLocation();
    //        FVector AttachedLocation = NewSkeletalMeshComponent->GetComponentLocation();
    //        FVector Direction = (AttachedLocation - RootLocation).GetSafeNormal();
    //        FRotator DesiredRotation = FRotator(0.0f, FMath::RadiansToDegrees(FMath::Atan2(Direction.Y, Direction.X)), 0.0f);

    //        // Add the desired angle to the Z-component of the rotator
    //        float NewZAngle = DesiredRotation.Yaw - 90;

    //        // Ensure the angle stays within the range [-180, 180] degrees
    //        NewZAngle = FMath::FindDeltaAngleDegrees(0.0f, NewZAngle);

    //        
    //        // Apply the rotation to the component's transform
    //        NewSkeletalMeshComponent->SetWorldRotation(FRotator(DesiredRotation.Pitch, NewZAngle, DesiredRotation.Roll));
    //    
    //    
    //        NewSkeletalMeshComponent->OnComponentHit.AddDynamic(this, &AModularEnemy::OnHit);
    //    
    //    }
    //    
    //}
}

//USkeletalMeshSocket* AModularEnemy::CreateSocket(USkeletalMesh* Skeleton, FVector Location)
//{
//    ////Create socket
//    //Skeleton->Modify();
//
//    //USkeletalMeshSocket* NewSocket = NewObject<USkeletalMeshSocket>(Skeleton);
//    //check(NewSocket);
//
//    //NewSocket->BoneName = boneName;
//    //FString socketNum = FString::FromInt(socketNames.Num());
//    //FString SocketName = FString::Printf(TEXT("%sSocket%d"), *NewSocket->BoneName.ToString(), socketNames.Num());
//    //
//    //NewSocket->SocketName = FName(*SocketName);
//    //NewSocket->RelativeScale = FVector{ 1,1,1 };
//    //
//    //
//    //FVector RelativeLocation = this->GetTransform().InverseTransformPosition(Location);
//    //
//    //NewSocket->RelativeLocation = RelativeLocation;
//
//    //socketNames.Add(NewSocket);
//    //Skeleton->AddSocket(NewSocket);
//    //return NewSocket;
//    return;
//}

void AModularEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    UE_LOG(LogTemp, Warning, TEXT("Component Hit!"));

    ULimbSkeletalMeshComponent* limb = Cast<ULimbSkeletalMeshComponent>(HitComponent);

    if (limb)
    {
        limb->ReceiveDamage(50);
    }
}






void AModularEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    USkeletalMesh* Skeleton = Cast<USkeletalMeshComponent>(RootComponent)->SkeletalMesh;


    //Skeleton->AddSocket
    /*Skeleton->Modify();
    Skeleton->
    for (int i = 0; i < socketNames.Num(); i++)
    {
        Skeleton.sock
    }*/
}