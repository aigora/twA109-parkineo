#include <Servo.h>
#define max 3
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
#define ir1 1
#define ir2 2
#define ir3 3
#define irentrada 4
#define irsalida 5

int barreras(int);
void plazas(void);
void semaforo(int);

Servo myservoent;
Servo myservosal;

int plazasocupadas=0;

void setup(){
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
    int aux=plazasocupadas;
    plazas();
    plazasocupadas=plazasocupadas+barreras(plazasocupadas);
    semaforo(plazasocupadas);
    if(plazasocupadas>max)plazasocupadas=max;
    if(plazasocupadas<0)plazasocupadas=0;
    if(aux!=plazasocupadas){
      Serial.print("El numero de plazas ocupadas es ");
      Serial.println(plazasocupadas);
    }
}

int barreras(int pocupadas){
    int cuenta=0;
    if(analogRead(irentrada)<100&&pocupadas<max){
        myservoent.write(90);
        delay(2000);
        myservoent.write(0);
        cuenta++;
    }
    if(analogRead(irsalida)<100){
        myservosal.write(90);
        delay(2000);
        myservosal.write(0);
        cuenta--;
    }
    return cuenta;
}

void plazas(){
    if(analogRead(ir1)<=100){
        analogWrite(rojo1,200);
        digitalWrite(verde1,LOW);
    }
    if(analogRead(ir2)<=100){
        analogWrite(rojo2,200);
        digitalWrite(verde2,LOW);
    }
    if(analogRead(ir3)<=100){
        analogWrite(rojo3,200);
        digitalWrite(verde3,LOW);
    }
    if(analogRead(ir1)>100){
        digitalWrite(rojo1,LOW);
        analogWrite(verde1,200);
    }
    if(analogRead(ir2)>100){
        digitalWrite(rojo2,LOW);
        analogWrite(verde2,200);
    }
    if(analogRead(ir3)>100){
        digitalWrite(rojo3,LOW);
        analogWrite(verde3,200);
    }
}

void semaforo(int pocupadas){
    if(pocupadas==max){
        digitalWrite(semafororojo,HIGH);
        digitalWrite(semaforoverde,LOW);
    }
    if(pocupadas<max){
        digitalWrite(semafororojo,LOW);
        digitalWrite(semaforoverde,HIGH);
    }
}
