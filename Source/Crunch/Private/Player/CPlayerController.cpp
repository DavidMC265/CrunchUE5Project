#include "Player/CPlayerController.h"
#include "Player/CPlayerCharacter.h"
#include "Widgets/GameplayWidget.h"

void ACPlayerController::OnPossess(APawn* NewPawn)
{
    Super::OnPossess(NewPawn);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(0, 4.0f, FColor::Green, TEXT("On Posses called!!"));
    }

    CPlayerCharacter = Cast<ACPlayerCharacter>(NewPawn);
    if (CPlayerCharacter)
    {
        CPlayerCharacter->ServerSideInit();
    }
}

void ACPlayerController::AcknowledgePossession(APawn* NewPawn)
{
    Super::AcknowledgePossession(NewPawn);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(0, 4.0f, FColor::Yellow, TEXT("AcknowledgePossession called!!"));
    }

    CPlayerCharacter = Cast<ACPlayerCharacter>(NewPawn);
    if (CPlayerCharacter)
    {
        CPlayerCharacter->ClientSideInit();
        SpawnGameplayWiget();
    }
}

void ACPlayerController::SpawnGameplayWiget()
{
    if (!IsLocalPlayerController()) { return; }

    GameplayWidget = CreateWidget<UGameplayWidget>(this, GameplayWidgetClass);
    if (GameplayWidget)
    {
        GameplayWidget->AddToViewport();
    }

}

