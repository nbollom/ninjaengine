# NinjaEngine
Cross platform game engine/designer tool

## Dependencies
* [cmake](https://cmake.org/download/)
* [QT5](https://www.qt.io/download/)
* [SDL2](https://www.libsdl.org/download-2.0.php)
* [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
* [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
* [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)
* [RapidJSON](https://github.com/miloyip/rapidjson)
 
## Build Instructions (POSIX)
1. Download the sources
2. Make sure the Dependencies are installed
3. Create a build directory and change to it: `mkdir build && cd build`
4. Run cmake to generate the make files: `cmake ..`
5. Run make: `make`

OSX users may need to specify the path to QT5 in the cmake command:

`cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt/5.x/clang_64/`

binaries will be created in the ./bin directory

## Build Instructions (Windows)
coming soon
