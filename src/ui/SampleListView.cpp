#include "SampleListView.h"

#include "SampleListModel.h"

namespace ui {
namespace {
namespace visual {
namespace colour {
const auto kOutline = juce::Colours::grey;
}

}  // namespace visual
}  // namespace

SampleListView::SampleListView(const juce::String& componentName,
                               TableListBoxModel* model)
    : juce::TableListBox(componentName, model) {
  setColour(juce::TableListBox::outlineColourId, visual::colour::kOutline);
  setOutlineThickness(1);

  setMultipleSelectionEnabled(true);

  const auto columnFlags = juce::TableHeaderComponent::visible;

  auto& tableHeader = getHeader();
  tableHeader.addColumn("#", SampleListColumn::ColumnNumber, 20, 20, -1,
                        columnFlags);
  tableHeader.addColumn("Name", SampleListColumn::ColumnName, 100, 20, -1,
                        columnFlags);
  tableHeader.setPopupMenuActive(false);
  tableHeader.setStretchToFitActive(true);

  resized();
}

SampleListView::~SampleListView() = default;
}  // namespace ui
