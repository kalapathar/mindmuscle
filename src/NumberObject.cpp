#include <iostream>

#include "NumberObject.h"

NumberObject::NumberObject(float w, float h, float X, float Y, unsigned int number) { // Init the digits starting at the given coordinates
    this->w = w;
    this->h = h;
    this->X = X;
    this->Y = Y;
    
    this->initObjects(number);
    this->updateNumber(number);
}

NumberObject::~NumberObject() {
    cout << "Destroying number object" << endl;
    delete tensObj;
    delete onesObj;
}

void NumberObject::initObjects(unsigned int number) {
    unsigned int tens = (number-(number%10)) / 10;
    unsigned int ones = number % 10;
    
    if (tensObj != NULL) delete tensObj;
    if (onesObj != NULL) delete onesObj;
    
    tensObj = new GameObject(this->intToString(tens), false, w, h, true, X, Y);
    onesObj = new GameObject(this->intToString(ones), false, w, h, true, X+w, Y);
}

void NumberObject::updateNumber(unsigned int number) {
    if (curNumber != number) {
        curNumber = number;
        // Recreate gameObject
        this->initObjects(number);
    }
}

void NumberObject::draw() {
    // Draw both ones and tens objects
    tensObj->draw();
    onesObj->draw();
}

const char * NumberObject::intToString(unsigned int number) {
    switch(number) {
        case 0:
            return "0";
            break;
        case 1:
            return "1";
            break;
        case 2:
            return "2";
            break;
        case 3:
            return "3";
            break;
        case 4:
            return "4";
            break;
        case 5:
            return "5";
            break;
        case 6:
            return "6";
            break;
        case 7:
            return "7";
            break;
        case 8:
            return "8";
            break;
        case 9:
            return "9";
            break;
    }
}