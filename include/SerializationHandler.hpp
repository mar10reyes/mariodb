#include <iostream>
#include <vector>
#include <cstring>

class SerializationHandler {
public:
    
    // Store serialized data
    std::vector<char> serializedData;

    // Serialize data into a sequence of bytes
    template<typename T>
    const char* serialize(const T& data) {
        // Assuming the size of data is serialized along with the data for deserialization
        serializedData.clear();
        serializeHelper(data);
        return serializedData.data();
    }

    // Deserialize a sequence of bytes back to original data
    template<typename T>
    T deserialize(const char* serializedData) {
        T data;
        deserializeHelper(serializedData, data);
        return data;
    }

private:
    // Serialize different types of data
    template<typename T>
    void serializeHelper(const T& data) {
        const char* byteData = reinterpret_cast<const char*>(&data);
        serializedData.insert(serializedData.end(), byteData, byteData + sizeof(T));
    }

    // Deserialize different types of data
    template<typename T>
    void deserializeHelper(const char* serializedData, T& data) {
        std::memcpy(&data, serializedData, sizeof(T));
    }

    // Additional serialization for strings
    void serializeHelper(const std::string& str) {
        const char* byteData = str.c_str();
        size_t size = str.size();
        serializeHelper(size);
        serializedData.insert(serializedData.end(), byteData, byteData + size);
    }

    // Additional deserialization for strings
    void deserializeHelper(const char* serializedData, std::string& str) {
        size_t size;
        deserializeHelper(serializedData, size);
        str.assign(serializedData + sizeof(size_t), size);
    }
};

