// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged,AActor*, InstigatorActor, URAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API URAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URAttributeComponent();

protected:

	// 개별 인스턴스에서는 변수를 숨기고 , BP에디터에서만 수정할 수 있음
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float Health;

	// HealthMax, Stamina, Strength
	// void SetHealth(int InputHealth);
	
public:

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	float GetHealth() const {return Health;}

	UFUNCTION(BlueprintCallable, Category= "Attributes")
	bool ApplyHealthChange(float Delta);
};
