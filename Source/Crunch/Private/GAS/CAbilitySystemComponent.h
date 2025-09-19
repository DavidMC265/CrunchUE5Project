#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CAbilitySystemComponent.generated.h"


UCLASS()
class UCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void ApplyInitialEffects();

private:
	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;
	
};
