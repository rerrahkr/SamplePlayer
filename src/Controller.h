#pragma once

#include <JuceHeader.h>

#include <memory>

class Model;

class Controller : private juce::MessageListener {
 public:
  /**
   * @brief Constructor.
   * @param[in] model Model object.
   */
  explicit Controller(std::weak_ptr<Model> model);

  using juce::MessageListener::postMessage;

 private:
  std::weak_ptr<Model> model_;

  /**
   * @brief Handle message from the view.
   * @param[in] message Mesage from the view.
   */
  void handleMessage(const juce::Message& message) override;
};
