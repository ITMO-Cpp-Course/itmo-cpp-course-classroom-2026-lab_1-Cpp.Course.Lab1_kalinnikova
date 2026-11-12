#include <catch2/catch_all.hpp>

#include "lab1/date.hpp"

using namespace lab1::date;

TEST_CASE("Leap year checks", "[leap]")
{
    REQUIRE(is_leap(2024) == true);
    REQUIRE(is_leap(2023) == false);
    REQUIRE(is_leap(2000) == true);
    REQUIRE(is_leap(1900) == false);
}

TEST_CASE("Days in month checks", "[days]")
{
    REQUIRE(days_in_month(2023, 2) == 28);
    REQUIRE(days_in_month(2024, 2) == 29);
    REQUIRE(days_in_month(2024, 4) == 30);
    REQUIRE(days_in_month(2024, 1) == 31);
}

TEST_CASE("Date validation", "[valid]")
{
    REQUIRE(is_valid({2024, 2, 29}) == true);
    REQUIRE(is_valid({2023, 2, 29}) == false);
    REQUIRE(is_valid({2024, 13, 1}) == false);
    REQUIRE(is_valid({-1, 1, 1}) == false);
    REQUIRE(is_valid({2024, 0, 1}) == false);
    REQUIRE(is_valid({0, 1, 1}) == true);
    REQUIRE(is_valid({9999, 12, 31}) == true);
    REQUIRE(is_valid({10000, 1, 1}) == false);
}
TEST_CASE("Day of week checks", "[weekday]")
{
    // четверг
    REQUIRE(day_of_week({1970, 1, 1}) == 4);

    // 2024-02-29 (високосный день) - четверг
    REQUIRE(day_of_week({2024, 2, 29}) == 4);

    // 2026-01-01 — четверг
    REQUIRE(day_of_week({2026, 1, 1}) == 4);

    REQUIRE(day_of_week({2025, 12, 31}) == 3);
}

TEST_CASE("Add days checks", "[add]")
{
    // + 0 дней — дата не меняется
    Date d1 = add_days({2026, 5, 15}, 0);
    REQUIRE(d1.year == 2026);
    REQUIRE(d1.month == 5);
    REQUIRE(d1.day == 15);

    // + 1 день
    Date d2 = add_days({2026, 5, 15}, 1);
    REQUIRE(d2.year == 2026);
    REQUIRE(d2.month == 5);
    REQUIRE(d2.day == 16);

    // переход через конец месяца
    Date d3 = add_days({2026, 1, 31}, 1);
    REQUIRE(d3.year == 2026);
    REQUIRE(d3.month == 2);
    REQUIRE(d3.day == 1);

    // отрицательное прибавление (вычитаем дни)
    Date d4 = add_days({2020, 3, 1}, -1);
    REQUIRE(d4.year == 2020);
    REQUIRE(d4.month == 2);
    REQUIRE(d4.day == 29);

    // переход через конец года
    Date d5 = add_days({2025, 12, 31}, 1);
    REQUIRE(d5.year == 2026);
    REQUIRE(d5.month == 1);
    REQUIRE(d5.day == 1);
}

TEST_CASE("Days between checks", "[diff]")
{
    // разница между 1 и 31 января = 30 дней
    REQUIRE(days_between({2020, 1, 1}, {2020, 1, 31}) == 30);

    // разница между одинаковыми датами = 0
    REQUIRE(days_between({2020, 5, 5}, {2020, 5, 5}) == 0);

    // порядок дат не должен быть важен (разница должна быть положительной)
    REQUIRE(days_between({2020, 1, 31}, {2020, 1, 1}) == 30);

    // разница между годами (2020 — високосный, 365 + 366 = 731)
    REQUIRE(days_between({2020, 1, 1}, {2022, 1, 1}) == 731);
}