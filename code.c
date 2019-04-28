#include <Servo.h>

#define verde1 2
#define rojo1 3
#define verde2 4
#define rojo2 5
#define verde3 6
#define rojo3 7
#define semaforoverde 8
#define semafororojo 9
#define servoentrada 10
#define servosalida 11
#define irentrada 12
#define irsalida 13

Servo myservoent;
Servo myservosal;

void setup()
{
    pinMode(verde1, OUTPUT);
    pinMode(verde2, OUTPUT);
    pinMode(verde3, OUTPUT);
    pinMode(rojo1, OUTPUT);
    pinMode(rojo2, OUTPUT);
    pinMode(rojo3, OUTPUT);
    pinMode(semaforoverde, OUTPUT);
    pinMode(semafororojo, OUTPUT);
    Serial.begin(9600);
    pinMode(irentrada, INPUT);
    pinMode(irsalida, INPUT);
    myservoent.attach(servoentrada);
    myservosal.attach(servosalida);
}

void loop()
{
    int plazaslibres=3;
    int valorirentrada=0;
    int i=0;
    valorirentrada=digitalRead(irentrada);
    if(valorirentrada&&plazaslibres){
        digitalWrite(semafororojo, LOW);
        digitalWrite(semaforoverde, HIGH);
        for(i=0;i<=60;i++){
            myservoent.write(i);
            delay(25);
        }
        delay(2000);
        digitalWrite(semafororojo, HIGH);
        digitalWrite(semaforoverde, LOW);
        for(i=60;i>=0;i--){
            myservoent.write(i);
            delay(25);
        }
    }
    else{
        digitalWrite(semafororojo, HIGH);
        digitalWrite(semaforoverde, LOW);
    }
}
