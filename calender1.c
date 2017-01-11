
#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<conio.h>

#define TRUE    1
#define FALSE   0

char month[][10]={"january","february","march","april","may","june","july","august","september","october","november","december"};
int noofdays[]={31,28,31,30,31,30,31,31,30,31,30,31};

int GetKey()
{
    union REGS in , out;
    in.h.ah = 0x8;
    int86( 0x21 , &in , &out );
    return out.h.al;
}
 int daycode(int year)
 {
     int d1, d2, d3;
     int day;

     d1 = (year - 1) / 4.0;
     d2 = (year - 1) / 100.;
     d3 = (year - 1) / 400.;

     day = (year + d1 - d2 + d3) % 7;

     return day;
 }

void calender(int year, char currentmonth[20], int day)
{
    int monthlimit, daylimit;

    for ( monthlimit = 0; monthlimit < 12; monthlimit++ )
	{
        if(strcmp(month[monthlimit], currentmonth)== 0)
        {
            printf("%d %s",year, currentmonth);
            printf("\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n" );

		// Correct the position for the first date
            for ( daylimit = 1; daylimit <= 1 + day * 5; daylimit++ )
            {
                printf(" ");
            }

            // Print all the dates for one month
            for ( daylimit = 1; daylimit <= noofdays[monthlimit]; daylimit++ )
            {
                printf("%2d", daylimit );

                // Is day before Sat? Else start next line Sun.
                if ( ( daylimit + day ) % 7 > 0 )
                    printf("   " );
                else
                    printf("\n " );
            }
        }
        else
        {
            day = ( day + noofdays[monthlimit] ) % 7;
        }

	}
}

int determineleapyear(int year)
{
	if(year% 4 == FALSE && year%100 != FALSE || year%400 == FALSE)
	{
		noofdays[1] = 29;
		return TRUE;
	}
	else
	{
		noofdays[1] = 28;
		return FALSE;
	}
}

 int main()
 {
//  clrscr();
    //char month[][10]={"january","february","march","april","may","june","july","august","september","october","november","december"};
    //char days[][10]={"mon","tue","wed","thu","fri","sat","sun"};

    int currentyear,start,key,i;
    char in[]="january", currentmonth[20];
    int year=2017;
    currentyear = year;
    strcpy(currentmonth, in);

    start = daycode(currentyear);
    determineleapyear(currentyear);
    calender(currentyear,currentmonth,start);
    while(key != 27)
    {
        //scanf("%d", &key);
        key = GetKey();
        if(key == 72)
        {
            currentyear = currentyear+1;
            start = daycode(currentyear);
            determineleapyear(currentyear);
            calender(currentyear,currentmonth,start);
        }
        else if(key == 80)
        {
            currentyear = currentyear-1;
            start = daycode(currentyear);
            determineleapyear(currentyear);
            calender(currentyear,currentmonth,start);
        }
        else if(key == 75)
        {
            i = 0;
            while(strcmp(currentmonth, month[i]) != 0)
            {
                i++;
            }
            if(i == 0)
            {
                i = 11;
                currentyear = currentyear - 1;
            }
            else
                i--;
            strcpy(currentmonth,month[i]);
            start = daycode(currentyear);
            determineleapyear(currentyear);
            calender(currentyear,currentmonth,start);
        }
        else if(key == 77)
        {
            i = 0;
            while(strcmp(currentmonth, month[i]) != 0)
            {
                i++;
            }
            if(i == 11)
            {
                i = 0;
                currentyear = currentyear + 1;
            }
            else
                i++;
            strcpy(currentmonth,month[i]);
            start = daycode(currentyear);
            determineleapyear(currentyear);
            calender(currentyear,currentmonth,start);
        }

    }
    return 0;

 }
