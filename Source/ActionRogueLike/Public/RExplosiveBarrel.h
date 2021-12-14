// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RExplosiveBarrel.generated.h"

class USphereComponent;

UCLASS()
class ACTIONROGUELIKE_API ARExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARExplosiveBarrel();

protected:

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
