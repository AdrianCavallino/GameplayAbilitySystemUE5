// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ProjectileSpell.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

//#include "Kismet/KismetSystemLibrary.h"


void UProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                       const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//UKismetSystemLibrary::PrintString(this, FString("Activate Ability (C++)"), true, true, FLinearColor::Yellow, 3);

	/* Check for server Authority to spawn projectile (Only allow on server so the client only receive the replication) */
	if(!HasAuthority(&ActivationInfo)) return;

	UAbilityTask_PlayMontageAndWait* AbilityTask_PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, FName(), AnimMontage);
	
	UAbilityTask_WaitGameplayEvent* GameplayEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, EventTag);

	GameplayEvent->EventReceived.AddDynamic(this, &UProjectileSpell::OnEventReceived);

	AbilityTask_PlayMontageAndWait->Activate();
	GameplayEvent->Activate();

	//SpawnProjectile();
}

void UProjectileSpell::OnEventReceived(FGameplayEventData Payload)
{
	SpawnProjectile();
	
	UGameplayAbility::K2_EndAbility();
}

void UProjectileSpell::SpawnProjectile()
{
	if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetSocketLocation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		//TODO: Set the Projectile Rotation
		
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//TODO: Give the projectile GameplayEffectSpec to deal damage to target.
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}
