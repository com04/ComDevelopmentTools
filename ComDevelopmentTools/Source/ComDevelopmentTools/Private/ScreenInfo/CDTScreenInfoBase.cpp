// Copyright 2018-2019 com04 All Rights Reserved.


#include "CDTScreenInfoBase.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "EngineUtils.h"
#include "Array.h"

#define LOCTEXT_NAMESPACE "CDTScreenInfoBase"


TWeakObjectPtr<ACDTScreenInfoBase> ACDTScreenInfoBase::CurrentInfo = nullptr;



ACDTScreenInfoBase::ACDTScreenInfoBase()
: Super(),
  bEnabled(false)
{
}


/**
* Flag check Actor
*/
void ACDTScreenInfoBase::SetEnable(bool Enable)
{
	if (Enable)
	{
		if (CurrentInfo.IsValid())
		{
			CurrentInfo->SetEnable(false);
		}
		Setup();
	}
	else
	{
		if (bEnabled)
		{
			Restore();
		}
	}
}

/**
 * now enabled?
 */
bool ACDTScreenInfoBase::IsEnabled() const
{
	return bEnabled;
}


/**
 * Setup materials
 */
void ACDTScreenInfoBase::Setup()
{
	PreSetup();

	for (TActorIterator<AActor> It(GetWorld(), AActor::StaticClass()); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor->IsPendingKill())
		{
			continue;
		}

		TArray<UActorComponent*> PrimitiveComponents = Actor->GetComponentsByClass(UPrimitiveComponent::StaticClass());
		// no target to draw
		if (PrimitiveComponents.Num() <= 0)
		{
			continue;
		}
		TArray<UActorComponent*> ActorComponents = Actor->GetComponentsByClass(UActorComponent::StaticClass());

		// check count
		int32 Count = 0;
		if (CheckActor(Actor))
		{
			++Count;
		}
		for (auto Component : ActorComponents)
		{
			if (!IsValid(Component))
			{
				continue;
			}
			if (CheckComponent(Actor, Component))
			{
				++Count;
			}
		}

		// override material
		for (auto Component : PrimitiveComponents)
		{
			if (!IsValid(Component))
			{
				continue;
			}
			UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(Component);
			if (Primitive)
			{
				AddRestoreComponent(Primitive);
				
				int32 MaterialNum = Primitive->GetNumMaterials();
				for (int32 Index = 0 ; Index < MaterialNum ; ++Index)
				{
					UMaterialInterface* BaseMaterial = Primitive->GetMaterial(Index);
					UMaterialInstanceDynamic* DynamicMaterial = CreateMaterial(Actor, Component, BaseMaterial, Count);
					if (DynamicMaterial)
					{
						Primitive->SetMaterial(Index, DynamicMaterial);
					}
				}
			}
		}
	}
	PostSetup();
	
	
	bEnabled = true;
	CurrentInfo = this;
}

/**
 * Restore materials
 */
void ACDTScreenInfoBase::Restore()
{
	for (auto& Data : RestoreData)
	{
		if (!Data.Primitive.IsValid())
		{
			continue;
		}
		int32 MaterialNum = FMath::Min(Data.Primitive->GetNumMaterials(), Data.Materials.Num());
		for (int32 Index = 0 ; Index < MaterialNum ; ++Index)
		{
			Data.Primitive->SetMaterial(Index, Data.Materials[Index]);
		}
	}
	RestoreData.Empty();
	
	PostRestore();
	bEnabled = false;
	if (CurrentInfo == this)
	{
		CurrentInfo.Reset();
	}
}


/**
 * cache restore materials
 */
void ACDTScreenInfoBase::AddRestoreComponent(UPrimitiveComponent* Primitive)
{
	SRestoreData Data;
	Data.Primitive = Primitive;
	
	int32 MaterialNum = Primitive->GetNumMaterials();
	Data.Materials.Reserve(MaterialNum);
	for (int32 Index = 0 ; Index < MaterialNum ; ++Index)
	{
		UMaterialInterface* BaseMaterial = Primitive->GetMaterial(Index);
		Data.Materials.Add(BaseMaterial);
	}
	RestoreData.Add(Data);
}


