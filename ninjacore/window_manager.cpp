//
// Created by nbollom on 13/10/16.
//

#include "window_manager.h"

namespace NinjaCore {

    WindowManager_ptr window_manager = make_shared<WindowManager>();

    Window_ptr WindowManager::OpenWindow(Size window_size, Size design_size, string title, bool fullscreen) {
        Window_ptr window = make_shared<Window>(window_size, design_size, title, fullscreen);
        _windows.push_back(window);
        return window;
    }
}