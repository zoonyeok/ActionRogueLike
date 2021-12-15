// Fill out your copyright notice in the Description page of Project Settings.


#include "RInteractionComponent.h"
#include "DrawDebugHelpers.h"
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

	FVector End = EyeLocation + (EyeRotation.Vector() * 200);
	
	//FHitResult Hit;
	///bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit,EyeLocation,End,ObjectQueryParams);

	float Radius = 30.f;
	TArray<FHitResult> Hits;
	FCollisionShape Sphere;
	Sphere.SetSphere(30.f);
	
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits,EyeLocation,End,FQuat::Identity,ObjectQueryParams,Sphere);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	if (bBlockingHit)
	{
		for(FHitResult Hit : Hits)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor)
			{
				if (HitActor->Implements<URGamePlayInterface>())
				{
					APawn* MyPawn = Cast<APawn>(MyOwner);
			
					IRGamePlayInterface::Execute_Interact(HitActor,MyPawn);
					break;
				}
			}
			DrawDebugSphere(GetWorld(),Hit.ImpactPoint,Radius,32,LineColor,false,2.0f);
		}
	}
	
	DrawDebugLine(GetWorld(),EyeLocation,End,LineColor,false,2.0f,0,2.0f);
}

