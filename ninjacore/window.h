//
// Created by nbollom on 13/10/16.
//

#ifndef PROJECT_WINDOW_H
#define PROJECT_WINDOW_H

#include <memory>
#include "types.h"

using namespace std;

namespace NinjaCore {

    class Window {
    private:
        Size _window_size;
        Size _design_size;
        string _title;
        bool _fullscreen;

    public:
        Window(Size window_size, Size design_size, string title, bool fullscreen);

    };

    typedef shared_ptr<Window> Window_ptr;

}

#endif //PROJECT_WINDOW_H
