#include <iostream>
#include <sstream>
using namespace std;

int main() {

    double value1, value2;
    do {
        cout << "\nВвод: ";
        string inputString;
        cin >> inputString;

        stringstream stream_buffer(inputString);

        double result;
        value1 = value2 = 0.00;
        char arithmetic_sign = ' ';
        stream_buffer >> value1 >> arithmetic_sign >> value2;

        switch (arithmetic_sign) {
            case '+':
                result = value1 + value2;
                break;
            case '-':
                result = value1 - value2;
                break;
            case '*':
                result = value1 * value2;
                break;
            case '/':
                result = value1 / value2;
                break;
            default:
                cerr << "Ops, wrong entry format\n";
                continue;
        }
        cout << " = " << fixed << result << endl;
    } while (value1 >= 0 && value2 >=0);

    return 0;
}
