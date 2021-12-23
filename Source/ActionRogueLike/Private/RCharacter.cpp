// Fill out your copyright notice in the Description page of Project Settings.


#include "RCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "RMagicProjectile.h"
#include "RInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ARCharacter::ARCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//GetMesh()->SetRelativeLocationAndRotation(FVector(0.f,0.f,-90.f), FRotator(0.f,-90.f,0.f));

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	
	SpringArmComp->TargetArmLength = 250.f;
	//SpringArmComp->SetRelativeRotation(FRotator(-15.f,0.f,0.f));
	SpringArmComp->SocketOffset = FVector(0.f,90.f,0.f);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<URInteractionComponent>(TEXT("InteractionComp"));

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Character(TEXT("SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Meshes/Gideon.Gideon'"));
	// if (SK_Character.Succeeded())
	// {
	// 	GetMesh()->SetSkeletalMesh(SK_Character.Object);
	// }

	AttributeComp = CreateDefaultSubobject<URAttributeComponent>(TEXT("AttributeComp"));
	
}

// Called when the game starts or when spawned
void ARCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame

void ARCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// -- Rotation Visualization -- //
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the actor's forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
	
}

// Called to bind functionality to input
void ARCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&ARCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ARCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);
	
	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ARCharacter::Jump);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ARCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract",IE_Pressed,this, &ARCharacter::PrimaryInteract);
}

void ARCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	FVector Direction = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction,Value);
}

void ARCharacter::MoveRight(float Value)
{
	
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// X = Forward (Red)
	// Y = Right (Green)
	// Z = Up (Blue)

	// 어느 쪽이 전방인지 알아내어 플레이어가 그 방향으로 이동하려 한다고 기록합니다.
	const FVector Direction = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction,Value);
}

void ARCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);
	
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack,this,&ARCharacter::PrimaryAttack_TimeElaped,0.2f);

	// GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void ARCharacter::PrimaryAttack_TimeElaped()
{
	if (ensure(ProjectileClass)) // nullptr이면 exception 발생 ,컴파일시 한 번만 알림 , shipping빌드에서는 사용 안됨 
	{
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		FTransform SpawnTM = FTransform(GetControlRotation(),HandLocation);
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;
		
		GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTM,SpawnParams);
	}
}

void ARCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}
