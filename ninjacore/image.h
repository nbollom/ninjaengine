//
// Created by nbollom on 12/10/16.
//

#ifndef PROJECT_IMAGE_H
#define PROJECT_IMAGE_H

#include <memory>

using namespace std;

namespace NinjaCore {

    class Image {

    public:
        Image();

    };

    typedef shared_ptr<Image> Image_ptr;
    extern Image_ptr create_image();

}

#endif //PROJECT_IMAGE_H
