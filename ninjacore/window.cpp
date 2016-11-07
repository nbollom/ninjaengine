//
// Created by nbollom on 13/10/16.
//

#include "window.h"
#include "types.h"

namespace NinjaCore {

    Window::Window(Size window_size, Size design_size, string title, bool fullscreen) {
        _window_size = window_size;
        _design_size = design_size;
        _title = title;
        _fullscreen = fullscreen;
    }

}
