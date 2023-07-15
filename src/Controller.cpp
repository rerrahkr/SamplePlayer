#include "Controller.h"

#include "./ui/CustomMessage.h"
#include "Model.h"

Controller::Controller(std::weak_ptr<Model> model) : model_(std::move(model)) {}

void Controller::handleMessage(const juce::Message& message) {
  auto model = model_.lock();
  if (!model) {
    return;
  }

  if (const auto* destructMessage =
          dynamic_cast<const ui::DestructMessage*>(&message)) {
    model->removeAllActionListeners();
  } else if (const auto* selectinosChangedMessage =
                 dynamic_cast<const ui::SelectedSampleChangedMessage*>(
                     &message)) {
    if (selectinosChangedMessage->newIndex == -1) {
      model->deselecteSample();
    } else {
      model->selectSample(selectinosChangedMessage->newIndex);
    }
  } else if (const auto* deleteKeyPressedMessage =
                 dynamic_cast<const ui::DeleteSelectedSampleMessage*>(
                     &message)) {
    const auto index = model->selectedSampleIndex();
    if (index.has_value()) {
      model->deleteSample(index.value());
    }
  } else if (const auto* sampleImportRequestedMessage =
                 dynamic_cast<const ui::SampleImportRequestedMessage*>(
                     &message)) {
    model->importSamples(sampleImportRequestedMessage->file);
  }
}
