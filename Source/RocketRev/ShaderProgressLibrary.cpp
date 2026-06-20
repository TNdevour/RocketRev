// Fill out your copyright notice in the Description page of Project Settings.


#include "ShaderProgressLibrary.h"

#include "RocketRev.h"
#include "ShaderCompiler.h"

static int32 InitialJobCount = 0;

int32 UShaderProgressLibrary::GetRemainingShaderJobs()
{
	return GShaderCompilingManager ? GShaderCompilingManager->GetNumRemainingJobs() : 0;
}

int32 UShaderProgressLibrary::GetTotalShaderJobs()
{
	return InitialJobCount;
}

float UShaderProgressLibrary::GetShaderCompileProgress()
{
	int32 Remaining = GetRemainingShaderJobs();
	if (InitialJobCount == 0)
	{
		InitialJobCount = Remaining; // store first time
		UE_LOG(MyLog, Display, TEXT("InitialJobCount: %d"), InitialJobCount);
	}
	return (InitialJobCount > 0) ? 1.0f - static_cast<float>(Remaining) / static_cast<float>(InitialJobCount) : 1.0f;
	
}

