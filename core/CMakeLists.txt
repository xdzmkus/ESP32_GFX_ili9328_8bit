# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

set(SOURCES Src/main.cpp Src/stm32_mini.c)

idf_component_register(
    SRCS ${SOURCES}     # list the source files of this component
    INCLUDE_DIRS . Inc  # optional, add here public include directories
    PRIV_INCLUDE_DIRS   # optional, add here private include directories
    REQUIRES freertos esp_common lcd # optional, list the public requirements (component names)
    PRIV_REQUIRES       # optional, list the private requirements
)
