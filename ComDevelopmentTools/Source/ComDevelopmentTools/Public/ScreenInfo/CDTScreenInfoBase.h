// Copyright 2018-2019 com04, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CDTScreenInfoBase.generated.h"

class AActor;
class UActorComponent;
class UMaterialInterface;
class UMaterialInstanceDynamic;
class UPrimitiveComponent;

/**
* 
*/
UCLASS(BlueprintType, abstract, Category="ComDeveloperTools")
class COMDEVELOPMENTTOOLS_API ACDTScreenInfoBase : public AActor
{
	GENERATED_BODY()

	/**
	 */
	ACDTScreenInfoBase();

public:
	/**
	 * enbale/disable screen info
	 */
	UFUNCTION(BlueprintCallable, Category="ComDeveloperTools|ScreenInfo")
	void SetEnable(bool Enable);
	
	/**
	 * now enabled?
	 */
	UFUNCTION(BlueprintCallable, Category="ComDeveloperTools|ScreenInfo")
	bool IsEnabled() const;
	
protected:
	/**
	 * setup counter draw material
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="ComDeveloperTools|Internal")
	UMaterialInstanceDynamic* CreateMaterial(AActor* Actor, UActorComponent* Component, UMaterialInterface* Material, int32 Count);
	
	
	/**
	 * Flag check Actor
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="ComDeveloperTools|Internal")
	bool CheckActor(AActor* Actor);
	
	/**
	 * Flag check Component
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="ComDeveloperTools|Internal")
	bool CheckComponent(AActor* Actor, UActorComponent* Component);
	

	/**
	 * call from before setup
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="ComDeveloperTools|Internal")
	void PreSetup();
	
	/**
	 * call from after setup
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="ComDeveloperTools|Internal")
	void PostSetup();

	/**
	 * call from after restore
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="ComDeveloperTools|Internal")
	void PostRestore();

	/**
	 * Setup materials
	 */
	void Setup();
	/**
	 * Restore materials
	 */
	void Restore();
	
	
	static TWeakObjectPtr<ACDTScreenInfoBase> CurrentInfo;
private:
	/**
	 * cache restore materials
	 */
	void AddRestoreComponent(UPrimitiveComponent* Primitive);
	
	
	/// material restore data
	struct SRestoreData
	{
		TWeakObjectPtr<UPrimitiveComponent> Primitive;
		
		UPROPERTY()
		TArray<UMaterialInterface*> Materials;
	};
	
	TArray<SRestoreData> RestoreData;
	
	/// now enable
	bool bEnabled;
};
