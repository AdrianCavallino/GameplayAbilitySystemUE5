// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

class AAuraPlayerController;
DECLARE_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FVector&);

/**
 * 
 */
UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()

public:
	FMouseTargetDataSignature ValidData;
	
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "TargetDataUnderMouse",  HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility, AAuraPlayerController* OwningController);

	virtual void Activate() override;

private:
	UPROPERTY()
	TObjectPtr<AAuraPlayerController> CurrentController;


	void SendMouseCursorData();
	
	
};
