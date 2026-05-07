EE355 final project

Louie Shen  louieshe@usc.edu
Mina Kharim mkarim@usc.edu

Phase 1:

Created a contact class with two subclasses: Phone and Email, including virtual methods for each of them, also implemented with their respective constructor.  

Created new class dates, and provided print_date to output dates in long form. 

Implemented Person class that hold communication forms, with constructors, destructor and print() for outputs. 

Implemented Network Class with Person stored in doubly linked lists of Person nodes. Supporting `loadDB()`, `saveDB()`, `push_back()`, `search()`, `remove()`, and the destructor.The main menu (`showMenu`) supports: (1) Save, (2) Load, (3) Add person, (4) Remove person, (5) Search by last name.

### Compilation

```bash
g++ -c contact.cpp -o contact.o
g++ -c date.cpp -o date.o
g++ -c misc.cpp -o misc.o
g++ -c network.cpp -o network.o
g++ -c person.cpp -o person.o
g++ -c test_network.cpp -o test_network.o
g++ contact.o date.o misc.o network.o person.o test_network.o -o test
./test
```

---

Phase 2:

Extends Phase 1 with friend connections and enhanced search. 

Add menu option 6 ("Connect") to make two people friends (bidirectional). Prompt for both people by first/last name; print "Person not found" if either doesn't exist.

Define a unique ID per person: concatenate first + last name, lowercase, spaces removed (e.g. "Enania" + "Mordak Young" → `enaniamordakyoung`). Implement the helper function `string codeName(string str1, string str2)` in `misc.h`/`misc.cpp`.

Update `print_person()` to list each friend's code and full name at the end

Implement `Person::print_friends()` to print friends sorted alphabetically by code name. Ties on the first letter are broken by the second letter; further ties can be resolved arbitrarily.

Add menu option 7 ("Wise Search") to search by any stored field — phone number, email, or birth date — not just last name.

Phase 3:

Implemented and maintained a vector storing people to speed up the search. 

