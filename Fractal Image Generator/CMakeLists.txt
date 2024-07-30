cmake_minimum_required(VERSION 3.21)

project(FractalImageGenerator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
find_package(OpenMP)

add_executable(fractals main.cpp FractalCreator.cpp Mandelbrot.cpp Presets.cpp RGB.cpp ZoomList.cpp Bitmap.cpp)

if(OpenMP_FOUND)
    message(STATUS "Found OpenMP")
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        # Clang-specific flags
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -fopenmp")
        if(APPLE)
            # macOS-specific settings
            include_directories("/opt/homebrew/opt/libomp/include")
            link_directories("/opt/homebrew/opt/libomp/lib")
            set(OpenMP_CXX_LIB_NAMES "omp")
        endif()
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # GCC-specific flags
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        # MSVC-specific flags
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /openmp")
    endif()
    target_link_libraries(fractals PUBLIC OpenMP::OpenMP_CXX)
else()
    message(WARNING "OpenMP not found!")
endif()

