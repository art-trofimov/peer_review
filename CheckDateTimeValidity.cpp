struct DateTime
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    DateTime &ValidateYear() {
        if (year < 1) {
            throw domain_error("year is too small"s);
        }
        if (year > 9999) {
            throw domain_error("year is too big"s);
        }
        return *this;
    }

    DateTime &ValidateMonth() {
        if (month < 1) {
            throw domain_error("month is too small"s);
        }
        if (month > 12) {
            throw domain_error("month is too big"s);
        }
        return *this;
    }

    DateTime &ValidateDay() {
        const bool is_leap_year = (year % 4 == 0) && !(year % 100 == 0 && year % 400 != 0);
        const array month_lengths = {31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (day < 1) {
            throw domain_error("day is too small"s);
        }
        if (day > month_lengths[month - 1]) {
            throw domain_error("day is too big"s);
        }
        return *this;
    }

    DateTime &ValidateHour() {
        if (hour < 0) {
            throw domain_error("hour is too small"s);
        }
        if (hour > 23) {
            throw domain_error("hour is too big"s);
        }
        return *this;
    }

    DateTime &ValidateMinute() {
        if (minute < 0) {
            throw domain_error("minute is too small"s);
        }
        if (minute > 59) {
            throw domain_error("minute is too big"s);
        }
        return *this;
    }

    DateTime &ValidateSecond() {
        if (second < 0) {
            throw domain_error("second is too small");
        }
        if (second > 59) {
            throw domain_error("second is too big"s);
        }
        return *this;
    }
};


void CheckDateTimeValidity(const DateTime& dt) {
    dt.ValidateYear()
      .ValidateMonth()
      .ValidateDay()
      .ValidateHour()
      .ValidateMinute()
      .ValidateSecond();    
}