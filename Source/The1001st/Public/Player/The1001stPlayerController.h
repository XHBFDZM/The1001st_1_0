// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"

#include "GameplayTagContainer.h"
#include "Input/DA_InputConfig.h"

#include "The1001stPlayerController.generated.h"

/**
 * 
 */
class UInputMappingContext;
class IEnemyInterface;
struct FInputActionValue;

class UThe1001stAbilitySystemComponent;


UCLASS()
class THE1001ST_API AThe1001stPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AThe1001stPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> The1001stContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& Value);

/*用作储存Mouse拿到的敌人转换来的接口*/
private:
	void CursorTrace();
	IEnemyInterface* CurActor;
	IEnemyInterface* NowActor;

/*用来触发GameplayAbility的输入绑定函数，每个和Input有关的Ability都会在增强输入组件绑定一个GaemplayTag，故传入GameplayTag来做映射*/
private:
	void InputActionPressed(FGameplayTag GameplayTag);
	void InputActionHeld(FGameplayTag GameplayTag);
	void InputActionReleased(FGameplayTag GameplayTag);
/*DA_InputConfigs是专用作储存 GameplayTag->InputAction 的DataAsset*/
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputConfig")
	TObjectPtr<UDA_InputConfig> DA_InputConfigs;

/*PlayerController中存放一个ASC指针，通过BlueprintLib获得*/
public:
	TObjectPtr<UThe1001stAbilitySystemComponent> ASC = nullptr;
	UThe1001stAbilitySystemComponent* GetASC();
};
