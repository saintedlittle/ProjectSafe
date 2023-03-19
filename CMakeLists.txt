cmake_minimum_required(VERSION 3.25)
project(ProjectSafe)

set(CMAKE_CXX_STANDARD 20)

set(VCPKG_TARGET_TRIPLET "x64-windows-static")
set(VCPKG_BUILD_TYPE "static")

set(LIBS_DIR ${CMAKE_SOURCE_DIR}/libs)

find_package(cryptopp CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)

find_library(DiscordRpcLib NAMES discord-rpc PATHS ${LIBS_DIR})

add_executable(ProjectSafe
        src/main.cpp
        src/app/App.cpp
        src/app/App.h
        src/encryption/Encryptor.cpp
        src/encryption/Encryptor.h
        src/util/Colors.h
        src/key/SafeKey.cpp
        src/key/SafeKey.h
        src/file/FileManager.cpp src/file/FileManager.h src/discord/Discord.h)

target_link_libraries(ProjectSafe PRIVATE cryptopp::cryptopp cxxopts::cxxopts ${DiscordRpcLib})

# Install the executable and any required DLLs
install(TARGETS ProjectSafe RUNTIME DESTINATION bin COMPONENT app)
install(FILES ${LIBS_DIR}/discord-rpc.dll DESTINATION bin COMPONENT app)

# Create an installer
set(CPACK_GENERATOR NSIS) # Use NSIS as the installer generator
set(CPACK_PACKAGE_NAME "ProjectSafe")
set(CPACK_PACKAGE_VENDOR "LeakTeam")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "This program can encrypt and decrypt files and strings.")
set(CPACK_PACKAGE_VERSION "2.2.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\ProjectSafe.exe")
set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_NAME} ${CPACK_PACKAGE_VERSION}")
set(CPACK_NSIS_URL_INFO_ABOUT "http://leanfe.github.io")
set(CPACK_NSIS_CONTACT "fetik228zxc@gmail.com")
set(CPACK_NSIS_MODIFY_PATH ON)

# Add options to create desktop icons and specify custom icons for the installer
set(CPACK_NSIS_CREATE_DESKTOP_ICON "ON")
set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/icon.ico")
set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/icon.ico")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

set(CPACK_NSIS_CREATE_DESKTOP_SHORTCUT ON)
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
set(CPACK_NSIS_MENU_LINKS "bin\\\\ProjectSafe.exe" "${CPACK_PACKAGE_NAME}")

include(CPack)

# Build the installer and upload files
add_custom_command(TARGET ProjectSafe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/dist
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:ProjectSafe> ${CMAKE_BINARY_DIR}/dist/
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} cpack -C ${CPACK_PACKAGE_NAME}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/${CPACK_PACKAGE_NAME}.exe ${CMAKE_BINARY_DIR}/dist/
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${LIBS_DIR}/discord-rpc.dll ${CMAKE_BINARY_DIR}/dist/
        COMMENT "Building installer and uploading files"
        )

# Define the target that builds the installer and uploads files
add_custom_target(installer DEPENDS ProjectSafe)