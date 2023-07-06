#include "SampleListModel.h"

#include "../Model.h"

namespace ui {
namespace {
/// Definitions for visual design
namespace visual {
/// Colour definitions
namespace colour {
const auto kTextColour =
    juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
        juce::TableListBox::textColourId);
const auto kSelectedTextColour = juce::Colours::darkblue;
const auto kBackground =
    juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
        juce::TableListBox::backgroundColourId);
const auto kOddRowBackground = [] {
  const auto& lookAndFeel =
      juce::Desktop::getInstance().getDefaultLookAndFeel();
  const auto backgoundColour =
      lookAndFeel.findColour(juce::TableListBox::backgroundColourId);
  const auto textColour =
      lookAndFeel.findColour(juce::TableListBox::textColourId);
  constexpr auto proportion = .3f;
  return backgoundColour.interpolatedWith(textColour, proportion);
}();
const auto kSelectedRowBackground = juce::Colours::lightblue;
}  // namespace colour

constexpr int fontSize = 14;
}  // namespace visual
}  // namespace

SampleListModel::SampleListModel(const SampleListState& model)
    : model_(model) {}

SampleListModel::~SampleListModel() {}

int SampleListModel::getNumRows() {
  return static_cast<int>(model_.samples().size());
}

void SampleListModel::paintRowBackground(juce::Graphics& g, int rowNumber,
                                         int /*width*/, int /*height*/,
                                         bool rowIsSelected) {
  if (rowIsSelected) {
    g.fillAll(visual::colour::kSelectedRowBackground);
  } else if (rowNumber % 2) {
    g.fillAll(visual::colour::kOddRowBackground);
  }
}

void SampleListModel::paintCell(juce::Graphics& g, int rowNumber, int columnId,
                                int width, int height, bool rowIsSelected) {
  g.setColour(rowIsSelected ? visual::colour::kSelectedTextColour
                            : visual::colour::kTextColour);
  g.setFont(juce::Font(visual::fontSize));

  juce::String text;
  switch (columnId) {
    case SampleListColumn::ColumnNumber:
      text = juce::String(rowNumber + 1);
      break;

    case SampleListColumn::ColumnName:
      text = model_.samples()[rowNumber].name;
      break;

    default:
      break;
  }

  g.drawText(text, 2, 0, width - 4, height, juce::Justification::centredLeft);

  g.setColour(visual::colour::kBackground);
  g.fillRect(width - 1, 0, 1, height);
}

void SampleListModel::selectedRowsChanged(int /*lastRowSelected*/) {
  if (onSelctionsChanged) {
    onSelctionsChanged();
  }
}

void SampleListModel::deleteKeyPressed(int /*lastRowSelected*/) {
  if (onDeleteKeyPressed) {
    onDeleteKeyPressed();
  }
}
}  // namespace ui
