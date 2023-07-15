#include "P86.h"

#include <ranges>
#include <string>

namespace file {
namespace {
constexpr std::int64_t kSampleBlockOffset{0x610};

template <typename T>
T readAs24bit(const juce::MemoryBlock& memory, int offset) {
  std::uint8_t bytes[3];
  memory.copyTo(bytes, offset, 3);
  return static_cast<T>(bytes[0]) | (static_cast<T>(bytes[1]) << 8) |
         (static_cast<T>(bytes[2]) << 16);
}

std::vector<std::pair<std::size_t, std::vector<std::int8_t>>> loadSamples(
    const juce::MemoryBlock& memory) {
  if (memory.getSize() < kSampleBlockOffset) {
    return {};
  }

  std::string magic(12, '\0');
  memory.copyTo(magic.data(), 0, magic.size());
  using namespace std::string_literals;
  if (magic != "PCM86 DATA\n\0"s) {
    return {};
  }

  const auto size = readAs24bit<std::size_t>(memory, 13);
  if (size != memory.getSize()) {
    return {};
  }

  std::vector<std::pair<std::size_t, std::vector<std::int8_t>>> samples;

  int headerOffset{0x10}, sampleOffset{0};
  constexpr std::size_t kNSample{256};
  for (std::size_t i = 0; i < kNSample; ++i) {
    const auto sampleStartOffset = readAs24bit<int>(memory, headerOffset);
    headerOffset += 3;

    const auto sampleLength = readAs24bit<std::size_t>(memory, headerOffset);
    headerOffset += 3;
    if (!sampleLength) {
      continue;
    }

    if (samples.empty()) {
      sampleOffset = sampleStartOffset;
    }

    int startOffset = kSampleBlockOffset + sampleStartOffset - sampleOffset;
    if (memory.getSize() <
        (static_cast<std::size_t>(startOffset) + sampleLength)) {
      return {};
    }

    std::vector<std::int8_t> rawSample(sampleLength);
    memory.copyTo(rawSample.data(), startOffset, sampleLength);

    samples.emplace_back(std::make_pair(i, std::move(rawSample)));
  }

  return samples;
}
}  // namespace

P86::P86(const juce::File& file) : path_(file.getFullPathName()) {
  if (!file.existsAsFile()) {
    return;
  }

  if (file.getSize() < kSampleBlockOffset) {
    return;
  }

  juce::MemoryBlock memory;
  if (!file.loadFileAsData(memory)) {
    return;
  }

  raws_ = loadSamples(memory);
}

Samples P86::samples() const {
  Samples samples;
  samples.reserve(raws_.size());

  for (auto [index, rawSample] : raws_) {
    juce::Array<float> sample;
    for (auto data : rawSample) {
      sample.add(static_cast<float>(data));
    }

    const juce::String name(index);
    const int samplingRate{16540};
    const juce::String details =
        juce::StringArray{
            "Original name: " + name,
            "File: " + path_,
            "Sample Number: " + juce::String(index),
            "Sampling rate: " + juce::String(samplingRate) + "Hz",
            "Key: G5",
        }
            .joinIntoString("\n");

    samples.emplace_back(name, details, std::move(sample), samplingRate);
  }

  return samples;
}
}  // namespace file
