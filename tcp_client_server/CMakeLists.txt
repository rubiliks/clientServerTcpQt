cmake_minimum_required(VERSION 3.16)

project(tcp_client_server LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(tcp_client_server
  main.cpp
  server.h server.cpp
)
target_link_libraries(tcp_client_server Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(tcp_client_server  Qt6::Network)


include(GNUInstallDirs)
install(TARGETS tcp_client_server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
