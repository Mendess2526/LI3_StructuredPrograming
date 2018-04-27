#ifndef __DATE_TIME_INTERVAL_H__
#define __DATE_TIME_INTERVAL_H__

#include "types.h"

DATETIME_INTERVAL dateTime_interval_create(DATETIME from, DATETIME to);

DATETIME dateTime_interval_from(DATETIME_INTERVAL dti);

DATETIME dateTime_interval_to(DATETIME_INTERVAL dti);

int dateTime_interval_is_between(DATETIME_INTERVAL dti, DATETIME d);

void dateTime_interval_destroy(DATETIME_INTERVAL dti);

void dateTime_interval_destroy_full(DATETIME_INTERVAL dti);

#endif /* __DATE_TIME_INTERVAL_H__ */
