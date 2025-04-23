# CIS17B-S25-33477-Assignment4

## Overview
This C++ program simulates a storage management system for "Congo", a warehouse that tracks items by ID and description. It uses both `unordered_map` (for fast lookup) and `map` (for ordered listing).

## Features
- `StoredItem` class: holds ID, description, location
- `StorageManager` class:
  - Adds items to both maps
  - Finds items by ID
  - Lists items by description (alphabetical)
  - Removes items from both maps
- Smart pointers (`shared_ptr`)
- Custom exceptions: `DuplicateItemException`, `ItemNotFoundException`
- Basic test functions included
