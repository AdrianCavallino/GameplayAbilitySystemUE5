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
	}
	
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	//ValidData.Broadcast(CurrentController->GetCursorHit());

	FGameplayAbilityTargetData_LocationInfo* Data = new FGameplayAbilityTargetData_LocationInfo();

	FGameplayAbilityTargetingLocationInfo X;
	X.SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
	X.SourceAbility = Ability;
	X.LocationType = EGameplayAbilityTargetingLocationType::ActorTransform;
	X.SourceComponent = nullptr;
	FTransform LocationInfo;
	LocationInfo.SetLocation(CurrentController->GetCursorHit());
	X.LiteralTransform = LocationInfo;

	Data->TargetLocation = X;

	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(Data);

	//AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), DataHandle, Fga);

	
}
