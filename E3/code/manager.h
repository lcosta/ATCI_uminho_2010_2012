/*
 
 Teaching: ATC I
 Exercise: T2
 Studant: Leonardo Costa (no. 62936)
 2011-2012
 SCM Repository: http://goo.gl/J8NqV
 
 == Documentations
 
    * set bits *
        __________________
        |7|6|5||4|3|2|1|0|
            
           id | 4..0, ID da estacao, ranger 0..2^5=32, setID( TYPE )
            
              | 5, F/C -> 0/1
        flags | 6, desactivo/activo -> 0/1
              | 7, manual/automatico -> offAutomatic( TYPE ) / onAutomatic( TYPE )
                                        TYPE: const U8 onMask[8] or 

                
*/



#ifndef _TEMP_MANAGER_
#define _TEMP_MANAGER_

#define CONFIG_FILE "config.dat"
#define DATA_FILE "dados.dat"

#define SIZE_STATION_ID 32
#define MAX_STATION_ID 0x1F

#define SIZE_MOD 256
#define SIZE_PAGE 10

#define ID_MASK 0x1F


typedef struct {
    unsigned short id;
    unsigned short automatic;
    unsigned short active;
    unsigned short celsius;
    short temp_count;
    short temp_min;
    short temp_max;
    short temp_med;
    short temp_mod[SIZE_MOD];
} t_station;


/******** COMMUNICATION INTERFACE ********/
/*****************************************/
int readStations();
int saveStations();
int readTemperatureAutomatic();
int readTemperatureManual();

t_station getStation(unsigned short n);
int setStation(t_station s);
unsigned short codeStation(t_station s);

/******** FLAGS ********/
/***********************/
unsigned short getAutomatic(unsigned short station);
unsigned short getActive(unsigned short station);
unsigned short getCelsius(unsigned short station);
unsigned short setCelsius(unsigned short station, short is_true);

/******** ID ********/
/********************/
unsigned short getId(unsigned short station);


unsigned short getOn(unsigned short idx);
unsigned short getOff(unsigned short idx);

void showStations();

float fahrenheitToCelsius(short fahrenheit);
void showTemperatureStats();
void checkNegative(int * n);
#endif

