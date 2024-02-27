// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAssetManager.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "..\Public\AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);

	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitializeGameplayTags();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
