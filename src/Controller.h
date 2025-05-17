#pragma once

#include <JuceHeader.h>

#include <memory>

class Store;
class PluginProcessor;

class Controller : private juce::MessageListener {
 public:
  /**
   * @brief Constructor.
   * @param[in] model Model object.
   */
  explicit Controller(std::weak_ptr<Store> model, PluginProcessor& processor);

  using juce::MessageListener::postMessage;

 private:
  std::weak_ptr<Store> model_;
  PluginProcessor& processor_;

  /**
   * @brief Handle message from the view.
   * @param[in] message Mesage from the view.
   */
  void handleMessage(const juce::Message& message) override;
};
