#include <iostream>
//Створити шаблонний клас (колекцію) List для роботи з двозв’язним списком. 
//Визначити у ньому декілька конструкторів (у тому числі конструктор за замовчуванням, який створює порожній список), метод виведення, можливо інші методи. 
//Для числових масивів передбачити сортування їх елементів за зменшенням.
//Написати програму, що демонструє роботу з цим шаблоном для списків цілих чисел і списків символів.
//У програмі передбачити створення двох масивів об’єктів класу List - по одному кожного виду (масив списків цілих чисел та масив списків символів). 
//За допомогою зовнішньої функції, яка виконує злиття об’єктів (Списків) масиву-параметру в єдиний List, створити об’єднаний список цілих чисел і об’єднаний список символів.
//У кожному отриманому списку видалити k-й з кінця елемент списку (k вводиться з клавіатури).
//На основі отриманого списку цілих чисел x1, x2, ... xn побудувати новий список, що містить елементи x1 ×xn, x2 ×xn, ..., xn-1 ×xn.
//Програма повинна забезпечувати наочне виведення усіх вхідних, вихідних та проміжних даних, а також контроль можливих помилок. 
//Для обробки помилок (у тому числі і не коректного введення даних) використати виключні ситуації.


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

    DoublyLinkedList(int length, const T* elements) {
        head = nullptr;
        tail = nullptr;
        size = 0;

        for (int i = 0; i < length; i++) {
            insertAtEnd(elements[i]);
        }
    }

    ~DoublyLinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
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

    void printList() {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void sortDescending() {
        if (size <= 1) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            Node<T>* current = head;
            while (current->next != nullptr) {
                if (current->data < current->next->data) {
                    T temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }


    void removeAtPosition(int position) {
        if (position < 0 || position >= size) {
            return; 
        }

        Node<T>* current = tail;
        for (int i = 0; i < position; i++) {
            current = current->prev;
        }

        if (current->next != nullptr) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }

        if (current->prev != nullptr) {
            current->prev->next = current->next;
        } else {
            tail = current->next;
        }

        delete current;
        size--;
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

        return -1; 
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

        Iterator& operator--() {
            current = current->prev;
            return *this;
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
    
    void multiplyByLastElement() {
        if (size <= 1) {
            return;
        }

        T lastElement = tail->data;
        Node<T>* current = head;
        while (current != nullptr) {
            current->data *= lastElement;
            current = current->next;
        }
    }
};


template <typename T>
DoublyLinkedList<T> mergeLists(DoublyLinkedList<T>* lists, int numLists) {
    DoublyLinkedList<T> mergedList;

    for (int i = 0; i < numLists; i++) {
        DoublyLinkedList<T>& currentList = lists[i];
        typename DoublyLinkedList<T>::Iterator it = currentList.begin();
        for (; it != currentList.end(); ++it) {
            mergedList.insertAtEnd(*it);
        }
    }

    return mergedList;
}


int main() {

    char characters1[] = {'a', 'k', 'd', 'f'};
    char characters2[] = {'v', 'g', 'q'};
    char characters3[] = {'d', 'g'};
    char characters4[] = {'l'};

    
    DoublyLinkedList<char> myCharList1(4, characters1);
    DoublyLinkedList<char> myCharList2(3, characters2);
    DoublyLinkedList<char> myCharList3(2, characters3);
    DoublyLinkedList<char> myCharList4(1, characters4);

    DoublyLinkedList<char> lists1[] = {myCharList1, myCharList2, myCharList3, myCharList4};
    DoublyLinkedList<char> mergedList1 = mergeLists(lists1, 4);
    mergedList1.sortDescending();
    std::cout << "List of characters: ";
    mergedList1.printList();

    int numbers1[] = {4, 12, 5, 7, 10};
    int numbers2[] = {43, 6, 9};
    int numbers3[] = {8, 19, 2};
    int numbers4[] = {3};

    DoublyLinkedList<int> myIntList1(5, numbers1);
    DoublyLinkedList<int> myIntList2(3, numbers2);
    DoublyLinkedList<int> myIntList3(3, numbers3);
    DoublyLinkedList<int> myIntList4(1, numbers4);

    DoublyLinkedList<int> lists2[] = {myIntList1, myIntList2, myIntList3, myIntList4};

    DoublyLinkedList<int> mergedList2 = mergeLists(lists2, 4);
    mergedList2.sortDescending();
    std::cout << "List of numbers: ";
    mergedList2.printList();

    std::cout << std::endl;



    int k;
    std::cout << "enter num of element to delete: ";
    std::cin >> k;
    
    mergedList1.removeAtPosition(k);
    mergedList2.removeAtPosition(k);

    std::cout << "List of characters after: ";
    mergedList1.printList();
    
    std::cout << "List of numbers after: ";
    mergedList2.printList();



    std::cout << "\nList of numbers after multiplication: ";   
    mergedList2.multiplyByLastElement();
    mergedList2.printList();


    return 0;
}
