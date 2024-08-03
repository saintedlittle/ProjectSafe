cmake_minimum_required(VERSION 3.22)
project(ProjectSafe)

set(CMAKE_CXX_STANDARD 20)

set(LIBS_DIR "D:/ProjectSafe/libs")

# Путь к Qt
set(Qt_DIR "D:\\Qt\\6.7.2\\msvc2019_64\\lib\\cmake\\Qt6")
set(Qt_BIN_DIR "D:\\Qt\\6.7.2\\msvc2019_64\\bin")
set(Qt_PLUGINS_DIR "D:\\Qt\\6.7.2\\msvc2019_64\\plugins\\platforms")

# Qt-шная хуйня
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Поиск необходимых пакетов
find_package(cryptopp CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
# Найдите библиотеку Discord RPC
find_library(DiscordRpcLib NAMES discord-rpc PATHS ${LIBS_DIR})

# Добавление исходных файлов
add_executable(ProjectSafe
        src/main.cpp
        src/console/App.cpp
        src/console/App.h
        src/encryption/Encryptor.cpp
        src/encryption/Encryptor.h
        src/util/Colors.h
        src/key/SafeKey.cpp
        src/key/SafeKey.h
        src/file/FileManager.cpp src/file/FileManager.h src/discord/Discord.h
        src/locale/LocalizationManager.cpp
        src/locale/LocalizationManager.h
        src/gui/GUIManager.cpp
        src/gui/GUIManager.h
        src/gui/GUIManager.h
        src/gui/widgets/chat/ChatItemWidget.cpp
        src/gui/widgets/chat/ChatItemWidget.h
        src/gui/widgets/chat/ChatItemWidget.h
        src/gui/widgets/ChatListWidget.cpp
        src/gui/widgets/ChatListWidget.h
        src/gui/widgets/ChatListWidget.h
        src/gui/widgets/MainWidget.cpp
        src/gui/widgets/MainWidget.h
        src/gui/widgets/MainWidget.h
        src/gui/widgets/ChatListWidget.cpp
        src/gui/widgets/MainWidget.cpp
        src/gui/tasks/DiscordThread.h
        src/gui/tasks/DiscordThread.h
        src/gui/tasks/DiscordThread.h
        src/gui/widgets/chat/ChatHeaderWidget.cpp
        src/gui/widgets/chat/ChatHeaderWidget.h
        src/gui/widgets/chat/ChatHeaderWidget.h
        src/gui/widgets/chat/ChatHeaderWidget.cpp
        src/gui/widgets/chat/ChatHeaderWidget.h
        src/gui/widgets/chat/ChatWindowWidget.cpp
        src/gui/widgets/chat/ChatWindowWidget.h
        src/gui/widgets/chat/ChatWindowWidget.h
        src/gui/widgets/chat/ChatInputPanel.cpp
        src/gui/widgets/chat/ChatInputPanel.h
)

# Подключение библиотек и директорий
target_include_directories(ProjectSafe PRIVATE ${WEBVIEW2_INCLUDE_DIRS} ${INCLUDE_WINRT_DIR})
target_link_libraries(ProjectSafe PRIVATE cryptopp::cryptopp cxxopts::cxxopts ${DiscordRpcLib} Qt6::Core Qt6::Gui Qt6::Widgets)

# Установка исполняемого файла и необходимых DLL
install(TARGETS ProjectSafe RUNTIME DESTINATION bin COMPONENT app)
install(FILES ${LIBS_DIR}/discord-rpc.dll DESTINATION bin COMPONENT app)

# Добавление кастомных команд для создания директорий и копирования DLL
add_custom_command(TARGET ProjectSafe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/dist
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/dist/platforms
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:ProjectSafe> ${CMAKE_BINARY_DIR}/dist/
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${LIBS_DIR}/discord-rpc.dll ${CMAKE_BINARY_DIR}/dist/
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt_BIN_DIR}/Qt6Core.dll ${CMAKE_BINARY_DIR}/dist/
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt_BIN_DIR}/Qt6Gui.dll ${CMAKE_BINARY_DIR}/dist/
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt_BIN_DIR}/Qt6Widgets.dll ${CMAKE_BINARY_DIR}/dist/
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt_PLUGINS_DIR}/qwindows.dll ${CMAKE_BINARY_DIR}/dist/platforms/
        COMMENT "Building installer and uploading files"
)

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

# Добавляем файлы для установки в инсталлятор
set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS
        "File /r \"${CMAKE_BINARY_DIR}/dist/*\""
        "CreateDirectory \"\$INSTDIR\\platforms\""
        "File /r \"${CMAKE_BINARY_DIR}/dist/platforms/*\""
)

include(CPack)

# Определение цели, которая строит инсталлятор и загружает файлы
add_custom_target(installer DEPENDS ProjectSafe)
