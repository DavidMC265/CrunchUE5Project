#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"


UCLASS()
class ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//Only called on the server
	void OnPossess(APawn* NewPawn) override;

	//Only called on client and on the listen server
	void AcknowledgePossession(APawn* NewPawn) override;

private:
	UPROPERTY()
	class ACPlayerCharacter* CPlayerCharacter;
	
};
