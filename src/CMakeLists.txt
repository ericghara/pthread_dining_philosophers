add_library(lib
        chopstick.c
        chopstick.h
        philosopher.c
        philosopher.h
        philosopher.c
)

target_include_directories(lib PUBLIC ${CMAKE_CURRENT_LIST_DIR})