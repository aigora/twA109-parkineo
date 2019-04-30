#include <Servo.h>

#define max 3

#define verde1 2
#define rojo1 3
#define verde2 4
#define rojo2 5
#define verde3 6
#define rojo3 7
#define ir1 1
#define ir2 2
#define ir3 3
#define semaforoverde 8
#define semafororojo 9
#define servoentrada 10
#define servosalida 11
#define irentrada 4
#define irsalida 5

void barreraentrada(int);
void barrerasalida(void);
void plazas(void);

Servo myservoent;
Servo myservosal;

int plazasocupadas;

void setup(){
    plazasocupadas=0;
    Serial.begin(9600);
    pinMode(verde1, OUTPUT);
    pinMode(verde2, OUTPUT);
    pinMode(verde3, OUTPUT);
    pinMode(rojo1, OUTPUT);
    pinMode(rojo2, OUTPUT);
    pinMode(rojo3, OUTPUT);
    pinMode(semaforoverde, OUTPUT);
    pinMode(semafororojo, OUTPUT);
    myservoent.attach(servoentrada);
    myservosal.attach(servosalida);
    myservoent.write(0);
    myservosal.write(0);
}

void loop(){
    if(analogRead(irentrada)&&(plazasocupadas<max)){
        barreraentrada(plazasocupadas);
        plazasocupadas++;
    }
    if(analogRead(irsalida)){
        barrerasalida();
        plazasocupadas--;
    }
    plazas();
    if(plazasocupadas>=max)plazasocupadas=max;
    if(plazasocupadas<=0)plazasocupadas=0;
    if(plazasocupadas<max){
        digitalWrite(semaforoverde,HIGH);
        digitalWrite(semafororojo,LOW);
    }
    if(plazasocupadas==max){
        digitalWrite(semaforoverde,LOW);
        digitalWrite(semafororojo,HIGH);
    }
}

void barreraentrada(int plazasocupadas){
        myservoent.write(90);
        delay(2000);
        myservoent.write(0);
}
void barrerasalida(){
    myservosal.write(90);
    delay(2000);
    myservosal.write(0);
}
void plazas(){
    if(analogRead(ir1)){
        digitalWrite(rojo1,HIGH);
        digitalWrite(verde1,LOW);
    }
    if(analogRead(ir2)){
        digitalWrite(rojo2,HIGH);
        digitalWrite(verde2,LOW);
    }
    if(analogRead(ir3)){
        digitalWrite(rojo3,HIGH);
        digitalWrite(verde3,LOW);
    }
    if(analogRead(ir1)==0){
        digitalWrite(rojo1,LOW);
        digitalWrite(verde1,HIGH);
    }
    if(analogRead(ir2)==0){
        digitalWrite(rojo2,LOW);
        digitalWrite(verde2,HIGH);
    }
    if(analogRead(ir3)==0){
        digitalWrite(rojo3,LOW);
        digitalWrite(verde3,HIGH);
    }
}
