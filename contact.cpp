#include "contact.h"
#include <sstream>

static string normalize_phone(string phone_num){
    string digits;

    for (int i = 0; i < phone_num.size(); i++){
        if (phone_num[i] >= '0' && phone_num[i] <= '9')
            digits += phone_num[i];
    }

    if (digits.size() == 10)
        return digits.substr(0, 3) + "-" + digits.substr(3, 3) + "-" + digits.substr(6, 4);

    return phone_num;
}

Email::Email(string type, string email_addr){
    this->type = type;
    this->email_addr = email_addr;
}

void Email::print(){
    cout << "Email (" << type << "): " << email_addr << endl;
}

string Email::get_contact(string style){
    if (style == "full")
        return "(" + type + ") " + email_addr;

    return email_addr;
}

void Email::set_contact(){
    cout << "Type of email address: ";
    getline(cin, type);
    cout << "Email address: ";
    getline(cin, email_addr);
}

Phone::Phone(string type, string phone_num){
    this->type = type;
    this->phone_num = normalize_phone(phone_num);
}

void Phone::print(){
    cout << "Phone (" << type << "): " << phone_num << endl;
}

string Phone::get_contact(string style){
    if (style == "full")
        return "(" + type + ") " + phone_num;

    return phone_num;
}

void Phone::set_contact(){
    cout << "Type of phone number: ";
    getline(cin, type);
    cout << "Phone number: ";
    getline(cin, phone_num);
    phone_num = normalize_phone(phone_num);
}
