// Fill out your copyright notice in the Description page of Project Settings.


#include "ShaderProgressLibrary.h"
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
		
	}
	return (InitialJobCount > 0) ? 1.0f - (float)Remaining / (float)InitialJobCount : 1.0f; 
}

