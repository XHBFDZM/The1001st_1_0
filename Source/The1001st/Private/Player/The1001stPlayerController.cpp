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
	//���bReplicates����������Ϸ�еĸ��ƹ��ܣ��������ϵı仯����Ŀǰ��ʱ��֪��
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
}

void AThe1001stPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//���ԣ����û��ָ������ֱ�Ӳ�������Ϸ
	check(The1001stContext);

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (SubSystem)
	{
		SubSystem->AddMappingContext(The1001stContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	//�������ӿ�
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//���񲻻����ع�ꣿ��ɶ��˼
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
		//�õ�Spline�����ɫ����ĵ�
		FVector ClosestLocation = SplineComponent->FindLocationClosestToWorldLocation(CurPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		//�õ�����Spline�յ�����߷���
		FVector Direction = SplineComponent->FindDirectionClosestToWorldLocation(ClosestLocation, ESplineCoordinateSpace::World);
		//�ƶ�
		CurPawn->AddMovementInput(Direction, 1.0f, false);
		//������С��Limit��ͣ����
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
	//�ϴε������ε����ͬһ����Ϊ��
	if (CurActor == PreActor)
	{
		return;
	}
	//�ϴε����Ϊ��
	if (PreActor)
	{
		PreActor->UnhighlightActor();
	}
	//��ε����Ϊ��
	if(CurActor)
	{
		CurActor->HighlightActor();
	}
}

//����
void AThe1001stPlayerController::InputActionPressed(FGameplayTag GameplayTag)
{
	//�����LeftMouseButton
	if (GameplayTag.MatchesTagExact(FThe1001stGameplayTags::GetThe1001stGameplayTags().Input_LMB))
	{
		bHasTarget = CurActor ? true : false;
		//����һ���Զ��ܲ�
		bAutoRun = false;
	}
}
//��ס
void AThe1001stPlayerController::InputActionHeld(FGameplayTag GameplayTag)
{
	//��������
	if (!GameplayTag.MatchesTagExact(FThe1001stGameplayTags::GetThe1001stGameplayTags().Input_LMB))
	{
		//Ӧ��GA
		if (GetASC())
		{
			GetASC()->InputAbilityHeld(GameplayTag);
		}
		return;
	}

	//�����Ŀ��Actor
	if (bHasTarget)
	{
		//Ӧ��GA
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
//�ɿ�
void AThe1001stPlayerController::InputActionReleased(FGameplayTag GameplayTag)
{
	//��������
	if (!GameplayTag.MatchesTagExact(FThe1001stGameplayTags::GetThe1001stGameplayTags().Input_LMB))
	{
		//Ӧ��GA
		if (GetASC())
		{
			GetASC()->InputAbilityReleased(GameplayTag);
		}
		return;
	}

	//�����Ŀ��Actor
	if (bHasTarget)
	{
		//Ӧ��GA
		if (GetASC())
		{
			GetASC()->InputAbilityReleased(GameplayTag);
		}
		return;
	}

	APawn* CurPawn = GetPawn();
	//˵���ǵ㰴
	if (CurPawn && HeldDurationTime <= LongPressTimeLimit)
	{
		UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, CurPawn->GetActorLocation(), CashedDestination, CurPawn);
		
		SplineComponent->ClearSplinePoints();
		for (const FVector& NavPoint : NavPath->PathPoints)
		{
			SplineComponent->AddSplinePoint(NavPoint,ESplineCoordinateSpace::World);
		}
		//��ֹ����û�е�������ĵط�һֱ�ƶ�
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