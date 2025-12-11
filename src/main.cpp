#include <iostream>
#include "../include/calculator.h"

// TOPIC 5 — Header / Source Structure

/*
    Header (.h / .hpp)
    Contains declarations:
    class definitions
    function declarations
    struct definitions
    enums
    constants
    templates
    
    Source (.cpp)
    Contains implementations:
    function bodies
    method bodies
    logic
    
    Use this rule:
    ✔️ If a class has logic → split into .h and .cpp
    ✔️ If a class is tiny or templated → header-only
    ✔️ If a class is used in multiple files → split
    ✔️ If it’s implementation detail → .cpp
    
    ✔️ Rule 1 — Headers include ONLY what they need
    If header uses std::string, include <string>.
    ✔️ Rule 2 — Never include <iostream> in headers (unless needed)
    Put heavy includes in .cpp, not .h.
    ✔️ Rule 3 — Use #pragma once
    Simple and modern include guard.
    ✔️ Rule 4 — Don’t put using namespace std; in headers
*/

int main()
{
    // Calculator calculator; // to create an object
    std::unique_ptr<Calculator> calculator = std::make_unique<Calculator>(); // or use a pointer
    std::cout << "Add: " << calculator->Add(3, 3) << std::endl;
    std::cout << "Sub: " << calculator->Sub(9, 2) << std::endl;
    std::cout << "Mul: " << calculator->Mul(6, 6) << std::endl;
    std::cout << "Div Wrong: " << calculator->Div(9, 0) << std::endl;
    std::cout << "Div Right: " << calculator->Div(9.0, 3.0) << std::endl;
    return 0;
}




// ###
// TOPIC 4 - Smart Pointers 
// Modern C++ Memory Safety

// /*
//     - raw points use "new" and "delete" (unsafe)
//     - smart pointers prevent all bad lucks.
    
//     std::unique_ptr (only one owner)
//     ↪ object destroyed when owner goes out of scope { ... }
//     - destructor is automatic don't need "delete"
//     - you cannot copy it as it passes ownership hence becomes null (e.g. auto p2 = std::move(p1); // p1 becomes null)
//     e.g. std::unique_ptr<Player> p = std::make_unique<Player>(100);
    
//     std::shared_ptr (multiple owners)
//     ↪ object detroyed when last referes goes away
//     - multiple smart pointers share the same object
//     - destructors runs when "all" owners of the same object die
//     e.g. std::shared_ptr<Player> p1 = std::make_shared<Player>(100);
//          std::shared_ptr<Player> p2 = p1; // both own it
    
//     std::weak_ptr (non-owning reference)
//     A → B
//     B → A
//     They will never reach zero references, which means:
//     -  destructors never run
//     - memory is leaked
//     - application keeps growing in RAM
//     Player → Weapon (shared_ptr)
//     Weapon → Player (weak_ptr)
//     Player OWNS the Weapon
//     Weapon just REFERS to Player but DOES NOT keep Player alive
//     does NOT keep the object alive
//     it only observes an object owned by shared_ptr
//     when the object dies, weak_ptr automatically becomes “expired”
//     it does NOT hold a valid address anymore
//     to use a weak pointer:
//     auto sp = weak.lock(); // auto means var in C#
//     if (sp) {
//         // object still alive
//     }
    
//     CODE EXAMPLE:
//     #include <iostream>
//     #include <memory>

//     class Player {
//     public:
//         Player()  { std::cout << "Player created\n"; }
//         ~Player() { std::cout << "Player destroyed\n"; }
//     };

//     int main() {
//         // 1) UNIQUE_PTR → owns Player exclusively
//         std::unique_ptr<Player> up = std::make_unique<Player>();

//         // 2) SHARED_PTR → shared ownership
//         std::shared_ptr<Player> sp1 = std::make_shared<Player>();
//         std::shared_ptr<Player> sp2 = sp1; // both share

//         std::cout << "Shared count: " << sp1.use_count() << "\n"; // prints 2

//         // 3) WEAK_PTR → does NOT own the object
//         std::weak_ptr<Player> wp = sp1; // refers to same Player, but does NOT keep alive

//         // Check if weak_ptr sees object alive
//         if (auto locked = wp.lock()) {
//             std::cout << "Weak_ptr sees player alive\n";
//         }

//         // Destroy both shared_ptr owners
//         sp1.reset();
//         sp2.reset();  // Player destroyed here (use_count hits 0)

//         // Now weak_ptr is expired
//         if (wp.expired()) {
//             std::cout << "Weak_ptr: object expired\n";
//         }

//         // unique_ptr goes out of scope automatically here → destroyed

//         return 0;
//     }
// */

// class Player
// {
// public:

//     int health;
//     Player(int h) : health(h)
//     {
//         std::cout << "construted player" << std::endl;
//     }
//     ~Player()
//     {
//         std::cout << "Destructed player" << std::endl;
//     }
// };

// int main()
// {
//     // unique pointer
//     std::unique_ptr<Player> up = std::make_unique<Player>(100);
//     std::cout << "start unique pointer: " << up->health << std::endl;
//     up->health = 80;
//     std::cout << "change unique pointer: " << up->health << std::endl;
    
//     // shared pointer 
//     std::shared_ptr<Player> sp1 = std::make_shared<Player>(100);
//     std::cout << "start sp1 count: " << sp1.use_count() << std::endl;
//     auto sp2 = sp1;
        
//     // weak pointer
//     std::weak_ptr<Player> wp = sp1; // refer to sp1 without owning it
//     if (wp.expired() == false)
//     {
//         std::cout << "weak pointer referring" << std::endl;
//     }
//     else 
//     {
//         std::cout << "weak pointer not referring" << std::endl;
//     }

//     std::cout << "start sp1 count: " << sp1.use_count() << std::endl;
//     sp1.reset(); // kill the owner sp1
    
//     std::cout << "update sp2 count: " << sp2.use_count() << std::endl;
//     sp2.reset(); // kill the owner sp2
    
//     // weak point dies when the object dies not the pointer, so if all owners then
//     // it gets expired in this case after sp2 is reset()
//     if (wp.expired() == false)
//     {
//         std::cout << "weak pointer referring" << std::endl;
//     }
//     else 
//     {
//         std::cout << "weak pointer not referring" << std::endl;
//     }
//     return 0;
// }




// ####
// TOPIC 3 - Object lifetime and RAII
// RAII = Resource Acquisition Is Initialization (object lifetime cruciality)

// /*
//     RAII = An object owns a resource, and when the object dies, the resource is released.
//     ✔️ Why RAII exists: To avoid manual delete and give you automatic cleanup, safely.
     
//     Stack object created in a function dies once hit the end of the body { .. } <-- end 
//     Heap object die when manually deleted 
    
//     e.g.
//     Stack Object: <-- acts like a temporary guest that comes and goes by itself
//     {
//         Player p(100); <-- lives
//     } <-- dies here
    
//     Heap object: <-- acts like living in the house so manual "delete" necessaty
//     {
//         Player* p = new Player(100); <-- create address on  heap and store in pointer
//     } <-- stil alive
//     ...
//     delete p; <-- dies here only with "delete"
    
//     memory leak: if pointer dies incorrectly the address (heap object) stays -> memoery leak
    
// */

// class Logger
// {
// public:
//     Logger() // constructor
//     {
//         std::cout << "Constructing Logger" << std::endl;
//     }
    
//     ~Logger() // destructor (if not added c++ will run it anyways)
//     {
//         // excplicit destructor allows to delete pointers related to the object :)
//         std::cout << "Destructing Logger" << std::endl;
//     }
// };

// int main()
// {
//     Logger a; // stack object; autoamtic construct and destruct
//     Logger* b = new Logger(); // heap object
//     delete b; // manually delete heap object

//     return 0;
// }




// ####
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




// ####
// TOPIC 1 - Value Semantics 
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