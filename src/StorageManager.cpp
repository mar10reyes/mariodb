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

bool StorageManager::flushPage(Page page) {
    
    // Assuming you want to open a file for writing
    storePageOnDisk(this->databaseFilePath, page);

    return true;
}

Page StorageManager::getPage(int pageNumber) {
    
    // Implement the logic for getting a page based on the ItemId
    std::vector<char> pageData(Page::PAGE_SIZE, 'A');

    retrievePageFromDisk(this->databaseFilePath, pageNumber, pageData);

    return Page(pageData);
}

StorageManager::~StorageManager() {
    // Implement the destructor logic, if needed
}

// Function to store a page on disk
void storePageOnDisk(const std::string& filename, Page page) {
    
    int pageNumber              = page.pageNumber;
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

    // Move to the correct position in the file
    file.seekg(position);

    // Read the page data from the file into the vector
    file.read(pageData.data(), Page::PAGE_SIZE);

    // Close the file
    file.close();
}