find_package(simppl)

add_executable(nm_dbus_example
    main.cpp
)

set_property(TARGET nm_dbus_example PROPERTY CXX_STANDARD 11)

target_include_directories(nm_dbus_example PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../include)

target_link_libraries(nm_dbus_example NMDBus)

