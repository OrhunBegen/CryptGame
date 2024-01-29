// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	UPhysicsHandleComponent* PhysicsHandle =  GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle != nullptr)
	{
		UE_LOG(LogTemp, Display , TEXT("%s"),	*PhysicsHandle->GetName() );
	}
	else
	{
		UE_LOG(LogTemp, Warning , TEXT("No Physics Handle Component found on") );
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Released Grabber"));
}

void UGrabber::Grab()
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector()*MaxGrabDistance;
	
	UE_LOG(	LogTemp, Display, TEXT("Grabber Location: %s , %s"), *Start.ToString(), *End.ToString());
	
	//DrawDebugSphere(GetWorld(), End , 10, 10, FColor::Blue, false, 5);
	//DrawDebugLine(GetWorld(),Start, End, FColor::Red , false , 5);
	
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	FHitResult HitResult;
	
	bool HasHit = GetWorld()->SweepSingleByChannel
	    (
		HitResult,
		Start,End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
		);

	if (HasHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.Location ,10 , 10, FColor::Green, false, 5 );
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint ,10 , 10, FColor::Red, false, 5 );
		AActor* HitActor = HitResult.GetActor();

		UE_LOG (LogTemp, Display , TEXT("Hitted Actor name: %s"), *HitActor->GetActorNameOrLabel());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Actor Hit"));
	}
}

