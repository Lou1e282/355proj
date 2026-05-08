EE355 final project

Louie Shen  louieshe@usc.edu
Mina Karim  mkarim@usc.edu

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

Phase 3 Extra Credit:

We enlarged the database so Person now includes additional user information as key-value pairs using a map. Required fields unchanged but each entry now can include extra line before the separator, such as:

college: USC
major: Prompt Engineering
state: IDLE

When loading a database, the program reads these extra key-value lines until it
reaches "--------------------" and stores them in the Person object. When saving
or printing the database, the extra information is written back out with the
normal person information. Wise Search can also match these extra keys or values.

Time complexity: C++ map operations such as inserting or looking up one extra
field take O(log m), where m is the number of extra fields stored for one person.
The current Wise Search still scans through all n people, so searching basic
fields is O(n). If Wise Search also checks extra information, the worst case is
O(n * m), because it may inspect each person's extra fields.

ChatGPT Report:

ChatGPT was used as a coding assistant to help plan and implement the Phase 3
extra credit feature. It suggested storing flexible extra user information with
a map, updating the database load/save format, and documenting the time
complexity. The final code was reviewed and adjusted to fit the existing project
structure.

Demo Instructions:

1. Compile and run the project.
2. Choose option 2 to load `networkDB.txt`.
3. Choose option 5 or print the database to show each person's normal fields
   plus the new extra fields such as college, major, and state.
4. Choose option 7 for Wise Search and search for an extra value, for example
   `USC`, `Prompt Engineering`, or `IDLE`.
5. Choose option 3 to add a new person. After entering phone and email, enter
   extra key-value fields when prompted, then leave the key blank to stop.
6. Choose option 1 to save the database, then open the saved file to show that
   the extra information was written back in the same key-value format.






