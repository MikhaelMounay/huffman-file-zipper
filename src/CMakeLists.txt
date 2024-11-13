project(HuffmanFileZipper_lib)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

file(GLOB_RECURSE SRC *.cpp *.h *.ui)
list(REMOVE_ITEM SRC ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_library(HuffmanFileZipper_lib ${SRC})
target_link_libraries(HuffmanFileZipper_lib
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
