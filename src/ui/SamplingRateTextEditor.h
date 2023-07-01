#pragma once

#include <JuceHeader.h>

namespace ui {
class SamplingRateTextEditor : public juce::TextEditor {
 public:
  SamplingRateTextEditor(const juce::String& componentName = {},
                         juce::juce_wchar passwordCharacter = 0);

  /**
   * @brief Set sampling rate.
   * @param[in] rate Sampling rate (Hz).
   */
  void setRate(unsigned int hz);

  /**
   * @brief Get sampling rate.
   * @return Sampling rate (Hz).
   */
  unsigned int rate() const noexcept;

 private:
  int rate_;
};
}  // namespace ui
