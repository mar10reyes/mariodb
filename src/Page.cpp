#include "Page.hpp"
#include <iostream>
#include <string.h>
#include <cstring>

//function declaration
std::vector<char> itemIdToCharVec(ItemId itemId);

Page::Page()
{
    // init page with default values
    std::vector<char> pageData(Page::PAGE_SIZE, 0);
    this->items = pageData;
    
    this->pageNumber = 0;
    this->header = PageHeader();
    this->header.itemWriteOffset   = PAGE_SIZE;
    this->header.itemIdWriteOffset = HEADER_SIZE; //write after the header
}

Page::Page(std::vector<char>& items) 
{
    this->items = items;

    this->pageNumber = 0;
    this->header = PageHeader();
    this->header.itemWriteOffset   = PAGE_SIZE;
    this->header.itemIdWriteOffset = HEADER_SIZE; //write after the header
}

bool UpdateOffsets(int itemWriteOffset, int itemIdWriteOffset, Page &page)
{
    std::vector<char> offsets(Page::HEADER_SIZE); // Allocate space for both integers and is Available boolean

    char* itemWriteOffsetInBytes = reinterpret_cast<char*>(&itemWriteOffset);
    std::copy(itemWriteOffsetInBytes, itemWriteOffsetInBytes + sizeof(int), offsets.begin());

    // Copy bytes of slotInPage into the char vector after pageId
    char* itemIdWriteOffsetInBytes = reinterpret_cast<char*>(&itemIdWriteOffset);
    std::copy(itemIdWriteOffsetInBytes, itemIdWriteOffsetInBytes + sizeof(int), offsets.begin() + sizeof(int));

    int i = 0;
    int j = 0;

    while (j < offsets.size()) {
        page.items[i] = offsets[j];
        i++;
        j++;
    }

    return true;
}

ItemId Page::AddItem(std::vector<char> item)
{
    int offset = this->header.itemWriteOffset;

    int item_size = item.size();

    //FIXME: make sure inludes other things like headers and other data that is included in a page
    if (offset >= 0 && offset <= PAGE_SIZE) {
        
        int i = offset - item_size;
        int j = 0;

        while (j < item_size) {
            this->items[i] = item[j];
            i++;
            j++;
        }
    }

    ItemId itemId = ItemId();
    itemId.pageId = this->pageNumber;

    itemId.slotInPage = offset;
    itemId.isAvailable = false;

    const std::vector<char> itemIdInCharVect = itemIdToCharVec(itemId);

    int itemIdWriteOffset = this->header.itemIdWriteOffset;
    
    int item_id_size = itemIdInCharVect.size();

    if (itemIdWriteOffset >= 0 && itemIdWriteOffset <= PAGE_SIZE) {
        
        int i = itemIdWriteOffset;
        int j = 0;

        while (j < item_id_size) {
            this->items[i] = itemIdInCharVect[j];
            i++;
            j++;
        }
    }

    this->header.itemWriteOffset   += -item_size;
    this->header.itemIdWriteOffset += item_id_size;

    UpdateOffsets(this->header.itemWriteOffset, this->header.itemIdWriteOffset, *this);
    
    return itemId;
}

//FIXME: this method only works when the itemId reinterpretation to char makes sense as a character, otherwise it wont write it to page therefor to disk.
std::vector<char> itemIdToCharVec(ItemId itemId) {

    int pageId       = itemId.pageId;
    int slotInPage   = itemId.slotInPage;
    bool isAvailable = itemId.isAvailable;

    std::vector<char> mergedData(ItemId::SIZE); // Allocate space for both integers and is Available boolean

    // Copy bytes of pageId into the char vector
    char* pageIdBytes = reinterpret_cast<char*>(&pageId);
    std::copy(pageIdBytes, pageIdBytes + sizeof(int), mergedData.begin());

    // Copy bytes of slotInPage into the char vector after pageId
    char* slotBytes = reinterpret_cast<char*>(&slotInPage);
    std::copy(slotBytes, slotBytes + sizeof(int), mergedData.begin() + sizeof(int));

    // Copy bytes of isAvaliable into the char vector after slotInPage
    char* isAvailableInBytes = reinterpret_cast<char*>(&isAvailable);
    std::copy(isAvailableInBytes, isAvailableInBytes + sizeof(bool), mergedData.begin() + sizeof(int) + sizeof(int));

    return mergedData;
}