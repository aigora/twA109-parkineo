#include <string.h>
#include <time.h>
#include "SerialPort.h"


void Crear_Conexion(SerialPort *PuertoSerie,char *portName);
void CerrarConexion(SerialPort *PueroSerie);
int readSerialPort(SerialPort * PuertoSerie,char *buffer, unsigned int buf_size);
int writeSerialPort(SerialPort *PuertoSerie,char *buffer, unsigned int buf_size);
int isConnected(SerialPort *PuertoSerie);
void autoConnect(SerialPort *arduino,char*);

void main(void){
	SerialPort *arduino; //Arduino SerialPort object
	char* portName = "\\\\.\\COM5"; // Puerto serie en el que está Arduino
	char incomingData[MAX_DATA_LENGTH]; // Buffer para datos procedentes de Arduino
	arduino = (SerialPort *)malloc(sizeof(SerialPort)); // Crear estructura de datos del puerto serie
	Crear_Conexion(arduino,portName);
	autoConnect(arduino,incomingData); // Apertura del puerto serie
}
void autoConnect(SerialPort *arduino,char *incomingData){
    FILE *salida;
    time_t t;
    struct tm *tm;
    char output[100];
	int plazasocupadas,p1,p2,p3,p1aux=0,p2aux=0,p3aux=0,plazasocupadasaux=0;
	char readResult[MAX_DATA_LENGTH];
	while (!isConnected(arduino)){ // Espera la conexión con Arduino
		printf("Esperando la conexion con Arduino");
		Sleep(100);
		Crear_Conexion(arduino,arduino->portName);
	}
	if (isConnected(arduino)){
		printf("Conectado con Arduino en el puerto %s\n\n",arduino->portName);
		printf("Ahora aparece informacion sobre el estado del parking en tiempo real\n");
		printf("\n");
		printf("--------------------------------------------------------\n");
		printf("|   Total coches   |               Plaza               |\n"); 
		printf("|     interior     |     1     |     2     |     3     |\n");
		printf("--------------------------------------------------------\n");
		printf(" ");
        salida=fopen("historial.txt","wt");
        if(salida==NULL) printf("No se ha podido abrir el fichero\n");
        else{
            fprintf(salida,"HISTORIAL PARKING\n");
            fprintf(salida,"|   Total coches   |               Plaza               |     Fecha y hora      |\n"); 
			fprintf(salida,"|     interior     |     1     |     2     |     3     |                       |\n");
        }
	}
	else printf ("Se ha perdido la conexion con Arduino\n");
	while (isConnected(arduino)){
        printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		readSerialPort(arduino,incomingData,MAX_DATA_LENGTH);
		plazasocupadas=incomingData[0]-'0';
		p1=incomingData[1]-'0';
		p2=incomingData[2]-'0';
		p3=incomingData[3]-'0';
        if(plazasocupadas>=0&&plazasocupadas<=3){
            printf("|        %d       ",plazasocupadas);
            if(salida==NULL) printf("No se ha podido abrir el fichero\n");
            else if(plazasocupadasaux!=plazasocupadas||p1aux!=p1||p2aux!=p2||p3aux!=p3){
                fprintf(salida,"|        %d       ",plazasocupadas);
                if(p1==1)fprintf(salida,"  |  Ocupada");
                else fprintf(salida,"  |   Libre ");
                if(p2==1)fprintf(salida,"  |  Ocupada");
                else fprintf(salida,"  |   Libre ");
                if(p3==1)fprintf(salida,"  |  Ocupada  ");
                else fprintf(salida,"  |   Libre   ");
                t=time(NULL);
                tm=localtime(&t);
                strftime(output,100,"%d/%m/%Y %H:%M:%S",tm);
                fprintf(salida,"|  %s  |\n",output);
            }
        }
		else printf("|   Actualizando ");
		if(p1==1) printf("  |  Ocupada");
		else printf("  |   Libre ");
		if(p2==1) printf("  |  Ocupada");
		else printf("  |   Libre ");
		if(p3==1) printf("  |  Ocupada  |");
		else printf("  |   Libre   |");
		plazasocupadasaux=plazasocupadas;
		p1aux=p1;
		p2aux=p2;
		p3aux=p3;
		Sleep(500);
	}
	fclose(salida);
}

void Crear_Conexion(SerialPort *PuertoSerie, char *portName)
{

	PuertoSerie->connected = 0;
	PuertoSerie->portName = portName;
    PuertoSerie->handler = CreateFileA((portName),
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL);
    if (PuertoSerie->handler == INVALID_HANDLE_VALUE)
	{
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
            printf("ERROR: Handle was not attached. Reason: %s not available\n", portName);
        }
    	else
        {
            printf("ERROR!!!");
        }
    }
    else 
	{
        DCB dcbSerialParameters = {0};

        if (!GetCommState(PuertoSerie->handler, &dcbSerialParameters))
		{
            printf("failed to get current serial parameters");
        }
        else 
		{
            dcbSerialParameters.BaudRate = CBR_9600;
            dcbSerialParameters.ByteSize = 8;
            dcbSerialParameters.StopBits = ONESTOPBIT;
            dcbSerialParameters.Parity = NOPARITY;
            dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

            if (!SetCommState(PuertoSerie->handler, &dcbSerialParameters))
            {
                printf("ALERT: could not set Serial port parameters\n");
            }
            else 
			{
                PuertoSerie->connected = 1;
                PurgeComm(PuertoSerie->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(ARDUINO_WAIT_TIME);
            }
        }
    }
}
void CerrarConexion(SerialPort * PuertoSerie)
{
    if (PuertoSerie->connected)
	{
        PuertoSerie->connected = 0;
        CloseHandle(PuertoSerie->handler);
    }
}
int readSerialPort(SerialPort * PuertoSerie,char *buffer, unsigned int buf_size)
{
    DWORD bytesRead;
    unsigned int toRead = 0;

    ClearCommError(PuertoSerie->handler, &PuertoSerie->errors, &PuertoSerie->status);

    if (PuertoSerie->status.cbInQue > 0)
	{
        if (PuertoSerie->status.cbInQue > buf_size)
		{
            toRead = buf_size;
        }
        else toRead = PuertoSerie->status.cbInQue;
    }

    memset(buffer, 0, buf_size);

    if (ReadFile(PuertoSerie->handler, buffer, toRead, &bytesRead, NULL)) return bytesRead;

    return 0;
}
int writeSerialPort(SerialPort *PuertoSerie,char *buffer, unsigned int buf_size)
{
    DWORD bytesSend;

    if (!WriteFile(PuertoSerie->handler, (void*) buffer, buf_size, &bytesSend, 0))
	{
        ClearCommError(PuertoSerie->handler, &PuertoSerie->errors, &PuertoSerie->status);
        return 0;
    }
    else return 1;
}

int isConnected(SerialPort *PuertoSerie)
{
    if (!ClearCommError(PuertoSerie->handler, &PuertoSerie->errors, &PuertoSerie->status))
		PuertoSerie->connected = 0;
    return PuertoSerie->connected;
}
