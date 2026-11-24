#pragma once

#include <Arduino.h>
#include <stdio.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include "include/Pin_assignments.h"
#include "include/Hardware.h"
#include "include/ServoControls.h"

void MotorsPinModes(){
    // set pin modes motors
    pinMode(RIGHT_MOTORS_IN13, OUTPUT);
    pinMode(RIGHT_MOTORS_IN24, OUTPUT);
    pinMode(EN_MOTORS_RIGHT, OUTPUT);

    pinMode(LEFT_MOTORS_IN13, OUTPUT);
    pinMode(LEFT_MOTORS_IN24, OUTPUT);
    pinMode(EN_MOTORS_LEFT, OUTPUT);
}
void Init_Right_Motors(Motors* MotorsRightSide){
    // assign pin macros to struct data storage
    MotorsRightSide->IN13 = RIGHT_MOTORS_IN13;
    MotorsRightSide->IN24 = RIGHT_MOTORS_IN24;
    MotorsRightSide->EN = EN_MOTORS_RIGHT;
    // set initial state
    digitalWrite(MotorsRightSide->IN13, LOW);
    digitalWrite(MotorsRightSide->IN24, LOW);
    analogWrite(MotorsRightSide->EN, 0);
}

void Init_Left_Motors(Motors* MotorsLeftSide){
    // assign pin macros to struct data storage
    MotorsLeftSide->IN13 = LEFT_MOTORS_IN13;
    MotorsLeftSide->IN24 = LEFT_MOTORS_IN24;
    MotorsLeftSide->EN = EN_MOTORS_LEFT;
    // set initial state
    digitalWrite(MotorsLeftSide->IN13, LOW);
    digitalWrite(MotorsLeftSide->IN24, LOW);
    analogWrite(MotorsLeftSide->EN, 0);
}

void Init_Servos(Servo* servo_a, Servo* servo_b){
    // attach servos to pins
    (*servo_a).attach(SERVO_1);
    (*servo_b).attach(SERVO_2);
    // set initial positions of both servos
    MoveBothServos(servo_a, servo_b, 90, 90);
}

void Init_Bluetooth(SoftwareSerial* BTdevice){
    // baud rate (Serial for YesSerial = true in BluetoothReadWrite.cpp)
    Serial.begin(9600);
    (*BTdevice).begin(9600);
}

void Init_Hardware(Motors* MotorsRightSide, Motors* MotorsLeftSide, Servo* servo_a, Servo* servo_b, SoftwareSerial* BTdevice){
    // call all init functions in one
    Init_Right_Motors(MotorsRightSide);
    Init_Left_Motors(MotorsLeftSide);
    MotorsPinModes();

    Init_Servos(servo_a, servo_b);

    Init_Bluetooth(BTdevice);
}
