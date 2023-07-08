target_sources(${PROJECT_NAME}
    PRIVATE
        Controller.cpp
        Model.cpp
        PluginEditor.cpp
        PluginProcessor.cpp
        ui/ExportSettingsView.cpp
        ui/NestableGrid.cpp
        ui/SampleListModel.cpp
        ui/SampleListView.cpp
        ui/SamplingRateTextEditor.cpp)

# target_include_directories(sampleplayer PUBLIC ${PROJECT_SOURCE_DIR}/include)
