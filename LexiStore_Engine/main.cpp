#include <iostream>
#include <string>
#include "KVStore.h"
#include "Entry.h"
#include "Utils.h"

using namespace std;
using namespace LexiStore;
    
   // A quick helper to prove the Rule of Three works before the menu starts
   void testMemoryLogic() {
    cout << ">>> Initializing Memory Logic Check..." << endl;
    Entry e1("Admin", "SuperUser");
    Entry e2 = e1; // Tests Copy Constructor
    Entry e3;
    e3 = e1;       // Tests Assignment Operator
   
    cout << "Original: "; e1.display();
    cout << "Copy:     "; e2.display();
    cout << "Assign:   "; e3.display();
    cout << ">>> Memory Check Passed (No Crashes)\n" << endl;
   }
   
   int main() {
   KVStore myStore;
   int choice;

   cout << "=== LexiStore Engine: Pro Edition ===" << endl;

   // 1. Run the automated check
   testMemoryLogic();

   // 2. Interactive Database Menu (Uses Utils!)
   do {
    cout << "--- Database Menu ---" << endl;
    cout << "1. Add New Entry (+=)\n2. Search by Key ([])\n3. Display All Database\n0. Exit System" << endl;
        
    // Using your Utils here!
    choice = getInt(0, 3, "Select an option: ");

    if (choice == 1) {
        // std::string rather than char[128]: `cin >> buffer` on a fixed array
        // has no idea how big that array is, so a key longer than 127
        // characters walks straight off the end of the stack frame. Reading
        // into a string grows it instead, and the token-at-a-time behaviour is
        // unchanged.
        std::string k, v;
        cout << "Enter Key: ";   cin >> k;
        cout << "Enter Value: "; cin >> v;

        myStore += Entry(k.c_str(), v.c_str()); // Triggers your resizing logic!
        cout << "Entry added successfully." << endl;
        clearBuffer();
    } 
    else if (choice == 2) {
        std::string k;
        cout << "Enter Key to Search: "; cin >> k;

        const char* val = myStore[k.c_str()]; // Triggers your search logic!
        if (val) {
        cout << ">> FOUND: Key [" << k << "] has Value [" << val << "]" << endl;
        } else {
        cout << ">> NOT FOUND: Key [" << k << "] does not exist." << endl;
        }
      clearBuffer();
       }
        else if (choice == 3) {
        myStore.display(); // Triggers your loop display!
       }

    } while (choice != 0);

   cout << "Shutting down LexiStore. All memory cleared. Goodbye!" << endl;

    return 0;
}