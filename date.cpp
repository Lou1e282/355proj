#include "date.h"
#include <iostream> 
#include <sstream> 

Date::Date(string date_str){
    char sl1, sl2; 
    std::stringstream ss(date_str);
    ss >> month >> sl1 >> day >> sl2 >> year;   // sstream and slash
}

string Date::get_date(){
    std::stringstream ss;
    ss << month << "/" << day << "/" << year;
    return ss.str();
}


void Date::print_date(string date_str){
    static const string MONTHS[12] = {"January", 
        "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    std::cout << MONTHS[month - 1] << " " << day << ", " << year << std::endl; 
}

bool Date::operator==(const Date& rhs){
    return month == rhs.month && day == rhs.day && year == rhs.year;
}
