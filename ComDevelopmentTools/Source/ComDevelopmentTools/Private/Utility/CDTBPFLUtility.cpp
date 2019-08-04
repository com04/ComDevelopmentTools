// Copyright 2018-2019 com04, Inc. All Rights Reserved.

#include "CDTBPFLUtility.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"


// ------------------------------------------------------
// Primitives
// ------------------------------------------------------
/**
 * Simple Collisionが有効か
 */
bool UCDTBPFLUtility::HasCollisionSimple(UPrimitiveComponent* Primitive)
{
	if (!IsValid(Primitive))
	{
		return false;
	}
	// Static Mesh
	UStaticMeshComponent* StaticMeshComp = Cast<UStaticMeshComponent>(Primitive);
	if (StaticMeshComp)
	{
		UStaticMesh* StaticMesh = StaticMeshComp->GetStaticMesh();
		if (StaticMesh)
		{
			if (StaticMesh->BodySetup)
			{
				return StaticMesh->BodySetup->AggGeom.GetElementCount() > 0;
			}
		}
		return false;
	}

	// Skeletal Mesh
	USkeletalMeshComponent* SkeletalMeshComp = Cast<USkeletalMeshComponent>(Primitive);
	if (SkeletalMeshComp)
	{
		if (SkeletalMeshComp->GetBodySetup())
		{
			return SkeletalMeshComp->GetBodySetup()->AggGeom.GetElementCount() > 0;
		}
	}

	return false;
}

/**
 * Complex Collisionが有効か
 */
bool UCDTBPFLUtility::HasCollisionComplex(UPrimitiveComponent* Primitive)
{
	if (!IsValid(Primitive))
	{
		return false;
	}
	// Static Mesh
	UStaticMeshComponent* StaticMeshComp = Cast<UStaticMeshComponent>(Primitive);
	if (StaticMeshComp)
	{
		UStaticMesh* StaticMesh = StaticMeshComp->GetStaticMesh();
		if (StaticMesh)
		{
			if (StaticMesh->BodySetup)
			{
#if WITH_PHYSX
				return StaticMesh->BodySetup->TriMeshes.Num() > 0;
#endif
			}
		}
		return false;
	}

	// Skeletal Mesh
	USkeletalMeshComponent* SkeletalMeshComp = Cast<USkeletalMeshComponent>(Primitive);
	if (SkeletalMeshComp)
	{
		if (SkeletalMeshComp->GetBodySetup())
		{
#if WITH_PHYSX
			return SkeletalMeshComp->GetBodySetup()->TriMeshes.Num() > 0;
#endif
		}
	}

	return false;
}

// ------------------------------------------------------
// Materials
// ------------------------------------------------------
/**
* MaterialのScalarパラメーター情報取得
*/
TArray<FCDTMaterialScalarParameterInfo> UCDTBPFLUtility::GetMaterialScalarParameterInfo(UMaterialInterface* Material)
{
	TArray<FCDTMaterialScalarParameterInfo> Ret;
	if (Material)
	{
		TArray<FMaterialParameterInfo> ParameterInfos;
		TArray<FGuid> Guids;
		Material->GetAllScalarParameterInfo(ParameterInfos, Guids);
		for (auto& Parameter : ParameterInfos)
		{
			float OutputValue;
			if (Material->GetScalarParameterValue(Parameter, OutputValue))
			{
				FCDTMaterialScalarParameterInfo Info;
				Info.Name = Parameter.Name;
				Info.Value = OutputValue;
				Ret.Add(Info);
			}
		}
	}
	return Ret;
}
	
/**
* MaterialのVectorパラメーター情報取得
*/
TArray<FCDTMaterialVectorParameterInfo> UCDTBPFLUtility::GetMaterialVectorParameterInfo(UMaterialInterface* Material)
{
	TArray<FCDTMaterialVectorParameterInfo> Ret;
	if (Material)
	{
		TArray<FMaterialParameterInfo> ParameterInfos;
		TArray<FGuid> Guids;
		Material->GetAllVectorParameterInfo(ParameterInfos, Guids);
		for (auto& Parameter : ParameterInfos)
		{
			FLinearColor OutputValue;
			if (Material->GetVectorParameterValue(Parameter, OutputValue))
			{
				FCDTMaterialVectorParameterInfo Info;
				Info.Name = Parameter.Name;
				Info.Value = OutputValue;
				Ret.Add(Info);
			}
		}
	}
	return Ret;
}
	
/**
* MaterialのTextureパラメーター情報取得
*/
TArray<FCDTMaterialTextureParameterInfo> UCDTBPFLUtility::GetMaterialTextureParameterInfo(UMaterialInterface* Material)
{
	TArray<FCDTMaterialTextureParameterInfo> Ret;
	if (Material)
	{
		TArray<FMaterialParameterInfo> ParameterInfos;
		TArray<FGuid> Guids;
		Material->GetAllTextureParameterInfo(ParameterInfos, Guids);
		for (auto& Parameter : ParameterInfos)
		{
			UTexture* OutputValue;
			if (Material->GetTextureParameterValue(Parameter, OutputValue))
			{
				FCDTMaterialTextureParameterInfo Info;
				Info.Name = Parameter.Name;
				Info.Value = OutputValue;
				Ret.Add(Info);
			}
		}
	}
	return Ret;
}
	
/**
* MaterialのSwitchパラメーター情報取得
*/
TArray<FCDTMaterialSwitchParameterInfo> UCDTBPFLUtility::GetMaterialSwitchParameterInfo(UMaterialInterface* Material)
{
	TArray<FCDTMaterialSwitchParameterInfo> Ret;
	if (Material)
	{
		TArray<FMaterialParameterInfo> ParameterInfos;
		TArray<FGuid> Guids;
		Material->GetAllStaticSwitchParameterInfo(ParameterInfos, Guids);
		for (auto& Parameter : ParameterInfos)
		{
			bool OutputValue;
			FGuid OutputGuid;
			if (Material->GetStaticSwitchParameterValue(Parameter, OutputValue, OutputGuid))
			{
				FCDTMaterialSwitchParameterInfo Info;
				Info.Name = Parameter.Name;
				Info.Value = OutputValue;
				Ret.Add(Info);
			}
		}
	}
	return Ret;
}
	
	

