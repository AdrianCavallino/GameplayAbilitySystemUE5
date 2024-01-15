// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SpawnProjectileNotify.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API USpawnProjectileNotify : public UAnimNotify
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere)
	FGameplayTag EventTag;
	
};
