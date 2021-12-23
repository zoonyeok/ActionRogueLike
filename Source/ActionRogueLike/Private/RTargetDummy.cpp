// Fill out your copyright notice in the Description page of Project Settings.


#include "RTargetDummy.h"

// Sets default values
ARTargetDummy::ARTargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<URAttributeComponent>(TEXT("AttributeComp"));
	AttributeComp->OnHealthChanged.AddDynamic(this, &ARTargetDummy::OnHealthChangedInDummy);
}

void ARTargetDummy::OnHealthChangedInDummy(AActor* InstigatorActor, URAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimetoHit",GetWorld()->TimeSeconds);
	}
}
