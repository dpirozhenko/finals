#include <iostream>
#include <fstream>
#include <cmath>

// Спроектувати клас «Сфера», який є спадкоємцем класу «Точка».
// Ввести в базовий клас абстрактну функцію для обчислення площі поверхні фігури, перевизначивши її в дочірньому класі для обчислення площі поверхні сфери.
// Класи повинні також мати конструктори, методи виведення об’єктів, методи для виконання поставлених завдань, можливо інші методи.

// Розробити програму, яка створює масив сфер і визначає площу їх поверхонь.
// Записати радіуси кожної сфери і обчислену площу їх поверхонь у окремі рядки текстового файлу.
// Вивести (програмно) вміст створеного файлу для перегляду.

// Програма повинна забезпечувати наочне виведення усіх вхідних, вихідних та проміжних даних, а також контроль можливих помилок.
// Для обробки помилок (у тому числі і не коректного введення даних) використати виключні ситуації.


using namespace std;

class Point{
private:
    int x;
    int y;
public:

    Point() : x(0), y(0) {}

    Point(int x_, int y_) : x(x_), y(y_) {}

    int get_x(){
        return x;
    }

    int get_y(){
        return y;
    }

    //virtual void sqare() = 0; 

};

class Sphere{
private:
    Point center;
    Point out;
    int r;
    float square;

public:
    Sphere() : r(0), square(0) {}

    Sphere(int x, int y) : out(x, y),  r(0), square(0) {} 

    Sphere(int x1, int y1, int x2, int y2) : center(x1, y1), out(x2, y2),  r(0), square(0) {}

    void set_radius(int rad){
        r = rad;
    }

    void set_square(float s){
        square = s;
    }

    void  calculate_radius(){
        int x = this->out.get_x() - this->center.get_x();
        int y = this->out.get_y() - this->center.get_y();

        int r = sqrt(pow(x,2) + pow(y,2));
        this->set_radius(r);

    }

    void calculate_sqare(){
        this->calculate_radius();
        float s = 4 * M_PI * pow(r, 2);
        this->set_square(s);

    }

    string info_for_file(){
        this->calculate_radius();
        this->calculate_sqare();

        string ss = "The radius is: " + to_string(r) + " The square is: " + to_string(square) + ";";
        return ss;
    }

};

void fill_array1(Sphere * spheres){
    Sphere a(0, 1, 0, 3);
    Sphere b(1, 1, 3, 3);
    Sphere c(4, 4);
    Sphere d(10, 10);
    Sphere e(5, 5);
    Sphere f(13, 13);

    spheres[0] = a;
    spheres[1] = b;
    spheres[2] = c;
    spheres[3] = d;
    spheres[4] = e;
    spheres[5] = f;

}

int fill_array(Sphere * spheres){
    int x1, x2, y1, y2, size, flag;
    cout << "Enter how many spheres do you want o create: ";
    cin >> size;

    for(int i = 0; i < size; i++){
        cout << "1-> to enter your coordinates\n2-> center at (0; 0): " << endl;
        cin >> flag;

        if(flag == 1){
            cout << "enter x1: ";
            cin >> x1;
            cout << "enter y1: ";
            cin >> y1;
            cout << "enter x2: ";
            cin >> x2;
            cout << "enter y2: ";
            cin >> y2;
            Sphere a(x1, y1, x2, y2);
            spheres[i] = a;
        }else if(flag == 2){
            cout << "enter x2: ";
            cin >> x2;
            cout << "enter y2: ";
            cin >> y2;
            Sphere b(x2, y2);
            spheres[i] = b;
        }else{
            throw "You`ve entered not 1, not 2";
        }

    }

    return size;

}

void to_file(Sphere * spheres, int s){
    fstream file;

    file.open("spheres.txt", ios::out);

    if (file.is_open()) {
        for(int i = 0; i < s; i++){
            file << spheres[i].info_for_file() << endl;
        }
            
    file.close();
    }


}

void read_file(){
    fstream file;
    string line;

    file.open("spheres.txt", ios::in);

    if (file.is_open()) {
        while(getline(file, line)){
            cout << line << endl;
        }
            
    file.close();
    }

}

int main(){

    Sphere * spheres = new Sphere[100];
    int size;
    try{
       size = fill_array(spheres); 
    }
     catch (const char* exception) // обробка винятків типу const char*
    {
        std::cerr << "Error: " << exception << std::endl;
    }

    to_file(spheres, size);

    read_file();

}
