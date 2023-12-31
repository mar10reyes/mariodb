#pragma once

#include <vector>
#include "ItemId.hpp"
#include "PageHeader.hpp"

class Page {
    public:
        PageHeader header;
    public:
        const static int PAGE_SIZE = 4096;
        int pageNumber;
        std::vector<char> items;
    public:
        Page();
        Page(std::vector<char>& items) {
            this->items = items;
        }
        ItemId AddItem(std::vector<char> item);
        char* GetPageItems();
        char* GetItem(ItemId itemId);
        void DeleteItem(ItemId itemId);
        void UpdateItem(ItemId itemId);
};