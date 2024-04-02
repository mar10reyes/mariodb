#include "StorageManager.hpp"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdint> // For types like uint32_t
#include "SerializationHandler.hpp"
#include <filesystem>

// Function prototypes
void storePageOnDisk(const std::string& filename, Page page);
void retrievePageFromDisk(const std::string& filename, int pageNumber, std::vector<char>& pageData);
void DeserializePageOffsets(Page &page);

StorageManager::StorageManager(const std::string& dbname, const std::string& dbFilepath)
    : databaseName(dbname), databaseFilePath(dbFilepath) {}

bool StorageManager::flushPage(Page page) {
    
    // Assuming you want to open a file for writing
    storePageOnDisk(this->databaseFilePath, page);

    return true;
}

Page StorageManager::getPage(int pageNumber) {
    
    // Implement the logic for getting a page based on the ItemId
    std::vector<char> pageData(Page::PAGE_SIZE, 0);

    retrievePageFromDisk(this->databaseFilePath, pageNumber, pageData);
    Page page = Page(pageData);
    page.pageNumber = pageNumber;

    bool pageWasBlank = true;
    for (char value : pageData) {
        if (value != 0) {
            pageWasBlank = false;
            break;
        }
    }

    if(!pageWasBlank) {
        DeserializePageOffsets(page);
    }

    return page;
}

StorageManager::~StorageManager() {
    // Implement the destructor logic, if needed
}

void DeserializePageOffsets(Page &page)
{
    char offsets[Page::HEADER_SIZE];

    std::memcpy(offsets, page.items.data(), Page::HEADER_SIZE);

    char itemOffsetInBytes[sizeof(int)];
    char itemIdOffsetInBytes[sizeof(int)];

    std::memcpy(itemOffsetInBytes, offsets, sizeof(int)); 
    std::memcpy(itemIdOffsetInBytes, offsets + sizeof(int), sizeof(int));

    SerializationHandler serializationHandler;
    std::string _serializedData;

    _serializedData = itemOffsetInBytes;
    serializationHandler.serializedData = std::vector<char> (_serializedData.begin(), _serializedData.end());
    int itemOffset = serializationHandler.deserialize<int>(itemOffsetInBytes);
    
    _serializedData = itemIdOffsetInBytes;
    serializationHandler.serializedData = std::vector<char> (_serializedData.begin(), _serializedData.end());
    int itemIdOffset = serializationHandler.deserialize<int>(itemIdOffsetInBytes);

    page.header.itemWriteOffset   = itemOffset;
    page.header.itemIdWriteOffset = itemIdOffset;
}

// Function to store a page on disk
void storePageOnDisk(const std::string& filename, Page page) {
    
    int pageNumber              = page.pageNumber;
    std::vector<char>& pageData = page.items;
    
    std::ofstream file(filename, std::ios::binary | std::ios::in | std::ios::out);

    // Calculate the position to write based on page number and page size
    std::streampos position = static_cast<std::streampos>(pageNumber) * Page::PAGE_SIZE;

    // Move to the correct position in the file
    file.seekp(position);

    // Write the page data to the file
    file.write(pageData.data(), Page::PAGE_SIZE);

    // Close the file
    file.close();
}

// Function to retrieve a page from disk
void retrievePageFromDisk(const std::string& filename, int pageNumber, std::vector<char>& pageData) {
    std::ifstream file(filename, std::ios::binary);

    file.seekg(0, std::ios::end);
    
    if (file.tellg() == 0) {
        file.close();
        return;
    }

    // Calculate the position to read based on page number and page size
    std::streampos position = static_cast<std::streampos>(pageNumber) * Page::PAGE_SIZE;

    // Move to the correct position in the file
    file.seekg(position);

    // Read the page data from the file into the vector
    file.read(pageData.data(), Page::PAGE_SIZE);

    // Close the file
    file.close();
}