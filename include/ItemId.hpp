#pragma once

class ItemId
{
    public:
        int pageId;
        int slotInPage;
        bool isAvailable;
        const static int SIZE = (sizeof(int) * 2) + sizeof(bool); //pageId(int) + slotInPage(int) + isAvailable(bool)
    public:
        ItemId();
};
