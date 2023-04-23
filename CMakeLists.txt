cmake_minimum_required(VERSION 3.13.0)

# プロジェクト設定
project(jucetemplate VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()

add_subdirectory(lib/juce)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

juce_add_plugin(jucetemplate
    COMPANY_NAME "Rerrah"
    COMPANY_COPYRIGHT "Rerrah"
    IS_SYNTH TRUE
    IS_MIDI_EFFECT FALSE
    PLUGIN_MANUFACTURER_CODE Rera
    PLUGIN_CODE Temp
    FORMATS Standalone #VST3
    # VST3_CATEGORIES "Fx"
    PRODUCT_NAME "JUCETemplate")

juce_generate_juce_header(jucetemplate)

add_subdirectory(src)

target_link_libraries(jucetemplate
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

target_compile_definitions(jucetemplate
    PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)
