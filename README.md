# NinjaEngine
Cross platform game engine/designer tool

## Requirements
* cmake
* QT5
* SDL2
* SDL2_image
* SDL2_ttf
* SDL2_mixer
* json-c
 
## Build Instructions (POSIX)
1. Download the sources
2. Make sure the requirements are installed
3. Create a build directory and change to it: `mkdir build && cd build`
4. Run cmake to generate the make files: `cmake ..`
5. Run make: `make`

(OSX users may need to specify the path to QT5 in the cmake command:
`cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt/5.x/clang_64/`

binaries will be created in the ./bin directory

## Build Instructions (Windows)
coming soon
