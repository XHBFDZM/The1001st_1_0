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

		//当Medaiator里的四个参数初始化好以后，绑定AS的委托
		OverlayMediator->BindCallbacksToDependencies();

		return OverlayMediator;
	}
	return OverlayMediator;
}

void AThe1001stHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	//Prefab只需要知道Mediator
	//Mediator需要知道Controller，State，ASC，AS
	//HUD现在Prefab和Mediator都有了,都是在HUD里创建的

	checkf(OverlayPrefabClass, TEXT("OverlayPrefabClass is Null"));
	checkf(OverlayMediatorClass, TEXT("OverlayMediatorClass is Null"))

	//添加了Prefab
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	UUserWidget* UserWidget = CreateWidget<UUserWidget>(World, OverlayPrefabClass);
	//Cast了Prefab
	OverlayPrefab = Cast<UBasePrefab>(UserWidget);
	//Mediator的结构体，在HUD(Module)里创建了Mediator
	const FMediatorParams MediatorParams(PC, PS, ASC, AS);
	OverlayMediator = GetOverlayMediator(MediatorParams);
	//Prefab里设置了Mediator引用
	OverlayPrefab->SetOwnerMediator(OverlayMediator);
	//Mediator广播初始值
	OverlayMediator->BroadcastInitialValues();

	//添加Prefab到视口
	UserWidget->AddToViewport();
}
