#include "ItemId.hpp"

class Page {
    private:
        PageHeader header;
    public:
        char* items;
    public:
        char* GetPageItems();
        char* GetItem(ItemId itemId);
        void DeleteItem(ItemId itemId);
        void UpdateItem(ItemId itemId);
}