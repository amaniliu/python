#pragma once
#include <list>
#include <memory>
#include "htdevdefs.h"


class IHCamera;

class /*HTDEVICE_SHARED_EXPORT*/ HCameraLists
{
public:
    static std::list<std::shared_ptr<IHCamera>> FindAll();
};
