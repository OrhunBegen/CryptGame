// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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
	
	UPhysicsHandleComponent* PhysicsHandle =  GetPhysicsHandle();
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
	
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	
	if (PhysicsHandle && PhysicsHandle-> GetGrabbedComponent())
	{
		
		FVector TargetLocation = GetComponentLocation() + GetForwardVector()*HoldDistance; 
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}

}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle =  GetPhysicsHandle();
	

	if (PhysicsHandle && PhysicsHandle-> GetGrabbedComponent() != nullptr)
	{
		PhysicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
		
		
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
	
	
	//UE_LOG(LogTemp, Warning, TEXT("Released Grabber"));
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle =  GetPhysicsHandle();
	if (PhysicsHandle == nullptr){return;}

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);
	

	if (HasHit)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		HitComponent->SetSimulatePhysics(true);

		AActor* HitActor = HitResult.GetActor();

		
		HitActor->Tags.Add("Grabbed");

		HitActor->DetachFromActor(	FDetachmentTransformRules::KeepWorldTransform);
		
		
		PhysicsHandle->GrabComponentAtLocationWithRotation
				(
				HitComponent,
				NAME_None,
				HitResult.ImpactPoint,
				GetComponentRotation()
				);
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(Result == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Physics Handle Component found "));
		return nullptr;
	}
	else
	{
		return Result;
	}
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector()*MaxGrabDistance;
	
	UE_LOG(	LogTemp, Display, TEXT("Grabber Location: %s , %s"), *Start.ToString(), *End.ToString());
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	
	return GetWorld()->SweepSingleByChannel
		(
		OutHitResult,
		Start,End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
		);
	
}