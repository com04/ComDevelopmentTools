// Copyright 2018-2019 com04, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Materials/MaterialInterface.h"
#include "CDTBPFLUtility.generated.h"


/**
 * マテリアルのScalarパラメーター
 */
USTRUCT(BlueprintType, Category="ComDeveloperTools|Utility")
struct FCDTMaterialScalarParameterInfo
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
};
/**
 * マテリアルのVectorパラメーター
 */
USTRUCT(BlueprintType, Category = "ComDeveloperTools|Utility")
struct FCDTMaterialVectorParameterInfo
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Value;
};
/**
 * マテリアルのTextureパラメーター
 */
USTRUCT(BlueprintType, Category = "ComDeveloperTools|Utility")
struct FCDTMaterialTextureParameterInfo
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture* Value;
};
/**
 * マテリアルのSwitchパラメーター
 */
USTRUCT(BlueprintType, Category = "ComDeveloperTools|Utility")
struct FCDTMaterialSwitchParameterInfo
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Value;
};

UCLASS()
class COMDEVELOPMENTTOOLS_API UCDTBPFLUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
	// ------------------------------------------------------
	// Primitives
	// ------------------------------------------------------
	/**
	 * Simple Collisionが有効か
	 */
	UFUNCTION(BlueprintCallable, Category="ComDeveloperTools|Utility")
	static bool HasCollisionSimple(UPrimitiveComponent* Primitive);
	
	/**
	 * Complex Collisionが有効か
	 */
	UFUNCTION(BlueprintCallable, Category="ComDeveloperTools|Utility")
	static bool HasCollisionComplex(UPrimitiveComponent* Primitive);
	

	// ------------------------------------------------------
	// Materials
	// ------------------------------------------------------
	/**
	 * MaterialのScalarパラメーター情報取得
	 */
	UFUNCTION(BlueprintCallable, Category="ComDeveloperTools|Utility")
	static TArray<FCDTMaterialScalarParameterInfo> GetMaterialScalarParameterInfo(UMaterialInterface* Material);
	
	/**
	 * MaterialのVectorパラメーター情報取得
	 */
	UFUNCTION(BlueprintCallable, Category="ComDeveloperTools|Utility")
	static TArray<FCDTMaterialVectorParameterInfo> GetMaterialVectorParameterInfo(UMaterialInterface* Material);
	
	/**
	 * MaterialのTextureパラメーター情報取得
	 */
	UFUNCTION(BlueprintCallable, Category="ComDeveloperTools|Utility")
	static TArray<FCDTMaterialTextureParameterInfo> GetMaterialTextureParameterInfo(UMaterialInterface* Material);
	
	/**
	 * MaterialのSwitchパラメーター情報取得
	 */
	UFUNCTION(BlueprintCallable, Category="ComDeveloperTools|Utility")
	static TArray<FCDTMaterialSwitchParameterInfo> GetMaterialSwitchParameterInfo(UMaterialInterface* Material);
	
	
};

