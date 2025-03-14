# CMakeList.txt : CMake project for CHIP8_emulator, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CHIP8_emulator   "main.cpp" "utility.h" "utility.cpp" "system.h" "system.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CHIP8_emulator PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
