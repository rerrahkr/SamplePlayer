#include "Model.h"

#include "file/P86.h"

Store::Store() {}

Samples Store::samples() const { return samples_; }

std::optional<std::size_t> Store::selectedSampleIndex() const {
  return selectedSampleIndex_;
}

bool Store::selectSample(std::size_t index) {
  if (samples_.size() <= index || index == selectedSampleIndex_) {
    return false;
  }

  selectedSampleIndex_ = index;
  sendActionMessage("");
  return true;
}

void Store::deselecteSample() { selectedSampleIndex_.reset(); }

bool Store::deleteSample(std::size_t index) {
  if (samples_.size() <= index) {
    return false;
  }

  samples_.erase(samples_.begin() + index);
  sendActionMessage("");
  return true;
}

juce::StringArray Store::importableExtensions() const { return {".p86"}; }

bool Store::importSamples(const juce::File& file) {
  if (file.getFileExtension().toLowerCase() == ".p86") {
    auto importeds = file::P86(file).samples();
    if (importeds.empty()) {
      return false;
    }

    samples_.reserve(samples_.size() + importeds.size());
    std::move(importeds.begin(), importeds.end(), std::back_inserter(samples_));

    sendActionMessage("");
    return true;
  }

  return false;
}
