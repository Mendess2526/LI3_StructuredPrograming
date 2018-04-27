#include "dateTimeInterval.h"
#include "dateTime.h"

#include <stdlib.h>

struct _dateTime_interval{
    DATETIME from;
    DATETIME to;
};

DATETIME_INTERVAL dateTime_interval_create(DATETIME from, DATETIME to){
    DATETIME_INTERVAL dti = (DATETIME_INTERVAL) malloc(sizeof(struct _dateTime_interval));
    dti->from = from;
    dti->to = to;
    return dti;
}

DATETIME dateTime_interval_from(DATETIME_INTERVAL dti){
    return dti->from;
}

DATETIME dateTime_interval_to(DATETIME_INTERVAL dti){
    return dti->to;
}

int dateTime_interval_is_between(DATETIME_INTERVAL dti, DATETIME d){
    return dateTime_compare(d, dti->from) >= 0
           && dateTime_compare(d, dti->to) <= 0;
}

void dateTime_interval_destroy(DATETIME_INTERVAL dti){
    free(dti);
}

void dateTime_interval_destroy_full(DATETIME_INTERVAL dti){
    dateTime_destroy(dti->from);
    dateTime_destroy(dti->to);
    dateTime_interval_destroy(dti);
}

