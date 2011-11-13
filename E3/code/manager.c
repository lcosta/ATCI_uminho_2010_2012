/*
 
 Teaching: ATC I
 Exercise: T3
 Studant: Leonardo Costa (no. 62936)
 2011-2012
 SCM Repository: http://goo.gl/J8NqV
 
 */

#include <stdio.h>
#include "macros.h"
#include "manager.h"

const unsigned short _on[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; 
const unsigned short _off[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

t_station STATIONS[SIZE_STATION_ID];

/******** COMMUNICATION INTERFACE ********/
/*****************************************/
int readStations(){
    puts("load config...");
    FILE * f_config = fopen(CONFIG_FILE, "r");
    unsigned int station;
    unsigned int station_id;
    int i,j = 0;
    
    if (f_config == NULL){
        printf("ficheiro nao existe");
        return FALSE;
    } else {
        while (!feof(f_config) && (i <= MAX_STATION_ID)){
            fscanf(f_config, "%2X", &station);
            station_id = getId(station);
            STATIONS[station_id] = getStation(station);
            
            STATIONS[station_id].temp_min = 1000;
            STATIONS[station_id].temp_max = -1000;
            STATIONS[station_id].temp_med = 0;
            STATIONS[station_id].temp_count = 0;
            
            // init mod
            for(j=0; j<SIZE_MOD; j++){
                STATIONS[station_id].temp_mod[j] = 0;
            }
            
            i++;
        }
        
    }
    fclose(f_config);
    showStations();
    return TRUE;
}

int saveStations(){
    puts("...save config.");
    FILE * f_config = fopen(CONFIG_FILE, "w");
    
    if (f_config == NULL){
        printf("erro ao tentar abrir configuracoes");
        return FALSE;
    } else {
        int i = 0;
        unsigned short s;
        while (i <= MAX_STATION_ID){
            s = codeStation(STATIONS[i]);
            if(s){
                fprintf(f_config, "%2X", s);
                printf(">%2X\n", s);
            }
            i++;
        }
        puts("\n");
    }
    fclose(f_config);
    return TRUE;
}

int readTemperatureAutomatic(){
    FILE * f_data = fopen(DATA_FILE, "r");
    unsigned int station_id;
    int station_temperature;
    
    puts("read temperature automatic...");

    if (f_data == NULL){
        printf("ficheiro nao existe");
        return FALSE;
    } else {
        while (!feof(f_data)){
            
            if(fscanf(f_data, "%2X%2X", &station_id, &station_temperature) && 
               (station_id>= 0 && station_id < SIZE_STATION_ID) && STATIONS[station_id].automatic){
                
                //for moda calc
                STATIONS[station_id].temp_mod[station_temperature] += 1;
                
                checkNegative(&station_temperature);
            
                printf("id:%d (%X)  temp:%d\n", station_id, station_id, station_temperature);
                
                // set values min and max
                STATIONS[station_id].temp_count++;
                if(station_temperature < STATIONS[station_id].temp_min)
                    STATIONS[station_id].temp_min = station_temperature;
                if(station_temperature > STATIONS[station_id].temp_max)
                    STATIONS[station_id].temp_max = station_temperature;
        
                STATIONS[station_id].temp_med += station_temperature;
            } else {
                // clear invalid data
                fgetc(f_data);
            }
        }
        
    }
    fclose(f_data);
    showTemperatureStats();
    return TRUE;
}


int readTemperatureManual(){
    puts("read temperature manual...");
    FILE * f_data = fopen(DATA_FILE, "r");
    unsigned int station_id;
    int station_temperature;
    char x;
    int page = 0;
    if (f_data == NULL){
        printf("ficheiro nao existe");
        return FALSE;
    } else {
        printf("Para sair digite 'q' + ENTER - lista de %d em %d\n", SIZE_PAGE, SIZE_PAGE);
        while (!feof(f_data)){
            if(fscanf(f_data, "%2X%2X", &station_id, &station_temperature) && 
                (station_id>=0 && station_id < SIZE_STATION_ID) && STATIONS[station_id].automatic == FALSE){            

                    if(page % (SIZE_PAGE+1) == 0){
                        scanf( "%c", &x );
                        if(x=='q') return 1;
                        page = 1;
                    }

                    // negative
                    checkNegative(&station_temperature);

                    printf("> id:%d (%X)  temp:%.2f C\n", station_id, station_id, 
                        (STATIONS[station_id].celsius ? station_temperature : fahrenheitToCelsius(station_temperature)));
                    page++;

            } else {
                // clear invalid data
                fgetc(f_data);
            }
        }
        
    }
    fclose(f_data);
    puts(">\n");
    return TRUE;
}

void checkNegative(int * n){
    if(*n & _on[7]){
        *n &= _off[7];
        *n = (*n) * (-1);
    }
}

t_station getStation(unsigned short n){
    t_station s;
    s.id = getId(n);
    s.automatic = getAutomatic(n);
    s.active = getActive(n);
    s.celsius = getCelsius(n);
    return s;
}

int setStation(t_station s){
    STATIONS[s.id] = s;
    return codeStation(s);
}

unsigned short codeStation(t_station s){
    unsigned short code = 0x00;
    code = s.automatic | s.active | s.celsius | s.id;
    return code;
}

/******** FLAGS ********/
/***********************/

unsigned short getAutomatic(unsigned short station){
  return station & _on[5];
}

unsigned short getActive(unsigned short station){
  return station & _on[6];
}

unsigned short getCelsius(unsigned short station){
  return station & _on[7];
}

unsigned short setCelsius(unsigned short station, short is_true){
  return is_true ? station | _off[7] : station & _off[7];
}


/******** ID ********/
/********************/

unsigned short getId(unsigned short station){
  return station & ID_MASK;
}


unsigned short getOn(unsigned short idx){
  return _on[idx];
}

unsigned short getOff(unsigned short idx){
  return _off[idx];
}


void showStations(){
    int i =0;
    puts("\nStations List");
    while (i <= MAX_STATION_ID){
        printf("> %2X -> ID:%u, C:%u, AC:%u, AUT:%u\n",
               codeStation(STATIONS[i]), STATIONS[i].id, STATIONS[i].celsius,
               STATIONS[i].active, STATIONS[i].automatic);
        
        i++;
    }
    puts(">\n");
}

float fahrenheitToCelsius(short fahrenheit){
    return (fahrenheit - 32.0)*5.0/9.0;
}

void showTemperatureStats(){
    int i,j = 0;
    float med = 0.0;
    int mod, moda;
    char unit;
    puts("\nEstatisticas de Temperaturas");
    while (i <= MAX_STATION_ID){
        if(STATIONS[i].temp_count > 0 ){
            med = ((float)STATIONS[i].temp_med) / ((float)STATIONS[i].temp_count);
            // calc moda
            mod = moda = 0;
            for(j=0;j<SIZE_MOD;j++){
                if(STATIONS[i].temp_mod[j] > mod){
                    mod = STATIONS[i].temp_mod[j];
                    moda = j;
                    checkNegative(&moda);
                }
            }
            unit = STATIONS[i].celsius ? 'C' : 'F';
            printf("> ID:%d, min:%d %c, med:%.2f %c, max:%d %c, moda:%d %c\n", i, STATIONS[i].temp_min, unit, med, 
            unit,  STATIONS[i].temp_max, unit, moda, unit);

        }
        i++;
    }
    puts(">\n");
}