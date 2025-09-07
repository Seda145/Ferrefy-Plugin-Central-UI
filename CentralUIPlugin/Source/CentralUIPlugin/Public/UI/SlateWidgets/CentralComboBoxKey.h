/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/DataTable.h"
#include "CentralSlateWidgetInterface.h"
#include "Components/ComboBoxKey.h"

#include "CentralComboBoxKey.generated.h"


USTRUCT(BlueprintType)
struct FS_CentralComboBoxKeyStyle : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FComboBoxStyle WidgetStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FTableRowStyle ItemStyle;

	// 'UComboBoxKey::ForegroundColor': Direct access to ForegroundColor is deprecated. Please use the getter. Note that this property is only set at construction and is not modifiable at runtime. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		//FSlateColor ForegroundColor;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FMargin ContentPadding;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		bool bHasDownArrow;

	FS_CentralComboBoxKeyStyle()
		: WidgetStyle (FComboBoxStyle())
		, ItemStyle (FTableRowStyle())
		//, ForegroundColor (FSlateColor(FLinearColor::Black))
		, ContentPadding (FMargin(0.f, 0.f))
		, bHasDownArrow (true)
	{}
};


/**
* A Central widget (centralized properties).
* The combobox allows you to display a list of options to the user in a dropdown menu for them to select one.
* Use OnGenerateConentWidgetEvent to return a custom built widget.
*/
UCLASS(meta = (DisplayName = "ComboBox (Key) (C)"))
class CENTRALUIPLUGIN_API UCentralComboBoxKey : public UComboBoxKey, public ICentralSlateWidgetInterface {
	GENERATED_BODY()

private:

#if WITH_EDITORONLY_DATA

	UPROPERTY(Transient)
		UDataTable* TrackedCentralStyleDataTable = nullptr;

	FDelegateHandle TrackedCentralStyleDataTableHandle = FDelegateHandle();

#endif // WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (RowType = "/Script/CentralUIPlugin.S_CentralComboBoxKeyStyle"))
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

	/* Note: Parent does not use FObjectInitializer which is unusual in widgets. */
	UCentralComboBoxKey();

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);

#endif // WITH_EDITOR

	virtual FDataTableRowHandle GetCentralStyle() const override;

	virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) override;

	virtual TArray<FString> GetCentralManagedPropertyNames() const override;

};
