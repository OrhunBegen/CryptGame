// Fill out your copyright notice in the Description page of Project Settings.


#include "MoverCode.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMoverCode::UMoverCode()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoverCode::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
}


// Called every frame
void UMoverCode::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const AActor *Owner= GetOwner();

	const FString Name = *Owner->GetActorNameOrLabel();
	const FString Location = Owner->GetActorLocation().ToString();
	
//	UE_LOG(LogTemp, Warning, TEXT("gotten component: %s, %s"), *Name, *Location);
	

	if(SMove)
	{
		FVector CurrentLocation = GetOwner()-> GetActorLocation();
	
		FVector TargetLocation =OriginalLocation + MoveOffset;
	
		float Speed = FVector::Distance(OriginalLocation, TargetLocation)/ MoveTime;
		
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation , TargetLocation, DeltaTime, Speed);

		GetOwner()->SetActorLocation(NewLocation);
		
	}

}

