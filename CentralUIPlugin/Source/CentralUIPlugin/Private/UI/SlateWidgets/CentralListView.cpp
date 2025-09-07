/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#include "CentralListView.h"
#include "LogCentralUIPlugin.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/ConstructorHelpers.h"


#define LOCTEXT_NAMESPACE "CentralUIPlugin"


UCentralListView::UCentralListView(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer) {

	ConstructorHelpers::FObjectFinderOptional<UDataTable> Obj(TEXT("/CentralUIPlugin/Data/DataTables/UI/Slate/ListView/DT_Slate_ListView.DT_Slate_ListView"));
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

void UCentralListView::PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) {
	Super::PostEditChangeProperty(InPropertyChangedEvent);

	if (InPropertyChangedEvent.Property && InPropertyChangedEvent.Property->GetFName() == TEXT("CentralStyle")) {
		LoadCentralStyle();
	}
}

#endif

void UCentralListView::OnWidgetRebuilt() {
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

FDataTableRowHandle UCentralListView::GetCentralStyle() const {
	return CentralStyle;
}

void UCentralListView::SetCentralStyle(FDataTableRowHandle InStyle, bool bInLoadStyle) {
	CentralStyle = InStyle;
	if (bInLoadStyle) {
		LoadCentralStyle();
	}
}

TArray<FString> UCentralListView::GetCentralManagedPropertyNames() const {
	TArray<FString> Names;
	// As long as property names are equal on style and styled object, we can simply iterate.
	for (TFieldIterator<FProperty> It(FS_CentralListViewStyle::StaticStruct()); It; ++It) {
		if (It != nullptr) {
			Names.Add(It->GetNameCPP());
		}
	}
	return Names;
}

bool UCentralListView::LoadCentralStyle() {
	const FS_CentralListViewStyle* DTPtr = CentralStyle.GetRow<FS_CentralListViewStyle>(TEXT("Loading Central Style"));
	if (DTPtr == nullptr) {
		UE_LOG(LogCentralUIPlugin, Warning, TEXT("Invalid datatable row handle."));
		return false;
	}

	// Here we update the slate widget using the Central style.

	WidgetStyle = DTPtr->WidgetStyle;
	ScrollBarStyle = DTPtr->ScrollBarStyle;
	Orientation = DTPtr->Orientation;
	bEnableFixedLineOffset = DTPtr->bEnableFixedLineOffset;
	FixedLineScrollOffset = DTPtr->FixedLineScrollOffset;
	SetSelectionMode(DTPtr->SelectionMode);
	ConsumeMouseWheel = DTPtr->ConsumeMouseWheel;
	bClearSelectionOnClick = DTPtr->bClearSelectionOnClick;
	bReturnFocusToSelection = DTPtr->bReturnFocusToSelection;
#if WITH_EDITORONLY_DATA
    EntrySpacing = DTPtr->EntrySpacing;
#endif  // WITH_EDITORONLY_DATA
    // TODO, dealing with InitHorizontalEntrySpacing, InitVerticalEntrySpacing. Can't set after initialization? See ListView.h.
	SetWheelScrollMultiplier(DTPtr->WheelScrollMultiplier);
	bEnableScrollAnimation = DTPtr->bEnableScrollAnimation;
	AllowOverscroll = DTPtr->bEnableScrollAnimation;
	bEnableRightClickScrolling = DTPtr->bEnableRightClickScrolling;

	// Slate still doesn't sync for one or more properties so we have to do it manually...
	SynchronizeProperties();

	return true;
}

#if WITH_EDITOR

void UCentralListView::ActOnCentralStyleDataTableChanged() {
	LoadCentralStyle();
}

#endif // WITH_EDITOR


#undef LOCTEXT_NAMESPACE