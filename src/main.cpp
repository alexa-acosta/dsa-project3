#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "bst.h"
#include "hashmap.h"
#include "utils.h"

// menu
void showMenu() {
    std::cout << "======= Menu =======\n";
    std::cout << "1. Load dataset from file\n";
    std::cout << "2. Use Balanced BST\n";
    std::cout << "3. Use Hashmap\n";
    std::cout << "4. Insert new entry\n";
    std::cout << "5. Search for exact match\n";
    std::cout << "6. Show timings\n";
    std::cout << "7. Show memory usage\n";
    std::cout << "8. Exit\n";
    std::cout << "=====================\n";
    std::cout << "Enter your choice: ";
}

int main() {
    int choice;
    bool running = true;
    std::vector<std::string> dataset;
    BST bst;
    Hashmap hashmap;
    bool data_loaded = false;
    bool bst_built = false;
    bool hashmap_built = false;

    while (running) {
        showMenu();
        std::cin >> choice;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                std::string filename = "data/counties.csv";
                std::cout << "Loading dataset from " << filename << "...\n";
                dataset = read_csv(filename);
                if (!dataset.empty()) {
                    std::cout << "Dataset loaded successfully with " << dataset.size() << " entries.\n";
                    data_loaded = true;
                }
                break;
            }
            case 2: {
                if (!data_loaded) {
                    std::cout << "Please load a dataset first (Option 1).\n";
                    break;
                }
                std::cout << "Building Balanced BST...\n";
                // clear the BST for a new build
                bst = BST(); 
                Timer timer;
                timer.start();
                for (const auto& entry : dataset) {
                    bst.insert(entry);
                }
                timer.stop();
                std::cout << "Dataset inserted into BST in " << timer.get_duration_microseconds() << " microseconds.\n";
                bst_built = true;
                break;
            }
            case 3: {
                if (!data_loaded) {
                    std::cout << "Please load a dataset first (Option 1).\n";
                    break;
                }
                std::cout << "Building Hashmap...\n";
                // clear the hashmap for a new build
                hashmap = Hashmap();
                Timer timer;
                timer.start();
                for (const auto& entry : dataset) {
                    hashmap.insert(entry);
                }
                timer.stop();
                std::cout << "Dataset inserted into Hashmap in " << timer.get_duration_microseconds() << " microseconds.\n";
                hashmap_built = true;
                break;
            }
            case 4: {
                std::string new_entry;
                std::cout << "Enter new entry: ";
                std::getline(std::cin, new_entry);
                
                if (bst_built) {
                    bst.insert(new_entry);
                    std::cout << "New entry added to BST.\n";
                }
                if (hashmap_built) {
                    hashmap.insert(new_entry);
                    std::cout << "New entry added to Hashmap.\n";
                }
                if (!bst_built && !hashmap_built) {
                    std::cout << "Please build a data structure first (Option 2 or 3).\n";
                }
                break;
            }
            case 5: {
                if (!bst_built && !hashmap_built) {
                    std::cout << "Please build a data structure first (Option 2 or 3).\n";
                    break;
                }
                std::string search_key;
                std::cout << "Enter key to search: ";
                std::getline(std::cin, search_key);

                Timer timer;

                if (bst_built) {
                    timer.start();
                    bool bst_found = bst.search(search_key);
                    timer.stop();
                    long long bst_time = timer.get_duration_microseconds();
                    std::cout << "BST search result: " << (bst_found ? "Found" : "Not Found") << " in " << bst_time << " microseconds.\n";
                }

                if (hashmap_built) {
                    timer.start();
                    bool hashmap_found = hashmap.search(search_key);
                    timer.stop();
                    long long hashmap_time = timer.get_duration_microseconds();
                    std::cout << "Hashmap search result: " << (hashmap_found ? "Found" : "Not Found") << " in " << hashmap_time << " microseconds.\n";
                }
                break;
            }
            case 6: {
                if (!bst_built && !hashmap_built) {
                    std::cout << "Please build a data structure first (Option 2 or 3).\n";
                    break;
                }
                std::cout << "--- Benchmarking Search on Loaded Data ---\n";
                if (!dataset.empty()) {
                    std::string search_key = dataset.back(); // searches for an existing key
                    std::cout << "Searching for key: '" << search_key << "'\n";

                    Timer timer;

                    if (bst_built) {
                        timer.start();
                        bst.search(search_key);
                        timer.stop();
                        std::cout << "BST search time: " << timer.get_duration_microseconds() << " microseconds.\n";
                    }

                    if (hashmap_built) {
                        timer.start();
                        hashmap.search(search_key);
                        timer.stop();
                        std::cout << "Hashmap search time: " << timer.get_duration_microseconds() << " microseconds.\n";
                    }
                } else {
                    std::cout << "Dataset is not loaded. Cannot benchmark.\n";
                }
                break;
            }
            case 7: {
                if (!bst_built && !hashmap_built) {
                    std::cout << "Please build a data structure first (Option 2 or 3).\n";
                    break;
                }
                std::cout << "--- Memory Usage (Rough Estimation) ---\n";
                if (bst_built) {
                    std::cout << "Balanced BST size: " << bst.size() << " elements\n";
                    std::cout << "Balanced BST memory: " << bst.get_memory_usage() << " bytes\n";
                }
                if (hashmap_built) {
                    std::cout << "Hashmap size: " << hashmap.size() << " elements\n";
                    std::cout << "Hashmap memory: " << hashmap.get_memory_usage() << " bytes\n";
                }
                break;
            }
            case 8: {
                std::cout << "Exiting...\n";
                running = false;
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
        std::cout << std::endl;
    }

    return 0;
}