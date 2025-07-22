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
	void BroadcastInitialValues() override;
	void BindCallbacksToDependencies() override;
public:
	void HealthChanged(const FOnAttributeChangeData& Data);
	void MaxHealthChanged(const FOnAttributeChangeData& Data);
	void ManaChanged(const FOnAttributeChangeData& Data);
	void MaxManaChanged(const FOnAttributeChangeData& Data);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UDataTable> MessageDataTable;
private:
	template<typename T>
	T* GetRowDataByGameplayTag(UDataTable* DataTable,const FGameplayTag& GameplayTag);
public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
	FOnMessageTagSignature OnMessageTagSignature;
};

template<typename T>
inline T* UOverlayMediator::GetRowDataByGameplayTag(UDataTable* DataTable, const FGameplayTag& GameplayTag)
{
	return DataTable->FindRow<T>(GameplayTag.GetTagName(), "anything");
}
