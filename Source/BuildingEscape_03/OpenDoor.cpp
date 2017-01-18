// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape_03.h"
#include "OpenDoor.h"

#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	float CurrentActorMass = 0.f;

	// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Iterate through them adding their masses
	for (auto& Actor : OverlappingActors)
	{
		CurrentActorMass = Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		TotalMass += CurrentActorMass;
		UE_LOG(LogTemp, Warning, TEXT("Actor %s weights %f!"), *Actor->GetName(), CurrentActorMass);
		UE_LOG(LogTemp, Warning, TEXT("The total mass on the pressure plate is %f"), TotalMass);
	}

	return TotalMass;
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the Trigger Volume
	if (GetTotalMassOfActorsOnPlate() > TriggerMass)
	{
		OnOpen.Broadcast();
	}
	else 
	{
		OnClose.Broadcast();
	}
}