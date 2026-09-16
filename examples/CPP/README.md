# ERS C++ examples

The `CMakeLists.txt` file can be used as a starting point for a project that uses ERS.
Each of the examples in this uses this CMake file as the base for their own CMake configuration.

The rest of this README goes over the requirements and builds steps to use ERS in C++.

## Requirements

Before starting it is assumed a C/C++ compatible compiler which supports C++20 is preinstalled, if this isn't the case we recommend MSVC (Visual studio) on Windows, and GCC or Clang on Linux distributions.

ERS also requires CMake and VCPKG to be installed and added to the path.

### Windows

Create a directory to clone vcpkg in this example we use `C:/Local`.

```bash
mkdir C:/local
cd C:/local
git clone https://github.com/microsoft/vcpkg
```

Then add a new variable called VCPKG_ROOT to your systems environment variables. This variable needs to point to ```C:/Local/vcpkg``` (or wherever vcpkg is installed).

### Linux

Create a directory to clone vcpkg in this example we use the home directory.

```bash
cd ~
git clone https://github.com/microsoft/vcpkg
```

Then add a new variable called VCPKG_ROOT to your systems environment variables. This variable needs to point to ```/home/user/vcpkg``` (or wherever vcpkg is installed).

## Building

```cmake
# Execute this in a shell from inside template project directory

mkdir build
cd build
cmake .. # This downloads the latest ERS build depending on the version specific in CMakeLists.txt
cmake --build . # Optionally add -j16 to build with 16 threads (or specify more if needed)
```
