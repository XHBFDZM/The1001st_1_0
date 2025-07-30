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

/*��������Mouse�õ��ĵ���ת�����Ľӿ�*/
private:
	void CursorTrace();
	IEnemyInterface* CurActor;
	IEnemyInterface* NowActor;

/*��������GameplayAbility������󶨺�����ÿ����Input�йص�Ability��������ǿ���������һ��GaemplayTag���ʴ���GameplayTag����ӳ��*/
private:
	void InputActionPressed(FGameplayTag GameplayTag);
	void InputActionHeld(FGameplayTag GameplayTag);
	void InputActionReleased(FGameplayTag GameplayTag);
/*DA_InputConfigs��ר�������� GameplayTag->InputAction ��DataAsset*/
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputConfig")
	TObjectPtr<UDA_InputConfig> DA_InputConfigs;

/*PlayerController�д��һ��ASCָ�룬ͨ��BlueprintLib���*/
public:
	TObjectPtr<UThe1001stAbilitySystemComponent> ASC = nullptr;
	UThe1001stAbilitySystemComponent* GetASC();
};
