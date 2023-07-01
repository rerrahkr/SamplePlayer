#pragma once

#include <JuceHeader.h>

#include <functional>
#include <memory>

#include "SamplingRateTextEditor.h"

namespace ui {
class ExportSettingsView final : public juce::Component {
 public:
  ExportSettingsView();
  ~ExportSettingsView();

  void resized() override;

  /**
   * @brief Called when "OK" button is clicked.
   */
  std::function<void()> onOkButtonClicked;

 private:
  // Type
  std::unique_ptr<juce::Label> typeLabel_;
  std::unique_ptr<juce::ComboBox> typeComboBox_;

  // Sampling rate
  std::unique_ptr<juce::Label> rateLabel_;
  std::unique_ptr<SamplingRateTextEditor> rateEditor_;

  // Key
  std::unique_ptr<juce::Label> keyLabel_;
  std::unique_ptr<juce::ComboBox> keyEditor_;

  // Buttons
  std::unique_ptr<juce::TextButton> okButton_, cancelButton_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ExportSettingsView)
};
}  // namespace ui
