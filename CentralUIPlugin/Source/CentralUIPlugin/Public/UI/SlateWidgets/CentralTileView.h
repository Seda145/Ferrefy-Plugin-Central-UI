/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/DataTable.h"
#include "CentralSlateWidgetInterface.h"
#include "Components/TileView.h"

#include "CentralTileView.generated.h"


USTRUCT(BlueprintType)
struct FS_CentralTileViewStyle : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		FTableViewStyle WidgetStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		FScrollBarStyle ScrollBarStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		TEnumAsByte<EOrientation> Orientation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		EListItemAlignment TileAlignment;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entry")
		float EntryHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entry")
		float EntryWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scroll")
		float WheelScrollMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scroll")
		bool bEnableScrollAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scroll")
		bool AllowOverscroll = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scroll")
		bool bEnableRightClickScrolling = true;


	FS_CentralTileViewStyle()
		: WidgetStyle (FTableViewStyle())
		, ScrollBarStyle (FScrollBarStyle())
		, Orientation (EOrientation::Orient_Vertical)
		, TileAlignment (EListItemAlignment::EvenlyDistributed)
		, bEnableFixedLineOffset (false)
		, FixedLineScrollOffset (0.f)
		, SelectionMode (ESelectionMode::Type::Single)
		, ConsumeMouseWheel (EConsumeMouseWheel::WhenScrollingPossible)
		, bClearSelectionOnClick (false)
		, bReturnFocusToSelection (false)
		, EntrySpacing (0.f)
		, EntryHeight (128.f)
		, EntryWidth (128.f)
		, WheelScrollMultiplier (1.f)
		, bEnableScrollAnimation (false)
		, AllowOverscroll (true)
		, bEnableRightClickScrolling (true)
	{}
};


/**
* A Central widget (centralized properties).
* A ListView that presents the contents as a set of tiles all uniformly sized.
*
* To make a widget usable as an entry in a TileView, it must inherit from the IUserObjectListEntry interface.
*/
UCLASS(meta = (DisplayName = "Tile View (C)"))
class CENTRALUIPLUGIN_API UCentralTileView : public UTileView, public ICentralSlateWidgetInterface {
	GENERATED_BODY()

private:

#if WITH_EDITORONLY_DATA

	UPROPERTY(Transient)
		UDataTable* TrackedCentralStyleDataTable = nullptr;

	FDelegateHandle TrackedCentralStyleDataTableHandle = FDelegateHandle();

#endif // WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (RowType = "/Script/CentralUIPlugin.S_CentralTileViewStyle"))
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

	UCentralTileView(const FObjectInitializer& InObjectInitializer);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);

#endif // WITH_EDITOR

	virtual FDataTableRowHandle GetCentralStyle() const override;

	virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) override;

	virtual TArray<FString> GetCentralManagedPropertyNames() const override;

};
