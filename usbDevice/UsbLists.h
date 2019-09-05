#pragma once
#include <list>
#include <memory>

class IUsb;

class UsbLists
{
    public:
    std::list<std::shared_ptr<IUsb>>  find_all();
    static std::list<std::shared_ptr<IUsb>>  find_vid_pid(int vid, int pid);
};