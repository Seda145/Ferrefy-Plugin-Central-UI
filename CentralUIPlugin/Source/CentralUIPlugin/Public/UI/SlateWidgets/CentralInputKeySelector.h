/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/DataTable.h"
#include "CentralSlateWidgetInterface.h"
#include "Components/InputKeySelector.h"

#include "CentralInputKeySelector.generated.h"


USTRUCT(BlueprintType)
struct FS_CentralInputKeySelectorStyle : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FButtonStyle WidgetStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FTextBlockStyle TextStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FMargin Margin;

	FS_CentralInputKeySelectorStyle()
		: WidgetStyle (FButtonStyle())
		, TextStyle (FTextBlockStyle())
		, Margin (FMargin())
	{}
};


/** 
* A Central widget (centralized properties).
* A widget for selecting a single key or a single key with a modifier. 
*/
UCLASS(meta = (DisplayName = "Input Key Selector (C)"))
class CENTRALUIPLUGIN_API UCentralInputKeySelector : public UInputKeySelector, public ICentralSlateWidgetInterface {
	GENERATED_BODY()

private:

#if WITH_EDITORONLY_DATA

	UPROPERTY(Transient)
		UDataTable* TrackedCentralStyleDataTable = nullptr;

	FDelegateHandle TrackedCentralStyleDataTableHandle = FDelegateHandle();

#endif // WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (RowType = "/Script/CentralUIPlugin.S_CentralInputKeySelectorStyle"))
		FDataTableRowHandle CentralStyle = FDataTableRowHandle();

public:

private:

#if WITH_EDITOR

	UFUNCTION()
		void ActOnCentralStyleDataTableChanged();

#endif // WITH_EDITOR

	virtual bool LoadCentralStyle() override;

protected:

	virtual void OnWidgetRebuilt() override;

public:

	UCentralInputKeySelector(const FObjectInitializer& InObjectInitializer);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);

#endif // WITH_EDITOR

	virtual FDataTableRowHandle GetCentralStyle() const override;

	virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) override;

	virtual TArray<FString> GetCentralManagedPropertyNames() const override;

};
