// Fill out your copyright notice in the Description page of Project Settings.


#include "The1001st/Public/Player/The1001stPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

#include "Input/The1001stEnhancedInputComponent.h"

#include "AbilitySystem/The1001stAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "The1001stGameplayTags.h"

#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Components/SplineComponent.h"


AThe1001stPlayerController::AThe1001stPlayerController()
{
	bReplicates = true;
	//这个bReplicates用作多人游戏中的复制功能（服务器上的变化），目前暂时不知道
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
}

void AThe1001stPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//断言，如果没有指定输入直接不继续游戏
	check(The1001stContext);

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (SubSystem)
	{
		SubSystem->AddMappingContext(The1001stContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	//不锁定视口
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//捕获不会隐藏光标？？啥意思
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AThe1001stPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UThe1001stEnhancedInputComponent* The1001stEnhancedInputComponent = CastChecked<UThe1001stEnhancedInputComponent>(InputComponent);

	The1001stEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AThe1001stPlayerController::Move);

	The1001stEnhancedInputComponent->BindOwnActions(DA_InputConfigs, this, &AThe1001stPlayerController::InputActionPressed, &AThe1001stPlayerController::InputActionHeld, &AThe1001stPlayerController::InputActionReleased);
}

void AThe1001stPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	const FRotator WorldRotation = GetControlRotation();
	const FRotator YawRotation = FRotator(0.0f,WorldRotation.Yaw,0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AThe1001stPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	AutoRun();
}

void AThe1001stPlayerController::AutoRun()
{
	if (!bAutoRun)
	{
		return;
	}
	APawn* CurPawn = GetPawn();
	if (CurPawn)
	{
		//拿到Spline上离角色最近的点
		FVector ClosestLocation = SplineComponent->FindLocationClosestToWorldLocation(CurPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		//拿到朝向Spline终点的切线方向
		FVector Direction = SplineComponent->FindDirectionClosestToWorldLocation(ClosestLocation, ESplineCoordinateSpace::World);
		//移动
		CurPawn->AddMovementInput(Direction, 1.0f, false);
		//如果相差小于Limit，停下来
		if ((CashedDestination - ClosestLocation).Length() <= MoveRediusLimit)
		{
			bAutoRun = false;
		}
	}
}

void AThe1001stPlayerController::CursorTrace()
{
	this->GetHitResultUnderCursor(ECC_Visibility, false, this->HitResult);
	if(!HitResult.bBlockingHit)
	{
		return;
	}
	PreActor = CurActor;
	CurActor = Cast<IEnemyInterface>(HitResult.GetActor());
	//上次点击和这次点击是同一个或都为空
	if (CurActor == PreActor)
	{
		return;
	}
	//上次点击不为空
	if (PreActor)
	{
		PreActor->UnhighlightActor();
	}
	//这次点击不为空
	if(CurActor)
	{
		CurActor->HighlightActor();
	}
}

//按下
void AThe1001stPlayerController::InputActionPressed(FGameplayTag GameplayTag)
{
	//如果是LeftMouseButton
	if (GameplayTag.MatchesTagExact(FThe1001stGameplayTags::GetThe1001stGameplayTags().Input_LMB))
	{
		bHasTarget = CurActor ? true : false;
		//重置一下自动跑步
		bAutoRun = false;
	}
}
//按住
void AThe1001stPlayerController::InputActionHeld(FGameplayTag GameplayTag)
{
	//非鼠标左键
	if (!GameplayTag.MatchesTagExact(FThe1001stGameplayTags::GetThe1001stGameplayTags().Input_LMB))
	{
		//应用GA
		if (GetASC())
		{
			GetASC()->InputAbilityHeld(GameplayTag);
		}
		return;
	}

	//如果有目标Actor
	if (bHasTarget)
	{
		//应用GA
		if (GetASC())
		{
			GetASC()->InputAbilityHeld(GameplayTag);
		}
		return;
	}

	if (APawn* CurPawn = GetPawn())
	{
		HeldDurationTime += GetWorld()->DeltaTimeSeconds;

		if (HitResult.bBlockingHit)
		{
			CashedDestination = HitResult.ImpactPoint;

			const FVector& CurDirection = (CashedDestination - CurPawn->GetActorLocation()).GetSafeNormal();

			CurPawn->AddMovementInput(CurDirection, 1.0f, false);
		}
	}
}
//松开
void AThe1001stPlayerController::InputActionReleased(FGameplayTag GameplayTag)
{
	//非鼠标左键
	if (!GameplayTag.MatchesTagExact(FThe1001stGameplayTags::GetThe1001stGameplayTags().Input_LMB))
	{
		//应用GA
		if (GetASC())
		{
			GetASC()->InputAbilityReleased(GameplayTag);
		}
		return;
	}

	//如果有目标Actor
	if (bHasTarget)
	{
		//应用GA
		if (GetASC())
		{
			GetASC()->InputAbilityReleased(GameplayTag);
		}
		return;
	}

	APawn* CurPawn = GetPawn();
	//说明是点按
	if (CurPawn && HeldDurationTime <= LongPressTimeLimit)
	{
		UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, CurPawn->GetActorLocation(), CashedDestination, CurPawn);
		
		SplineComponent->ClearSplinePoints();
		for (const FVector& NavPoint : NavPath->PathPoints)
		{
			SplineComponent->AddSplinePoint(NavPoint,ESplineCoordinateSpace::World);
		}
		//防止按到没有导航网格的地方一直移动
		CashedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
		bAutoRun = true;
	}
	HeldDurationTime = 0.0f;
	bHasTarget = false;
}

UThe1001stAbilitySystemComponent* AThe1001stPlayerController::GetASC()
{
	if (!ASC)
	{
		ASC = Cast<UThe1001stAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return ASC;
}