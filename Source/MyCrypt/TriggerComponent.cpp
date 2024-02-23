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


	if (Mover == nullptr)
	{
		return;
	}

	AActor* Actor =	GetAcceptableActor();
	if (Actor != nullptr)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component != nullptr)
		{
			Component ->SetSimulatePhysics(false);
			
		}
		Actor ->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		Mover -> SetShouldMove(true);
	}
	else
	{
		Mover -> SetShouldMove(false);
	}
}


void UTriggerComponent::SetMover(UMoverCode* NewMover)
{
	Mover = NewMover;
}


AActor* UTriggerComponent::GetAcceptableActor() const
{
	
	TArray<AActor*>Actors;
	GetOverlappingActors(Actors);

	
	for (AActor* Actor : Actors)
	{
		const bool AcceptableTag = Actor->ActorHasTag(TagName);
		const bool GrabbedTag = Actor->ActorHasTag("Grabbed");
		if (AcceptableTag && !GrabbedTag)
		{
			return Actor;
		}
	}
	return nullptr;
}