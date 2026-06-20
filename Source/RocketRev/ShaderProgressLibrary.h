// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ShaderProgressLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ROCKETREV_API UShaderProgressLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** Returns remaining shader compile jobs */     
	UFUNCTION(BlueprintPure, Category="Shaders")     
	static int32 GetRemainingShaderJobs();      
	
	/** Returns total shader jobs (store at start) */     
	UFUNCTION(BlueprintPure, Category="Shaders")     
	static int32 GetTotalShaderJobs();      
	
	/** Returns progress as 0.0 - 1.0 */     
	UFUNCTION(BlueprintPure, Category="Shaders")     
	static float GetShaderCompileProgress(); 
	
};
