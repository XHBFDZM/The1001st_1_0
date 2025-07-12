// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/The1001stHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Prefabs/BasePrefab.h"

#include "UI/Mediators/OverlayMediator.h"

void AThe1001stHUD::BeginPlay()
{
	Super::BeginPlay();

}

UOverlayMediator* AThe1001stHUD::GetOverlayMediator(const FMediatorParams& Params)
{
	if (OverlayMediator == nullptr)
	{
		OverlayMediator = NewObject<UOverlayMediator>(this, OverlayMediatorClass);
		OverlayMediator->SetParams(Params);

		return OverlayMediator;
	}
	return OverlayMediator;
}

void AThe1001stHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	//Prefabֻ��Ҫ֪��Mediator
	//Mediator��Ҫ֪��Controller��State��ASC��AS
	//HUD����Prefab��Mediator������


	checkf(OverlayPrefabClass, TEXT("OverlayPrefabClass is Null"));
	checkf(OverlayMediatorClass, TEXT("OverlayMediatorClass is Null"))

	//�����Prefab
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	UUserWidget* UserWidget = CreateWidget<UUserWidget>(World, OverlayPrefabClass);
	UserWidget->AddToViewport();
	//Cast��Prefab
	OverlayPrefab = Cast<UBasePrefab>(UserWidget);
	//Mediator�Ľṹ�壬��HUD(Module)�ﴴ����Mediator
	const FMediatorParams MediatorParams(PC, PS, ASC, AS);
	OverlayMediator = GetOverlayMediator(MediatorParams);
	//Prefab��������Mediator����
	OverlayPrefab->SetOwnerMediator(OverlayMediator);
	//���Prefab���ӿ�
	UserWidget->AddToViewport();
}
