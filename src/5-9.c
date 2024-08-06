#include <stdio.h>

static char daytab[2][12] = {{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                             {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int year, int month, int day) {
  int leap;
  char *p;

  leap = (((year % 4 == 0) && (year % 100 != 0)) || year % 400 == 0);
  for (p = daytab[leap]; p - daytab[leap] < month - 1; ++p)
    day += *p;
  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
  int leap;
  char *p;

  leap = (((year % 4 == 0) && (year % 100 != 0)) || year % 400 == 0);
  for (p = daytab[leap]; yearday > *p; ++p)
    yearday -= *p;
  *pmonth = p - daytab[leap] + 1;
  *pday = yearday;
}

int main() {
  printf("%d\n", day_of_year(1988, 2, 29));
  return 0;
}
