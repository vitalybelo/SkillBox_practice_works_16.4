#pragma once
#include <iostream>
#include <sstream>
#include <cctype>
using namespace std;

enum toggle_switch {
    COMMON_TOGGLE = 1, LIGHTS_INSIDE = 2, LIGHTS_OUTSIDE = 4,
    BOILER_INSIDE = 8, BOILER_OUTSIDE = 16, AIR_CONDITIONER = 32
};

class SmartHome {

private:
    int switches;
    int currentHour;
    int insideTempSensor;
    int outsideTempSensor;
    bool insideLightSwitch;
    bool movementSensor;
    bool commonToggle;

public:
    SmartHome(int currentHour, int insideTemperature, int outsideTemperature,
              bool insideLightSwitch, bool movementSensor, bool commonToggle) {
        switches = 0;
        SmartHome::currentHour = currentHour;
        SmartHome::insideTempSensor = insideTemperature;
        SmartHome::outsideTempSensor = outsideTemperature;
        SmartHome::movementSensor = movementSensor;
        setLightToggle(insideLightSwitch);
        setCommonToggle(commonToggle);
    }

    void setLightToggle(bool toggle) {
        SmartHome::insideLightSwitch = toggle;
        if (toggle) {
            switches |= LIGHTS_INSIDE;
        } else {
            switches &= ~LIGHTS_INSIDE;
        }
    }

    void setCommonToggle(bool toggle) {
        SmartHome::commonToggle = toggle;
        if (toggle) {
            switches |= COMMON_TOGGLE;
        } else {
            switches &= ~COMMON_TOGGLE;
        }
    }

    void increaseCurrentHour(int hoursCount) {
        if (hoursCount <= 0) return;
        currentHour += hoursCount;
        if (currentHour >= 24) currentHour %= 24;
    }

    void stringToLower (string& s) {
        for (int i = 0; i < s.length(); i++)
            s[i] = tolower(s[i]);
    }

    void parserCommandLine (string& lineString, string& command, string& argument) {

        stringstream parserBuffer;
        parserBuffer << lineString;
        parserBuffer >> command >> argument;
        stringToLower(command);
        stringToLower(argument);
    }

    bool getBooleanParam(string& param, bool& toggle) {
        if (param == "on") {
            toggle = true;
        } else if (param == "off") {
            toggle = false;
        } else {
            cerr << "некорректное значение параметра";
            return false;
        }
        return true;
    }

    bool checkIntegerString (string& param) {
        for (int i = 0; i < param.length(); i++)
            if (param[i] < '0' || param[i] > '9') {
                if (param[i] == '-') continue;
                cout << "некорректное значение параметра";
                return false;
            }
        return true;
    }

    void displayCommandHelp () {
        cout << endl;
        cout << "Доступные команды панели управления:\n";
        cout << "common on/off - общий выключатель\n";
        cout << "light on/off - выключатель света\n";
        cout << "in число - температура внутри\n";
        cout << "out число - температура снаружи\n";
        cout << "time число - установка часа дня\n";
        cout << "move on/off - датчик движение\n";
        cout << "exit - завершение программы\n";
    }

    bool compileCommand () {

        string inputString, command, argument;
        do {
            command = "help";
            cout << "------------------------------------\n";
            cout << "Введите команду (или help): ";
            getline(cin,inputString);
            parserCommandLine(inputString, command, argument);
            if (command == "help")
                    displayCommandHelp();
        } while (command == "help");

        if (command == "common") {
            bool toggle;
            if (getBooleanParam(argument, toggle))
                    setCommonToggle(toggle);
        } else if (command == "light") {
            bool toggle;
            if (getBooleanParam(argument, toggle))
                setLightToggle(toggle);
        } else if (command == "move") {
            bool toggle;
            if (getBooleanParam(argument, toggle))
                movementSensor = toggle;
        } else if (command == "in") {
            if (checkIntegerString(argument))
                    insideTempSensor = stoi(argument);
        } else if (command == "out") {
            if (checkIntegerString(argument))
                outsideTempSensor = stoi(argument);
        } else if (command == "time") {
            if (checkIntegerString(argument))
                currentHour = stoi(argument) - 1;
        } else if (command == "exit") {
                return true;
        }
        return false;
    }

    void sensorControlPanel () {
        cout << endl;
        cout << "------------------------------------\n";
        cout << "Время: " << currentHour << ":00\n";
        cout << "------------------------------------\n";
        cout << "Общий выключатель: " << (commonToggle ? "ON" : "OFF") << endl;
        cout << "Температура внутри: " << insideTempSensor << endl;
        cout << "Температура снаружи: " << outsideTempSensor << endl;
        cout << "Движение снаружи дома:"<< (movementSensor ? "" : " не") << " обнаружено\n";
        cout << "------------------------------------\n";

    }

    void checkInsideBoilerStatus () {
        bool boilerON = switches & BOILER_INSIDE;
        if (commonToggle) {
            if (boilerON) {
                if (insideTempSensor >= 25) switches &= ~BOILER_INSIDE;
            } else {
                if (insideTempSensor < 22) switches |= BOILER_INSIDE;
            }
        } else {
            switches &= ~BOILER_INSIDE;
        }
        boilerON = switches & BOILER_INSIDE;
        cout << "ОТОПЛЕНИЕ дома: " << (boilerON ? "ON" : "OFF") << endl;
    }

    void checkOutsideBoilerStatus () {
        bool boilerON = switches & BOILER_OUTSIDE;
        if (commonToggle) {
            if (boilerON) {
                if (outsideTempSensor > 5) switches &= ~BOILER_OUTSIDE;
            } else {
                if (outsideTempSensor < 0) switches |= BOILER_OUTSIDE;
            }
        } else {
            switches &= ~BOILER_OUTSIDE;
        }
        boilerON = switches & BOILER_OUTSIDE;
        cout << "ОТОПЛЕНИЕ водопровода: " << (boilerON ? "ON" : "OFF") << endl;

    }

    void checkAirConditionerStatus () {

        bool conditionerON = switches & AIR_CONDITIONER;
        if (commonToggle) {
            if (conditionerON) {
                if (insideTempSensor <= 25) switches &= ~AIR_CONDITIONER;
            } else {
                if (insideTempSensor >= 30) switches |= AIR_CONDITIONER;
            }
        } else {
            switches &= ~AIR_CONDITIONER;
        }
        conditionerON = switches & AIR_CONDITIONER;
        cout << "КОНДИЦИОНИРОВАНИЕ дома: " << (conditionerON ? "ON" : "OFF") << endl;
    }

    void checkOutsideLighting () {

        bool lightON = switches & LIGHTS_OUTSIDE;
        if (commonToggle) {
            if (lightON) {
                bool daytime = currentHour >= 5 && currentHour < 16;
                if (daytime || !movementSensor)
                        switches &= ~LIGHTS_OUTSIDE;
            } else {
                bool evening = currentHour >= 16 && currentHour <= 23;
                bool night = currentHour >= 0 && currentHour < 5;
                if (evening || night)
                    if (movementSensor)
                        switches |= LIGHTS_OUTSIDE;
            }
        } else {
            switches &= ~LIGHTS_OUTSIDE;
        }
        lightON = switches & LIGHTS_OUTSIDE;
        cout << "ОСВЕЩЕНИЕ ландшафта: " << (lightON ? "ON" : "OFF") << endl;
    }

    void checkInsideLighting () {

        int lightTemperature = 5000;
        if (currentHour >= 16) {
            if (currentHour < 21) {
                lightTemperature -= (currentHour - 16) * 575;
            } else {
                lightTemperature = 2700;
            }
        }
        bool lightON = (switches & LIGHTS_INSIDE) && commonToggle;
        cout << "ОСВЕЩЕНИЕ внутри дома: " << (lightON ? "ON" : "OFF") << endl;
        if (lightON)
            cout << "ТЕМПЕРАТУРА цвета: " << lightTemperature << endl;
    }

    void smartHomeStatusDisplay () {

        checkInsideBoilerStatus();
        checkOutsideBoilerStatus();
        checkAirConditionerStatus();
        checkInsideLighting();
        checkOutsideLighting();
    }
};
