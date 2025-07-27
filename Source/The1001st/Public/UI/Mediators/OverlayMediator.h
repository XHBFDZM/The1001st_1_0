// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Mediators/BaseMediator.h"

#include "UI/Prefabs/BasePrefab.h"

#include "AbilitySystem/The1001stAttributeSet.h"

#include "OverlayMediator.generated.h"

USTRUCT(BlueprintType)
struct FMessageTagRow : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Text = FText();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UBasePrefab> Widget = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageTagSignature, FMessageTagRow, TagData);

class UThe1001stAbilitySystemComponent;
class UGameplayEffectTypes;
/**
 * 
 */

UCLASS()
class THE1001ST_API UOverlayMediator : public UBaseMediator
{
	GENERATED_BODY()

public:
	//OverlayMediator需要订阅的签名
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnValueChangeSignature OnHealthValueChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnValueChangeSignature OnMaxHealthValueChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnValueChangeSignature OnManaValueChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnValueChangeSignature OnMaxManaValueChanged;

public:
	void BroadcastInitialValues() override;
	void BindCallbacksToDependencies() override;

public:
	//捡东西Message的签名也放在OverlayMediator
	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
	FOnMessageTagSignature OnMessageTagSignature;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UDataTable> MessageDataTable;
private:
	template<typename T>
	T* GetRowDataByGameplayTag(UDataTable* DataTable,const FGameplayTag& GameplayTag);
};
template<typename T>
inline T* UOverlayMediator::GetRowDataByGameplayTag(UDataTable* DataTable, const FGameplayTag& GameplayTag)
{
	return DataTable->FindRow<T>(GameplayTag.GetTagName(), "anything");
}
