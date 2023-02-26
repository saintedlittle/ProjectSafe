cmake_minimum_required(VERSION 3.25)
project(ProjectSafe)

set(CMAKE_CXX_STANDARD 20)

set(VCPKG_TARGET_TRIPLET "x64-windows-static")
set(VCPKG_BUILD_TYPE "static")

find_package(cryptopp CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)

add_executable(ProjectSafe
        src/main.cpp
        src/app/App.cpp
        src/app/App.h
        src/encryption/Encryptor.cpp
        src/encryption/Encryptor.h
        src/util/Colors.h)

target_link_libraries(ProjectSafe PRIVATE cryptopp::cryptopp cxxopts::cxxopts)

# Install the executable and any required DLLs
install(TARGETS ProjectSafe RUNTIME DESTINATION bin)
install(FILES $<TARGET_FILE_DIR:ProjectSafe>/cryptopp.dll DESTINATION bin)
