// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

class AAuraPlayerController;
DECLARE_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FGameplayAbilityTargetDataHandle&);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseDynamicTargetDataSignature, const FGameplayAbilityTargetDataHandle&, Data);

/**
 * 
 */
UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()

public:
	virtual void Activate() override;
	
	FMouseTargetDataSignature ValidData;

	UPROPERTY(BlueprintAssignable)
	FMouseDynamicTargetDataSignature DynamicValidData;
	
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "TargetDataUnderMouse",  HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility, AAuraPlayerController* OwningController);

	void OnTargetDataDelegateSet(const FGameplayAbilityTargetDataHandle& GameplayAbilityTargetDataHandle, FGameplayTag GameplayTag);

private:
	UPROPERTY()
	TObjectPtr<AAuraPlayerController> CurrentController;


	void SendMouseCursorData();
	
	
};
