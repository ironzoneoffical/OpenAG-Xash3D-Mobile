cmake_minimum_required(VERSION 3.10)

project(OpenAG-Xash3D-Mobile)

# Platform detection
if(ANDROID)
    set(OPENAG_MOBILE ON)
    add_definitions(-DANDROID -D_LINUX -DLINUX)
else()
    set(OPENAG_MOBILE OFF)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set up compiler flags
if(NOT MSVC)
    if(NOT ANDROID)
        # Ensure 32-bit for desktop Linux
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
    endif()
endif()

# Configure current_version.h
find_package(Git)
if(GIT_FOUND)
    execute_process(COMMAND "${GIT_EXECUTABLE}" show -s --format=%ct
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            OUTPUT_VARIABLE CURRENT_VERSION
            OUTPUT_STRIP_TRAILING_WHITESPACE
            RESULT_VARIABLE CURRENT_VERSION_RESULT)

    if(CURRENT_VERSION_RESULT EQUAL "0")
        set(CURRENT_VERSION "${CURRENT_VERSION}ull")
    else()
        set(CURRENT_VERSION UINT64_MAX)
    endif()
else()
    set(CURRENT_VERSION UINT64_MAX)
endif()

configure_file(cl_dll/current_version.h.in current_version.h)

# Collect source files
add_subdirectory(cl_dll)
add_subdirectory(common)
add_subdirectory(dlls)
add_subdirectory(game_shared)
add_subdirectory(pm_shared)
add_subdirectory(public)

get_property(SOURCE_FILES GLOBAL PROPERTY SOURCE_FILES)
set(SOURCE_FILES ${SOURCE_FILES} "${CMAKE_BINARY_DIR}/current_version.h")

set(CMAKE_SHARED_LIBRARY_PREFIX "")

# Client DLL
add_library(client SHARED ${SOURCE_FILES})
target_include_directories(client PRIVATE
    ${CMAKE_BINARY_DIR}
    common
    dlls
    engine
    external
    game_shared
    pm_shared
    public
    utils/vgui/include)

# Compile definitions
if(NOT MSVC)
    target_compile_definitions(client PRIVATE
        -DGNUC
        -DPOSIX
        -D_POSIX
        -Dstricmp=strcasecmp
        -Dstrnicmp=strncasecmp
        -D_strnicmp=strncasecmp
        -D_snprintf=snprintf
        -D_snwprintf=swprintf
        -D_vsnprintf=vsnprintf
        -D_alloca=alloca)

    if(UNIX AND NOT ANDROID)
        target_compile_definitions(client PRIVATE
            -DLINUX
            -D_LINUX
            -DDISABLE_JUMP_ORIGIN
            -DDISABLE_VEC_ORIGIN)
    endif()
endif()

if(ANDROID)
    target_compile_definitions(client PRIVATE
        -DANDROID
        -D_LINUX
        -DLINUX
        -DDISABLE_DISCORD
        -DDISABLE_STEAM
        -DDISABLE_UPDATE_CHECK)
endif()

target_compile_definitions(client PRIVATE
    -DCLIENT_DLL
    -DCLIENT_WEAPONS)

# Compiler flags
if(NOT MSVC)
    target_compile_options(client PRIVATE
        -Wall
        -Wno-parentheses
        -Wno-sign-compare
        -Wno-unused-function
        -Wno-unused-variable
        -fno-strict-aliasing
        -fno-exceptions)
endif()

# Link libraries
if(ANDROID)
    target_link_libraries(client log android EGL GLESv1_CM)
else()
    # Desktop libraries (SDL2, OpenGL, VGUI)
    if(WIN32)
        target_link_libraries(client
            opengl32
            ${CMAKE_SOURCE_DIR}/lib/public/SDL2.lib
            ${CMAKE_SOURCE_DIR}/lib/public/game_controls.lib
            ${CMAKE_SOURCE_DIR}/lib/public/libcurl_a.lib
            ${CMAKE_SOURCE_DIR}/utils/vgui/lib/win32_vc6/vgui.lib)
    elseif(UNIX)
        if(APPLE)
            find_library(MAC_CARBON Carbon)
            find_library(MAC_OPENGL OpenGL)
            target_link_libraries(client
                ${MAC_CARBON}
                ${MAC_OPENGL}
                ${CMAKE_SOURCE_DIR}/linux/libSDL2-2.0.0.dylib
                ${CMAKE_SOURCE_DIR}/linux/release/vgui.dylib)
        else()
            set(VGUI_LINK_FLAGS "-L${CMAKE_SOURCE_DIR}/linux/release -l:vgui.so")
            set(SDL2_LINK_FLAGS "-L${CMAKE_SOURCE_DIR}/linux -lSDL2")
            set_property(TARGET client PROPERTY LINK_FLAGS "-Wl,--no-as-needed ${VGUI_LINK_FLAGS} ${SDL2_LINK_FLAGS}")
        endif()
    endif()
endif()
