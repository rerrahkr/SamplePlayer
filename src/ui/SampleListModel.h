#pragma once

#include <JuceHeader.h>

#include <functional>

struct SampleListState;

namespace ui {
class SampleListColumn {
 public:
  enum ColumnID {
    ColumnNumber = 1,
    ColumnName,
  };
};

class SampleListModel : public juce::TableListBoxModel {
 public:
  SampleListModel(const SampleListState& model);
  ~SampleListModel();

  int getNumRows() override;
  void paintRowBackground(juce::Graphics& g, int rowNumber, int /*width*/,
                          int /*height*/, bool rowIsSelected) override;
  void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width,
                 int height, bool rowIsSelected) override;

  /**
   * @brief Called when the selected rows are changed.
   */
  std::function<void()> onSelctionsChanged;

  /**
   * @brief Called when delete key is pressed.
   */
  std::function<void()> onDeleteKeyPressed;

 private:
  const SampleListState& model_;

  void selectedRowsChanged(int /*lastRowSelected*/) override;
  void deleteKeyPressed(int /*lastRowSelected*/) override;
};
}  // namespace ui
