// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RAttributeComponent.h"
#include "GameFramework/Character.h"
#include "RCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class URInteractionComponent;
class UAnimMontage;

UCLASS()
class ACTIONROGUELIKE_API ARCharacter : public ACharacter
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere,Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere,Category = "Attack")
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;
	

public:
	// Sets default values for this character's properties
	ARCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp; 

	UPROPERTY(VisibleAnywhere)
	URInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Components")
	URAttributeComponent* AttributeComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void PrimaryAttack();
	void PrimaryAttack_TimeElaped();
	
	void PrimaryInteract();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
