#include "SamplingRateTextEditor.h"

#include <algorithm>
#include <numeric>

namespace ui {
namespace {
/**
 * @brief Clamp given sampling rate.
 * @param[in] hz Sampling rate (Hz).
 * @return Clamped sampling rate (Hz).
 */
inline auto clampRate(unsigned int hz) {
  constexpr unsigned int kMinRate{0}, kMaxRate{192000};
  return std::clamp(hz, kMinRate, kMaxRate);
}

/**
 * @brief Parse sampling rate text.
 * @param[in] text Source text.
 * @return Parsed value, or \c 0 if parsing is failed.
 */
unsigned int parse(const juce::String& text) {
  const auto value = text.getLargeIntValue();
  if (value < std::numeric_limits<unsigned int>::max()) {
    return clampRate(static_cast<unsigned int>(value));
  } else {
    return 0u;
  }
}
}  // namespace

SamplingRateTextEditor::SamplingRateTextEditor(
    const juce::String& componentName, juce::juce_wchar passwordCharacter)
    : juce::TextEditor(componentName, passwordCharacter) {
  constexpr unsigned int kDefaultSamplingRate{44100};
  setRate(kDefaultSamplingRate);

  // Parse text to rate after finishing editting.
  const auto callback = [this] { setRate(parse(getText())); };
  onReturnKey = callback;
  onFocusLost = callback;
}

void SamplingRateTextEditor::setRate(unsigned int hz) {
  rate_ = clampRate(hz);

  // Text formatting
  const auto text = juce::String(rate_) + "Hz";
  setText(text);
}

unsigned int SamplingRateTextEditor::rate() const noexcept { return rate_; }
}  // namespace ui
