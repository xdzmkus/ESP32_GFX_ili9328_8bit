# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

set(SOURCES GFX.cpp
			fonts/font8.c
			fonts/font12.c
			fonts/font16.c
			fonts/font20.c
			fonts/font24.c
			io/LCD_IO_8bit.cpp
			ili932x/LCD_ili932x.cpp
			ili932x/LCD_ili9328_8bit.cpp
			)

set(INCLUDES fonts
			 ili932x
			 io
			 drv)

idf_component_register(
    SRCS ${SOURCES}     # list the source files of this component
    INCLUDE_DIRS . ${INCLUDES} # optional, add here public include directories
    PRIV_INCLUDE_DIRS   # optional, add here private include directories
    REQUIRES driver     # optional, list the public requirements (component names)
    PRIV_REQUIRES       # optional, list the private requirements
)
