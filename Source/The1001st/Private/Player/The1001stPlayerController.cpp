// Fill out your copyright notice in the Description page of Project Settings.


#include "The1001st/Public/Player/The1001stPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

#include "Input/The1001stEnhancedInputComponent.h"


AThe1001stPlayerController::AThe1001stPlayerController()
{
	bReplicates = true;
	//���bReplicates����������Ϸ�еĸ��ƹ��ܣ��������ϵı仯����Ŀǰ��ʱ��֪��
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
}

void AThe1001stPlayerController::CursorTrace()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if(!HitResult.bBlockingHit)
	{
		return;
	}
	CurActor = NowActor;
	NowActor= Cast<IEnemyInterface>(HitResult.GetActor());
	//�ϴε������ε����ͬһ����Ϊ��
	if (CurActor == NowActor)
	{
		return;
	}
	//�ϴε����Ϊ��
	if (CurActor)
	{
		CurActor->UnhighlightActor();
	}
	//��ε����Ϊ��
	if(NowActor)
	{
		NowActor->HighlightActor();
	}
}

void AThe1001stPlayerController::InputActionPressed(FGameplayTag GameplayTag)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green, FString::Printf(TEXT("Pressed: %s"), *GameplayTag.ToString()));
	}
}

void AThe1001stPlayerController::InputActionHeld(FGameplayTag GameplayTag)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, FString::Printf(TEXT("Held: %s"), *GameplayTag.ToString()));
	}
}

void AThe1001stPlayerController::InputActionReleased(FGameplayTag GameplayTag)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, FString::Printf(TEXT("Released: %s"), *GameplayTag.ToString()));
	}
}
