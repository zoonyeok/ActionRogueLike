// Fill out your copyright notice in the Description page of Project Settings.


#include "RInteractionComponent.h"
#include "RGamePlayInterface.h"
#include "EngineUtils.h"


// Sets default values for this component's properties
URInteractionComponent::URInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner(); // Character

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation,EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);
	
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(Hit,EyeLocation,End,ObjectQueryParams);

	AActor* HitActor = Hit.GetActor();
	if (HitActor)
	{
		if (HitActor->Implements<URGamePlayInterface>())
		{
			APawn* MyPawn = Cast<APawn>(MyOwner);
			
			IRGamePlayInterface::Execute_Interact(HitActor,MyPawn);
		}
	}
}

