#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>   // Подключаем библиотеку для работы с текстовыми потоками
#include "lab1/date.hpp"

using namespace lab1::date;

// Функция для превращения текста "2024-01-01" в структуру Date
Date parse_date(const std::string& str)
{
    Date d;
    char dash1, dash2;         // создали переменные для дефисов (символов между числами в дате)
    std::stringstream ss(str); // кладем нашу строку в поток

    // Читаем: число, символ, число, символ, число
    ss >> d.year >> dash1 >> d.month >> dash2 >> d.day;

    // Если поток не смог прочитать данные или дефисы оказались не дефисами
    if (ss.fail() || dash1 != '-' || dash2 != '-')
    {
        d.year = -1; // специально портим год, чтобы вывести ошибку ввода даты
    }
    return d;
}

// argc - количество слов (тут чисел), argv - массив слов

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: date_cli <command> [args]\n"; // вывели, что не так
        return 1; //завершили программу с ошибкой (ненулевым выходным кодом)
    }

    std::string command = argv[1];

    if (command == "validate")
    {
        if (argc < 3) //не ввели дату
        {
            std::cout << "Error: missing date argument\n";
            return 1; 
        }

        Date d = parse_date(argv[2]); // преобразовали переданную дату в наш формат
        if (is_valid(d))
        {
            std::cout << "OK\n";
        }
        else
        {
            std::cout << "INVALID\n";
            return 1;
        }
    }

    else if (command == "weekday")
    {
        if (argc < 3)
        {
            std::cout << "Error: missing date argument\n";
            return 1;
        }
        Date d = parse_date(argv[2]);
        if (!is_valid(d))
        {
            std::cout << "INVALID\n";
            return 1;
        }

        int w = day_of_week(d);

        //индекс 0 пустой, чтобы воспользоваться тем, что в функции мы обозначили дни недели цифрами от 1 до 7
        const char* names[] = {"", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
        std::cout << names[w] << "\n";
    }

    else if (command == "add")
    {
        if (argc < 4)
        {
            std::cout << "Error: missing arguments\n";
            return 1;
        }
        Date d = parse_date(argv[2]);
        int delta = std::stoi(argv[3]); // превращаем текст в число
        Date res = add_days(d, delta);

        if (!is_valid(res))
        {
            std::cout << "INVALID\n";
            return 1;
        }
        // std::setfill('0') добавляет нули, если число меньше 10, чтобы вывод был в стандартной форме
        std::cout << std::setfill('0') << std::setw(4) << res.year << "-" << std::setw(2) << res.month << "-"
                  << std::setw(2) << res.day << "\n";
    }
    else if (command == "diff")
    {
        if (argc < 4)
        {
            std::cout << "Error: missing arguments\n";
            return 1;
        }
        Date d1 = parse_date(argv[2]);
        Date d2 = parse_date(argv[3]);
        int diff = days_between(d1, d2);
        std::cout << diff << "\n";
    }

    else
    {
        std::cout << "Unknown command: " << command << "\n";
        return 1;
    }

    return 0;
}