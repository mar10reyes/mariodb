//#pragma once

#include <iostream>
#include "Page.hpp"
#include "StorageManager.hpp"
#include "SerializationHandler.hpp"

//function declararions
void testStorageManager();
void testItemIds(Page &page, int n);
void testItemWriteToPage(Page &page, std::vector<char> itemToAdd);

// g++ -std=c++11 -o program src/*.cpp -I include

int main(int argc, char const *argv[])
{
    std::cout<<"mariodb initialized!"<<std::endl;
    testStorageManager();
    return 0;
}

void testStorageManager() {
    // Example usage
    const char* filename = "./db.mdb";
    int pageNumber = 0;

    // Create a sample page with data (you should replace this with your actual page data)
    //std::vector<char> pageData(Page::PAGE_SIZE, 'A');
    //Page page = Page(pageData);
    Page page = Page();
    page.pageNumber = pageNumber;
    //page.header = PageHeader();
    //page.header.itemWriteOffset = 32;

    std::vector<char> item(16, 'C');
    std::vector<char> item2(16, 'D');
    std::vector<char> item3(16, 'E');
    std::vector<char> item4(16, 'F');
    std::vector<char> item5(16, 'G');
    std::vector<char> item6(16, 'H');

    testItemWriteToPage(page, item);
    testItemWriteToPage(page, item2);
    testItemWriteToPage(page, item3);
    testItemWriteToPage(page, item4);
    testItemWriteToPage(page, item5);
    testItemWriteToPage(page, item6);

    // std::cout<<"page before storage manager"<<std::endl;
    // // Display the retrieved page data (replace this with your actual processing)
    // for (int i=0; i < Page::PAGE_SIZE; i++) {
    //     std::cout << page.items[i];
    // }

    StorageManager storageManager = StorageManager(filename, filename);

    // Store the page on disk
    //storePageOnDisk(filename, pageNumber, pageData);
    storageManager.flushPage(page);

    // Clear the vector to store the retrieved page data
    //pageData.clear();
    //pageData.resize(Page::PAGE_SIZE);
    std::cout<<"page flushed!"<<std::endl;

    // Retrieve the page from disk
    //retrievePageFromDisk(filename, pageNumber, pageData);
    Page page1 = storageManager.getPage(0);

    std::cout<<"page retrieved!"<<std::endl;

    std::cout<<"page --------------------------"<<std::endl;
    std::cout<<"page --------------------------"<<std::endl;
    std::cout<<"page --------------------------"<<std::endl;
    std::cout<<std::endl;

    testItemIds(page, 6);

    std::cout<<"page1 --------------------------"<<std::endl;
    std::cout<<"page1 --------------------------"<<std::endl;
    std::cout<<"page1 --------------------------"<<std::endl;
    std::cout<<std::endl;

    testItemIds(page1, 6);

}

void testItemWriteToPage(Page &page, std::vector<char> itemToAdd) {
    std::cout<<"adding item..."<<std::endl;
    ItemId itemId = page.AddItem(itemToAdd);
    //ItemId itemId = page.AddItemMemcpy(itemToAdd);

    std::cout<<"item added at page: "<<itemId.pageId<<std::endl;
    std::cout<<"item added at slot: "<<itemId.slotInPage<<std::endl;
}

///------------------------------------------------------------------------------------------------------------------------------

// Function to print the binary representation of a byte
void printByteAsBits(unsigned char byte) {
    for (int i = 7; i >= 0; --i) {
        std::cout << ((byte >> i) & 1);
    }
}

// Function to print a set of bytes as bits
void printBytesAsBits(const unsigned char* bytes, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printByteAsBits(bytes[i]);
        std::cout << ' '; // Separate bytes by space
    }
    std::cout << std::endl;
}

///------------------------------------------------------------------------------------------------------------------------------

void testItemIds(Page &page, int n_items) {

    // return;
    
    std::cout<<"inside testItemIds"<<std::endl;
    
    // Display the retrieved page data (replace this with your actual processing)
    // for (int i=0; i < Page::PAGE_SIZE; i++) {
    //     std::cout << page.items[i];
    // }

    // char* itemIds;
    // // std::copy(page.items.begin(), page.items.begin() + (ItemId::SIZE * 6), itemIds);

    // std::memcpy(&itemIds, page.items, (ItemId::SIZE * 6));

    char itemIds[n_items * ItemId::SIZE]; // Allocate memory for 6 items
    std::memcpy(itemIds, page.items.data(), n_items * ItemId::SIZE);

    std::cout<<"--------------"<<std::endl;
    std::cout<<std::endl;



    for (size_t i = 0; i < n_items; i++)
    {
        // char* currentItemId[ItemId::SIZE];
        // // std::copy(itemIds, itemIds + ItemId::SIZE, currentItemId);
        // std::memcpy(currentItemId, itemIds, ItemId::SIZE);

        // char* slotInPageBytes;
        // char* pageIdInBytes;
        // char* isAvailableInBytes;

        // std::copy(currentItemId, currentItemId + sizeof(int), pageIdInBytes);
        // std::copy(currentItemId + sizeof(int), currentItemId + sizeof(int), slotInPageBytes);
        // std::copy(currentItemId + sizeof(int) + sizeof(int), currentItemId + sizeof(bool), isAvailableInBytes);

        char currentItemId[ItemId::SIZE];
        // char currentItemId[16];
        std::memcpy(currentItemId, itemIds + (i*ItemId::SIZE), ItemId::SIZE);
        // std::memcpy(currentItemId, itemIds, (size_t)16);

        // std::cout<<"size of currentItemId: "<<sizeof(currentItemId)<<std::endl;
        // size_t dataSize = sizeof(currentItemId);

        // std::cout << "Data in bits: ";
        // printBytesAsBits((const unsigned char*)currentItemId, dataSize);

        // char first8BytesOfPage[16];
        // std::memcpy(first8BytesOfPage, page.items.data(), (size_t)16);

        // size_t _dataSize = sizeof(first8BytesOfPage);

        // std::cout << "page in bits: ";
        // printBytesAsBits((const unsigned char*)first8BytesOfPage, _dataSize);


        char pageIdInBytes[sizeof(int)]; // Allocate memory for pageIdInBytes
        char slotInPageBytes[sizeof(int)]; // Allocate memory for slotInPageBytes
        char isAvailableInBytes[sizeof(bool)]; // Allocate memory for isAvailableInBytes

        // Copy the data from currentItemId into pageIdInBytes, slotInPageBytes, and isAvailableInBytes
        std::memcpy(pageIdInBytes, currentItemId, sizeof(int)); 
        std::memcpy(slotInPageBytes, currentItemId + sizeof(int), sizeof(int));
        std::memcpy(isAvailableInBytes, currentItemId + sizeof(int) + sizeof(int), sizeof(bool));

        // std::cout<<"size of pageIdInBytes: "<<sizeof(pageIdInBytes)<<std::endl;
        // std::cout<<"size of currentItemId: "<<sizeof(currentItemId)<<std::endl;

        // int pageId = reinterpret_cast<int>(&pageIdInBytes);
        // int slotInPage = reinterpret_cast<int>(&slotInPageBytes);
        // int isAvailable = reinterpret_cast<int>(&isAvailableInBytes);

        // int pageId;
        // int slotInPage;
        // bool isAvailable;

        SerializationHandler serializationHandler;
        std::string _serializedData;

        _serializedData = pageIdInBytes;
        serializationHandler.serializedData = std::vector<char> (_serializedData.begin(), _serializedData.end());
        int pageId = serializationHandler.deserialize<int>(pageIdInBytes);
        
        _serializedData = slotInPageBytes;
        serializationHandler.serializedData = std::vector<char> (_serializedData.begin(), _serializedData.end());
        int slotInPage = serializationHandler.deserialize<int>(slotInPageBytes);

        _serializedData = isAvailableInBytes;
        serializationHandler.serializedData = std::vector<char> (_serializedData.begin(), _serializedData.end());
        bool isAvailable = serializationHandler.deserialize<bool>(isAvailableInBytes);

        std::cout<<"--------------"<<std::endl;
        std::cout<<std::endl;

        std::cout<<"page id: "<<pageId<<std::endl;
        std::cout<<"Slot in page: "<<slotInPage<<std::endl;
        std::cout<<"is available: "<<isAvailable<<std::endl;

        std::cout<<std::endl;
        std::cout<<"--------------"<<std::endl;
    }
    
}