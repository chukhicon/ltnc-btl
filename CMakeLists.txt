cmake_minimum_required(VERSION 3.0.0)
project(khicon VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
# include_directories(
#     ${PROJECT_SOURCE_DIR}
#     ${PROJECT_SOURCE_DIR}
# )
file(GLOB game_SRC
    "${PROJECT_SOURCE_DIR}/*.cpp"
    "${PROJECT_SOURCE_DIR}/*.h"
)    

if (WIN32)
    set(SDL2_INCLUDE_DIR "C:/SDL2-2.0.20/x86_64-w64-mingw32/include/SDL2")
    set(SDL2_LIBRARY_DIR "C:/SDL2-2.0.20/x86_64-w64-mingw32/lib")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mwindows -static-libgcc -static-libstdc++")
    include_directories(${SDL2_INCLUDE_DIR})
    link_directories(${SDL2_LIBRARY_DIR})
else ()
    include_directories(/usr/include/SDL2)
    include_directories(/usr/include/SDL)
    link_directories(${SDL2_LIBRARY_DIRS})
endif ()

add_executable(khicon ${game_SRC})
set_target_properties(khicon PROPERTIES LINKER_LANGUAGE CXX)
if (WIN32)
    target_link_libraries(khicon -lmingw32)
endif ()
target_link_libraries(khicon
    -lSDL2main
    -lSDL2
    -lSDL2_image
    -lSDL2_mixer
    -lSDL2_ttf
)

# install(DIRECTORY res DESTINATION res)
file(COPY imgs Font DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
if (WIN32)
    file(GLOB lib
        "${SDL2_LIBRARY_DIR}/../bin/*.dll"
        "${SDL2_LIBRARY_DIR}/../bin/*.txt"
    )    
    file(COPY ${lib} "C:/mingw64/bin/libwinpthread-1.dll" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif ()
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
