// Copyright Epic Games, Inc. All Rights Reserved.

#include "The1001st/Public/Character/The1001stCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Player/The1001stPlayerState.h"
#include "AbilitySystem/The1001stAbilitySystemComponent.h"
#include "The1001st/Public/Player/The1001stPlayerController.h"
#include "UI/HUD/The1001stHUD.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AThe1001stCharacter

AThe1001stCharacter::AThe1001stCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	
	//Pawn������Controller
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//��Ҫʱ�����ٶȣ�����Ҫ����ֹ������Controller
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	//ʼ�ո����ٶ�
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	//���ɱ۲�����Controller
	CameraBoom->bUsePawnControlRotation = false;
	//Ҳ���̳и����
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AThe1001stCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AThe1001stCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//�ڿ���������Pawn֮�󣬿�ʼInitAbilityInfo

	//InitAbilityActorInfo for the Server
	InitAbilityInfo();
}

void AThe1001stCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//InitAbilityActorInfo for the Client
	InitAbilityInfo();
}

void AThe1001stCharacter::InitAbilityInfo()
{
	// PlayerState���캯����ʼ����ASC��AS��������ָ��
	// ASC�������ʼ��Avator��Owner
	// Character����Ҳ����ASC��AS��ָ�룬ͬʱҲ��Controllerָ�루������п��ƵĿͻ��ˣ�����Ӱ��û�еĻ������ó�ʼ��MVC��
	
	// �õ�PlayerState
	AThe1001stPlayerState* The1001stPlayerState = GetPlayerStateChecked<AThe1001stPlayerState>();
	// Init
	The1001stPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(The1001stPlayerState, this);
	// �ٸ�ֵ������
	AbilitySystemComponent = The1001stPlayerState->GetAbilitySystemComponent();
	AttributeSet = The1001stPlayerState->GetAttributeSet();

	if (AThe1001stPlayerController* The1001stPlayerController = Cast<AThe1001stPlayerController>(GetController()))
	{
		if (AThe1001stHUD* The1001stHUD = Cast<AThe1001stHUD>(The1001stPlayerController->GetHUD()))
		{
			The1001stHUD->InitOverlay(The1001stPlayerController, The1001stPlayerState, AbilitySystemComponent, AttributeSet);
		}

	}
}


