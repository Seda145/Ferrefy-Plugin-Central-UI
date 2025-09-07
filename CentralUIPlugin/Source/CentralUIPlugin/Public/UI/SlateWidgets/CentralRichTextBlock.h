/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#pragma once

#include "CoreMinimal.h"
#include "Delegates/IDelegateInstance.h"
#include "Engine/DataTable.h"
#include "CentralSlateWidgetInterface.h"
#include "Components/RichTextBlock.h"

#include "CentralRichTextBlock.generated.h"


USTRUCT(BlueprintType)
struct FS_CentralRichTextBlockStyle : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite, meta=(RequiredAssetDataTags = "RowStructure=/Script/UMG.RichTextStyleRow"))
		class UDataTable* TextStyleSet;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		TArray<TSubclassOf<URichTextBlockDecorator>> DecoratorClasses;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		float MinDesiredWidth;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		ETextTransformPolicy TextTransformPolicy;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
		TEnumAsByte<ETextJustify::Type> Justification;

	FS_CentralRichTextBlockStyle()
		: TextStyleSet (nullptr)
		, DecoratorClasses (TArray<TSubclassOf<URichTextBlockDecorator>>())
		, MinDesiredWidth (0.f)
		, TextTransformPolicy (ETextTransformPolicy::None)
		, Justification (ETextJustify::Left)
	{}
};


/**
* A Central widget (centralized properties).
* The rich text block
*
* * Fancy Text
* * No Children
*/
UCLASS(meta = (DisplayName = "Rich Text Block (C)"))
class CENTRALUIPLUGIN_API UCentralRichTextBlock : public URichTextBlock, public ICentralSlateWidgetInterface {
	GENERATED_BODY()

private:

#if WITH_EDITORONLY_DATA

	UPROPERTY(Transient)
		UDataTable* TrackedCentralStyleDataTable = nullptr;

	FDelegateHandle TrackedCentralStyleDataTableHandle = FDelegateHandle();

#endif // WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (RowType = "/Script/CentralUIPlugin.S_CentralRichTextBlockStyle"))
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

	UCentralRichTextBlock(const FObjectInitializer& InObjectInitializer);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);

#endif // WITH_EDITOR

	virtual FDataTableRowHandle GetCentralStyle() const override;

	virtual void SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) override;

	virtual TArray<FString> GetCentralManagedPropertyNames() const override;

};
