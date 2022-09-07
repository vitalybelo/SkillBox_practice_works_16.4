#include <iostream>
using namespace std;

bool DigitsOnlyEntered (const string& checkString);

int main() {
    setlocale(LC_ALL, "Russian_Russia.1251");

    string number;
    do {
        cout << "Введите целую часть числа = ";
        cin >> number;
    } while (!DigitsOnlyEntered(number));

    string fractional;
    do {
        cout << "Введите дробную часть числа = ";
        cin >> fractional;
    } while (!DigitsOnlyEntered(fractional));

    string numberString = number + "." + fractional;
    double numberDouble = stod(numberString);

    cout << endl;
    cout << "Исходная строка: " << numberString << endl;
    printf("Преобразованное число = %.6f %s",numberDouble,"\n");

    return 0;
}

bool DigitsOnlyEntered (const string& checkString) {
    for (char i : checkString)
        if (i < '0' || i > '9') return false;
    return true;
}
