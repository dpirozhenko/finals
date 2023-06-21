#include <iostream>

// Створити структуру даних черга для зберігання рядків, яка підтримує операції додавання та видалення елементів з черги і метод виведення черги у консоль.
// Створити чергу з імен людей, заданих користувачем.
// Відомо, що одна людина обслуговується за 3 хвилини, після чого покидає чергу.
// Визначити, хто залишиться у черзі після заданої користувачем кількості хвилин.

using namespace std;

class Node{
public:
    string data;
    Node* next;

    Node(string& s) : data(s), next(nullptr) {}

};


class Queue{
private:
    Node* front;
    Node* rear;

public:

    Queue() : front(nullptr), rear(nullptr) {}

    bool isEmpty(){
        return front == nullptr;
    }

    void enqueue(string& value){
        Node* newNode = new Node(value);
        if(isEmpty()){
            front = rear = newNode;
        }else{
            rear->next = newNode;
            rear = newNode;
        }

    }

    void dequeue(){
        if(isEmpty()){
            cout << "Queue is already empty" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;

        if(front == nullptr){
            rear = nullptr;
        }

        delete temp;

    }

    void info(){
        if(isEmpty()){
            cout << "Queue is empty" << endl;
            return;
        }
        Node* current = front;
        while(current != nullptr){
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;

    }



};

void fill_queue(Queue& q){
    string name;
    bool flag = true;
    int num;
    do{
        cout << "Enter the name to add to queue: ";
       // cin >> name;
        
       getline(cin, name);

        if(cin.fail()){
            throw "Invalid input...";
        }
        //cin.clear();
        q.enqueue(name);

        cout << "Want to stop? [1->no || 2-> yes] ";
        cin >> num;
        if(cin.fail()){
            throw "Invalid input...";
        }
        if(num != 1 && num != 2){
            throw "You should've entered 1 or 2 ...";
        }
        if(num == 2){
            flag =false;
        }

    }while(flag);

}

void take_out(Queue& q){
    int min;

    cout << "Enter the number of minutes: ";
    cin >> min;
    if(cin.fail()){
        throw "Invalid input...";
    }
    if(min<0){
        throw "Invalid input...";
    }
    int n = min/3;
    for(int i = 0; i < n; i++){
        q.dequeue();
    }


}

int main(){
    try{
        Queue myQueue;
        fill_queue(myQueue);
        cout << "Initial queue: " << endl;
        //myQueue.enqueue("sasa dsas");
        myQueue.info();

        take_out(myQueue);
        cout << "Current queue: " << endl;
        myQueue.info();
    }catch(const char* exception){
        cout << "Error... " << exception << endl;
    }
    


}
