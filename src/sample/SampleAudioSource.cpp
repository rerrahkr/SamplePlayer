#include "SampleAudioSource.h"

#include <algorithm>
#include <utility>

namespace sample {
SampleAudioSource::SampleAudioSource() : playbackPosition_(0) {}

SampleAudioSource::~SampleAudioSource() = default;

void SampleAudioSource::setSample(const Sample& sample) {
  sample_ = sample;
  playbackPosition_ = 0;
}

void SampleAudioSource::setSample(Sample&& sample) {
  sample_ = std::move(sample);
  playbackPosition_ = 0;
}

int SampleAudioSource::samplingRate() const { return sample_.samplingRate; }

void SampleAudioSource::prepareToPlay(int /*samplesPerBlockExpected*/,
                                      double /*sampleRate*/) {
  playbackPosition_ = 0;
}

void SampleAudioSource::releaseResources() {}

void SampleAudioSource::getNextAudioBlock(
    const juce::AudioSourceChannelInfo& bufferToFill) {
  if (playbackPosition_ == sample_.data.size()) {
    bufferToFill.buffer->clear(bufferToFill.startSample,
                               bufferToFill.numSamples);
    return;
  }

  const auto nRestSamples =
      static_cast<int>(sample_.data.size() - playbackPosition_);

  if (bufferToFill.numSamples < nRestSamples) {
    for (int channel = 0; channel < bufferToFill.buffer->getNumChannels();
         ++channel) {
      bufferToFill.buffer->copyFrom(channel, bufferToFill.startSample,
                                    sample_.data.data() + playbackPosition_,
                                    bufferToFill.numSamples);
    }

    playbackPosition_ += bufferToFill.numSamples;
  } else {
    for (int channel = 0; channel < bufferToFill.buffer->getNumChannels();
         ++channel) {
      bufferToFill.buffer->copyFrom(channel, bufferToFill.startSample,
                                    sample_.data.data() + playbackPosition_,
                                    nRestSamples);
    }
    bufferToFill.buffer->clear(nRestSamples,
                               bufferToFill.numSamples - nRestSamples);

    playbackPosition_ = sample_.data.size();
  }
}
}  // namespace sample
