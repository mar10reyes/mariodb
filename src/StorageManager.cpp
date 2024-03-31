#include "StorageManager.hpp"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdint> // For types like uint32_t

// Function prototypes
void storePageOnDisk(const std::string& filename, Page page);
void retrievePageFromDisk(const std::string& filename, int pageNumber, std::vector<char>& pageData);

StorageManager::StorageManager(const std::string& dbname, const std::string& dbFilepath)
    : databaseName(dbname), databaseFilePath(dbFilepath) {}


// Function to print the binary representation of a byte
void printByteAsBits2(unsigned char byte) {
    for (int i = 7; i >= 0; --i) {
        std::cout << ((byte >> i) & 1);
    }
}

// Function to print a set of bytes as bits
void printBytesAsBits2(const unsigned char* bytes, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printByteAsBits2(bytes[i]);
        std::cout << ' '; // Separate bytes by space
    }
    std::cout << std::endl;
}

bool StorageManager::flushPage(Page page) {
    // Assuming you want to open a file for writing
    // std::ofstream outputFile(databaseFilePath, std::ios::binary);

    // if (!outputFile.is_open()) {
    //     // Handle the case when the file cannot be opened
    //     // You might want to throw an exception or return false based on your error handling strategy
    //     return false;
    // }

    // // Implement the logic for flushing a page
    // // For example, you can write data to the file using outputFile.write()

    // // Close the file when done
    // outputFile.close();

    storePageOnDisk(this->databaseFilePath, page);

    return true;
}

Page StorageManager::getPage(int pageNumber) {
    // Implement the logic for getting a page based on the ItemId

    std::vector<char> pageData(Page::PAGE_SIZE, 'A');

    //pageData.clear();
    //pageData.resize(Page::PAGE_SIZE);

    // std::cout<<"pageNumber from retrievePageFromDisk: "<<pageNumber<<std::endl;

    retrievePageFromDisk(this->databaseFilePath, pageNumber, pageData);

    //Page p1 = Page(pageData);
    
    // char itemIds[6 * ItemId::SIZE];
    //char currentItemId[16];
    
    // std::memcpy(currentItemId, itemIds, ItemId::SIZE);
    //std::memcpy(currentItemId, pageData.data(), (size_t)16);

    //size_t dataSize = sizeof(currentItemId);

    //std::cout << "Data in (xxx) bits: ";
    //printBytesAsBits2((const unsigned char*)currentItemId, dataSize);

    //std::cout<<"page[1]: "<<pageData[0]<<std::endl;
    return Page(pageData); // Placeholder return value, modify as needed
}

StorageManager::~StorageManager() {
    // Implement the destructor logic, if needed
}

// Function to store a page on disk
void storePageOnDisk(const std::string& filename, Page page) {
    
    int pageNumber              = 0; //needs to be here because I put 222 as page number to test if the page number was beeing correct while other parts of the code still have 0 as page number
    // int pageNumber              = page.pageNumber;
    std::vector<char>& pageData = page.items;
    
    std::ofstream file(filename, std::ios::binary | std::ios::in | std::ios::out);
    //std::ofstream file(filename, std::ios::binary | std::ios::in | std::ios::out);

    // Calculate the position to write based on page number and page size
    std::streampos position = static_cast<std::streampos>(pageNumber) * Page::PAGE_SIZE;

    // Move to the correct position in the file
    file.seekp(position);

    // Write the page data to the file
    // file.write(pageData.data(), Page::PAGE_SIZE);
    file.write(pageData.data(), Page::PAGE_SIZE);

    // Close the file
    file.close();
}

// Function to retrieve a page from disk
void retrievePageFromDisk(const std::string& filename, int pageNumber, std::vector<char>& pageData) {
    std::ifstream file(filename, std::ios::binary);

    // Calculate the position to read based on page number and page size
    std::streampos position = static_cast<std::streampos>(pageNumber) * Page::PAGE_SIZE;

    std::cout<<"pos in file: "<<position<<std::endl;

    std::cout<<"getting reading pos"<<std::endl;

    // Move to the correct position in the file
    file.seekg(position);

    std::cout<<"moving to reading pos"<<std::endl;

    // Read the page data from the file into the vector
    file.read(pageData.data(), Page::PAGE_SIZE);

    std::cout<<"page read!"<<std::endl;
    //std::cout<<"page -> "<<pageData1[1]<<std::endl;
    std::cout<<"other"<<std::endl;

    // Close the file
    file.close();

    //return pageData;
}