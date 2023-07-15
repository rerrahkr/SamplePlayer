#include "PluginEditor.h"

#include "./ui/CustomMessage.h"
#include "./ui/ExportSettingsView.h"
#include "./ui/NestableGrid.h"
#include "./ui/SampleListModel.h"
#include "./ui/SampleListView.h"
#include "Controller.h"
#include "Model.h"
#include "PluginProcessor.h"

//==============================================================================
PluginEditor::PluginEditor(PluginProcessor& p, Controller& controller,
                           const EditorState& model)
    : AudioProcessorEditor(&p),
      processorRef(p),
      controller_(controller),
      model_(model),
      currentDirectory_(
          juce::File::getSpecialLocation(juce::File::currentApplicationFile)) {
  // Sample list
  sampleListModel_ = std::make_unique<ui::SampleListModel>(model);
  sampleListModel_->onSelctionsChanged = [this] {
    if (sampleListView_) {
      controller_.postMessage(new ui::SelectedSampleChangedMessage{
          sampleListView_->getSelectedRow()});
    }
  };
  sampleListModel_->onDeleteKeyPressed = [this] {
    controller_.postMessage(new ui::DeleteSelectedSampleMessage);
  };

  sampleListView_ = std::make_unique<ui::SampleListView>(
      "sampleList", sampleListModel_.get());
  addAndMakeVisible(sampleListView_.get());

  // Name
  nameLabel_ = std::make_unique<juce::Label>();
  nameLabel_->setText("Name", juce::dontSendNotification);
  nameLabel_->setJustificationType(juce::Justification::centredLeft);
  addAndMakeVisible(nameLabel_.get());

  nameTextEditor_ = std::make_unique<juce::TextEditor>();
  nameTextEditor_->setMultiLine(false);
  nameTextEditor_->setJustification(juce::Justification::centredLeft);
  nameTextEditor_->setText("Bass Drum 1");
  addAndMakeVisible(nameTextEditor_.get());

  // Detail view
  detailView_ = std::make_unique<juce::TextEditor>();
  detailView_->setReadOnly(true);
  detailView_->setMultiLine(true);
  detailView_->setText(R"(Original name: Bass drum 1
Type: ADPCM
File: C:\Users/User1\Desktop\file.pvi
Sample number: 1
Sampling rate: 16000Hz
Key: C5
Start offset: 0x100
Data length: 0x1284)");
  addAndMakeVisible(detailView_.get());

  // Buttons
  playButton_ = std::make_unique<juce::TextButton>("Play");
  playButton_->onClick = [this] {
    controller_.postMessage(new ui::PlayButtonClickedMessage);
  };
  addAndMakeVisible(playButton_.get());

  stopButton_ = std::make_unique<juce::TextButton>("Stop");
  stopButton_->onClick = [this] {
    controller_.postMessage(new ui::StopButtonClickedMessge);
  };
  addAndMakeVisible(stopButton_.get());

  importButton_ = std::make_unique<juce::TextButton>("Import");
  importButton_->onClick = [this] { onImportButtonClicked(); };
  addAndMakeVisible(importButton_.get());

  exportButton_ = std::make_unique<juce::TextButton>("Export");
  exportButton_->onClick = [this] { onExportButtonClicked(); };
  exportButton_->setEnabled(false);
  addAndMakeVisible(exportButton_.get());

  //
  setSize(400, 300);
  resized();
}

PluginEditor::~PluginEditor() {
  controller_.postMessage(new ui::DestructMessage{});
  sampleListView_->setModel(nullptr);
}

//==============================================================================
void PluginEditor::paint(juce::Graphics& g) {
  g.fillAll(
      getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void PluginEditor::resized() {
  if (!sampleListView_ || !nameLabel_ || !nameTextEditor_ || !exportButton_ ||
      !importButton_ || !stopButton_ || !playButton_ || !detailView_) {
    return;
  }

  constexpr auto contentsMargin = 10;
  auto area = getLocalBounds().reduced(contentsMargin);

  juce::Rectangle<int> rightArea;
  ui::NestableGrid contentsAreaGrid;
  contentsAreaGrid.setGap(10_px);
  contentsAreaGrid.setTemplateRows({1_fr});
  contentsAreaGrid.setTemplateColumns({2_fr, 3_fr});
  contentsAreaGrid.setItems({sampleListView_.get(), rightArea});
  contentsAreaGrid.performLayout(area);

  const auto gridGap = 5_px;
  const auto rowHeight = 24_px;

  juce::Rectangle<int> nameArea, buttonArea;
  ui::NestableGrid rightAreaGrid;
  rightAreaGrid.setGap(gridGap);
  rightAreaGrid.setTemplateRows(
      {rowHeight, 1_fr,
       juce::Grid::Px{rowHeight.pixels * 2 +
                      static_cast<int>(gridGap.pixels)}});
  rightAreaGrid.setTemplateColumns({1_fr});
  rightAreaGrid.setItems({nameArea, detailView_.get(), buttonArea});
  rightAreaGrid.performLayout(rightArea);

  constexpr auto nameTitleWidth = 50;
  nameLabel_->setBounds(nameArea.removeFromLeft(nameTitleWidth));
  nameTextEditor_->setBounds(nameArea);

  constexpr auto buttonWidth = 80;
  ui::NestableGrid buttonAreaGrid;
  buttonAreaGrid.setGap(gridGap);
  buttonAreaGrid.setTemplateRows({1_fr, 1_fr});
  buttonAreaGrid.setTemplateColumns({1_fr, 1_fr});
  buttonAreaGrid.setItems({
      playButton_.get(),
      stopButton_.get(),
      importButton_.get(),
      exportButton_.get(),
  });
  buttonAreaGrid.performLayout(buttonArea.removeFromRight(
      buttonWidth * 2 + static_cast<int>(gridGap.pixels)));
}

void PluginEditor::actionListenerCallback(const juce::String& /*message*/) {
  sampleListView_->updateContent();

  const auto sampleIndex = model_.selectedSampleIndex();
  if (sampleIndex.has_value()) {
    // Selected any sample.
    const auto index = static_cast<int>(sampleIndex.value());
    sampleListView_->selectRow(index);
    const auto sample = model_.samples()[index];
    nameTextEditor_->setText(sample.name, juce::dontSendNotification);
    detailView_->setText(sample.details, false);
  } else {
    // Deselected sample.
    constexpr int kDeselectedIndex{-1};
    sampleListView_->selectRow(kDeselectedIndex);
    nameTextEditor_->setText("", juce::dontSendNotification);
    detailView_->setText("", false);
  }
}

void PluginEditor::onImportButtonClicked() {
  static const juce::String filterString = "*";

  const auto chooserFlags = juce::FileBrowserComponent::openMode |
                            juce::FileBrowserComponent::canSelectFiles |
                            juce::FileBrowserComponent::canSelectMultipleItems;

  const auto callback = [this](const juce::FileChooser& chooser) {
    const auto files = chooser.getResults();
    if (files.isEmpty()) {
      return;
    }

    for (const auto& file : files) {
      // TODO: Import file
      if (!file.existsAsFile()) {
        return;
      }

      controller_.postMessage(new ui::SampleImportRequestedMessage(file));

      currentDirectory_ = file.getParentDirectory();
    }
  };

  fileChooser_ = std::make_unique<juce::FileChooser>(
      "Import", currentDirectory_, filterString, true, false, this);
  fileChooser_->launchAsync(chooserFlags, callback);
}

void PluginEditor::onExportButtonClicked() {
  if (!exportSettingsView_) {
    exportSettingsView_ = std::make_unique<ui::ExportSettingsView>();
    exportSettingsView_->onOkButtonClicked = [this] {
      const juce::String filterString("*");

      const auto chooserFlags = juce::FileBrowserComponent::saveMode |
                                juce::FileBrowserComponent::canSelectFiles;

      const auto callback = [this](const juce::FileChooser& chooser) {
        const auto file = chooser.getResult();

        // TODO: Export file
        if (!file.existsAsFile()) {
          return;
        }

        currentDirectory_ = file.getParentDirectory();
      };

      fileChooser_ = std::make_unique<juce::FileChooser>(
          "Export", currentDirectory_, filterString, true, false, this);
      fileChooser_->launchAsync(chooserFlags, callback);
      controller_.postMessage(new ui::CustomMessage{});
    };
  }

  juce::DialogWindow::showDialog(
      "Export Settings", exportSettingsView_.get(), this,
      juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
          juce::DialogWindow::backgroundColourId),
      true);
}
