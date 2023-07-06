#pragma once

#include <JuceHeader.h>

#include <optional>
#include <vector>

// TODO: Dummy
struct DummySample {
  juce::String name, details;
};

using Samples = std::vector<DummySample>;

/**
 * @brief Interface of sample list model.
 */
struct SampleListState {
  /**
   * @brief List of imported sample.
   * @return Imported samples.
   */
  virtual Samples samples() const = 0;

  /**
   * @brief Get the index of selected sample in the sample list.
   * @return Index, or invalid value if no sample is selected.
   */
  virtual std::optional<std::size_t> selectedSampleIndex() const = 0;
};

/**
 * @brief Interface of plugin editor model.
 */
struct EditorState : public SampleListState {};

/**
 * @brief Model class.
 */
class Model : public juce::ActionBroadcaster, public EditorState {
 public:
  /**
   * @brief Constructor.
   */
  Model();

  /**
   * @brief List of imported sample.
   * @return Imported samples.
   */
  Samples samples() const override;

  /**
   * @brief Get the index of selected sample in the sample list.
   * @return Index, or invalid value if no sample is selected.
   */
  std::optional<std::size_t> selectedSampleIndex() const override;

  /**
   * @brief Select sample.
   * @param[in] index Index of selected sample in the sample list.
   * @return \c true if selected index is changed, otherwise \c false.
   */
  bool selectSample(std::size_t index);

  /**
   * @brief Deselect sample.
   */
  void deselecteSample();

  /**
   * @brief Delete sample.
   * @param[in] index Index of deleted sample in the sample list.
   * @return \c true if specified sample is deleted, otherwise \c false.
   */
  bool deleteSample(std::size_t index);

 private:
  /// Sample list state
  Samples samples_;

  /// Index of selected sample.
  std::optional<std::size_t> selectedSampleIndex_;
};
