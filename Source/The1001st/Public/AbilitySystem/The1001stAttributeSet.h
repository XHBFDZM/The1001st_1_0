// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AttributeSet.h"
#include "AbilitySystem/The1001stAbilitySystemComponent.h"

#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"

#include "The1001stAttributeSet.generated.h"

 #define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
//Just һ���ṹ�� about Effect�������Ϣ
USTRUCT()
struct FEffectProperties {
	GENERATED_BODY()
	FEffectProperties(){}
	//��Դ
	UPROPERTY()
	ACharacter* SourceCharacter;
	UPROPERTY()
	AController* SourceController;
	UPROPERTY()
	UAbilitySystemComponent* SourceASC;
	UPROPERTY()
	AActor* SourceAvatorActor;
	//Ŀ��
	UPROPERTY()
	ACharacter* TargetCharacter;
	UPROPERTY()
	AController* TargetController;
	UPROPERTY()
	UAbilitySystemComponent* TargetASC;
	UPROPERTY()
	AActor* TargetAvatorActor;
	//�㱣�������ĸ���
	FGameplayEffectContextHandle EffectContextHandle;
};


UCLASS()
class THE1001ST_API UThe1001stAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UThe1001stAttributeSet();

	//���ڲ�̫��Ҫ֪�������ڸ���
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health,Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, MaxHealth);
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Mana,Category="Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, Mana);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UThe1001stAttributeSet, MaxMana);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
public:
	//����Clamp����
	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	//�����޸�ǰ�ĺ���Deal
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

//����Effect Apply����Ϣ
public:
	FEffectProperties EffectProps;
private:
	void SaveGameplayEffectData(const struct FGameplayEffectModCallbackData& Data, FEffectProperties EffectProperties);
};
