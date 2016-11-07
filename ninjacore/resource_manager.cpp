//
// Created by nbollom on 11/10/16.
//

#include "resource_manager.h"

namespace NinjaCore {

    Image_ptr ResourceManager::LoadImage(string filename) {
        return make_shared<Image>();
    }

    ResourceManager_ptr resource_manager = make_shared<ResourceManager>();

}
