#include <iostream>

// Створити структуру даних черга для зберігання числових значень, яка підтримує операції 
// додавання та видалення елементів з черги і метод виведення черги у консоль. 
// Користувачем задаються числа, що являють собою оцінки студентів за семестр. 
// Переглянути чергу і знайти кількість студентів з заданою оцінкою. 
// Видалити всіх студентів з заданою оцінкою і вивести перетворену чергу.

using namespace std;


struct Node {
    int data;
    Node* next;
    explicit Node(const int& value) : data(value), next(nullptr) {}
};

class LinkedListQueue {
private:
    Node* head;
    Node* tail;

public:
    

    LinkedListQueue() : head(nullptr), tail(nullptr) {}

    ~LinkedListQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(const int& value) {//вставка елементу вкінець черги
        Node* newNode = new Node(value);

        if (isEmpty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void dequeue() {//видалення елементу з початку черги
        if (isEmpty()) {
            cout << "Queue is empty. Unable to dequeue.\n";
            return;
        }

        Node* temp = head;
        head = head->next;
        delete temp;

        if (isEmpty()) {
            tail = nullptr;
        }
    }

    int& front() const {
        if (isEmpty()) {
            cout << "Queue is empty. No front element.\n";
            throw;
        }

        return head->data;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void print(){
        Node* currentNode = head;
        while (currentNode != nullptr) {
            cout << currentNode->data << " ";
            currentNode = currentNode->next;
        }
    }

    int count(int mark){
        int count = 0;
        Node* currentNode = head;
        while (currentNode != nullptr) {
            if (currentNode->data == mark) {
                count++;
            }
            currentNode = currentNode->next;
            
        }
        return count;
    }

    LinkedListQueue get_rid_of(int num){
        LinkedListQueue ll;

        Node* currentNode = head;
        while (currentNode != nullptr) {
            if (currentNode->data != num) {
                ll.enqueue(currentNode->data);
            }
            currentNode = currentNode->next;
            
        }

        return ll;
    }
    

    int getPosition(const int& value) const {
        int position = 0;
        Node* currentNode = head;
        while (currentNode != nullptr) {
            if (currentNode->data == value) {
                return position;
            }
            currentNode = currentNode->next;
            position++;
        }
        return -1; // If element not found
    }


};


void add_elements( LinkedListQueue* queue){
    bool flag = true;
    int num;
    string check;

    do{
        cout << "enter mark: ";
        cin >> num;
        queue->enqueue(num);
        cout << "Countinue? [y/n] ";
        cin >> check;
        if(check == "y" || check == "Y"){
            flag = false;
        }

    }while(flag);

}



int main() {
    LinkedListQueue queue;

    //add_elements(queue);

    bool flag = true;
    int num;
    char check;

    do{
        cout << "enter mark: ";
        cin >> num;
        queue.enqueue(num);
    
        cout << "Countinue? [y/n] ";
        cin >> check;
        cin.ignore();

    }while(check == 'y' || check == 'Y');


    cout << "Initial list" << endl;
    queue.print();

    int number;
    cout << "enter mark to delete ";
    cin >> number;
    int count = queue.count(number);
    cout << "Students with mark " << number << ": " << count << endl;

    cout << "New list:" << endl;

    LinkedListQueue queue2 = queue.get_rid_of(number);
    queue2.print();


    return 0;
}
