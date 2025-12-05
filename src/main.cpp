#include <iostream>

// TOPIC 3 - Object lifetime and RAII
// RAII = Resource Acquisition Is Initialization (object lifetime cruciality)

/*
    RAII = An object owns a resource, and when the object dies, the resource is released.
    ✔️ Why RAII exists: To avoid manual delete and give you automatic cleanup, safely.
     
    Stack object created in a function dies once hit the end of the body { .. } <-- end 
    Heap object die when manually deleted 
    
    e.g.
    Stack Object: <-- acts like a temporary guest that comes and goes by itself
    {
        Player p(100); <-- lives
    } <-- dies here
    
    Heap object: <-- acts like living in the house so manual "delete" necessaty
    {
        Player* p = new Player(100); <-- create address on  heap and store in pointer
    } <-- stil alive
    ...
    delete p; <-- dies here only with "delete"
    
    memory leak: if pointer dies incorrectly the address stays memoery leak
    
*/

class Logger
{
public:
    Logger() // constructor
    {
        std::cout << "Constructing Logger" << std::endl;
    }
    
    ~Logger() // destructor
    {
        std::cout << "Destructing Logger" << std::endl;
    }
};

int main()
{
    Logger a; // stack object; autoamtic construct and destruct
    Logger* b = new Logger(); // heap object
    delete b; // manually delete heap object

    return 0;
}

// TOPIC 2 — References vs Pointers
// This is the foundation for controlling access without copying in C++

// /*
//     Notes:
//     Reference: is an alias of a variable (e.g. another name for a variable int& r = a;) cannot be null
//     Pointer: is variable holding the address of a variable (int* p = a;) can be null
    
//     **A reference dies with its object.
//     A pointer survives but points to nothing valid.**
    
//     Think of the object (p) as a house.

//     Pointer
//     A pointer is like having the house address written on paper.
//     If the house is demolished:
//     You still hold the paper
//     The address is useless
//     If you go there → disaster
//     But you can rewrite the paper with a new address
//     Or null it out

//     Reference
//     A reference is like calling the house “my home”.
//     If the house is demolished:
//     You still say “my home”
//     But now the meaning is invalid
//     You cannot “rename” it to a different house
//     You cannot make it null
//     You simply have a meaningless alias
// */

// class Player 
// {
// public:
//     int health;
//     Player(int h) : health(h) {}
// };

// void ShowRef(const Player& x);
// void ShowPtr(const Player* x);

// int main() 
// {
//     std::cout << "hello world" << std::endl;
    
//     Player p(100); // stores value, but &p is the address
//     Player& ref = p; // another name for p..
//     Player* ptr = &p; // stores the address
    
//     ref.health = 60;
//     ptr->health = 80;
    
//     ShowRef(ref); // pass ref/p
//     ShowPtr(ptr); // pass address
//     return 0;
// }

// void ShowRef(const Player& x)
// {
//     std::cout << x.health << std::endl;
// }

// void ShowPtr(const Player* x)
// {
//     std::cout << x->health << std::endl;
// }

// TOPIC 1 1 -
// passing a variable to another it creates a copy
// class Item 
// {
// public:
//     int value;

//     Item(int v) : value(v) {
//         std::cout << "Construct: " << value << "\n";
//     }

//     Item(const Item& other) : value(other.value) {
//         std::cout << "Copy: " << value << "\n";
//     }
// };

// void Show(Item x) 
// {
//     std::cout << "Show: " << x.value << "\n";
// }

// int main() 
// {
//     Item firstItem(50);
//     Item secondItem = firstItem;   // Copy
//     Show(secondItem);              // Another copy
//     return 0;
// }