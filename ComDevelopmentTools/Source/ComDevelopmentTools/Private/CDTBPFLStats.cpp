// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CDTBPFLStats.h"
#include "ComDevelopmentTools.h"



#if STATS
#include "Stats/StatsData.h"
#include "Kismet\GameplayStatics.h"
/*
 * see StatRender2.cpp
 */

 
/**
 * 取得するStatの値
 */
enum class CDTGetStatType : uint8
{
	CallCount,
	Duration,
	Value,
};
 
/**
 * Statの数値を取得する
 *
 * @param StatName Stat名。頭にSTAT_が合っても無くてもOK
 * @param ValueType 取得する種類
 * @param StatType 取得する値
 * 
 */
int64 CDTHelperGetStat(FName StatName, EComplexStatField::Type ValueType, CDTGetStatType StatType)
{
	if (FGameThreadStatsData* StatsData = FLatestGameThreadStatsData::Get().Latest)
	{
		const FComplexStatMessage* SearchStatMessage = nullptr;
		
		FString SearchString(StatName.ToString());
		FString SearchStringAddPrefix(SearchString);
		if (SearchString.Find(TEXT("STAT_"), ESearchCase::IgnoreCase) == INDEX_NONE)
		{
			// STAT_がなければ付け足す
			SearchStringAddPrefix = FString(TEXT("STAT_")) + SearchString;
		}
		else
		{
			// STAT_が有るので消す
			SearchString = SearchStringAddPrefix.Replace(TEXT("STAT_"), TEXT(""), ESearchCase::IgnoreCase);
		}
		FName SearchName(*SearchString);
		FName SearchNameAddPrefix(*SearchStringAddPrefix);
		
		
		// Statが幾つかの変数に分かれて保存されているので検索する
		if (const FComplexStatMessage* StatMessage = StatsData->GetStatData(SearchName))
		{
			SearchStatMessage = StatMessage;
		}

		if (!SearchStatMessage)
		{
			for (const auto& GroupInfo : StatsData->ActiveStatGroups)
			{
				// FlatAggregate
				for (const auto& Aggregate : GroupInfo.FlatAggregate)
				{
					FName ShortName = Aggregate.NameAndInfo.GetShortName();
					if (ShortName == SearchNameAddPrefix)
					{
						SearchStatMessage = &Aggregate;
						break;
					}
				}
				if (SearchStatMessage)
				{
					break;
				}
				// HierAggregate
				for (const auto& Aggregate : GroupInfo.HierAggregate)
				{
					FName ShortName = Aggregate.NameAndInfo.GetShortName();
					if (ShortName == SearchNameAddPrefix)
					{
						SearchStatMessage = &Aggregate;
						break;
					}
				}
				if (SearchStatMessage)
				{
					break;
				}
				// CountersAggregate
				for (const auto& Aggregate : GroupInfo.CountersAggregate)
				{
					FName ShortName = Aggregate.NameAndInfo.GetShortName();
					if (ShortName == SearchNameAddPrefix)
					{
						SearchStatMessage = &Aggregate;
						break;
					}
				}
				if (SearchStatMessage)
				{
					break;
				}
				// MemoryAggregate
				for (const auto& Aggregate : GroupInfo.MemoryAggregate)
				{
					FName ShortName = Aggregate.NameAndInfo.GetShortName();
					if (ShortName == SearchNameAddPrefix)
					{
						SearchStatMessage = &Aggregate;
						break;
					}
				}
				if (SearchStatMessage)
				{
					break;
				}
			}
		}
		
		if (SearchStatMessage)
		{
			switch (StatType)
			{
			case CDTGetStatType::CallCount:
				return SearchStatMessage->GetValue_CallCount(ValueType);
			case CDTGetStatType::Duration:
				return SearchStatMessage->GetValue_Duration(ValueType);
			case CDTGetStatType::Value:
				return SearchStatMessage->GetValue_double(ValueType);
			}
		}

	}

	return 0.f;
}
#endif









// ------------------------------------------------------
// Stat Group
// ------------------------------------------------------
/**
 * StatGroupの計測を有効にする
 *
 * @Param Enable 有効にするか
 * @Param DispScreen 画面に表示するか
 */
void UCDTBPFLStats::SetEnableStatGroup(const UObject* WorldContextObject, FName StatGroupName, bool Enable, bool DispScreen)
{
#if STATS
	FGameThreadStatsData* StatsData = FLatestGameThreadStatsData::Get().Latest;
	{
		FString GroupString = StatGroupName.ToString();
		FString GroupStringAddPrefix = GroupString;
		if (GroupString.Find(TEXT("STATGROUP_"), ESearchCase::IgnoreCase) == INDEX_NONE)
		{
			// STATGROUP_がなければ付け足す
			GroupStringAddPrefix = FString(TEXT("STATGROUP_")) + GroupString;
		}
		else
		{
			// STATGROUP_が有るので消す
			GroupString = GroupStringAddPrefix.Replace(TEXT("STATGROUP_"), TEXT(""), ESearchCase::IgnoreCase);
		}
		const FName GroupNameFull = FName(*GroupStringAddPrefix, EFindName::FNAME_Find);
		
		bool Toggle = false;
		if (StatsData)
		{
			if(StatsData->GroupNames.Contains(GroupNameFull))
			{
				// 現在有効
			
				if (Enable)
				{
					return;
				}
				else
				{
					// 無効にしたい
					Toggle = true;
				}
			}
			else
			{
				// 現在無効
			
			
				if (Enable)
				{
					// 有効にしたい
					Toggle = true;
				}
				else
				{
					return;
				}
			}
		}
		else
		{
			// 設定がないので有効に
			Toggle = true;
		}
		
		if (Toggle)
		{
			if (APlayerController* TargetPC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
			{
				// スクリーンに表示するか
				FString DisplayString = DispScreen ? FString(TEXT("")) : FString(TEXT(" -nodisplay"));
				TargetPC->ConsoleCommand( FString(TEXT("stat ")) + GroupString + DisplayString, /*bWriteToLog=*/false);
			}
		}
	}

#endif
}





// ------------------------------------------------------
// Stat Duration
// ------------------------------------------------------
/**
 * Statの平均時間を取得（処理含む）
 */
float UCDTBPFLStats::GetStatDurationIncAverage(FName StatName)
{
#if STATS
	return FPlatformTime::ToMilliseconds(CDTHelperGetStat(StatName, EComplexStatField::IncAve, CDTGetStatType::Duration));
#else
	return 0.0f;
#endif
}

/**
 * Statの最大時間を取得（処理含む）
 */
float UCDTBPFLStats::GetStatDurationIncMax(FName StatName)
{
#if STATS
	return FPlatformTime::ToMilliseconds(CDTHelperGetStat(StatName, EComplexStatField::IncMax, CDTGetStatType::Duration));
#else
	return 0.0f;
#endif
}

/**
 * Statの平均時間を取得（処理含まず）
 */
float UCDTBPFLStats::GetStatDurationExcAverage(FName StatName)
{
#if STATS
	return FPlatformTime::ToMilliseconds(CDTHelperGetStat(StatName, EComplexStatField::ExcAve, CDTGetStatType::Duration));
#else
	return 0.0f;
#endif
}

/**
 * Statの最大時間を取得（処理含まず）
 */
float UCDTBPFLStats::GetStatDurationExcMax(FName StatName)
{
#if STATS
	return FPlatformTime::ToMilliseconds(CDTHelperGetStat(StatName, EComplexStatField::ExcMax, CDTGetStatType::Duration));
#else
	return 0.0f;
#endif
}


// ------------------------------------------------------
// Stat Value
// ------------------------------------------------------
/**
 * Statの平均数値を取得
 */
int32 UCDTBPFLStats::GetStatValueAverage(FName StatName)
{
#if STATS
	return CDTHelperGetStat(StatName, EComplexStatField::IncAve, CDTGetStatType::Value);
#else
	return 0.0f;
#endif
}

/**
 * Statの最大数値を取得
 */
int32 UCDTBPFLStats::GetStatValueMax(FName StatName)
{
#if STATS
	return CDTHelperGetStat(StatName, EComplexStatField::IncMax, CDTGetStatType::Value);
#else
	return 0.0f;
#endif
}


// ------------------------------------------------------
// Stat CallCount
// ------------------------------------------------------
/**
 * Statの呼出回数を取得
 */
int32 UCDTBPFLStats::GetStatCallCount(FName StatName)
{
#if STATS
	return CDTHelperGetStat(StatName, EComplexStatField::IncAve, CDTGetStatType::CallCount);
#else
	return 0.0f;
#endif
}

