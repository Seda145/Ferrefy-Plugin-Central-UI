/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/DataTable.h"
#include "CentralSlateWidgetInterface.h"
#include "Components/TextBlock.h"

#include "CentralTextBlock.generated.h"


USTRUCT(BlueprintType)
struct FS_CentralTextBlockStyle : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FSlateColor ColorAndOpacity;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FSlateFontInfo Font;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FSlateBrush StrikeBrush;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FVector2D ShadowOffset;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		FLinearColor ShadowColorAndOpacity;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		float MinDesiredWidth;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		ETextTransformPolicy TextTransformPolicy;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		TEnumAsByte<ETextJustify::Type> Justification;

	FS_CentralTextBlockStyle()
		: ColorAndOpacity (FLinearColor::White)
		, Font (FSlateFontInfo())
		, StrikeBrush (FSlateBrush())
		, ShadowOffset (FVector2D(1.0f, 1.0f))
		, ShadowColorAndOpacity (FLinearColor::Transparent)
		, MinDesiredWidth (0.f)
		, TextTransformPolicy (ETextTransformPolicy::None)
		, Justification (ETextJustify::Left)
	{}
};


/**
* A Central widget (centralized properties).
* A simple static text widget.
*
* * No Children
* * Text
*/
UCLASS(meta = (DisplayName = "Text (C)"))
class CENTRALUIPLUGIN_API UCentralTextBlock : public UTextBlock, public ICentralSlateWidgetInterface {
	GENERATED_BODY()

private:

#if WITH_EDITORONLY_DATA

	UPROPERTY(Transient)
		UDataTable* TrackedCentralStyleDataTable = nullptr;

	FDelegateHandle TrackedCentralStyleDataTableHandle = FDelegateHandle();

#endif // WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (RowType = "/Script/CentralUIPlugin.S_CentralTextBlockStyle"))
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

	UCentralTextBlock(const FObjectInitializer& InObjectInitializer);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);

#endif // WITH_EDITOR

	virtual FDataTableRowHandle GetCentralStyle() const override;

	virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) override;

	virtual TArray<FString> GetCentralManagedPropertyNames() const override;

};
