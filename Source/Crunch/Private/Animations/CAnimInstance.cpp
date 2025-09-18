#include "Animations/CAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"


void UCAnimInstance::NativeInitializeAnimation()
{
    OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
    if (OwnerCharacter)
    {
        OwnerMovementComp = OwnerCharacter->GetCharacterMovement();
    }
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{

}

void UCAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
    
}


