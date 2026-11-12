
#include "lab1/date.hpp"

namespace lab1::date
{

bool is_leap(int year) // проверка года на високосность
{
    // % - остаток от деления
    // && - и, || - или
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days_in_month(int year, int month) // определяем, сколько дней в месяце
{
    if (month == 2)
    {
        if (is_leap(year))
        {
            return 29;
        }
        else
        {
            return 28;
        }
    }

    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return 30;
    }

    return 31;
}

bool is_valid(Date date) // проверка даты на нормальность
{
    if (date.year < 0 || date.year > 9999)
        return false;
    if (date.month < 1 || date.month > 12)
        return false;
    if (date.day < 1 || date.day > days_in_month(date.year, date.month))
        return false;
    return true;
}

int days_from_epoch(Date date) // фнкция для подсчёта, сколько дней прошло с 01.01.0001
{
    int total_days = 0;

    // сколько дней прошло за полные прошедшие годы
    for (int y = 1; y < date.year;
         ++y) // ++ - прибавление 1 (если стоит до переменной, то сначала прибавляет 1, а потом использует)
    {
        if (is_leap(y))
        {
            total_days += 366;
        }
        else
        {
            total_days += 365;
        }
    }

    // сколько дней прошло за все полные месяцы в текущем году
    for (int m = 1; m < date.month; ++m)
    {
        total_days += days_in_month(date.year, m);
    }

    // прибавляем прошедшие дни в текущем месяце
    total_days += date.day;

    return total_days;
}

int day_of_week(Date date) // определяем день недели
{
    if (!is_valid(date)) // если введённая дата с ошибкой
    {
        return -1;
    }

    int total_days = days_from_epoch(date);

    // 01.01.0001 — понедельник (день 1) - остаток от деление 1 - совпадает с номером дня недели

    int w = total_days % 7;

    if (w == 0) // воскресенье
    {
        return 7;
    }
    return w;
}

Date date_from_days(int total_days) // функция для того, чтобы перевести количество дней с первого дня в дату
{
    Date d;
    d.year = 1;

    // вычитаем целые года
    while (true)
    {
        int days_in_year = 0;

        if (is_leap(d.year))
        {
            days_in_year = 366;
        }
        else
        {
            days_in_year = 365;
        }

        if (total_days > days_in_year)
        {
            total_days = total_days - days_in_year;
            d.year = d.year + 1;
        }
        else
        {
            break; // есои дней осталось меньше, чем в году — выходим из цикла
        }
    }

    // вычитаем целые месяцы
    d.month = 1;
    while (true)
    {
        int dim = days_in_month(d.year, d.month);

        if (total_days > dim)
        {
            total_days = total_days - dim;
            d.month = d.month + 1;
        }
        else
        {
            break;
        }
    }

    // то, что останется — дни в текущем месяце
    d.day = total_days;
    return d;
}

Date add_days(Date date, int delta) // прибавление дней
{
    int total = days_from_epoch(date) + delta; // перевели дату в дни и спокойно прибавили дни

    if (total < 1)
    {
        return {-1, 1, 1}; // если уйдём в минус, то вернём плохую дату
    }

    return date_from_days(total); // вернули дни в дату
}

int days_between(Date date1, Date date2) // находим, сколько дней между датами
{
    int days1 = days_from_epoch(date1);
    int days2 = days_from_epoch(date2);

    int diff = days1 - days2;
    if (diff < 0) // чтобы не было отрицательной разницы между датами
    {
        diff = -diff;
    }
    return diff;
}

} // namespace lab1::date
