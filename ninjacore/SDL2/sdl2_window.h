//
// Created by nbollom on 14/10/16.
//

#ifndef PROJECT_SDL2_WINDOW_H
#define PROJECT_SDL2_WINDOW_H

#include <SDL.h>
#include <string>
#include "../window.h"
#include "../types.h"

using namespace std;

namespace NinjaCore {

    class Window_SDL : public Window {
    private:
        SDL_Window *window;

    public:
        Window_SDL(Size window_size, Size design_size, string title, bool fullscreen);

    };

}

#endif //PROJECT_SDL2_WINDOW_H
