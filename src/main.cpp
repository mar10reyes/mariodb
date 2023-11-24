//#pragma once

#include <iostream>
#include "Page.hpp"
#include "StorageManager.hpp"

//function declararions
void testStorageManager();
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
    //page.pageNumber = pageNumber;
    //page.header = PageHeader();
    //page.header.itemWriteOffset = 32;

    std::vector<char> item(16, 'C');

    testItemWriteToPage(page, item);

    std::cout<<"page before storage manager"<<std::endl;
    // Display the retrieved page data (replace this with your actual processing)
    for (int i=0; i < Page::PAGE_SIZE; i++) {
        std::cout << page.items[i];
    }

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
    
}

void testItemWriteToPage(Page &page, std::vector<char> itemToAdd) {
    std::cout<<"adding item..."<<std::endl;
    ItemId itemId = page.AddItem(itemToAdd);

    std::cout<<"item added at page: "<<itemId.pageId<<std::endl;
    std::cout<<"item added at slot: "<<itemId.slotInPage<<std::endl;
}