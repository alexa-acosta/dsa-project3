#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <unordered_map>

class Hashmap {
private:
    std::unordered_map<std::string, bool> map;

public:
    void insert(const std::string& key);
    bool search(const std::string& key);
    size_t size() const;
    size_t get_memory_usage() const;
};

#endif