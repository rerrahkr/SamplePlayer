#pragma once

#include <memory>

#include "PluginProcessor.h"

namespace ui {
class ExportSettingsView;
class SampleListModel;
class SampleListView;
}  // namespace ui

//==============================================================================
class PluginEditor : public juce::AudioProcessorEditor {
 public:
  explicit PluginEditor(PluginProcessor &);
  ~PluginEditor() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

 private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  PluginProcessor &processorRef;

  std::unique_ptr<ui::SampleListModel> sampleListModel_;
  std::unique_ptr<ui::SampleListView> sampleListView_;

  std::unique_ptr<juce::Label> nameLabel_;
  std::unique_ptr<juce::TextEditor> nameTextEditor_;

  std::unique_ptr<juce::TextButton> playButton_, stopButton_;

  std::unique_ptr<juce::TextButton> importButton_, exportButton_;

  std::unique_ptr<juce::TextEditor> detailView_;

  // File chooser
  juce::File currentDirectory_;
  std::unique_ptr<juce::FileChooser> fileChooser_;

  std::unique_ptr<ui::ExportSettingsView> exportSettingsView_;

  void onImportButtonClicked();

  void onExportButtonClicked();

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
