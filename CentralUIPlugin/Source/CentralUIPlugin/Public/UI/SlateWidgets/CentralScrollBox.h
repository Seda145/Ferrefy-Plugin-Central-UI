/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/DataTable.h"
#include "CentralSlateWidgetInterface.h"
#include "Components/ScrollBox.h"

#include "CentralScrollBox.generated.h"


USTRUCT(BlueprintType)
struct FS_CentralScrollBoxStyle : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		FScrollBoxStyle WidgetStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		FScrollBarStyle WidgetBarStyle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scroll")
		TEnumAsByte<EOrientation> Orientation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scroll")
		ESlateVisibility ScrollBarVisibility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scroll")
		EConsumeMouseWheel ConsumeMouseWheel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scroll")
		FVector2D ScrollbarThickness;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scroll")
		FMargin ScrollbarPadding;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scroll")
		bool AlwaysShowScrollbar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scroll")
		bool AlwaysShowScrollbarTrack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scroll")
		bool AllowOverscroll;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scroll")
		//bool BackPadScrolling;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scroll")
		//bool FrontPadScrolling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scroll")
		bool bAnimateWheelScrolling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scroll")
		EDescendantScrollDestination NavigationDestination;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scroll")
		//float NavigationScrollPadding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scroll")
		EScrollWhenFocusChanges ScrollWhenFocusChanges;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scroll")
		bool bAllowRightClickDragScrolling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scroll")
		float WheelScrollMultiplier = 1.f;

	FS_CentralScrollBoxStyle()
		: WidgetStyle (FScrollBoxStyle())
		, WidgetBarStyle (FScrollBarStyle())
		, Orientation (EOrientation::Orient_Vertical)
		, ScrollBarVisibility (ESlateVisibility::Visible)
		, ConsumeMouseWheel (EConsumeMouseWheel::WhenScrollingPossible)
		, ScrollbarThickness (FVector2D(9.f, 9.f))
		, ScrollbarPadding (FMargin(2.f, 2.f))
		, AlwaysShowScrollbar (false)
		, AlwaysShowScrollbarTrack (false)
		, AllowOverscroll (true)
		// 'UScrollBox::BackPadScrolling': Direct access to BackPadScrolling is deprecated. Please use the getter. Note that BackPadScrolling is only set at construction and is not modifiable at runtime. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
		//, BackPadScrolling (false)
		// 'UScrollBox::FrontPadScrolling': Direct access to FrontPadScrolling is deprecated. Please use the getter. Note that FrontPadScrolling is only set at construction and is not modifiable at runtime. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
		//, FrontPadScrolling (false)
		, bAnimateWheelScrolling (false)
		, NavigationDestination (EDescendantScrollDestination::IntoView)
		// 'UScrollBox::NavigationScrollPadding': Direct access to NavigationScrollPadding is deprecated. Please use the getter. Note that NavigationScrollPadding is only set at construction and is not modifiable at runtime. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
		//, NavigationScrollPadding (0.f)
		, ScrollWhenFocusChanges (EScrollWhenFocusChanges::NoScroll)
		, bAllowRightClickDragScrolling (true)
		, WheelScrollMultiplier (1.f)
	{}
};


/**
* A Central widget (centralized properties).
* An arbitrary scrollable collection of widgets. Great for presenting 10-100 widgets in a list. Doesn't support virtualization.
*/
UCLASS(meta = (DisplayName = "Scroll Box (C)"))
class CENTRALUIPLUGIN_API UCentralScrollBox : public UScrollBox, public ICentralSlateWidgetInterface {
	GENERATED_BODY()

private:

#if WITH_EDITORONLY_DATA

	UPROPERTY(Transient)
		UDataTable* TrackedCentralStyleDataTable = nullptr;

	FDelegateHandle TrackedCentralStyleDataTableHandle = FDelegateHandle();

#endif // WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (RowType = "/Script/CentralUIPlugin.S_CentralScrollBoxStyle"))
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

	UCentralScrollBox(const FObjectInitializer& InObjectInitializer);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);

#endif // WITH_EDITOR

	virtual FDataTableRowHandle GetCentralStyle() const override;

	virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) override;

	virtual TArray<FString> GetCentralManagedPropertyNames() const override;

};
