/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/DataTable.h"
#include "CentralSlateWidgetInterface.h"
#include "Components/RadialSlider.h"

#include "CentralRadialSlider.generated.h"


USTRUCT(BlueprintType)
struct FS_CentralRadialSliderStyle : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance", meta = (ClampMin = "0", ClampMax = "360"))
		float SliderHandleStartAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance", meta=(ClampMin = "0", ClampMax = "360"))
		float SliderHandleEndAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance", meta=(ClampMin = "0", ClampMax = "360"))
		float AngularOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		FVector2D HandStartEndRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance", meta = (DisplayName="Style"))
		FSliderStyle WidgetStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		FLinearColor SliderBarColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		FLinearColor SliderProgressColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		FLinearColor SliderHandleColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		FLinearColor CenterBackgroundColor;

	/** Whether to show the slider handle (thumb).  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		bool ShowSliderHandle;

	/** Whether to show the slider hand.  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
		bool ShowSliderHand;

	/** Whether the value is changed when dragging vertically as opposed to along the radial curve.  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
		bool UseVerticalDrag;

	FS_CentralRadialSliderStyle()
		: SliderHandleStartAngle (60.f)
		, SliderHandleEndAngle (300.f)
		, AngularOffset (0.f)
		, HandStartEndRatio (FVector2D(0.f, 1.f))
		, WidgetStyle ()
		, SliderBarColor (FLinearColor::Gray)
		, SliderProgressColor (FLinearColor::White)
		, SliderHandleColor (FLinearColor::White)
		, CenterBackgroundColor (FLinearColor::Transparent)
		, ShowSliderHandle (true)
		, ShowSliderHand (false)
		, UseVerticalDrag (false)
	{}
};


/**
* A Central widget (centralized properties).
* A simple widget that shows a sliding bar with a handle that allows you to control the value between 0..1.
*
* * No Children
*/
UCLASS(meta = (DisplayName = "Radial Slider (C)"))
class CENTRALUIPLUGIN_API UCentralRadialSlider : public URadialSlider, public ICentralSlateWidgetInterface {
	GENERATED_BODY()

private:

#if WITH_EDITORONLY_DATA

	UPROPERTY(Transient)
		UDataTable* TrackedCentralStyleDataTable = nullptr;

	FDelegateHandle TrackedCentralStyleDataTableHandle = FDelegateHandle();

#endif // WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (RowType = "/Script/CentralUIPlugin.S_CentralRadialSliderStyle"))
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

	UCentralRadialSlider(const FObjectInitializer& InObjectInitializer);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);

#endif // WITH_EDITOR

	virtual FDataTableRowHandle GetCentralStyle() const override;

	virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) override;

	virtual TArray<FString> GetCentralManagedPropertyNames() const override;

};
