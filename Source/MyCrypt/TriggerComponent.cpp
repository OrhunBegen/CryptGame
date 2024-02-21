// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*>Actors;
	
	GetOverlappingActors(Actors);
	
	if(Actors.Num() > 0)
	{
		
		FString Name = Actors[0]->GetActorNameOrLabel();
		
		UE_LOG(LogTemp, Warning, TEXT("Triggered %s"), *Name);
	}

	
}