cmake_minimum_required(VERSION 3.22)
project(ProjectSafe)

set(CMAKE_CXX_STANDARD 20)

set(LIBS_DIR ${CMAKE_SOURCE_DIR}/libs)

find_package(cryptopp CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)

# Найдите библиотеку Discord RPC
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
        src/file/FileManager.cpp src/file/FileManager.h src/discord/Discord.h
        src/locale/LocalizationManager.cpp
        src/locale/LocalizationManager.h
)

# Подключение библиотек и директорий
target_include_directories(ProjectSafe PRIVATE ${WEBVIEW2_INCLUDE_DIRS} ${INCLUDE_WINRT_DIR})
target_link_libraries(ProjectSafe PRIVATE cryptopp::cryptopp cxxopts::cxxopts ${DiscordRpcLib})

# Установка исполняемого файла и необходимых DLL
install(TARGETS ProjectSafe RUNTIME DESTINATION bin COMPONENT app)
install(FILES ${LIBS_DIR}/discord-rpc.dll DESTINATION bin COMPONENT app)

# Создание инсталлятора
set(CPACK_GENERATOR NSIS) # Использовать NSIS как генератор инсталлятора
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

# Добавление опций для создания ярлыков на рабочем столе и указания пользовательских иконок для инсталлятора
set(CPACK_NSIS_CREATE_DESKTOP_ICON "ON")
set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/icon.ico")
set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/icon.ico")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

set(CPACK_NSIS_CREATE_DESKTOP_SHORTCUT ON)
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
set(CPACK_NSIS_MENU_LINKS "bin\\\\ProjectSafe.exe" "${CPACK_PACKAGE_NAME}")

include(CPack)

# Построение инсталлятора и загрузка файлов
add_custom_command(TARGET ProjectSafe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/dist
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:ProjectSafe> ${CMAKE_BINARY_DIR}/dist/
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} cpack -C ${CPACK_PACKAGE_NAME}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/${CPACK_PACKAGE_NAME}.exe ${CMAKE_BINARY_DIR}/dist/
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${LIBS_DIR}/discord-rpc.dll ${CMAKE_BINARY_DIR}/dist/
        COMMENT "Building installer and uploading files"
)

# Определение цели, которая строит инсталлятор и загружает файлы
add_custom_target(installer DEPENDS ProjectSafe)
