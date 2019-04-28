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
int contador(void);
void barreras(int);
void plazas(void);
Servo myservoent;
Servo myservosal;

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
}

void loop(){
    int plazasocupadas=0;
    plazasocupadas=plazasocupadas+contador();
    barreras(plazasocupadas);
    plazas();
}

int contador(void){
    if(analogRead(servoentrada)!=0){
        return 1;
    }
    if(analogRead(servosalida)!=0){
        return -1;
    }
    return 0;
}

void barreras(int plazasocupadas){
    if(analogRead(irentrada)!=0&&plazasocupadas<max){
        myservoent.write(90);
        delay(2000);
        myservoent.write(0);
    }
    if(analogRead(irsalida)!=0){
        myservosal.write(90);
        delay(2000);
        myservosal.write(0);
    }
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


