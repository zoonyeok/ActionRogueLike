// Fill out your copyright notice in the Description page of Project Settings.


#include "RCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARCharacter::ARCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f,0.f,-90.f), FRotator(0.f,-90.f,0.f));

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.f;
	SpringArmComp->SetRelativeRotation(FRotator(-15.f,0.f,0.f));

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Character(TEXT("Content/ParagonGideon/Characters/Heroes/Gideon/Meshes/Gideon.uasset"));
	if (SK_Character.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Character.Object);
	}
}

// Called when the game starts or when spawned
void ARCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(),Value);
}

// Called every frame
void ARCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&ARCharacter::MoveForward);

	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);

}

