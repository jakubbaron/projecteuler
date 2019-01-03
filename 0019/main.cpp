#include <iostream>
#include <map>

// You are given the following information, but you may prefer to do some research for yourself.
// 
// 1 Jan 1900 was a Monday.
// Thirty days has September,
// April, June and November.
// All the rest have thirty-one,
// Saving February alone,
// Which has twenty-eight, rain or shine.
// And on leap years, twenty-nine.
// A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
// How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?

enum class WEEKDAY {
  MONDAY = 0,
  TUESDAY = 1,
  WEDNESDAY = 2,
  THURSDAY = 3,
  FRIDAY = 4,
  SATURDAY = 5,
  SUNDAY = 6,
  END_OF_LIST = 7
};

WEEKDAY& operator++( WEEKDAY &c ) {
  using IntType = typename std::underlying_type<WEEKDAY>::type;
  c = static_cast<WEEKDAY>( static_cast<IntType>(c) + 1 );
  if ( c == WEEKDAY::END_OF_LIST)
    c = static_cast<WEEKDAY>(0);
  return c;
}

WEEKDAY operator++( WEEKDAY &c, int ) {
  WEEKDAY result = c;
  ++c;
  return result;
}

class Date {
  public:
    Date(int day_, int month_, int year_, WEEKDAY weekday_ = WEEKDAY::SUNDAY);
    void increase_day();
    static int count_sundays_between(Date date_from, Date& date_to) noexcept;
    const auto is_first_sunday_of_month() const noexcept;
    const auto is_lap_year() const noexcept;
    const auto get_year() const noexcept;
  private:
    int day;
    int month;
    int year;
    WEEKDAY weekday;
    std::map<int, int> current_month_lenghts;

    const static std::map<int, int> month_lenghts;

    const static std::map<int, int> month_lenghts_leap;
};

const auto Date::is_lap_year() const noexcept {
  return year % 4 == 0;
}

Date::Date(int day_, int month_, int year_, WEEKDAY weekday_): day(day_), month(month_), year(year_), weekday(weekday_), current_month_lenghts(Date::month_lenghts) {
  if(is_lap_year()) {
    current_month_lenghts = Date::month_lenghts_leap;
  } else {
    current_month_lenghts = Date::month_lenghts;
  }
}

const auto Date::get_year() const noexcept {
  return year;
}

void Date::increase_day() {
  day++;  
  weekday++;
  if(day <= current_month_lenghts[month]) {
    return; 
  }
  day = 1;
  month++;
  if(month <= 12) {
    return;
  }
  month = 1;
  year++;

  if(is_lap_year()) {
    current_month_lenghts = Date::month_lenghts_leap;
  } else {
    current_month_lenghts = Date::month_lenghts;
  }
}

const auto Date::is_first_sunday_of_month() const noexcept {
  return day == 1 && weekday == WEEKDAY::SUNDAY;
}

int Date::count_sundays_between(Date date_from, Date& date_to) noexcept {
  int sundays = 0;
  while(date_from.day != date_to.day || date_from.month != date_to.month || date_from.year != date_to.year) {
    if(date_from.is_first_sunday_of_month()) {
      sundays++;
    }
    date_from.increase_day();
  }
  return sundays;
}

const std::map<int, int> Date::month_lenghts = {
  {1, 31},
  {2, 28},
  {3, 31},
  {4, 30},
  {5, 31},
  {6, 30},
  {7, 31},
  {8, 31},
  {9, 30},
  {10, 31},
  {11, 30},
  {12, 31}
};

const std::map<int, int> Date::month_lenghts_leap = {
  {1, 31},
  {2, 29},
  {3, 31},
  {4, 30},
  {5, 31},
  {6, 30},
  {7, 31},
  {8, 31},
  {9, 30},
  {10, 31},
  {11, 30},
  {12, 31}
};
int main(int argc, char** argv) {
  Date date_from(1, 1, 1900, WEEKDAY::MONDAY);
  while(date_from.get_year() != 1901) {
    date_from.increase_day();
  }
  Date date_to(31, 12, 2000);
  std::cout << "Sundays between dates: " << Date::count_sundays_between(date_from, date_to) << std::endl;
  return EXIT_SUCCESS;
}
