#include "calendario.h"

typedef GSList * POSTS;

typedef struct _hora{
    POSTS posts;
}HORA;

typedef struct _dia{
    HORA *horas;
}DIA;

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
