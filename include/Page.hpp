#pragma once

#include <vector>
#include "ItemId.hpp"
#include "PageHeader.hpp"

class Page {
    public:
        PageHeader header;
    public:
        const static int PAGE_SIZE   = 4096;
        const static int HEADER_SIZE = sizeof(int)*2; //itemWriteOffset + itemIdWriteOffset
        int pageNumber;
        std::vector<char> items;
    public:
        Page();
        Page(std::vector<char>& items);
        ItemId AddItem(std::vector<char> item);
        char* GetPageItems();
        char* GetItem(ItemId itemId);
        void DeleteItem(ItemId itemId);
        void UpdateItem(ItemId itemId);
        bool HasSpaceForItem(std::vector<char> item);
};