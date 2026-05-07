
#include "person.h"
#include "misc.h"
#include <algorithm>
#include <sstream> 

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
    print_friends();
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
