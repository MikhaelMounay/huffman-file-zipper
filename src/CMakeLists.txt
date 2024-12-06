project(HuffmanFileZipper_lib)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

file(GLOB_RECURSE SRC *.cpp *.h *.ui ${CMAKE_SOURCE_DIR}/resources/*.qrc ${CMAKE_SOURCE_DIR}/resources/*.rc)
list(REMOVE_ITEM SRC ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_library(HuffmanFileZipper_lib ${SRC})
target_link_libraries(HuffmanFileZipper_lib
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
target_link_libraries(HuffmanFileZipper_lib bcrypt)
