// Fill out your copyright notice in the Description page of Project Settings.


#include "RMagicProjectile.h"

#include "RAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ARMagicProjectile::ARMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	// SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	// SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	// SphereComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ARMagicProjectile::OnActorBeginOverlap);
	//SphereComp->OnComponentHit.AddDynamic(this, &ARMagicProjectile::OnHit);	// 알림 설정 for when this component hits something blocking
	
	SphereComp->SetCollisionProfileName("Projectile"); // 프로젝트 세팅에서 설정시 사용
	
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComp"));
	EffectComp->SetupAttachment(SphereComp);

	MovementComp  = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

}

void ARMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// 팀원 체크 
void ARMagicProjectile::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult)
{
	// 자기가 쏜 Projectile과 충돌 방지 : OtherActor != GetInstigator()
	if (OtherActor && OtherActor != GetInstigator())
	{
		URAttributeComponent* AttributeComp = Cast<URAttributeComponent>(OtherActor->GetComponentByClass(URAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.f);

			//UE_LOG(LogTemp, Log, TEXT("HealthChanged to : %f"), AttributeComp->GetHealth());

			Destroy();
		}
	}

	// if (OtherComp->IsSimulatingPhysics())
	// {
	// 	OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	//
	// 	
	// }
	
}
