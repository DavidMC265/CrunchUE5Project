#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) 

UCLASS()
class UCAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	ATTRIBUTE_ACCESSORS(UCAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UCAttributeSet, MaxHealth);

	ATTRIBUTE_ACCESSORS(UCAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS(UCAttributeSet, MaxMana);

	virtual void GetLifetimeReplicatedProps(TArray < class FLifetimeProperty > & OutLifetimeProps) const override;  

private:
	UPROPERTY(ReplicatedUsing = On_RepHealth)
	FGameplayAttributeData Health;
	UPROPERTY(ReplicatedUsing = On_RepMaxHealth)
	FGameplayAttributeData MaxHealth;
	UPROPERTY(ReplicatedUsing = On_RepMana)
	FGameplayAttributeData Mana;
	UPROPERTY(ReplicatedUsing = On_RepMaxMana)
	FGameplayAttributeData MaxMana;
	
	UFUNCTION()
	void On_RepHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void On_RepMaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void On_RepMana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void On_RepMaxMana(const FGameplayAttributeData& OldValue);
};
