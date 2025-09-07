/**Copyright 2025: Roy Wierer (Ferrefy). All Rights Reserved.**/
#include "CentralUIPluginEditorInstaller.h"
#include "CentralSlateWidgetDetails.h"
#include "LogCentralUIPluginEditor.h"
#include "CentralUIPluginEditorUtils.h"
#include "CentralUIPluginEditorSettings.h"
#include "Engine/EngineTypes.h"
// Slate Widgets
#include "Components/BackgroundBlur.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/CircularThrobber.h"
#include "Components/ComboBoxString.h"
#include "Components/ComboBoxKey.h"
#include "Components/EditableText.h"
#include "Components/EditableTextBox.h"
#include "Components/ExpandableArea.h"
#include "Components/Image.h"
#include "Components/InputKeySelector.h"
#include "Components/ListView.h"
#include "Components/MultiLineEditableText.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/ProgressBar.h"
#include "Components/RichTextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/Slider.h"
#include "Components/RadialSlider.h"
#include "Components/Spacer.h"
#include "Components/SpinBox.h"
#include "Components/TextBlock.h"
#include "Components/Throbber.h"
#include "Components/TileView.h"
#include "Components/TreeView.h"
// Central Widgets
#include "CentralBackgroundBlur.h"
#include "CentralBorder.h"
#include "CentralButton.h"
#include "CentralCheckBox.h"
#include "CentralCircularThrobber.h"
#include "CentralComboBoxString.h"
#include "CentralComboBoxKey.h"
#include "CentralEditableText.h"
#include "CentralEditableTextBox.h"
#include "CentralExpandableArea.h"
#include "CentralImage.h"
#include "CentralInputKeySelector.h"
#include "CentralListView.h"
#include "CentralMultiLineEditableText.h"
#include "CentralMultiLineEditableTextBox.h"
#include "CentralProgressBar.h"
#include "CentralRichTextBlock.h"
#include "CentralScrollBox.h"
#include "CentralSlider.h"
#include "CentralRadialSlider.h"
#include "CentralSpacer.h"
#include "CentralSpinBox.h"
#include "CentralTextBlock.h"
#include "CentralThrobber.h"
#include "CentralTileView.h"
#include "CentralTreeView.h"


// Setup

void FCentralUIPluginEditorInstaller::RunAutomatedInstaller() {
	const UCentralUIPluginEditorSettings* Settings = GetDefault<UCentralUIPluginEditorSettings>();
	if (IsValid(Settings) && Settings->bHideReplacedSlateWidgetPalette) {
		HideReplacedSlateWidgetPalette();
	}
	else {
		ShowReplacedSlateWidgetPalette();
	}

	RegisterDetailPanels();
}

TArray<FSoftClassPath> FCentralUIPluginEditorInstaller::GetSlateWidgetsToHide() const {
	TArray<FSoftClassPath> SlateWidgetsToHide;
	SlateWidgetsToHide.Add(UBackgroundBlur::StaticClass());
	SlateWidgetsToHide.Add(UBorder::StaticClass());
	SlateWidgetsToHide.Add(UButton::StaticClass());
	SlateWidgetsToHide.Add(UCheckBox::StaticClass());
	SlateWidgetsToHide.Add(UCircularThrobber::StaticClass());
	SlateWidgetsToHide.Add(UComboBoxString::StaticClass());
	SlateWidgetsToHide.Add(UComboBoxKey::StaticClass());
	SlateWidgetsToHide.Add(UEditableText::StaticClass());
	SlateWidgetsToHide.Add(UEditableTextBox::StaticClass());
	SlateWidgetsToHide.Add(UExpandableArea::StaticClass());
	SlateWidgetsToHide.Add(UImage::StaticClass());
	SlateWidgetsToHide.Add(UInputKeySelector::StaticClass());
	SlateWidgetsToHide.Add(UListView::StaticClass());
	SlateWidgetsToHide.Add(UMultiLineEditableText::StaticClass());
	SlateWidgetsToHide.Add(UMultiLineEditableTextBox::StaticClass());
	SlateWidgetsToHide.Add(UProgressBar::StaticClass());
	SlateWidgetsToHide.Add(URichTextBlock::StaticClass());
	SlateWidgetsToHide.Add(UScrollBox::StaticClass());
	SlateWidgetsToHide.Add(USlider::StaticClass());
	SlateWidgetsToHide.Add(URadialSlider::StaticClass());
	SlateWidgetsToHide.Add(USpacer::StaticClass());
	SlateWidgetsToHide.Add(USpinBox::StaticClass());
	SlateWidgetsToHide.Add(UTextBlock::StaticClass());
	SlateWidgetsToHide.Add(UThrobber::StaticClass());
	SlateWidgetsToHide.Add(UTileView::StaticClass());
	SlateWidgetsToHide.Add(UTreeView::StaticClass());

	return SlateWidgetsToHide;
}

void FCentralUIPluginEditorInstaller::HideReplacedSlateWidgetPalette() const {
	for (const FSoftClassPath& WidgetX : GetSlateWidgetsToHide()) {
		UCentralUIPluginEditorUtils::HideWidgetOnUMGPalette(WidgetX);
	}
}

void FCentralUIPluginEditorInstaller::ShowReplacedSlateWidgetPalette() const {
	for (const FSoftClassPath& WidgetX : GetSlateWidgetsToHide()) {
		UCentralUIPluginEditorUtils::ShowWidgetOnUMGPalette(WidgetX);
	}
}

void FCentralUIPluginEditorInstaller::RegisterDetailPanels() const {
	// Register custom detail panels for all the centralized slate widgets
	// , to hide the style properties on individual widgets which we manage elsewhere.

	auto DoFor = [](const UClass* InClass) {
		if (IsValid(InClass)) {
			UCentralUIPluginEditorUtils::RegisterCustomPropertyModuleClassLayout(InClass->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FCentralSlateWidgetDetails::MakeInstance));
		}
	};

	DoFor(UCentralBackgroundBlur::StaticClass());
	DoFor(UCentralBorder::StaticClass());
	DoFor(UCentralButton::StaticClass());
	DoFor(UCentralCheckBox::StaticClass());
	DoFor(UCentralCircularThrobber::StaticClass());
	DoFor(UCentralComboBoxString::StaticClass());
	DoFor(UCentralComboBoxKey::StaticClass());
	DoFor(UCentralEditableText::StaticClass());
	DoFor(UCentralEditableTextBox::StaticClass());
	DoFor(UCentralExpandableArea::StaticClass());
	DoFor(UCentralImage::StaticClass());
	DoFor(UCentralInputKeySelector::StaticClass());
	DoFor(UCentralListView::StaticClass());
	DoFor(UCentralMultiLineEditableText::StaticClass());
	DoFor(UCentralMultiLineEditableTextBox::StaticClass());
	DoFor(UCentralProgressBar::StaticClass());
	DoFor(UCentralRichTextBlock::StaticClass());
	DoFor(UCentralScrollBox::StaticClass());
	DoFor(UCentralSlider::StaticClass());
	DoFor(UCentralRadialSlider::StaticClass());
	DoFor(UCentralSpacer::StaticClass());
	DoFor(UCentralSpinBox::StaticClass());
	DoFor(UCentralTextBlock::StaticClass());
	DoFor(UCentralThrobber::StaticClass());
	DoFor(UCentralTileView::StaticClass());
	DoFor(UCentralTreeView::StaticClass());
}

