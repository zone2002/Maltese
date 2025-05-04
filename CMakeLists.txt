cmake_minimum_required(VERSION 3.16)

project(Maltese VERSION 0.1 LANGUAGES CXX)

# 目录结构定义
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(RES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)

# 自动处理Qt元对象系统
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 编译器标准设置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Qt依赖
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# 收集源文件（关键修改：分离头文件和源文件）
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS
    ${INCLUDE_DIR}/*.h
    ${SRC_DIR}/*.h  # 包含需要moc处理的头文件
)

# 资源文件配置
set(QRC_FILES ${RES_DIR}/imgs.qrc)

# 可执行目标配置
if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_add_executable(Maltese
        MANUAL_FINALIZATION
        ${SOURCES}
        ${HEADERS}
        ${QRC_FILES}
    )
else()
    if(ANDROID)
        add_library(Maltese SHARED
            ${SOURCES}
            ${HEADERS}
            ${QRC_FILES}
        )
    else()
        add_executable(Maltese
            ${SOURCES}
            ${HEADERS}
            ${QRC_FILES}
        )
    endif()
endif()

# 目标属性配置（必须在目标创建后设置）
target_include_directories(Maltese PRIVATE
    ${INCLUDE_DIR}
    ${SRC_DIR}
)

target_link_libraries(Maltese PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

# macOS/iOS捆绑包配置
if(QT_VERSION VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION
        MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Maltese
    )
endif()

set_target_properties(Maltese PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 安装配置
include(GNUInstallDirs)
install(TARGETS Maltese
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Qt6最终化处理
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Maltese)
endif()

# 生成compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
