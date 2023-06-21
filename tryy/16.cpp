#include<iostream>
#define CAPACITY 1000

using namespace std;
//xеш мапа на онові списку

struct Pair {
  std::string first;
  std::string second;
  Pair(const std::string& first, const std::string& second) : first(first), second(second) {}
};

struct Node {
  Pair data;
  Node* next = nullptr;
  Node(Pair& data) : data(data) {}
};

class HashMap {
private:
  int hash(const std::string& key) const {
    int sum = 0;
    for (size_t i = 0; i < key.length(); i++) {
      sum += key[i];
    }

    return sum % CAPACITY;
  }

  Node* table[CAPACITY];

public:
  HashMap() {
    for (size_t i = 0; i < CAPACITY; i++) {
      table[i] = nullptr;
    }
  }

  void put(const std::string& key, const std::string& value) {
    int index = hash(key);
    Pair data(key, value);
    if (table[index] == nullptr) {
      table[index] = new Node(data);
      return;
    }

    Node* current = table[index];
    while (current->next != nullptr) {
      current = current->next;
    }

    current->next = new Node(data);
  }

  std::string get(const std::string& key) {
    int index = hash(key);
    Node* current = table[index];
    while (current != nullptr) {
            if (current->data.first == key) return current->data.second;
            current = current->next;
        }
    }
    
};

int main() {

  HashMap map;
  map.put("test", "test");
  map.put("sdfgsdg", "fsdf21314");
  std::cout << map.get("test") << std::endl;
  std::cout << map.get("sdfgsdg") << std::endl;


  return 0;
}
