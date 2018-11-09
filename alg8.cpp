//
// Created by savva on 02.11.18.
//

#include <iostream>
#include <string>
#include <vector>

int hash(const std::string &data, size_t tableSize) {
    int hash = 0;
    for (char i : data)
        hash = static_cast<int>((hash * 127 + i) % tableSize);
    return hash;
}


template<typename T>
class HashTable {
 public:
    HashTable() : keys_count(0), table(8) {}
    HashTable(const HashTable &) = delete;
    HashTable &operator=(const HashTable &) = delete;
    bool Has(const T &value) const;
    bool Add(const T &value);
    bool Remove(const T& value);
    void growTable();
 private:
    size_t keys_count;
    std::vector<T> table;
};

template<typename T>
bool HashTable<T>::Add(const T &value) {
    if (Has(value)) {
        return false;
    }

    if (keys_count + 1 >= table.size() * 3 / 4)
        growTable();

    auto index = hash(value, table.size());
    int h = 1;
    while (!table[index].empty() && table[index] != "~") {
        index = static_cast<int>((index + h * h) % table.size());
        h++;
    }
    table[index] = value;
    keys_count++;
    return true;
}

template<typename T>
bool HashTable<T>::Has(const T &value) const {
    int index = hash(value, table.size());
    size_t h = 1;
    while (table[index] != value &&
    (!table[index].empty() || table[index] == "~")) {
        index = static_cast<int>((index + h * h) % table.size());
        h++;
    }
    return (table[index] == value);
}

template<typename T>
bool HashTable<T>::Remove(const T &value) {
    if (!Has(value)) {
        return false;
    }
    int index = hash(value, table.size());
    int h = 1;
    while (table[index] != value && !table[index].empty()) {
        index = static_cast<int>((index + h * h) % table.size());
        h++;
    }
    table[index] = "~";
    return true;
}

template<typename T>
void HashTable<T>::growTable() {
    std::vector<T> newTable(table.size() * 2);
    for (const auto &i : table) {
        if (!i.empty() && i != "~") {
            int newHash = hash(i, newTable.size());
            newTable[newHash] = i;
        }
    }
    table = newTable;
}

int main() {
    HashTable<std::string> table;

    char operation = 0;
    std::string data;
    while (std::cin >> operation >> data) {
        if (operation == '+')
            std::cout << (table.Add(data) ? "OK" : "FAIL") << "\n";
        if (operation == '-')
            std::cout << (table.Remove(data) ? "OK" : "FAIL") << "\n";
        if (operation == '?')
            std::cout << (table.Has(data) ? "OK" : "FAIL") << "\n";
    }

    return 0;
}
