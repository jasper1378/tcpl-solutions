#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char *argv[]) {
  int year;
  int month;
  int day;
  int yearday;
  int pmonth;
  int pday;

  if (argc == 2) {
    if (strcmp(argv[1], "day_of_year") == 0) {
      printf("year = ");
      scanf("%d", &year);
      printf("month = ");
      scanf("%d", &month);
      printf("day = ");
      scanf("%d", &day);
      printf("day_of_year = %d\n", day_of_year(year, month, day));
      return EXIT_SUCCESS;
    } else if (strcmp(argv[1], "month_day") == 0) {
      printf("year = ");
      scanf("%d", &year);
      printf("yearday = ");
      scanf("%d", &yearday);
      month_day(year, yearday, &pmonth, &pday);
      printf("month_day = {month = %d, day = %d}\n", pmonth, pday);
      return EXIT_SUCCESS;
    }
  }
  return EXIT_FAILURE;
}
