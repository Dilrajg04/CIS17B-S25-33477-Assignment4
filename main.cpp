//
//  main.cpp
//  Assignment4
//
//  Created by Dilraj Grewal on 4/22/25.
//

#include <iostream>
#include <unordered_map>
#include <map>
#include <memory>
#include <stdexcept>
using namespace std;

class DuplicateItemException : public std::runtime_error {
public:
    DuplicateItemException(const std::string& msg) : std::runtime_error(msg) {}
};

class ItemNotFoundException : public std::runtime_error {
public:
    ItemNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

class StoredItem {
private:
    std::string id;
    std::string description;
    std::string location;

public:
    StoredItem(std::string id, std::string desc, std::string loc)
        : id(id), description(desc), location(loc) {}

    std::string getId() const { return id; }
    std::string getDescription() const { return description; }
    std::string getLocation() const { return location; }
};

class StorageManager {
private:
    std::unordered_map<std::string, std::shared_ptr<StoredItem>> itemById;
    std::map<std::string, std::shared_ptr<StoredItem>> itemByDescription;

public:
    void addItem(const std::shared_ptr<StoredItem>& item) {
        // TODO: Add item to both maps, throw if ID already exists
        if(itemById.count(item->getId())){
            throw DuplicateItemException("Item with ID ' " + item->getId() + "'already exists'");
        }
        itemById[item->getId()] = item;
        itemByDescription[item->getDescription()] = item; // <-- added line
    }

    std::shared_ptr<StoredItem> findById(const std::string& id) const {
        try {
                return itemById.at(id);
            } catch (const std::out_of_range&) {
                throw ItemNotFoundException("Item with ID " + id + " not found!");
            }
        }

    void removeItem(const std::string& id) {
        // TODO: Remove from both maps, throw if not found
        auto it = itemById.find(id);
        if (it == itemById.end()) {
            throw ItemNotFoundException("Item with ID " + id + " not found!");
        }

        std::string description = it->second->getDescription(); // get description before erasing
        itemById.erase(it); // remove from unordered map
        itemByDescription.erase(description); // remove from ordered map
    }


    void listItemsByDescription() const {
        // TODO: Iterate over itemByDescription and print info
        cout << "Items in Description Order: \n";
        for (const auto& pair : itemByDescription){
            const auto& item = pair.second;
            cout << "- " << item->getDescription() << ": " << item->getLocation() << "\n";
        }
        
    }
};

void testDuplicateAddition();
void testItemNotFound();

int main() {
    
    // TODO: Create StorageManager and test functionality
    
    //create the storage manager (our inventory system)
    StorageManager storage;
    
    //run some test functions to check edge cases
    cout << "Adding item: ITEM001 - LED Light\n";
    auto ledLight = std::make_shared<StoredItem>("ITEM001", "LED Light", "Aisle 3, Shelf 1");
    storage.addItem(ledLight);
    //add the first item to storage
    cout << "Adding item: ITEM002 - Fan Motor\n";
    auto fanMotor = std::make_shared<StoredItem>("ITEM002", "Fan Motor", "Aisle 2, Shelf 5");
    storage.addItem(fanMotor);
    //add the first item to storage
    cout << "Attempting to add ITEM001 again...\n";
    //try adding the first item again (should fail and throw an exception)
        try {
            auto duplicateLED = std::make_shared<StoredItem>("ITEM001", "LED Light", "Aisle 3, Shelf 1");
            storage.addItem(duplicateLED);
        } catch (const DuplicateItemException& e) {
            cout << "Error: " << e.what() << "\n";
        }
    //try to find ITEM002 in the system
        cout << "Retrieving ITEM002...\n";
        try {
            auto foundFan = storage.findById("ITEM002");
            cout << "Found: " << foundFan->getDescription() << " at " << foundFan->getLocation() << "\n";
        } catch (const ItemNotFoundException& e) {
            cout << "Error: " << e.what() << "\n";
        }
    //try removing a nonexistent item (ITEM003). Should also throw an error.
        cout << "Removing ITEM003...\n";
        try {
            storage.removeItem("ITEM003");
        } catch (const ItemNotFoundException& e) {
            cout << "Error: " << e.what() << "\n";
        }
    //show all items, sorted alphabetically by description
        storage.listItemsByDescription();

        return 0;
    }

