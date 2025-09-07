/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/DataTable.h"
#include "CentralSlateWidgetInterface.h"
#include "Components/ProgressBar.h"

#include "CentralProgressBar.generated.h"


USTRUCT(BlueprintType)
struct FS_CentralProgressBarStyle : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FLinearColor FillColorAndOpacity;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FProgressBarStyle WidgetStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		TEnumAsByte<EProgressBarFillType::Type> BarFillType;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		TEnumAsByte<EProgressBarFillStyle::Type> BarFillStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		bool bIsMarquee;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FVector2D BorderPadding;

	FS_CentralProgressBarStyle()
		: FillColorAndOpacity (FLinearColor::White)
		, WidgetStyle (FProgressBarStyle())
		, BarFillType (EProgressBarFillType::LeftToRight)
		, BarFillStyle (EProgressBarFillStyle::Mask)
		, bIsMarquee (false)
		, BorderPadding (FVector2D::ZeroVector)
	{}
};


/**
* A Central widget (centralized properties).
* The progress bar widget is a simple bar that fills up that can be restyled to fit any number of uses.
*
* * No Children
*/
UCLASS(meta = (DisplayName = "Progress Bar (C)"))
class CENTRALUIPLUGIN_API UCentralProgressBar : public UProgressBar, public ICentralSlateWidgetInterface {
	GENERATED_BODY()

private:

#if WITH_EDITORONLY_DATA

	UPROPERTY(Transient)
		UDataTable* TrackedCentralStyleDataTable = nullptr;

	FDelegateHandle TrackedCentralStyleDataTableHandle = FDelegateHandle();

#endif // WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (RowType = "/Script/CentralUIPlugin.S_CentralProgressBarStyle"))
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

	UCentralProgressBar(const FObjectInitializer& InObjectInitializer);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);

#endif // WITH_EDITOR

	virtual FDataTableRowHandle GetCentralStyle() const override;

	virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) override;

	virtual TArray<FString> GetCentralManagedPropertyNames() const override;

};
