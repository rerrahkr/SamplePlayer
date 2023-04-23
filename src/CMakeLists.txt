target_sources(sampleplayer
    PRIVATE
        PluginEditor.cpp
        PluginProcessor.cpp)

# target_include_directories(sampleplayer PUBLIC ${PROJECT_SOURCE_DIR}/include)

set(COMPILER_FLAGS)
if(MSVC)
    list(APPEND COMPILER_FLAGS /O2 /Wall /WX /utf-8 /D_CRT_SECURE_NO_WARNINGS)
else()
    list(APPEND COMPILER_FLAGS -O2 -Wall -Wextra -Werror -pedantic -pedantic-errors)
endif()
target_compile_options(sampleplayer PRIVATE ${COMPILER_FLAGS})

target_compile_features(sampleplayer PRIVATE cxx_std_20)
