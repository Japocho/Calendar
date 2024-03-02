#include <stdio.h>
#include <ctype.h>

int getYear(void);
int getType(void);
int getMonth(void);
int calculateFirstDayOfMonth(int year, int month, int IsLeapYear);
int calculateLeap(int year);
int calculateDays(int month, int IsLeapYear);
void printCalendar(int month, int day, int year, int dayOfWeek);
void printMonth(int year, int month, int dayOfWeek, int daysInMonth);
void printHeader(int year, int month);
void clear(void);

int main(void){
  int month;
  int day;
  int year;
  int dayOfWeek;
  int isLeapYear;
  int daysInMonth;
  int type;
  int i;
  
  year=getYear();
  type=getType();
  
  isLeapYear=calculateLeap(year);
  
  if(type){
    for(i=0;i<12;i++){
      dayOfWeek=calculateFirstDayOfMonth(year, i+1, isLeapYear);
      daysInMonth=calculateDays(i+1, isLeapYear);
      printMonth(year, i+1, dayOfWeek, daysInMonth);
    }
  }
  else{
    month=getMonth();
    dayOfWeek=calculateFirstDayOfMonth(year, month, isLeapYear);
    daysInMonth=calculateDays(month, isLeapYear);
    printMonth(year, month, dayOfWeek, daysInMonth);     
  }
}
 
/***********************************************************
getYear()
***********************************************************/
int getYear(void){
  int year;
  while(1){
    printf("\nEnter the year for which you would like to see the calendar:");
    scanf("%d", &year);
    clear();
    
    if(year<1752){
      printf("\nError: Year cannot be less than 1752.\n");
      printf("1752 is the year in which English speaking\n");
      printf("countries began using the Gregorian Calendar\n");
    }
    else
      break;
  }
  return year;
}

/***********************************************************
getType()
***********************************************************/
int getType(void){
  char choice;
  
  while(1){
    printf("\nWould you like to see the calendar for:\n");
    printf("The whole (Y)ear?\n");
    printf("One (M)onth?\n\n");
    printf("Enter Choice > ");
    choice=getchar();
    clear();//get the newline input and any errant characters they've entered
    
    if(toupper(choice)=='Y')
      return 1;
    else if(toupper(choice)=='M')
      return 0;
    else
      printf("\nERROR: invalid choice. Try again.\n");
  }
}

/***********************************************************
clear()
***********************************************************/
void clear(){
  while ( getchar() != '\n' ); //flush the input of characters
}

/***********************************************************
getMonth()
***********************************************************/
int getMonth(void){
  int month;

  while(1){
    printf("\nEnter the month and a number for which\nyou would like to see the calendar (1=Jan, 2=Feb, ..., 12=Dec):");
    scanf("%d", &month);
    clear();

    if(month>=1 && month<=12){
      return month;
    }
      printf("Error: Month cannot be less than 1 or greater than 12\n");
  
  }
}
/***********************************************************
calculateLeap()
***********************************************************/
int calculateLeap(int year){
  if((!(year%4) && (year%100)) || !(year%400))
    return 1;
  return 0;
}

/***********************************************************
calculateFistDayOfMonth()
***********************************************************/
int calculateFirstDayOfMonth(int year, int month, int IsLeapYear){
  int dayOfWeek;

  int keyValue[]={0,1,4,4,0,2,5,0,3,6,1,4,6};
  int code;
  int last2Digits;

  last2Digits=year%100;
  dayOfWeek=last2Digits;
  dayOfWeek=dayOfWeek/4;
  dayOfWeek++;//Add one for first day of month. We are always looking for the first day
  dayOfWeek=dayOfWeek+keyValue[month];// Adding key value
 
  if(month<3 && IsLeapYear){
    dayOfWeek--; //Year is a leap year so subtracting one for either jan or feb
    }
  
  year=(year/100)*100;
  
  while(year>2000){ //Year is greater than 2099 so adjust for century code
      year=year-400;
    }
  //get century code
  if(year>1699 && year<1800)
    code=4;
  else if(year>1799 && year<1900)
    code=2;
  else if(year>1899 && year<2000)
    code=0;
  else
    code=6;
  
  dayOfWeek=dayOfWeek+code;
  dayOfWeek=dayOfWeek+last2Digits;
  dayOfWeek=dayOfWeek%7;//get day of week: 1, 2, 3, 4, 5, 6, 0

  if(dayOfWeek==0)
    dayOfWeek=7; //the calculation makes Saturday 0, so change it to 7
  
 return dayOfWeek;
}

/***********************************************************
calculateDays()
***********************************************************/
int calculateDays(int month, int IsLeapYear){

    int daysInMonths[]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    daysInMonths[2]=28+IsLeapYear;

    return(daysInMonths[month]);
}

/***********************************************************
printMonth()
***********************************************************/
void printMonth(int year, int month, int dayOfWeek, int daysInMonth){
  int i;
  int day=1;
  int newline=0;

  printHeader(year, month);

  for(i=1;i<=7;i++)
   {
    if(i<dayOfWeek)
	printf("    ");
    else
     printf("%4d", day++);
   }
  printf("\n");

  for(i=0;day<=daysInMonth;i=(i+1)%7){
    printf("%4d", day++);

    if(i==6)
     printf("\n");
   }
  printf("\n");
}

/***********************************************************
printHeader()
***********************************************************/
void printHeader(int year, int month){
  char *months[]={"DUMMY", "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"};
  
  printf("\n\n\n");
  printf(" %-15s%12d\n", months[month],year); 
  printf(" ---------------------------\n");
  printf(" SUN MON TUE WED THU FRI SAT\n");
}
