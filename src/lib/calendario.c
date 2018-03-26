#include "calendario.h"

typedef struct _dia DIA;


typedef struct _mes{
    DIA *dias; 
}MES;

typedef struct _ano{
    MES *meses;
}ANO;

struct _calendario{
    ANO *anos;
};

void calendario_add_post(CALENDARIO cal, POST post){
    
}
