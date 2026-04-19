cmake_minimum_required(VERSION 3.16)

project(StringHunter2026 LANGUAGES C)

add_executable(StringHunter2026


    src/SimpleBinFile.c
    src/SimpleBinFile.h
    src/StringHunter.c
    src/StringHunter.h
    src/main.c
)

include(GNUInstallDirs)
install(TARGETS StringHunter2026
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
