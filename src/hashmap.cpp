#include "hashmap.h"

void Hashmap::insert(const std::string& key) {
    map[key] = true;
}

bool Hashmap::search(const std::string& key) {
    return map.count(key) > 0;
}

size_t Hashmap::size() const {
    return map.size();
}

size_t Hashmap::get_memory_usage() const {
    size_t string_size_sum = 0;
    for (const auto& pair : map) {
        string_size_sum += pair.first.capacity();
    }
    return sizeof(map) + string_size_sum + map.bucket_count() * sizeof(void*);
}