cmake_minimum_required(VERSION 3.16)

project(PasswordManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Gui)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    # 添加你的后端文件
    desktoppet.cpp
    desktoppet.h
    loginmanager.cpp
    loginmanager.h
    passwordmanager.cpp
    passwordmanager.h
    fileencryptor.cpp
    fileencryptor.h
    passwordgenerator.cpp
    passwordgenerator.h
    cryptoutils.cpp
    cryptoutils.h
    encryptionhandler.cpp
    encryptionhandler.h
    aes.c
    aes.h
    passwordstrengthchecker.h
    PassWordStrengthChecker.cpp
    # 如果你使用了像 Tiny AES 这样的外部 C++ 库，请将其源文件也添加在这里
    # 例如：aes.c
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    # 对 Qt6 使用 qt_add_executable
    qt_add_executable(PasswordManager
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    # 对 Qt5 或更旧的 CMake/Qt 设置回退到 add_executable
    if(ANDROID)
        add_library(PasswordManager SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(PasswordManager
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# 链接必要的 Qt 库
target_link_libraries(PasswordManager PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
)

# ... (CMakeLists.txt 的其余部分保持不变) ...

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PasswordManager)
endif()
