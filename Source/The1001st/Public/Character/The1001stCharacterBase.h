// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"

#include "Interaction/CombatInterface.h"

#include "The1001stCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;

UCLASS(Abstract)
class THE1001ST_API AThe1001stCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AThe1001stCharacterBase();

protected:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
protected:
	virtual void InitAbilityInfo();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attibutes")
	TSubclassOf<UGameplayEffect> PrimaryAttributeInitialEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attibutes")
	TSubclassOf<UGameplayEffect> SecondaryAttributeInitialEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attibutes")
	TSubclassOf<UGameplayEffect> VitalAttributeInitialEffect;
	void ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float Level) const;
	void InitializeDefaultAttributes() const;
};
