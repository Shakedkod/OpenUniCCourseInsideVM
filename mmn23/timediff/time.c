#include <stdio.h>
#include <limits.h>

#include "time.h"

#define DAYS_PER_YEAR 365
#define SECONDS_PER_HOUR (60 * 60)
#define SECONDS_PER_DAY (24 * SECONDS_PER_HOUR)

unsigned int _days_in_a_month[] = {
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
};
unsigned int _number_of_days_in_a_month[] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

long seconds_in_year(time t)
{
    return (
        (_days_in_a_month[t.month - 1] * SECONDS_PER_DAY) +
        ((t.day - 1) * SECONDS_PER_DAY) +
        (t.hour * SECONDS_PER_HOUR) +
        (t.minute * 60) +
        t.second
    );
}

unsigned long diff_time(time a, time b)
{
    long result, year;

    if (a.year == b.year)
    {
        if ((seconds_in_year(a) - seconds_in_year(b)) < 0)
            return seconds_in_year(b) - seconds_in_year(a);
        return seconds_in_year(a) - seconds_in_year(b);
    }

    if (a.year > b.year)
    {
        year = a.year - b.year;
        result = seconds_in_year(a) - seconds_in_year(b);
        return (year * DAYS_PER_YEAR * SECONDS_PER_DAY) + result;
    }

    year = b.year - a.year;
    result = seconds_in_year(b) - seconds_in_year(a);
    return (year * DAYS_PER_YEAR * SECONDS_PER_DAY) + result;
}

void print_time(time t)
{
    printf("%u/%u/%d %u:%u:%u", t.day, t.month, t.year, t.hour, t.minute, t.second);
}

int check_time(time t)
{
    if (t.day > _number_of_days_in_a_month[t.month - 1])
    {
        printf("The day %u isn't in this month\n", t.day);
        return 0;
    }

    return 1;
}