#pragma once

#include <JuceHeader.h>

namespace ui {
struct CustomMessage : public juce::Message {};

/// @brief Message that selected sample in the sample list is changed.
struct SelectedSampleChangedMessage : public juce::Message {
  /// New index of selection.
  const int newIndex;

  SelectedSampleChangedMessage(int newIndex) : newIndex(newIndex) {}
};

/// @brief Message to delete selected samples.
struct DeleteSelectedSampleMessage : public juce::Message {};

struct PlayButtonClickedMessage : public juce::Message {};

struct SampleImportRequestedMessage : public juce::Message {
  const juce::File file;

  SampleImportRequestedMessage(const juce::File& file) : file(file) {}
};

/// @brief Message that the view is destructing.
struct DestructMessage : public juce::Message {};
}  // namespace ui
