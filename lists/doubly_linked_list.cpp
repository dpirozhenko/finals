#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~DoublyLinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    void insertAtBeginning(T data) {
        Node<T>* newNode = new Node<T>;
        newNode->data = data;
        newNode->prev = nullptr;
        newNode->next = head;

        if (head != nullptr) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }

        head = newNode;
        size++;
    }

    void insertAtEnd(T data) {
        Node<T>* newNode = new Node<T>;
        newNode->data = data;
        newNode->prev = tail;
        newNode->next = nullptr;

        if (tail != nullptr) {
            tail->next = newNode;
        } else {
            head = newNode;
        }

        tail = newNode;
        size++;
    }

    void insertAtPosition(T data, int position) {
        if (position < 0 || position > size) {
            std::cout << "Invalid position." << std::endl;
            return;
        }

        if (position == 0) {
            insertAtBeginning(data);
        } else if (position == size) {
            insertAtEnd(data);
        } else {
            Node<T>* current = head;
            for (int i = 0; i < position - 1; i++) {
                current = current->next;
            }

            Node<T>* newNode = new Node<T>;
            newNode->data = data;
            newNode->prev = current;
            newNode->next = current->next;

            current->next->prev = newNode;
            current->next = newNode;

            size++;
        }
    }

    void remove(T data) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == data) {
                if (current == head) {
                    head = current->next;
                } else {
                    current->prev->next = current->next;
                }

                if (current == tail) {
                    tail = current->prev;
                } else {
                    current->next->prev = current->prev;
                }

                delete current;
                size--;
                return;
            }

            current = current->next;
        }

        std::cout << "Element not found." << std::endl;
    }

    int getPosition(T data) {
        Node<T>* current = head;
        int position = 0;
        while (current != nullptr) {
            if (current->data == data) {
                return position;
            }

            current = current->next;
            position++;
        }

        return -1; // Element not found.
    }

    class Iterator {
    private:
        Node<T>* current;

    public:
        Iterator(Node<T>* node) : current(node) {}

        T& operator*() const {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            current = current->next;
            return temp;
        }

        Iterator& operator--() {
            current = current->prev;
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            current = current->prev;
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }
};

int main() {
    DoublyLinkedList<int> myList;
    

    myList.insertAtEnd(1);
    myList.insertAtEnd(2);
    myList.insertAtEnd(3);
    myList.insertAtEnd(4);
    myList.insertAtEnd(5);


    std::cout << "List: ";
    for (DoublyLinkedList<int>::Iterator it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    myList.remove(3);

    std::cout << "List after removing 3: ";
    for (DoublyLinkedList<int>::Iterator it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << std::endl;

    int position = myList.getPosition(4);
    if (position != -1) {
        std::cout << "Position of 4: " << position << std::endl;
    } else {
        std::cout << "Element not found." << std::endl;
    }

    return 0;
}
