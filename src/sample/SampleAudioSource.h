#pragma once

#include <JuceHeader.h>

#include <cstddef>

#include "Sample.h"

namespace sample {
class SampleAudioSource final : public juce::AudioSource {
 public:
  SampleAudioSource();

  ~SampleAudioSource() override;

  void setSample(const sample::Sample& sample);

  void setSample(sample::Sample&& sample);

  int samplingRate() const;

  void prepareToPlay(int /*samplesPerBlockExpected*/,
                     double /*sampleRate*/) override;

  void releaseResources() override;

  void getNextAudioBlock(
      const juce::AudioSourceChannelInfo& bufferToFill) override;

 private:
  Sample sample_;
  std::size_t playbackPosition_;
};
}  // namespace sample
