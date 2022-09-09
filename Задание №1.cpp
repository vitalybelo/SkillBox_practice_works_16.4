#include <iostream>
#include <string>
#include "windows.h"
using namespace std;

class speedRunner {

private:
    float speed;

public:
    speedRunner() {
        speed = 0.00;
    }

    float getSpeed() const {
        return speed;
    }

    float decreaseSpeed (float speed) {
        return speedRunner::speed -= speed;
    }

    void setSpeed(float speed) {
        speedRunner::speed = speed;
    }

    bool equals(float reference, float precision) {
        return speed >= (reference - precision)
               && speed <= (reference + precision);
    }
    bool isBigger(float reference, float precision) {
        return speed >= (reference - precision);
    }
    bool isLess(float reference, float precision) {
        return speed <= (reference + precision);
    }
    bool inRange(float min, float max, float precision) {
        return speed >= (min - precision)
               && speed <= (max + precision);
    }
};


int main() {
    speedRunner speedRun;

    do {
        do {
            float speedIn;
            cout << "\nВведите скорость (0 - 150) (EXIT = -1): ";
            cin >> speedIn;
            speedRun.setSpeed(speedIn);
        } while (!speedRun.inRange(-1.00, 150.00, 0.001));

        // отображение скорости без перехода на новую строку
        // у меня в Clion из-за эха отображается некорректно
        // точно работает во внешней консоли (любая подходит)
        int eraseCount = 0;
        cout << "Скорость: ";
        while (speedRun.isBigger(0.1,0.01)) {
            // затираем старое значение скорости
            for (int i = 0; i < eraseCount; i++) cout << "\b";
            char speed[10];
            sprintf(speed,"%.2f", speedRun.decreaseSpeed(0.1));
            string speedString = string (speed);
            cout << speedString;
            eraseCount = speedString.length();
            Sleep(1);
        }

//        while (speedRun.isBigger(0.1,0.01))
//            printf("Скорость: %.2f %s", speedRun.decreaseSpeed(0.1),"\n");

    } while (!speedRun.equals(-1.00,0.01));

    return 0;
}

