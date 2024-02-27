// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTask/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ProjectileSpell.h"
#include "Player/AuraPlayerController.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility, AAuraPlayerController* OwningController)
{
	UTargetDataUnderMouse* Obj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);

	Obj->CurrentController = OwningController;
	
	return Obj;
}

void UTargetDataUnderMouse::Activate()
{
	if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
	{
		SendMouseCursorData();
	}
	else
	{
		//TODO: Listen to TargetData because it's on server
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &UTargetDataUnderMouse::OnTargetDataDelegateSet);
		const bool bCalledDelegate =  AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		if(!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
	
}

void UTargetDataUnderMouse::OnTargetDataDelegateSet(
	const FGameplayAbilityTargetDataHandle& GameplayAbilityTargetDataHandle, FGameplayTag GameplayTag)
{
	AbilitySystemComponent.Get()->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(GameplayAbilityTargetDataHandle);
		//DynamicValidData.Broadcast(GameplayAbilityTargetDataHandle);
	}
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

	FGameplayAbilityTargetData_LocationInfo* Data = new FGameplayAbilityTargetData_LocationInfo();

	FGameplayAbilityTargetingLocationInfo X;
	X.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	FTransform LocationInfo;
	LocationInfo.SetLocation(CurrentController->GetCursorHitLocation());
	X.LiteralTransform = LocationInfo;

	Data->TargetLocation = X;

	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(Data);

	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);

	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
		//DynamicValidData.Broadcast(DataHandle);
	}

	
}
