#include "Player/CPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ACPlayerCharacter::ACPlayerCharacter()
{
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
    CameraBoom->SetupAttachment(GetRootComponent());
    CameraBoom->bUsePawnControlRotation = true;

    ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("View Camera"));
    ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

    bUseControllerRotationYaw = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
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
        EnhancedInputComp->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::HandleLookInput);
        EnhancedInputComp->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::HandleMoveInput);
    }
}


void ACPlayerCharacter::HandleLookInput(const FInputActionValue& InputActionValue)
{
    FVector2D InputValue = InputActionValue.Get<FVector2D>();

    AddControllerPitchInput(-InputValue.Y);
    AddControllerYawInput(InputValue.X);
}


void ACPlayerCharacter::HandleMoveInput(const FInputActionValue& InputActionValue)
{
    FVector2D InputValue = InputActionValue.Get<FVector2D>();
    InputValue.Normalize();

    AddMovementInput(GetMoveFwdDir() * InputValue.Y + GetLookRightDir() * InputValue.X);

}

FVector ACPlayerCharacter::GetLookRightDir() const
{
    return ViewCamera->GetRightVector();
}

FVector ACPlayerCharacter::GetLookFwdDir() const
{
    return ViewCamera->GetForwardVector();
}

FVector ACPlayerCharacter::GetMoveFwdDir() const
{
    return FVector::CrossProduct(GetLookRightDir(), FVector::UpVector);
}




