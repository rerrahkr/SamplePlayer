#include "ExportSettingsView.h"

#include <ranges>

#include "NestableGrid.h"

namespace ui {
namespace {
const juce::StringArray types{
    "PVI",
    "PZI",
};

const juce::StringArray keys = [] {
  juce::StringArray array;
  const juce::StringArray keyNames{"C",  "C#", "D",  "Eb", "E",  "F",
                                   "F#", "G",  "G#", "A",  "Bb", "B"};
  const auto octaveRange = std::views::iota(0, 9);
  for (const juce::String& octave :
       octaveRange |
           std::views::transform([](int o) { return juce::String(o); })) {
    for (const auto& name : keyNames) {
      array.add(name + octave);
    }
  }
  return array;
}();
}  // namespace

ExportSettingsView::ExportSettingsView() : juce::Component("Export Settings") {
  // Helper
  const auto makeLabel = [](const juce::String& text) {
    auto label = std::make_unique<juce::Label>("", text);
    label->setJustificationType(juce::Justification::centredRight);
    return label;
  };

  // Type
  typeLabel_ = makeLabel("Export as");
  addAndMakeVisible(typeLabel_.get());
  typeComboBox_ = std::make_unique<juce::ComboBox>();
  typeComboBox_->addItemList(types, 1);
  typeComboBox_->setSelectedId(1);
  addAndMakeVisible(typeComboBox_.get());

  // Sampling rate
  rateLabel_ = makeLabel("Sampling rate");
  addAndMakeVisible(rateLabel_.get());
  rateEditor_ = std::make_unique<SamplingRateTextEditor>();
  addAndMakeVisible(rateEditor_.get());

  // Key
  keyLabel_ = makeLabel("Key");
  addAndMakeVisible(keyLabel_.get());
  keyEditor_ = std::make_unique<juce::ComboBox>();
  keyEditor_->addItemList(keys, 1);
  keyEditor_->setSelectedId(61);
  addAndMakeVisible(keyEditor_.get());

  // Buttons
  okButton_ = std::make_unique<juce::TextButton>("OK");
  okButton_->onClick = [this] {
    if (auto* dialg = findParentComponentOfClass<juce::DialogWindow>()) {
      dialg->exitModalState(0);
    }

    if (onOkButtonClicked) {
      onOkButtonClicked();
    }
  };
  addAndMakeVisible(okButton_.get());

  cancelButton_ = std::make_unique<juce::TextButton>("Cancel");
  cancelButton_->onClick = [this] {
    if (auto* dialog = findParentComponentOfClass<juce::DialogWindow>()) {
      dialog->exitModalState(1);
    }
  };
  addAndMakeVisible(cancelButton_.get());

  //
  setSize(300, 150);
  resized();
}

ExportSettingsView::~ExportSettingsView() = default;

void ExportSettingsView::resized() {
  if (!typeLabel_ || !typeComboBox_ || !rateLabel_ || !rateEditor_ ||
      !keyLabel_ || !keyEditor_) {
    return;
  }

  constexpr auto contentsMargin = 10;
  const auto rowHeight = 24_px;
  const auto gap = 5_px;

  auto contentArea = getLocalBounds().reduced(contentsMargin);
  auto buttonArea =
      contentArea.removeFromBottom(static_cast<int>(rowHeight.pixels));

  // Settings (Label + any component)
  juce::Grid settingGrid;
  settingGrid.rowGap = gap;
  settingGrid.templateRows = {rowHeight, rowHeight, rowHeight};
  settingGrid.templateColumns = {2_fr, 3_fr};
  settingGrid.alignContent = juce::Grid::AlignContent::start;
  settingGrid.items = {
      typeLabel_.get(),  typeComboBox_.get(), rateLabel_.get(),
      rateEditor_.get(), keyLabel_.get(),     keyEditor_.get(),
  };
  settingGrid.performLayout(
      contentArea.withTrimmedBottom(static_cast<int>(gap.pixels)));

  // Buttons
  const auto buttonWidth = 100_px;
  juce::Grid buttonGrid;
  buttonGrid.columnGap = gap;
  buttonGrid.templateRows = {1_fr};
  buttonGrid.templateColumns = {buttonWidth, buttonWidth};
  buttonGrid.justifyContent = juce::Grid::JustifyContent::end;
  buttonGrid.items = {cancelButton_.get(), okButton_.get()};
  buttonGrid.performLayout(buttonArea);
}
}  // namespace ui
