cmake_minimum_required(VERSION 3.9)

project(NMDBus VERSION 0.1.0 DESCRIPTION "A library to interact with network manager via DBus")

add_library(${PROJECT_NAME} SHARED
    ${CMAKE_CURRENT_LIST_DIR}/src/DbusHelpers.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AccessPoint.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ActiveConnection.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AgentManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Connection.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Device.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Dispatcher.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Ip4Config.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Settings.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/WirelessDevice.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER 
    ${CMAKE_CURRENT_LIST_DIR}/include/nmdbus/AccessPoint.h
    ${CMAKE_CURRENT_LIST_DIR}/include/nmdbus/ActiveConnection.h
    ${CMAKE_CURRENT_LIST_DIR}/include/nmdbus/AgentManager.h
    ${CMAKE_CURRENT_LIST_DIR}/include/nmdbus/Connection.h
    ${CMAKE_CURRENT_LIST_DIR}/include/nmdbus/DbusHelpers.h
    ${CMAKE_CURRENT_LIST_DIR}/include/nmdbus/DbusObject.h
    ${CMAKE_CURRENT_LIST_DIR}/include/nmdbus/Device.h
    ${CMAKE_CURRENT_LIST_DIR}/include/nmdbus/Dispatcher.h
    ${CMAKE_CURRENT_LIST_DIR}/include/nmdbus/ForwardProxy.h
    ${CMAKE_CURRENT_LIST_DIR}/include/nmdbus/Ip4Config.h
    ${CMAKE_CURRENT_LIST_DIR}/include/nmdbus/NetworkManager.h
    ${CMAKE_CURRENT_LIST_DIR}/include/nmdbus/DBusTypes.h
    ${CMAKE_CURRENT_LIST_DIR}/include/nmdbus/Settings.h
    ${CMAKE_CURRENT_LIST_DIR}/include/nmdbus/UUID.h
    ${CMAKE_CURRENT_LIST_DIR}/include/nmdbus/WirelessDevice.h
)

include(GNUInstallDirs)
configure_file(${CMAKE_CURRENT_LIST_DIR}/NMDBus.pc.in DESTINATION ${CMAKE_BINARY_DIR}/NMDBus.pc)

find_package(DBus1 REQUIRED)
find_package(simppl REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PUBLIC
    dbus-1::dbus-1
    simppl::simppl
    ${CMAKE_THREAD_LIBS_INIT}
)

if (BUILD_TESTING)
    add_subdirectory(examples)
endif()

install(TARGETS ${PROJECT_NAME} EXPORT NMDBusConfig
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ${PROJECT_NAME}Config DESTINATION /usr/share/NMDBusConfig/cmake)

export(TARGETS ${PROJECT_NAME} FILE NMDBusConfig.cmake)

install(FILES ${CMAKE_BINARY_DIR}/NMDBus.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
