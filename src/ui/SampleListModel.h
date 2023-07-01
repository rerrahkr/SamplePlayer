#pragma once

#include <JuceHeader.h>

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
  SampleListModel();

  ~SampleListModel();

  int getNumRows() override;

  void paintRowBackground(juce::Graphics& g, int rowNumber, int /*width*/,
                          int /*height*/, bool rowIsSelected) override;

  void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width,
                 int height, bool rowIsSelected) override;
};
}  // namespace ui
