#ifndef DATE_H
#define DATE_H

#include <string>
using namespace std;

class Date{
private:
    int month;
    int day;
    string year; 
public:
    Date(string date_str); 
    string get_date();
    void print_date(string date_str); 
    bool operator==(const Date& rhs);
}; 

#endif
