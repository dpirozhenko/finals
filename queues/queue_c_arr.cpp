#include<iostream>
// Ната's queue (3) laba (кільцевий масив)

using namespace std;

template<typename T>
class Node
{
public:
	T data;
	Node* prev;
	Node* next;

	Node(T& value, Node<T>* prevN = nullptr, Node<T>* nextN = nullptr);
};

template<typename T>
class Queue
{
private:
	Node<T>* head;
	Node<T>* tail;
	int size;
public:
	Queue();
	Queue(T& data);

	int get_size();
	bool is_empty();
	void erase();
	void insert(T& data);
	void clear();

	class Iterator
	{
	private:
		Node<T>* curr;
	public:
		Iterator(Node<T>* node) :curr(node) {}
		T& operator*() { return curr->data; }
		Iterator& operator++(int)
		{
			curr = curr->next;
			return *this;
		}
		bool operator!=(const Iterator& other)
		{
			return curr != other.curr;
		}
	};

	Iterator begin() { return Iterator(head); }
	Iterator end() { return Iterator(nullptr); }

};

template<typename T>
Node<T>::Node(T& value, Node<T>* prevN, Node<T>* nextN)
{
	data = value;
	prev = prevN;
	next = nextN;
}

template<typename T>
Queue<T>::Queue()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

template<typename T>
Queue<T>::Queue(T& data)
{
	insert(data);
}

template<typename T>
int Queue<T>::get_size()
{
	return size;
}

template<typename T>
bool Queue<T>::is_empty()
{
	return head == nullptr;
}

template<typename T>
void Queue<T>::erase()
{
	if (is_empty())
	{
		cerr << "Queue is empty" << endl;
		return;
	}

	Node<T>* temp = head;
	head = head->next;
	if (head != nullptr)
	{
		head->prev = nullptr;
	}
	else
	{
		tail = nullptr;
	}

	delete temp;
	size--;
}

template<typename T>
void Queue<T>::insert(T& data)
{
	Node<T>* newNode = new Node<T>(data, nullptr, nullptr);

	if (is_empty())
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	size++;
}

template<typename T>
void Queue<T>::clear()
{
	while (!is_empty())
	{
		erase();
	}
}

template<typename T>
void print(Queue<T> q)
{
	for (auto i = q.begin(); i != q.end(); i++)
	{
		cout << *i << " ";
	}cout << endl;
}

int main()
{
	
	Queue<int> my_q;

	int n, val;
	cout << "Enter the size:";
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cout << "[" << i + 1 << "] : ";
		cin >> val;
		my_q.insert(val);
	}
	
	print(my_q);
	my_q.erase();
	print(my_q);
	my_q.clear();
	print(my_q);

	return 0;
}
