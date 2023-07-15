#pragma once

#include <JuceHeader.h>

#include <cstdint>
#include <utility>
#include <vector>

namespace sample {
struct Sample {
  juce::String name, details;
  juce::Array<float> data;
  int samplingRate;

  Sample(const juce::String& name, const juce::String& details,
         const juce::Array<float>& data, int samplingRate)
      : name(name), details(details), data(data), samplingRate(samplingRate) {}
  Sample(const juce::String& name, const juce::String& details,
         juce::Array<float>&& data, int samplingRate)
      : name(name),
        details(details),
        data(std::move(data)),
        samplingRate(samplingRate) {}
};
}  // namespace sample

using Samples = std::vector<sample::Sample>;
