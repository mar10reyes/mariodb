#pragma once

#include <vector>
#include "ItemId.hpp"
#include "PageHeader.hpp"

class Page {
    private:
        PageHeader header;
    public:
        // const static int PAGE_SIZE = 4096;
        const static int PAGE_SIZE = 1;
        int pageNumber;
        std::vector<char> items;
    public:
        Page(std::vector<char>& items) {
            this->items = items;
        }
        char* GetPageItems();
        char* GetItem(ItemId itemId);
        void DeleteItem(ItemId itemId);
        void UpdateItem(ItemId itemId);
};