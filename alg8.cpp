//

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

int hash(const std::string &data, size_t tableSize) {
    int hash = 0;
    for (char i : data)
        hash = static_cast<int>((hash * 127 + i) % tableSize);
    return hash;
}

template<typename T>
class HashTable {
 public:
    HashTable() : keys_count(0), table(8) {
        std::fill(table.begin(), table.end(), empty);
    }
    HashTable(const HashTable &) = delete;
    HashTable &operator=(const HashTable &) = delete;
    bool Has(const T &value) const;
    bool Add(const T &value);
    bool Remove(const T &value);
    void growTable();
    size_t getSize() { return table.size(); }
 private:
    int keys_count;
    const std::string del = "DELETED";
    const std::string empty = "EMPTY";
    std::vector<T> table;
};

template<typename T>
bool HashTable<T>::Has(const T &value) const {
    int index = hash(value, table.size());
    int quadJump = 0;
    while (!table[index].empty() && quadJump < table.size()) {
        if (table[index] == value) {
            return true;
        }
        index = static_cast<int>((index + quadJump + 1) % table.size());
        quadJump++;
    }
    return false;
}

template<typename T>
bool HashTable<T>::Remove(const T &value) {
    size_t quadJump = 0;
    auto index = static_cast<size_t>(hash(value, table.size()));
    while (table[index] != value && quadJump < table.size()) {
        if (!table[index].empty()) {
            return false;
        }
        index = (index + quadJump + 1) % table.size();
        quadJump++;
    }
    if (table[index] == value) {
        table[index] = del;
        keys_count--;
        return true;
    }
    return false;
}

template<typename T>
void HashTable<T>::growTable() {
    std::vector<T> newTable(table.size() * 2);
    std::fill(newTable.begin(), newTable.end(), empty);
    std::vector<T> oldTable(table);
    table = newTable;
    for (const auto &i : oldTable) {
        if (!i.empty() && i != del) {
            keys_count--;
            Add(i);
        }
    }
}

template<typename T>
bool HashTable<T>::Add(const T &value) {
    if (keys_count + 1 >= static_cast<int>(table.size()) * 3 / 4) {
        growTable();
    }

    int quadJump = 0;
    int index = hash(value, table.size());
    int deletedIndex = 0;
    bool deletedFound = false;
    while (!table[index].empty() && quadJump < table.size()) {
        if (table[index] == value) {
            return false;
        }

        if (table[index] == del) {
            deletedIndex = index;
            deletedFound = true;
        }
        index = static_cast<int>((index + quadJump + 1) % table.size());
        quadJump++;
    }

    if (!table[index].empty()) {
        if (deletedFound) {
            table[deletedIndex] = value;
            keys_count++;
            return true;
        }
        return false;
    }
    table[index] = value;
    keys_count++;
    return true;
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
