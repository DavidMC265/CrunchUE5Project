#include "Player/CPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


ACPlayerCharacter::ACPlayerCharacter()
{
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
    CameraBoom->SetupAttachment(GetRootComponent());

    ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("View Camera"));
    ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}


void ACPlayerCharacter::PawnClientRestart()
{
    Super::PawnClientRestart();

    // Using PawnClientRestart instead of BeginPlay for inputs

    APlayerController* OwningPlayerController = GetController<APlayerController>();
    if (OwningPlayerController)
    {
        UEnhancedInputLocalPlayerSubsystem* InputSubsystem = OwningPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
        if (OwningPlayerController)
        {
            InputSubsystem->RemoveMappingContext(GameplayInputMappingContext);
            InputSubsystem->AddMappingContext(GameplayInputMappingContext, 0);
        }
    }
}

void ACPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (EnhancedInputComp)
    {
        EnhancedInputComp->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Jump);
    }
}
