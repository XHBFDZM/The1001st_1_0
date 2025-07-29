// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"

#include "GameplayTagContainer.h"
#include "Input/DA_InputConfig.h"
#include "The1001stGameplayTags.h"

#include "The1001stEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class THE1001ST_API UThe1001stEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class OwnerClass, typename PressedFuncType, typename HeldFuncType, typename ReleasedFuncType>
	void BindOwnActions(const UDA_InputConfig* InputConfigs, OwnerClass* Object, PressedFuncType PressedFunc, HeldFuncType HeldFunc, ReleasedFuncType ReleasedFunc);
};

template<class OwnerClass, typename PressedFuncType, typename HeldFuncType, typename ReleasedFuncType>
inline void UThe1001stEnhancedInputComponent::BindOwnActions(const UDA_InputConfig* InputConfigs, OwnerClass* Object, PressedFuncType PressedFunc, HeldFuncType HeldFunc, ReleasedFuncType ReleasedFunc)
{
	for (const FInputConfig& InputConfig : InputConfigs->InputConfigs)
	{
		if (InputConfig.InputAction && InputConfig.GameplayTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(InputConfig.InputAction, ETriggerEvent::Started, Object, PressedFunc, InputConfig.GameplayTag);
			}
			if (HeldFunc)
			{
				BindAction(InputConfig.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, InputConfig.GameplayTag);
			}
			if (ReleasedFunc)
			{
				BindAction(InputConfig.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, InputConfig.GameplayTag);
			}
		}
	}
}
