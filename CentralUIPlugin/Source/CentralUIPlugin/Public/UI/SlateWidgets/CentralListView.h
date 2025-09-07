/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/DataTable.h"
#include "CentralSlateWidgetInterface.h"
#include "Components/ListView.h"

#include "CentralListView.generated.h"


USTRUCT(BlueprintType)
struct FS_CentralListViewStyle : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FTableViewStyle WidgetStyle;
	
	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FScrollBarStyle ScrollBarStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		TEnumAsByte<EOrientation> Orientation;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		bool bEnableFixedLineOffset;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite, meta = (EditCondition = bEnableFixedLineOffset, ClampMin = 0.0f, ClampMax = 0.5f))
		float FixedLineScrollOffset;

	UPROPERTY(EditAnywhere, Category = "Navigation", BlueprintReadWrite)
		TEnumAsByte<ESelectionMode::Type> SelectionMode;

	UPROPERTY(EditAnywhere, Category = "Navigation", BlueprintReadWrite)
		EConsumeMouseWheel ConsumeMouseWheel;

	UPROPERTY(EditAnywhere, Category = "Navigation", BlueprintReadWrite)
		bool bClearSelectionOnClick;

	UPROPERTY(EditAnywhere, Category = "Navigation", BlueprintReadWrite)
		bool bReturnFocusToSelection;

	UPROPERTY(EditAnywhere, Category = "Entry", BlueprintReadWrite)
		float EntrySpacing;

	UPROPERTY(EditAnywhere, Category = "Scroll", BlueprintReadWrite)
		float WheelScrollMultiplier;

	UPROPERTY(EditAnywhere, Category = "Scroll", BlueprintReadWrite)
		bool bEnableScrollAnimation;

	UPROPERTY(EditAnywhere, Category = "Scroll", BlueprintReadWrite)
		bool AllowOverscroll = true;

	UPROPERTY(EditAnywhere, Category = "Scroll", BlueprintReadWrite)
		bool bEnableRightClickScrolling = true;

	FS_CentralListViewStyle()
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
* A virtualized list that allows up to thousands of items to be displayed.
* 
* An important distinction to keep in mind here is "Item" vs. "Entry"
* The list itself is based on a list of n items, but only creates as many entry widgets as can fit on screen.
* For example, a scrolling ListView of 200 items with 5 currently visible will only have created 5 entry widgets.
*
* To make a widget usable as an entry in a ListView, it must inherit from the IUserObjectListEntry interface.
*/
UCLASS(meta = (DisplayName = "List View (C)", EntryInterface = UserObjectListEntry))
class CENTRALUIPLUGIN_API UCentralListView : public UListView, public ICentralSlateWidgetInterface {
	GENERATED_BODY()

private:

#if WITH_EDITORONLY_DATA

	UPROPERTY(Transient)
		UDataTable* TrackedCentralStyleDataTable = nullptr;

	FDelegateHandle TrackedCentralStyleDataTableHandle = FDelegateHandle();

#endif // WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (RowType = "/Script/CentralUIPlugin.S_CentralListViewStyle"))
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

	UCentralListView(const FObjectInitializer& InObjectInitializer);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);

#endif // WITH_EDITOR

	virtual FDataTableRowHandle GetCentralStyle() const override;

	virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) override;

	virtual TArray<FString> GetCentralManagedPropertyNames() const override;

};
