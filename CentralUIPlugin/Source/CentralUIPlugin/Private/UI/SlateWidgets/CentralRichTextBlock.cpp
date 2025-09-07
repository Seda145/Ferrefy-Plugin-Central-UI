/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#include "CentralRichTextBlock.h"
#include "LogCentralUIPlugin.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/ConstructorHelpers.h"


#define LOCTEXT_NAMESPACE "CentralUIPlugin"


UCentralRichTextBlock::UCentralRichTextBlock(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer) {

	ConstructorHelpers::FObjectFinderOptional<UDataTable> Obj(TEXT("/CentralUIPlugin/Data/DataTables/UI/Slate/RichTextBlock/DT_Slate_RichTextBlock.DT_Slate_RichTextBlock"));
	if (Obj.Succeeded()) {
		FDataTableRowHandle NewStyle = FDataTableRowHandle();
		NewStyle.DataTable = Obj.Get();
		NewStyle.RowName = TEXT("Default");
		SetCentralStyle(NewStyle, false);
	}
	else {
		UE_LOG(LogCentralUIPlugin, Warning, TEXT("Could not set a default datatable for this widget."));
	}
}

#if WITH_EDITOR

void UCentralRichTextBlock::PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) {
	Super::PostEditChangeProperty(InPropertyChangedEvent);

	if (InPropertyChangedEvent.Property && InPropertyChangedEvent.Property->GetFName() == TEXT("CentralStyle")) {
		LoadCentralStyle();
	}
}

#endif

void UCentralRichTextBlock::OnWidgetRebuilt() {
	Super::OnWidgetRebuilt();

#if WITH_EDITOR

	// Track datatable modification.

	// Remove old binding
	if (IsValid(TrackedCentralStyleDataTable)) {
		TrackedCentralStyleDataTable->OnDataTableChanged().Remove(TrackedCentralStyleDataTableHandle);
		TrackedCentralStyleDataTable = nullptr;
	}

	/** Should be save to const_cast:
	// https://en.cppreference.com/w/cpp/language/const_cast
	// https://stackoverflow.com/questions/357600/is-const-cast-safe
	// https://forums.unrealengine.com/t/losing-const-qualifier-through-soft-pointer-hacky/779114/2
	*/
	TrackedCentralStyleDataTable = const_cast<UDataTable*>(CentralStyle.DataTable.Get());
	if (IsValid(TrackedCentralStyleDataTable)) {
		TrackedCentralStyleDataTableHandle = TrackedCentralStyleDataTable->OnDataTableChanged().AddUObject(this, &ThisClass::ActOnCentralStyleDataTableChanged);
	}

#endif // WITH_EDITOR

	LoadCentralStyle();
}

FDataTableRowHandle UCentralRichTextBlock::GetCentralStyle() const {
	return CentralStyle;
}

void UCentralRichTextBlock::SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) {
	CentralStyle = InStyle;
	if (bInLoadStyle) {
		LoadCentralStyle();
	}
}

TArray<FString> UCentralRichTextBlock::GetCentralManagedPropertyNames() const {
	TArray<FString> Names;
	// As long as property names are equal on style and styled object, we can simply iterate.
	for (TFieldIterator<FProperty> It(FS_CentralRichTextBlockStyle::StaticStruct()); It; ++It) {
		if (It != nullptr) {
			Names.Add(It->GetNameCPP());
		}
	}

	// Additionally, the following Slate properties are no longer useful and considered "managed":
	Names.Add(TEXT("bOverrideDefaultStyle"));
	Names.Add(TEXT("DefaultTextStyleOverride"));

	return Names;
}

bool UCentralRichTextBlock::LoadCentralStyle() {
	const FS_CentralRichTextBlockStyle* DTPtr = CentralStyle.GetRow<FS_CentralRichTextBlockStyle>(TEXT("Loading Central Style"));
	if (DTPtr == nullptr) {
		UE_LOG(LogCentralUIPlugin, Warning, TEXT("Invalid datatable row handle."));
		return false;
	}

	// Here we update the slate widget using the Central style.

	SetTextStyleSet(DTPtr->TextStyleSet);
	DecoratorClasses = DTPtr->DecoratorClasses;
	SetMinDesiredWidth(DTPtr->MinDesiredWidth);
	SetTextTransformPolicy(DTPtr->TextTransformPolicy);
	SetJustification(DTPtr->Justification);

	// Slate still doesn't sync for one or more properties so we have to do it manually...
	SynchronizeProperties();

	return true;
}

#if WITH_EDITOR

void UCentralRichTextBlock::ActOnCentralStyleDataTableChanged() {
	LoadCentralStyle();
}

#endif // WITH_EDITOR


#undef LOCTEXT_NAMESPACE