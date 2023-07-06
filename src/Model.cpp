#include "Model.h"

Model::Model() {
  samples_ = {
      {"ABC", "abc"},
      {"DEF", "def"},
      {"GHI", "ghi"},
  };
}

Samples Model::samples() const { return samples_; }

std::optional<std::size_t> Model::selectedSampleIndex() const {
  return selectedSampleIndex_;
}

bool Model::selectSample(std::size_t index) {
  if (samples_.size() <= index || index == selectedSampleIndex_) {
    return false;
  }

  selectedSampleIndex_ = index;
  sendActionMessage("");
  return true;
}

void Model::deselecteSample() { selectedSampleIndex_.reset(); }

bool Model::deleteSample(std::size_t index) {
  if (samples_.size() <= index) {
    return false;
  }

  samples_.erase(samples_.begin() + index);
  sendActionMessage("");
  return true;
}
