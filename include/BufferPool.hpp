#pragma once

#include "Page.hpp"

class BufferPool
{
    public:
        std::vector<Page> frames;
    public:
        BufferPool(/* args */);
        ~BufferPool();
};
