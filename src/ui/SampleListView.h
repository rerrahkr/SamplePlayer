#pragma once

#include <JuceHeader.h>

namespace ui {
class SampleListView : public juce::TableListBox {
 public:
  SampleListView(const juce::String& componentName = "",
                 juce::TableListBoxModel* model = nullptr);

  ~SampleListView();
};
}  // namespace ui
