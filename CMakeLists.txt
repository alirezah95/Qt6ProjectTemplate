cmake_minimum_required(VERSION 3.16)

project(ProjectTemplate VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

#
# Set up project properties
#

# Define main target based on project name to change it easily
set(MAIN_TARGET_NAME app${CMAKE_PROJECT_NAME})
set(MAIN_TARGET_URI  ${CMAKE_PROJECT_NAME})

set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Qml)

# Set QT_IMPORT_PATH
set(QML_IMPORT_PATH
    ${QT_QML_OUTPUT_DIRECTORY}
    CACHE
    STRING ""
    FORCE
)

# Some properties for mobile devices
set(PROJECT_VERSION_SHORT ${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR})
set(BUILD_CODE 8)
set(PACKAGE_IDENTIFIER "com.example.projecttemplate")

# NO_CACHEGEN is set for qt_add_qml_module() in DEBUG mode so we can have a better QML Preview
# functionality (Only Qt6.6 and later)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(MODULE_CACHEGEN_STATE
        NO_CACHEGEN
    )
endif()

#
# Intialize the project
#

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(${MAIN_TARGET_NAME}
    Src/main.cpp
)

qt_add_qml_module(${MAIN_TARGET_NAME}
    URI ProjectTemplate
    ${MODULE_CACHEGEN_STATE}
    VERSION 1.0

    QML_FILES
        Qml/Main.qml
)

#
# Add submodules here
#

add_subdirectory(Res/)
add_subdirectory(Qml/Style)

#
# Target related properties and definitions
#

# Pass main target uri to C++
target_compile_definitions(${MAIN_TARGET_NAME} PRIVATE
    MAIN_MODULE="${MAIN_TARGET_URI}"
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${MAIN_TARGET_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER ${PACKAGE_IDENTIFIER}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    # Override android package source directory
    # QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
)

if (ANDROID)
    set_target_properties(appNuve PROPERTIES
         QT_ANDROID_EXTRA_LIBS
             "${ANDROID_SDK_ROOT}/android_openssl/ssl_3/${CMAKE_ANDROID_ARCH_ABI}/libcrypto_3.so;${ANDROID_SDK_ROOT}/android_openssl/ssl_3/${CMAKE_ANDROID_ARCH_ABI}/libssl_3.so"
    )
elseif (IOS)
    set(PRODUCT_NAME ${PROJECT_NAME})
    set(PRODUCT_BUNDLE_IDENTIFIER ${PACKAGE_IDENTIFIER})

    # Configure custom Info.plist
    configure_file(${CMAKE_SOURCE_DIR}/Res/iOS/Info.plist.in
        ${CMAKE_CURRENT_BINARY_DIR}/Info.plist
        @ONLY
    )

    set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/Info.plist"
        PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources
    )

    set_target_properties(${MAIN_TARGET_NAME} PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_BINARY_DIR}/Info.plist"
    )

    # Prepare ios icon pack
    set(IOS_ASSETS_PATH
        ${CMAKE_SOURCE_DIR}/Res/iOS/Assets.xcassets
    )

    # Path to .xcassets folder
    set(CMAKE_XCODE_ATTRIBUTE_ASSET_CATALOGS ${IOS_ASSETS_PATH})
    # App Icon name: Must match the prefix of icon-set folder inside .xcassets
    set(CMAKE_XCODE_ATTRIBUTE_ASSET_CATALOGS_APP_ICON "AppIcon")

    # Add .xcassets as resource
    target_sources(${MAIN_TARGET_NAME} PRIVATE
        ${IOS_ASSETS_PATH}
    )

    # Set assets location to Resources
    set_source_files_properties(${IOS_ASSETS_PATH}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources
    )

    # Set appicon pack name
    set_target_properties(${MAIN_TARGET_NAME} PROPERTIES
        XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME AppIcon;
    )
endif()

target_link_libraries(${MAIN_TARGET_NAME} PRIVATE
    Qt6::Quick
    appResources
    ApplicationStyleplugin
)

include(GNUInstallDirs)
install(TARGETS ${MAIN_TARGET_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
