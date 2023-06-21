#include <iostream>
#include <exception>

// Власний клас винятку
class MyException : public std::exception {
public:
    // Перевизначений метод what() для повернення повідомлення про помилку
    const char* what() const noexcept override {
        return "Моя власна помилка!";
    }
};

int main() {
    try {
        // Викидання винятку типу std::exception
        throw std::exception();
    } catch (const std::exception& e) {
        std::cout << "Виняток типу std::exception: " << e.what() << std::endl;
    }

    try {
        // Викидання власного винятку типу MyException
        throw MyException();
    } catch (const MyException& e) {
        std::cout << "Власний виняток: " << e.what() << std::endl;
    }

    return 0;
}
