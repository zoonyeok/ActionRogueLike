// Fill out your copyright notice in the Description page of Project Settings.

#include "RExplosiveBarrel.h"
#include "Components/SphereComponent.h"

// Sets default values
ARExplosiveBarrel::ARExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ARExplosiveBarrel::OnOverlapBegin);
	SphereComp->SetSphereRadius(1000.f);
	RootComponent = SphereComp;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(SphereComp);
}

void ARExplosiveBarrel::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	
	if (OtherActor == nullptr || OtherActor == this || OtherComp == nullptr)
		return;

	const FVector Start = GetActorLocation();
	const FVector End = GetActorLocation();
	TArray<FHitResult> Hits;
	const FCollisionShape Sphere = FCollisionShape::MakeSphere(SphereComp->GetScaledSphereRadius());
	
	bool bHit = GetWorld()->SweepMultiByChannel(Hits,Start,End,FQuat::Identity,ECC_WorldDynamic,Sphere);
	if (bHit)
	{
		for(const FHitResult& Hit : Hits)
		{
			Hit.Component->AddRadialForce(GetActorLocation(),100000.f,1000000.f, ERadialImpulseFalloff::RIF_Constant,true);
		}
	}
}
