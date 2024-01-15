// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/SpawnProjectileNotify.h"

#include "AbilitySystemBlueprintLibrary.h"

void USpawnProjectileNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                    const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	FGameplayEventData EventData;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, EventData);
	
}
