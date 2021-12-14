// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RGamePlayInterface.h"
#include "GameFramework/Actor.h"
#include "RItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARItemChest : public AActor , public IRGamePlayInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float TargetPitch;
	
	void Interact_Implementation(APawn* InstigatorPawn);
	
public:	
	// Sets default values for this actor's properties
	ARItemChest();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
