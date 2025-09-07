/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/DataTable.h"
#include "CentralSlateWidgetInterface.h"
#include "Components/TreeView.h"

#include "CentralTreeView.generated.h"


USTRUCT(BlueprintType)
struct FS_CentralTreeViewStyle : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		FTableViewStyle WidgetStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		FScrollBarStyle ScrollBarStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		TEnumAsByte<EOrientation> Orientation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		bool bEnableFixedLineOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance", meta = (EditCondition = bEnableFixedLineOffset, ClampMin = 0.0f, ClampMax = 0.5f))
		float FixedLineScrollOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation")
		TEnumAsByte<ESelectionMode::Type> SelectionMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation")
		EConsumeMouseWheel ConsumeMouseWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation")
		bool bClearSelectionOnClick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation")
		bool bReturnFocusToSelection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entry")
		float EntrySpacing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scroll")
		float WheelScrollMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scroll")
		bool bEnableScrollAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scroll")
		bool AllowOverscroll = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scroll")
		bool bEnableRightClickScrolling = true;

	FS_CentralTreeViewStyle()
		: WidgetStyle (FTableViewStyle())
		, ScrollBarStyle (FScrollBarStyle())
		, Orientation (EOrientation::Orient_Vertical)
		, bEnableFixedLineOffset (false)
		, FixedLineScrollOffset (0.f)
		, SelectionMode (ESelectionMode::Type::Single)
		, ConsumeMouseWheel (EConsumeMouseWheel::WhenScrollingPossible)
		, bClearSelectionOnClick (false)
		, bReturnFocusToSelection (false)
		, EntrySpacing (0.f)
		, WheelScrollMultiplier (1.f)
		, bEnableScrollAnimation (false)
		, AllowOverscroll (true)
		, bEnableRightClickScrolling (true)
	{}
};


/**
* A Central widget (centralized properties).
* Similar to ListView, but can display a hierarchical tree of elements.
* The base items source for the tree identifies the root items, each of which can have n associated child items.
* There is no hard limit to the nesting - child items can have children and so on
*
* To make a widget usable as an entry in a TreeView, it must inherit from the IUserObjectListEntry interface.
*/
UCLASS(meta = (DisplayName = "Tree View (C)"))
class CENTRALUIPLUGIN_API UCentralTreeView : public UTreeView, public ICentralSlateWidgetInterface {
	GENERATED_BODY()

private:

#if WITH_EDITORONLY_DATA

	UPROPERTY(Transient)
		UDataTable* TrackedCentralStyleDataTable = nullptr;

	FDelegateHandle TrackedCentralStyleDataTableHandle = FDelegateHandle();

#endif // WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (RowType = "/Script/CentralUIPlugin.S_CentralTreeViewStyle"))
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

	UCentralTreeView(const FObjectInitializer& InObjectInitializer);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);

#endif // WITH_EDITOR

	virtual FDataTableRowHandle GetCentralStyle() const override;

	virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) override;

	virtual TArray<FString> GetCentralManagedPropertyNames() const override;

};
