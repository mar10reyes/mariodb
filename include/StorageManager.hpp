#pragma once

#include <string>
#include "Page.hpp"

class StorageManager {
private:
    std::string databaseName;
    std::string databaseFilePath;
public:
    bool flushPage(Page page);
    Page getPage(int pageNumber);
    StorageManager(const std::string& dbname, const std::string& dbFilepath);
    ~StorageManager();
};
