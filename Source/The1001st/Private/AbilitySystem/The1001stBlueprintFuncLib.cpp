// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/The1001stBlueprintFuncLib.h"

#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Mediators/OverlayMediator.h"
#include "UI/Mediators/AttributeMenuMediator.h"
#include "UI/HUD/The1001stHUD.h"
#include "Player/The1001stPlayerState.h"
#include "AbilitySystem/The1001stAbilitySystemComponent.h"
#include "AbilitySystem/The1001stAttributeSet.h"

UOverlayMediator* UThe1001stBlueprintFuncLib::GetOverlayMediator(UObject* WorldContext)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContext, 0);
	if (PlayerController)
	{
		AThe1001stHUD* The1001stHUD = Cast<AThe1001stHUD>(PlayerController->GetHUD());
		AThe1001stPlayerState* The1001stPlayerState = PlayerController->GetPlayerState<AThe1001stPlayerState>();
		if (The1001stHUD && The1001stPlayerState)
		{
			UAbilitySystemComponent* AbilitySystemComponent = The1001stPlayerState->GetAbilitySystemComponent();
			UAttributeSet* AttributeSet = The1001stPlayerState->GetAttributeSet();
			const FMediatorParams& Params = FMediatorParams(PlayerController, The1001stPlayerState, AbilitySystemComponent, AttributeSet);

 			UOverlayMediator* OverlayMediator = The1001stHUD->GetOverlayMediator(Params);
			return OverlayMediator;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("GetOverlayMediator: PlayerController or The1001stHUD is null!"));
	return nullptr;
}

UAttributeMenuMediator* UThe1001stBlueprintFuncLib::GetAttributeMenuMediator(UObject* WorldContext)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContext, 0);
	if (PlayerController)
	{
		AThe1001stHUD* The1001stHUD = Cast<AThe1001stHUD>(PlayerController->GetHUD());
		AThe1001stPlayerState* The1001stPlayerState = PlayerController->GetPlayerState<AThe1001stPlayerState>();
		if (The1001stHUD && The1001stPlayerState)
		{
			UAbilitySystemComponent* AbilitySystemComponent = The1001stPlayerState->GetAbilitySystemComponent();
			UAttributeSet* AttributeSet = The1001stPlayerState->GetAttributeSet();
			const FMediatorParams& Params = FMediatorParams(PlayerController, The1001stPlayerState, AbilitySystemComponent, AttributeSet);

			UAttributeMenuMediator* AttributeMenuMediator = The1001stHUD->GetAttributeMenuMediator(Params);
			return AttributeMenuMediator;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("GetAttributeMenuMediator: PlayerController or The1001stHUD is null!"));
	return nullptr;
}
