//
// Created by nbollom on 13/10/16.
//

#ifndef PROJECT_WINDOW_MANAGER_H
#define PROJECT_WINDOW_MANAGER_H

#include <memory>
#include <vector>
#include <string>
#include "window.h"
#include "types.h"

using namespace std;

namespace NinjaCore {

    class WindowManager {
    private:
        vector<Window_ptr> _windows;

    public:
        Window_ptr OpenWindow(Size window_size, Size design_size, string title, bool fullscreen);

    };

    typedef shared_ptr<WindowManager> WindowManager_ptr;

    extern WindowManager_ptr window_manager;

}

#endif //PROJECT_WINDOW_MANAGER_H
