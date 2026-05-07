
#include "person.h"
#include "misc.h"
#include <algorithm>
#include <cctype>
#include <sstream> 

static string trim(string text){
    int start = 0;
    int end = text.size() - 1;

    while (start < text.size() && isspace(text[start]))
        start++;

    while (end >= start && isspace(text[end]))
        end--;

    if (start > end)
        return "";

    return text.substr(start, end - start + 1);
}

static string get_contact_type(string contact){
    int start = contact.find("(");
    int end = contact.find(")");

    if (start == string::npos || end == string::npos)
        return "";

    return contact.substr(start + 1, end - start - 1);
}

static string get_contact_value(string contact){
    int end = contact.find(")");

    if (end == string::npos)
        return contact;

    return contact.substr(end + 2);
}


Person::Person(){
    // I'm already done! 
    set_person();
}


Person::~Person(){
    delete birthdate;
    delete email;
    delete phone; 
}

Person::Person(string f_name, string l_name, string b_date, string email, string phone){
    // phone and email strings are in full version
    this->f_name = f_name;
    this->l_name = l_name; 
    birthdate = new Date(b_date);
    this->email = new Email(get_contact_type(email), get_contact_value(email));
    this->phone = new Phone(get_contact_type(phone), get_contact_value(phone));

    next = 0;
    prev = 0;     
}   



Person::Person(string filename){
    set_person(filename);
}


void Person::set_person(){
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    string temp;
    string type;

    cout << "First Name: ";
    // pay attention to how we read first name, as it can have spaces!
    std::getline(std::cin,f_name);

	cout << "Last Name: ";
    std::getline(std::cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    std::getline(std::cin,temp);
    // pay attention to how we passed argument to the constructor of a new object created dynamically using new command
    birthdate = new Date(temp); 

    cout << "Type of email address: ";
    std::getline(std::cin, type);
    cout << "Email address: ";
    std::getline(std::cin, temp); 
    email = new Email(type, temp); 

    cout << "Type of phone number: ";
    std::getline(std::cin, type);
    cout << "Phone number: ";
    std::getline(std::cin, temp);
    phone = new Phone(type, temp); 

    while (true){
        string key;
        string value;
        cout << "Extra info key (blank to stop): ";
        std::getline(std::cin, key);
        key = trim(key);
        if (key == "")
            break;
        cout << "Extra info value: ";
        std::getline(std::cin, value);
        add_info(key, value);
    }
}


void Person::set_person(string filename){
    // reads a Person from a file
    // Look at person_template files as examples.     
    // Phone number in files can have '-' or not.
    std::ifstream fin(filename.c_str());

    if(!fin) {
        std::cout << "File does not exist!" << std::endl; 
        return;
    }

    string b_date;
    string contact1;
    string contact2;

    std::getline(fin, f_name);
    std::getline(fin, l_name);
    std::getline(fin, b_date);
    std::getline(fin, contact1);
    std::getline(fin, contact2);

    birthdate = new Date(b_date);

    if (contact1.find("@") != string::npos){
        email = new Email(get_contact_type(contact1), get_contact_value(contact1));
        phone = new Phone(get_contact_type(contact2), get_contact_value(contact2));
    }
    else{
        phone = new Phone(get_contact_type(contact1), get_contact_value(contact1));
        email = new Email(get_contact_type(contact2), get_contact_value(contact2));
    }

    next = 0;
    prev = 0;

    string line;
    while (std::getline(fin, line)){
        if (line == "--------------------")
            break;

        int colon = line.find(":");
        if (colon != string::npos){
            string key = trim(line.substr(0, colon));
            string value = trim(line.substr(colon + 1));
            if (key != "")
                add_info(key, value);
        }
    }
}


bool Person::operator==(const Person& rhs){
    // Note: you should check first name, last name and birthday between two persons
    // refer to bool Date::operator==(const Date& rhs)
    return f_name == rhs.f_name && l_name == rhs.l_name && *birthdate == *rhs.birthdate;
}

bool Person::operator!=(const Person& rhs){ 
    return !(*this == rhs);
}


void Person::print_person(){
    // Already implemented for you! Do not change!
	cout << l_name <<", " << f_name << endl;
    birthdate->print_date("Month D, YYYY");
    phone->print();
    email->print();
    print_extra_info();
    print_friends();
}

void Person::print_extra_info(){
    for (map<string, string>::iterator it = extraInfo.begin(); it != extraInfo.end(); it++)
        cout << it->first << ": " << it->second << endl;
}

void Person::add_info(string key, string value){
    extraInfo[key] = value;
}

void Person::makeFriend(Person* newFriend){
    if (newFriend == NULL || newFriend == this)
        return;

    for (int i = 0; i < myfriends.size(); i++){
        if (myfriends[i] == newFriend)
            return;
    }

    myfriends.push_back(newFriend);
}

void Person::print_friends(){
    vector<Person*> sortedFriends = myfriends;
    sort(sortedFriends.begin(), sortedFriends.end(), [](Person* lhs, Person* rhs){
        return codeName(lhs->f_name, lhs->l_name) < codeName(rhs->f_name, rhs->l_name);
    });

    for (int i = 0; i < sortedFriends.size(); i++){
        cout << codeName(sortedFriends[i]->f_name, sortedFriends[i]->l_name)
             << " (" << sortedFriends[i]->f_name << " "
             << sortedFriends[i]->l_name << ")" << endl;
    }
}
