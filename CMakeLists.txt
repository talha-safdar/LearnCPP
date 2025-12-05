# CMakeLists.txt for Project Tora

# 1. Minimum CMake Version Requirement
# (A version like 3.10 is widely available and supports modern CMake features)
cmake_minimum_required(VERSION 3.10)

# 2. Project Definition
# Define the project name and the language used
project(Syrum VERSION 1.0
    LANGUAGES CXX
)

# 3. C++ Standard Configuration
# This is the critical part to fix your std::make_unique error and 'auto' warning.
# Set the compiler to use C++20 (recommended)
set(CMAKE_CXX_STANDARD 20)
# Make C++20 mandatory; configuration will fail if the compiler doesn't support it
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Source File Discovery
# Define a variable (TORA_SOURCES) containing all .cpp files in the src/ directory.
# NOTE: While file(GLOB) is simple, remember to use "CMake: Configure" 
#       in VS Code if you add new files to src/.
file(GLOB SOURCES "src/*.cpp")

# 5. Executable Target Definition
# Create the executable named 'Tora' from the discovered source files
add_executable(Syrum ${SOURCES})

# 6. Target-Specific Include Directories
# Tell the 'Tora' target where to find header files (in the 'include' directory).
# PRIVATE means only source files of the 'Tora' target can use this path.
target_include_directories(Syrum PRIVATE
    include
)

# 7. (Optional) Linking Libraries
# If you need external libraries (like SFML, Boost, etc.), link them here.
# Example: target_link_libraries(Tora PRIVATE sfml-graphics)