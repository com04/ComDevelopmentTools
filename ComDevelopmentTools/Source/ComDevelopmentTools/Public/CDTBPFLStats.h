// Copyright 2018-2019 com04, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CDTBPFLStats.generated.h"


UCLASS()
class COMDEVELOPMENTTOOLS_API UCDTBPFLStats : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
	// ------------------------------------------------------
	// Stat Group
	// ------------------------------------------------------
	/**
	 * StatGroupの計測を有効にする
	 *
	 * @Param Enable 有効にするか
	 * @Param DispScreen 画面に表示するか
	 */
	UFUNCTION(BlueprintCallable, Category="ComDeveloperTools|Stats", meta = ( WorldContext = WorldContextObject))
	static void SetEnableStatGroup(const UObject* WorldContextObject, FName StatGroupName, bool Enable, bool DispScreen=false);
	
	
	// ------------------------------------------------------
	// Stat Duration
	// ------------------------------------------------------
	/**
	 * Statの平均時間を取得（処理含む）
	 */
	UFUNCTION(BlueprintCallable, Category="ComDeveloperTools|Stats")
	static float GetStatDurationIncAverage(FName StatName);
	
	/**
	 * Statの最大時間を取得（処理含む）
	 */
	UFUNCTION(BlueprintCallable, Category="ComDeveloperTools|Stats")
	static float GetStatDurationIncMax(FName StatName);
	
	/**
	 * Statの平均時間を取得（処理含まず）
	 */
	UFUNCTION(BlueprintCallable, Category="ComDeveloperTools|Stats")
	static float GetStatDurationExcAverage(FName StatName);
	
	/**
	 * Statの最大時間を取得（処理含まず）
	 */
	UFUNCTION(BlueprintCallable, Category="ComDeveloperTools|Stats")
	static float GetStatDurationExcMax(FName StatName);
	
	
	// ------------------------------------------------------
	// Stat Value
	// ------------------------------------------------------
	/**
	 * Statの平均数値を取得
	 */
	UFUNCTION(BlueprintCallable, Category="ComDeveloperTools|Stats")
	static int32 GetStatValueAverage(FName StatName);
	
	/**
	 * Statの最大数値を取得
	 */
	UFUNCTION(BlueprintCallable, Category="ComDeveloperTools|Stats")
	static int32 GetStatValueMax(FName StatName);
	
	
	// ------------------------------------------------------
	// Stat CallCount
	// ------------------------------------------------------
	/**
	 * Statの呼出回数を取得
	 */
	UFUNCTION(BlueprintCallable, Category="ComDeveloperTools|Stats")
	static int32 GetStatCallCount(FName StatName);
};

