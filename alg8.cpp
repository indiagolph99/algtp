//

#include <vector>
#include <iostream>


int hash(const std::string &data, size_t tableSize) {
    int hash = 0;
    for (char i : data)
        hash = static_cast<int>((hash * 127 + i) % tableSize);
    return hash;
}

template<typename T>
class HashTable {
public:
    class HashNode {
    public:
        HashNode() : deleted(false), empty(true) {}
        T value;
        bool deleted;
        bool empty;
    };

    HashTable() : keys_count(0), table(16) {}
    HashTable(const HashTable &) = delete;
    HashTable &operator=(const HashTable &) = delete;
    bool Has(const T &value) const;
    bool Add(const T &value);
    bool Remove(const T &value);
    void growTable();
    size_t getSize() { return table.size(); }
private:
    int keys_count;
    std::vector<HashNode> table;
};

template<typename T>
bool HashTable<T>::Has(const T &value) const {
    int index = hash(value, table.size());
    int quadJump = 0;
    while (quadJump < table.size()) {
        if (!table[index].empty) {
            if (table[index].value == value && !table[index].deleted) {
                return true;
            }
        } else {
            return false;
        }
        index = static_cast<int>((index + quadJump + 1) % table.size());
        ++quadJump;
    }
    return false;
}
template<typename T>
bool HashTable<T>::Remove(const T &value) {
    size_t quadJump = 0;
    auto index = static_cast<size_t>(hash(value, table.size()));
    while (quadJump < table.size()) {
        if (!table[index].empty) {
            if (table[index].value == value && !table[index].deleted) {
                table[index].deleted = true;
                keys_count--;
                return true;
            }
        } else {
            return false;
        }
        index = (index + quadJump + 1) % table.size();
        ++quadJump;
    }
    return false;
}

template<typename T>
void HashTable<T>::growTable() {
    std::vector<HashNode> newTable(table.size() * 2);
    std::vector<HashNode> oldTable(std::move(table));
    table = std::move(newTable);
    for (const auto &i : oldTable) {
        if (!i.empty && !i.deleted) {
            keys_count--;
            Add(i.value);
        }
    }
}

template<typename T>
bool HashTable<T>::Add(const T &value) {

    if(Has(value)) {
        return false;
    }

    if (keys_count + 1 >= static_cast<int>(table.size()) * 3 / 4) {
        growTable();
    }

    size_t quadJump = 0;
    auto index = static_cast<size_t>(hash(value, table.size()));
    while (quadJump < table.size()) {
        if (table[index].empty || table[index].deleted) {
            table[index].value = value;
            table[index].empty = false;
            table[index].deleted = false;
            keys_count++;
            return true;
        }
        index = (index + quadJump + 1) % table.size();
        ++quadJump;
    }
    return false;
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
