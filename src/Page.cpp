#include "Page.hpp"
#include <iostream>

//function declaration
std::vector<char> itemIdToCharVec(ItemId itemId);

Page::Page()
{
    // init page with default values
    std::vector<char> pageData(Page::PAGE_SIZE, 'A');
    this->items = pageData;
    
    this->pageNumber = 0;
    this->header = PageHeader();
    this->header.itemWriteOffset   = PAGE_SIZE;
    this->header.itemIdWriteOffset = 0;
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

    const std::vector<char> itemIdInCharVect = itemIdToCharVec(itemId);
    int itemIdWriteOffset = this->header.itemIdWriteOffset;
    
    int item_id_size = item.size();

    if (itemIdWriteOffset >= 0 && itemIdWriteOffset <= PAGE_SIZE) {
        
        int i = itemIdWriteOffset;
        int j = 0;

        while (j < item_id_size) {
            this->items[i] = itemIdInCharVect[j];
            i++;
            j++;
        }
    }
    
    return itemId;
}

//FIXME: this method only works when the itemId reinterpretation to char makes sense as a character, otherwise it wont write it to page therefor to disk.
std::vector<char> itemIdToCharVec(ItemId itemId) {

    int pageId     = itemId.pageId;
    int slotInPage = itemId.slotInPage;

    std::vector<char> mergedData(sizeof(int) * 2); // Allocate space for both integers

    // Copy bytes of pageId into the char vector
    char* pageIdBytes = reinterpret_cast<char*>(&pageId);
    std::copy(pageIdBytes, pageIdBytes + sizeof(int), mergedData.begin());

    std::cout<<"pageIdBytes: "<<pageIdBytes<<std::endl;

    // Copy bytes of slotInPage into the char vector after pageId
    char* slotBytes = reinterpret_cast<char*>(&slotInPage);
    std::copy(slotBytes, slotBytes + sizeof(int), mergedData.begin() + sizeof(int));

    return mergedData;
}