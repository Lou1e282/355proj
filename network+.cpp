
#include "network.h"
#include <limits>
#include "misc.h"
#include <cctype>
#include <fstream>
#include <dirent.h>

static string trimExtraField(string text){
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

static string lowerText(string text){
    for (int i = 0; i < text.size(); i++)
        text[i] = tolower(text[i]);
    return text;
}

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}

// added vector people

Network::Network(string fileName){
    head = tail = NULL, count = 0, loadDB(fileName);
}

Network::~Network(){ 
    Person* ptr = head;
    while (ptr != NULL){
        Person* next = ptr->next;
        delete ptr;
        ptr = next;
    }
}

Person* Network::search(Person* searchEntry){
    // Searches the Network for searchEntry
    // if found, returns a pointer to it, else returns NULL
    for (int i = 0; i < people.size(); i++){
        if (*people[i] == *searchEntry)
            return people[i];
    }
    return NULL;
}


Person* Network::search(string fname, string lname){
    // New == for Person, only based on fname and lname
    // if found, returns a pointer to it, else returns NULL
    // Note: two ways to implement this, 1st making a new Person with fname and lname and and using search(Person*), 2nd using fname and lname directly. 
    for (int i = 0; i < people.size(); i++){
        if (people[i]->f_name == fname && people[i]->l_name == lname)
            return people[i];
    }
    return NULL;
}




void Network::loadDB(string filename){
    ifstream fin(filename.c_str());
    if (!fin)
        return;

    Person* ptr = head;
    while (ptr != NULL){
        Person* next = ptr->next;
        delete ptr;
        ptr = next;
    }
    head = NULL;
    tail = NULL;
    count = 0;
    people.clear();

    string fname, lname, bdate, contact1, contact2, line;
    while (getline(fin, fname)){
        if (fname == "")
            continue;
        if (!getline(fin, lname))
            break;
        if (!getline(fin, bdate))
            break;
        if (!getline(fin, contact1))
            break;
        if (!getline(fin, contact2))
            break;
        Person* person;
        if (contact1.find("@") != string::npos)
            person = new Person(fname, lname, bdate, contact1, contact2);
        else
            person = new Person(fname, lname, bdate, contact2, contact1);

        while (getline(fin, line)){
            if (line == "--------------------")
                break;

            int colon = line.find(":");
            if (colon != string::npos){
                string key = trimExtraField(line.substr(0, colon));
                string value = trimExtraField(line.substr(colon + 1));
                if (key != "")
                    person->add_info(key, value);
            }
        }

        push_back(person);
    }
}

void Network::saveDB(string filename){
    ofstream fout(filename.c_str());
    Person* ptr = head;
    while (ptr != NULL){
        fout << ptr->f_name << endl;
        fout << ptr->l_name << endl;
        fout << ptr->birthdate->get_date() << endl;
        fout << ptr->email->get_contact("full") << endl;
        fout << ptr->phone->get_contact("full") << endl;
        for (map<string, string>::iterator it = ptr->extraInfo.begin(); it != ptr->extraInfo.end(); it++)
            fout << it->first << ": " << it->second << endl;
        if (ptr->next != NULL)
            fout << "--------------------" << endl;
        ptr = ptr->next;
    }
}


void Network::printDB(){
    // Leave me alone! I know how to print! 
    // Note: Notice that we don't need to update this even after adding to Personattributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of people: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}



void Network::push_front(Person* newEntry){
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    people.push_back(newEntry); 
    count++;
}


void Network::push_back(Person* newEntry){
    // Adds a new Person (newEntry) to the back of LL
    newEntry->next = NULL;
    newEntry->prev = tail;

    if (tail != NULL)
        tail->next = newEntry;
    else
        head = newEntry;

    tail = newEntry;
    people.push_back(newEntry); 
    count++;
}


bool Network::remove(string fname, string lname){
    Person* ptr = search(fname, lname);
    if (ptr == NULL)
        return false;

    Person* curr = head;
    while (curr != NULL){
        for (int i = 0; i < curr->myfriends.size(); i++){
            if (curr->myfriends[i] == ptr){
                curr->myfriends.erase(curr->myfriends.begin() + i);
                i--;
            }
        }
        curr = curr->next;
    }

    if (ptr->prev != NULL)
        ptr->prev->next = ptr->next;
    else
        head = ptr->next;

    if (ptr->next != NULL)
        ptr->next->prev = ptr->prev;
    else
        tail = ptr->prev;

    for (int i = 0; i < people.size(); i++){
        if (people[i] == ptr){
            people.erase(people.begin() + i);
            break;
        }
    }

    delete ptr;
    count--;
    return true;
 
}


void Network::showMenu(){
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!

    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Remove a person \n";
        cout << "5. Print people with last name  \n";
        cout << "6. Connect \n";
        cout << "7. Wise Search \n";
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, fname2, lname2, query;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            getline(cin, fileName);
            // Save the network database into the file with the given name,
            // with each person saved in the format the save as printing out the person info,
            // and people are delimited similar to "networkDB.txt" format
            saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){
            cout << "Loading network database \n";
            // print format: one filename one line.
            // This step just shows all the available .txt file to load.
            DIR* dir = opendir(".");
            if (dir != NULL){
                dirent* entry;
                while ((entry = readdir(dir)) != NULL){
                    string name = entry->d_name;
                    if (name.size() >= 4 && name.substr(name.size() - 4) == ".txt")
                        cout << name << endl;
                }
                closedir(dir);
            }
            cout << "Enter the name of the load file: "; 
            getline(cin, fileName);
            // If file with name FILENAME does not exist: 
            ifstream fin(fileName.c_str());
            if (!fin){
                cout << "File " << fileName << " does not exist!" << endl;
                continue;
            }
            fin.close();
            loadDB(fileName);
            // If file is loaded successfully, also print the count of people in it: 
            cout << "Network loaded from " << fileName << " with " << count << " people \n";
        }
        else if (opt == 3){
            // Add a new Person ONLY if it does not exists!
            cout << "Adding a new person \n";
            Person* person = new Person();
            if (search(person->f_name, person->l_name) == NULL)
                push_front(person);
            else {
                cout << "Person already exists! \n";
                delete person;
            }
        }
        else if (opt == 4){
            // if found, cout << "Remove Successful! \n";
            // if not found: cout << "Person not found! \n";
            cout << "Removing a person \n";
            cout << "First name: ";
            getline(cin, fname);
            cout << "Last name: ";
            getline(cin, lname);
            if (remove(fname, lname))
                cout << "Remove Successful! \n";
            else
                cout << "Person not found! \n";
        }
        else if (opt==5){
            // print the people with the given last name
            // if not found: cout << "Person not found! \n";
            cout << "Print people with last name \n";
            cout << "Last name: ";
            getline(cin, lname);
            bool found = false;
            Person* ptr = head;
            while (ptr != NULL){
                if (ptr->l_name == lname){
                    ptr->print_person();
                    cout << "------------------------------" << endl;
                    found = true;
                }
                ptr = ptr->next;
            }
            if (!found)
                cout << "Person not found! \n";
        }
        else if (opt==6){
            cout << "Connect \n";
            cout << "First person's first name: ";
            getline(cin, fname);
            cout << "First person's last name: ";
            getline(cin, lname);
            cout << "Second person's first name: ";
            getline(cin, fname2);
            cout << "Second person's last name: ";
            getline(cin, lname2);

            Person* person1 = search(fname, lname);
            Person* person2 = search(fname2, lname2);

            if (person1 == NULL || person2 == NULL)
                cout << "Person not found" << endl;
            else {
                person1->makeFriend(person2);
                person2->makeFriend(person1);
                cout << "Connect Successful!" << endl;
            }
        }
        else if (opt==7){
            cout << "Wise Search \n";
            cout << "Search: ";
            getline(cin, query);
            query = trimExtraField(query);
            string lowerQuery = lowerText(query);

            bool found = false;
            Person* ptr = head;
            while (ptr != NULL){
                bool match = lowerText(ptr->f_name) == lowerQuery ||
                             lowerText(ptr->l_name) == lowerQuery ||
                             ptr->birthdate->get_date() == query ||
                             lowerText(ptr->email->get_contact()) == lowerQuery ||
                             lowerText(ptr->email->get_contact("")) == lowerQuery ||
                             ptr->phone->get_contact() == query ||
                             ptr->phone->get_contact("") == query ||
                             lowerText(codeName(ptr->f_name, ptr->l_name)) == lowerQuery;

                for (map<string, string>::iterator it = ptr->extraInfo.begin(); !match && it != ptr->extraInfo.end(); it++)
                    match = lowerText(it->first) == lowerQuery || lowerText(it->second) == lowerQuery;

                if (!match && query.find("/") != string::npos){
                    Date searchDate(query);
                    match = ptr->birthdate->get_date() == searchDate.get_date();
                }

                if (!match){
                    Phone searchPhone("", query);
                    match = ptr->phone->get_contact("") == searchPhone.get_contact("");
                }

                if (match){
                    ptr->print_person();
                    cout << "------------------------------" << endl;
                    found = true;
                }
                ptr = ptr->next;
            }

            if (!found)
                cout << "Person not found! \n";
        }
        
        else
            cout << "Nothing matched!\n";
        
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}
