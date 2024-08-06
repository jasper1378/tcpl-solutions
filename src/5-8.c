#include <stdio.h>
#include <stdlib.h>

#define ASSERT(cond_, emsg_)                                                   \
  if (!(cond_)) {                                                              \
    fprintf(stderr, "ERROR: " emsg_ "\n");                                     \
    exit(EXIT_FAILURE);                                                        \
  }

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int year, int month, int day) {
  int i, leap;

  ASSERT(year >= 0, "invalid year");
  ASSERT(month >= 1 && month <= 12, "invalid month");

  leap = (((year % 4 == 0) && (year % 100 != 0)) || year % 400 == 0);

  ASSERT(day >= 1 && day <= daytab[leap][month], "invalid day");

  for (i = 1; i < month; i++)
    day += daytab[leap][i];
  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
  int i, leap;

  ASSERT(year >= 0, "invalid year");
  ASSERT(pmonth != NULL, "NULL pmonth");
  ASSERT(pday != NULL, "NULL pday");

  leap = (((year % 4 == 0) && (year % 100 != 0)) || year % 400 == 0);

  ASSERT((yearday >= 1) &&
             ((leap && yearday <= 366) || (!leap && yearday <= 365)),
         "invalid yearday")

  for (i = 1; yearday > daytab[leap][i]; i++)
    yearday -= daytab[leap][i];
  *pmonth = i;
  *pday = yearday;
}
