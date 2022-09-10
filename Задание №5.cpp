#include <iostream>
#include "smarthome.h"
using namespace std;

/**
 * Оборудование которое мы имеем:
 * 1. 2 датчика температуры и датчик движения на улице
 * 2. Общий выключатель, выключает все кроме датчиков
 * 3. Выключатели: свет = 2, отопление = 2, кондиционер
 *
 * Как работает умный дом:
 * Выполняются все условия описанные в тех.задании:
 * 1. отопление дома: вкл < 22 , выкл >= 25 градусов
 * 2. отопление трубы: вкл < 0 , выкл  > 5 градусов
 * 3. кондиционер: вкл >= 30 , выкл <= 25 градусов
 * 4. свет на улице: с 16:00 до 5:00 если есть движение
 * 5. свет в доме: вкл руками, с 16:00 до 20:00 меняет
 *    температуру цвета от 5000к до 2700к
 *
 * Управляется это все командами. Чтобы увидеть список
 * команд введите ? или help например
 * После каждой команды автоматически время увеличивается
 * нва один час, но есть команда установки нужного времени
 * для проверки работы разных условий
 *
 * Для реализации напилил класс. Так показалось проще.
*/

int main() {
    SmartHome smartHome = SmartHome (0,25,17,false,false, true);

    do {
        smartHome.sensorControlPanel();
        smartHome.smartHomeStatusDisplay();

        if (smartHome.compileCommand()) break;

        smartHome.increaseCurrentHour(1);

    } while (true);

    return 0;
}

