#include "Character/CCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GAS/CAbilitySystemComponent.h"
#include "GAS/CAttributeSet.h"

ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CAbilitySystemComponent = CreateDefaultSubobject<UCAbilitySystemComponent>(TEXT("CAbility System Component"));
	CAttributeSet = CreateDefaultSubobject<UCAttributeSet>(TEXT("CAttribute Set"));
}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* ACCharacter::GetAbilitySystemComponent() const
{
	return CAbilitySystemComponent;
}

void ACCharacter::ServerSideInit()
{
	if (CAbilitySystemComponent)
	{
		CAbilitySystemComponent->InitAbilityActorInfo(this, this);
		CAbilitySystemComponent->ApplyInitialEffects();
	}
}

void ACCharacter::ClientSideInit()
{
	if (CAbilitySystemComponent)
	{
		CAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

}


