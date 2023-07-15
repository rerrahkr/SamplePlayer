#pragma once

#include <JuceHeader.h>

#include <cstdint>
#include <utility>
#include <vector>

#include "../sample/Sample.h"

namespace file {
class P86 {
 public:
  explicit P86(const juce::File& file);

  Samples samples() const;

 private:
  const juce::String path_;
  std::vector<std::pair<std::size_t, std::vector<std::int8_t>>> raws_;
};
}  // namespace file
