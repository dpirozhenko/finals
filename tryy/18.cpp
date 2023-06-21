#include <iostream>

// Створити абстрактний клас для представлення транспортного засобу TVehicle,
// у якому оголосити атрибути максимальної швидкості і наявної кількості пасажирів та метод для виведення інформації про транспортний засіб.
// Створити класи нащадки для представлення автомобіля і автобусу.
// 
// У класі автомобіля перевантажити оператори + та - для додавання та прибирання пасажирів,
// причому з кожним доданим пасажиром швидкість авто падає на 3 км/г, і максимальна кількість пасажирів автомобіля складає 7 людей,
// також додати конструктор і гетери.
// У класі автобусу перевантажити оператори + та - для додавання та прибирання пасажирів,
// причому з кожним доданим пасажиром швидкість автобусу падає на  2 км/г, і максимальна кількість пасажирів автобусу складає 25 людей ,
// також додати конструктор і гетери.
// 
// 
// Створити за введеними значеннями об’єкти цих двох класів,
// 
// додати задану кількість пасажирів у автомобіль та прибрати задану кількість пасажирів з автобусу,
// після чого визначити, швидкість якого з об’єктів більше.

using namespace std;

class TVehicle {
public:
	int max_speed;
	int capacity;

	TVehicle() : max_speed(0), capacity(0) {}
	TVehicle(int s, int c) : max_speed(s), capacity(c) {}

	void info() {
		cout << "Max speed is: " << max_speed << " and capacity is " << capacity << endl;
	}


};

class Avto : public TVehicle {
public:
	Avto() : TVehicle() {}

	Avto(int speed, int cap) : TVehicle(speed, cap) {}

	void operator+(int n) {
		if (capacity >= 7) {
			throw "no more place!";
		}
		else {
			int cap = n + capacity;
			if (cap > 7) {
				throw  "Max is 7!";
			}
			else {
				capacity = cap;
				max_speed -= 3*n;
			}
		}
		
	}

	void operator-(int n) {
		if (n > 7) {
			throw "Only 7 people are here..";
		}
		else {
			capacity -= n;
			max_speed += 3 * n;
		}
		


	}


	int get_max_speed() {
		return max_speed;
	}

	int get_capacity() {
		return capacity;
	}



};

class Bus : public TVehicle {
public:
	
	Bus() : TVehicle() {}

	Bus(int speed, int cap) : TVehicle(speed, cap) {}

	void operator+(int n) {
		if (capacity >= 25) {
			throw "no more place!";
		}
		else {
			int cap = n + capacity;
			if (cap > 25) {
				throw "Max is 25! There are ";
			}
			else {
				capacity = cap;
				max_speed -= 2 * n;
			}
		}

	}

	void operator-(int n) {
		if (n > 25) {
			throw "Only 25 people are here..";
		}
		else {
			capacity -= n;
			max_speed += 2 * n;
		}
	}

	int get_max_speed() {
		return max_speed;
	}

	int get_capacity() {
		return capacity;
	}
};

// Створити за введеними значеннями об’єкти цих двох класів,
// 
// додати задану кількість пасажирів у автомобіль та прибрати задану кількість пасажирів з автобусу,
// після чого визначити, швидкість якого з об’єктів більше.

void find_bigger_speed(Avto& a, Bus& b) {
	if (a.get_max_speed() == b.get_max_speed()) {
		cout << "the speed is the same";
	}
	else if (a.get_max_speed() > b.get_max_speed()) {
		cout << "the speed of avto is bigger";
	}
	else {
		cout << "the speed of the bus is bigger";
	}
}

void create_obj(Avto& a, Bus& b) {
	int anum, bnum, asp, bsp;
	cout << "Let's create the initial states for avto and bus: " << endl;
	cout << "How many passangers in avto?(max is 7) ";
	cin >> anum;
	if (cin.fail() ){
		throw "Your input is incorrect...";
	}
	if (anum > 7) {
		throw "The max is 7...";
	}
	cout << "Initial speed for avto: ";
	cin >> asp;
	if (cin.fail()) {
		throw "Your input is incorrect...";
	}
	cout << "How many passangers in bus?(max is 25) ";
	cin >> bnum;
	if (cin.fail()) {
		throw "Your input is incorrect...";
	}
	if (bnum > 7) {
		throw "The max is 7...";
	}
	cout << "Initial speed for avto: ";
	cin >> bsp;
	if (cin.fail()) {
		throw "Your input is incorrect...";
	}

	Avto myAvto(asp, anum);
	Bus myBus(bsp, bnum);
	a = myAvto;
	b = myBus;
}

void change(Avto& a, Bus& b) {
	int n1, n2;

	cout << "how many passangers do you want to add to avto (max is 7): ";
	cin >> n1;
	if (cin.fail()) {
		throw "Your input is incorrect...";
	}
	a + n1;

	cout << "how many passangers do you want to take off the bus: ";
	cin >> n2;
	if (cin.fail()) {
		throw "Your input is incorrect...";
	}
	b - n2;

	cout << "Current state: " << endl;
	a.info();
	b.info();
}

int main() {
	try {
		Avto a;
		Bus b;
		create_obj(a, b);
		cout << "Initial state: " << endl;
		a.info();
		b.info();

		change(a, b);
		cout << "Current state: " << endl;
		a.info();
		b.info();


		find_bigger_speed(a, b);

	}
	catch (const char* expression) {
		cout << "Error... " << expression << endl;
	}



}
