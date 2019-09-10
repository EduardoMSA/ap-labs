#include <stdio.h>
#include <stdlib.h>

/* month_day function's prototype*/
void month_day(int year, int yearday, char **pmonth, int *pday);
//void month_day(int year, int yearday);

int main(int argc, char **argv) {
    int day, year, yearday, *pday;
    char *month, **pmonth;
    year = atoi(argv[1]);
    yearday = atoi(argv[2]);
    pday = &day;
    pmonth = &month;
    month_day(year,yearday,pmonth,pday);
    printf("%s %d, %d\n", month, day, year);
    return 0;
}

void month_day(int year, int yearday, char **pmonth, int *pday){
  int leap_year, jan, feb, mar, apr, may, jun, jul, agu, sep, oct, nov, dec;

  if (year%4 == 0){
    if (year%100 == 0){
      if (year%400 == 0){
        leap_year = 1;
      } else{
        leap_year = 0;
      }
    } else{
      leap_year = 1;
    }
  } else{
    leap_year = 0;
  }

  jan = 31;
  if(leap_year){
    feb = 29;
  } else{
    feb = 28;
  }
  mar=31;
  apr=30;
  may=31;
  jun=30;
  jul=31;
  agu=31;
  sep=30;
  oct=31;
  nov=30;
  dec=31;

  int day,month;

  if (yearday <= jan){
    *pday=yearday;
    *pmonth="Jan";
  } else if (yearday <= (jan+feb)){
    *pday=yearday-jan;
    *pmonth="Feb";
  } else if (yearday <= (jan+feb+mar)){
    *pday=yearday-(jan+feb);
    *pmonth="Mar";
  } else if (yearday <= (jan+feb+mar+apr)){
    *pday=yearday-(jan+feb+mar);
    *pmonth="Apr";
  } else if (yearday <= (jan+feb+mar+apr+may)){
    *pday=yearday-(jan+feb+mar+apr);
    *pmonth="May";
  } else if (yearday <= (jan+feb+mar+apr+may+jun)){
    *pday=yearday-(jan+feb+mar+apr+may);
    *pmonth="Jun";
  } else if (yearday <= (jan+feb+mar+apr+may+jun+jul)){
    *pday=yearday-(jan+feb+mar+apr+may+jun);
    *pmonth="Jul";
  } else if (yearday <= (jan+feb+mar+apr+may+jun+jul+agu)){
    *pday=yearday-(jan+feb+mar+apr+may+jun+jul);
    *pmonth="Agu";
  } else if (yearday <= (jan+feb+mar+apr+may+jun+jul+agu+sep)){
    *pday=yearday-(jan+feb+mar+apr+may+jun+jul+agu);
    *pmonth="Sep";
  } else if (yearday <= (jan+feb+mar+apr+may+jun+jul+agu+sep+oct)){
    *pday=yearday-(jan+feb+mar+apr+may+jun+jul+agu+sep);
    *pmonth="Oct";
  } else if (yearday <= (jan+feb+mar+apr+may+jun+jul+agu+sep+oct+nov)){
    *pday=yearday-(jan+feb+mar+apr+may+jun+jul+agu+sep+oct);
    *pmonth="Nov";
  } else if (yearday <= (jan+feb+mar+apr+may+jun+jul+agu+sep+oct+nov+dec)){
    *pday=yearday-(jan+feb+mar+apr+may+jun+jul+agu+sep+oct+nov);
    *pmonth="Dec";
  }

}
