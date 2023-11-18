#include "StorageManager.hpp"
#include <fstream>
#include <iostream>

// Function prototypes
void storePageOnDisk(const std::string& filename, Page page);
void retrievePageFromDisk(const std::string& filename, int pageNumber, std::vector<char>& pageData);

StorageManager::StorageManager(const std::string& dbname, const std::string& dbFilepath)
    : databaseName(dbname), databaseFilePath(dbFilepath) {}

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

    retrievePageFromDisk(this->databaseFilePath, pageNumber, pageData);
    //std::cout<<"page[1]: "<<pageData[0]<<std::endl;
    return Page(pageData); // Placeholder return value, modify as needed
}

StorageManager::~StorageManager() {
    // Implement the destructor logic, if needed
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
    std::ifstream file(filename, std::ios::binary | std::ios::in);

    // Calculate the position to read based on page number and page size
    std::streampos position = static_cast<std::streampos>(pageNumber) * Page::PAGE_SIZE;

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