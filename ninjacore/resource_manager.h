//
// Created by nbollom on 11/10/16.
//

#ifndef PROJECT_RESOURCE_MANAGER_H
#define PROJECT_RESOURCE_MANAGER_H

#include <string>
#include <memory>
#include "image.h"

using namespace std;

namespace NinjaCore {

    class ResourceManager {
    public:
        Image_ptr LoadImage(string filename);
    };

    typedef shared_ptr<ResourceManager> ResourceManager_ptr;

    extern ResourceManager_ptr resource_manager;

}

#endif //PROJECT_RESOURCE_MANAGER_H
