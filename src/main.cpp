#include <iostream>
#include <vector>
#include <unordered_map>
#include "../include/calculator.h"
#include "../include/LogBuffer.h"
#include "../include/Player.h"
#include <algorithm>

// TOPIC 9 - STL Algorithms + Lambdas
/*
    being() means first element in list (inclusive)
	end() means one past last element in list (marks the stopping point) (exclusive) used for not found

    Algorithms: express intent; 
    Lambdas: provide the condition.
    Together, they replace most manual loops.

    syntax:     [](params) { body }
	example:    [](int x) { return x > 0; }

    [] = capture nothing
    [&] = capture all by reference
	[=] = capture all by value
    [x] = capture x by value
	[x, &y] = capture x by value, y by reference
    e.g.:
    int threshold = 50;
    auto lowHp = [&](const Player& p) { return p.hp < threshold; };

	std::find: used == to find an element in a container
    e.g.:
	auto it = std::find(v.begin(), v.end(), 42);

	std::find_if: used with a condition (lambda)
    e.g.:
    auto it = std::find_if(players.begin(), players.end(),
    [](const Player& p) { return p.hp < 50; });

    std::count_if:
    int lowCount = std::count_if(players.begin(), players.end(),
    [](const Player& p) { return p.hp < 50; });

    std::any_of, std::all_of: Checks existence / universality.
    e.g.:
    bool anyDead = std::any_of(players.begin(), players.end(),
        [](const Player& p) { return p.hp <= 0; });
    bool allAlive = std::all_of(players.begin(), players.end(),
        [](const Player& p) { return p.hp > 0; });

    std::sort: Sorts a container.
    std::sort(players.begin(), players.end(),
    [](const Player& a, const Player& b) {
        return a.hp > b.hp; // descending
    });

    std::remove_if:
    e.g.:
    players.erase(
        std::remove_if(players.begin(), players.end(),
            [](const Player& p) { return p.hp <= 0; }),
        players.end()
    );
    Important: remove_if doesn’t erase; erase does.

    Algorithm	Returns
    find_if	    iterator
    count_if	number
    any_of	    bool
    all_of	    bool
    sort	    void
    remove_if	iterator
*/
int main()
{
    std::vector<Player> players = {
        {1, "Alice", 100},
        {2, "Bob", 40},
        {3, "Eve", 0},
        {4, "Mallory", 70}
    };

    // 1) find_if
    auto it = std::find_if(players.begin(), players.end(),
        [](const Player& p) { return p.hp < 50; });

    if (it != players.end())
        std::cout << "Found low HP player: " << it->name << "\n";
    else
        std::cout << "No low HP player\n";

    // 2) count_if
    auto lowCount = std::count_if(players.begin(), players.end(),
        [](const Player& p) { return p.hp < 50; });

    std::cout << "Low HP count: " << lowCount << "\n";

    // 3) any_of
    bool anyDead = std::any_of(players.begin(), players.end(),
        [](const Player& p) { return p.hp <= 0; });

    if (anyDead)
        std::cout << "At least one player is dead\n";

    // 4) all_of
    bool allAlive = std::all_of(players.begin(), players.end(),
        [](const Player& p) { return p.hp > 0; });

    if (allAlive)
        std::cout << "All players are alive\n";

    // 5) sort (descending HP)
    std::sort(players.begin(), players.end(),
        [](const Player& a, const Player& b) {
            return a.hp > b.hp;
        });

    std::cout << "\nSorted players:\n";
    for (const auto& p : players)
        std::cout << p.name << " (" << p.hp << ")\n";

    // 6) erase-remove
    players.erase(
        std::remove_if(players.begin(), players.end(),
            [](const Player& p) { return p.hp <= 0; }),
        players.end()
    );

    std::cout << "\nAfter removing dead players:\n";
    for (const auto& p : players)
        std::cout << p.name << " (" << p.hp << ")\n";

    return 0;
}



// TOPIC 8 - STL Containers
/*
	they are like containers like .NET collections or Java collections
        Default → std::vector
        Need fast lookup by key → std::unordered_map
        Need ordering → std::map
        FIFO/LIFO → std::queue / std::stack
        Set semantics → std::unordered_set

	std::vector<T> (List<T> in C#): fast  iteration, simple ownership and easy to move
        std::vector<int> v = {1,2,3};
        v.push_back(4);
        v[0];        // fast

    Because std::vector has contiguous memory, much better cache locality, faster iteration, and is almost always faster in real-world code.

    std::list<T>

	std::unordered_map<K,V> (like Dictionary in .NET): use this over std::map unless ordering needed
        std::unordered_map<int, std::string> m;
        m[1] = "Player";

    std::map<K, V>:
        std::map<int, std::string> m;

	std::unordered_set<T> / std::set<T> (liek HashSet in .NET): use unordered_set over set unless ordering needed
        std::unordered_set<int> s;
        s.insert(10);

    std::array<T, N>: fixed-size array
		std::array<int, 3> a = {1,2,3};

	std::deque<T>: double-ended queue: like linked list but with random access
        std::deque<int> d;
        d.push_back(1);
		d.push_front(0);

    Adapters: stack, queue, priority_queue:
    std::stack<int> s;
    s.push(1);
    s.pop();

	Ownership and Lifietime:
    std::vector<Player> players;            // owns Players
    std::vector<std::unique_ptr<Player>> p; // owns pointers

    By value when objects are small / movable
    unique_ptr for polymorphism or large objects

    Performance rules (memorise these)
        Prefer vector
        Prefer unordered_* over ordered versions
        Avoid new inside containers
        Use emplace_back when constructing in place

    v.emplace_back(10); // constructs in-place

    e.g.:
    std::unordered_map<int, Player> players;
    players.emplace(1, Player{100});

*/
//int main()
//{
//	std::vector<Player> players;
//	std::unordered_map<int, size_t> indexById;
//
//    // add players
//    players.emplace_back(Player(1, "Altair", 100));
//	players.emplace_back(Player(2, "Ezio", 80));
//	players.emplace_back(Player(3, "Edward", 40));
//
//    // fill map
//    for (size_t i = 0; i < players.size(); ++i)
//    {
//		indexById[players[i].id] = i;
//    }
//
//	// lookup player by id
//	// it is an iterator pointer hence we use ->
//	int searchId = 2;
//	auto it = indexById.find(searchId); // auto = figure out type for me
//    if (it != indexById.end())
//    {
//		rsize_t index = it->second; // second because pair<key, value> key = first, value = second
//        players[index].hp -= 20; // modify hp
//    }
//
//	// print players
//    for (const auto& p : players)
//    {
//        std::cout
//            << "Player ID: " << p.id
//            << ", Name: " << p.name
//			<< ", HP: " << p.hp 
//            << std::endl;
//    }
//
//    return 0;
//}



// TOPIC 7 - Copy vs Move Semantics
/*
	Copy: creates a new object that owns its own data: T b = a;   // copy can be expensive
	Move: transfers ownership of data from one object to another: T b = std::move(a); // move is cheap
    e.g.:
    #include <iostream>
    #include <vector>

    class Box {
    public:
        std::vector<int> data;

        Box() { std::cout << "Default\n"; }

        Box(const Box& other) : data(other.data) {
            std::cout << "Copy\n";
        }

        Box(Box&& other) noexcept : data(std::move(other.data)) {
            std::cout << "Move\n";
        }
    };

        int main() {
        Box a;
        a.data = {1,2,3};

        Box b = a;              // COPY
        Box c = std::move(a);   // MOVE
    }

    Output:
    Default
    Copy
    Move

    b = a → deep copy of vector
    c = std::move(a) → vector ownership transferred
    a.data becomes empty (but valid)

    If your type owns RAII members → moves are automatic

    Copy = duplicate data
    Move = steal data
	std::move = “you may steal from this” // the object doesn't get destroyed, but its resources are moved

    Returning an object does not mean “move” — it usually means “construct it directly where it’s needed.”
*/

//LogBuffer CreateBuffer()
//{
//    LogBuffer b;
//    b.data = { 1, 2, 3, 4 };
//    return b;
//}
//
//int main()
//{
//    std::cout << "---- A ----\n";
//	LogBuffer a; // default constructor
//
//	std::cout << "---- B ----\n";
//    LogBuffer b = std::move(a); // move constructor (steal from a)
//
//	std::cout << "---- C ----\n";
//	LogBuffer c = CreateBuffer(); // RVO: no copy, no move, RVO = return value optimization
//
//    return 0;
//}




// TOPIC 6 - Contstructors, Destructors, Rule of 0/3/5
/*
    Constructors: allocate resouces
	Destructors: release resouces (stack objects auto, heap manual delete)

    5 special member fucntions:
	C++ auto generates them:
    1. Destructor
    2. Copy constructor
	3. Copy assignment operator
	4. Move constructor
	5. Move assignment operator
	they control how objects are copied, moved, and destroyed.

	RULE of 0 (do nothing if class owns nothing):
	- if class doesn't manage resources, rely on compiler-generated functions:
    class Vec2 {
    public:
        float x, y;
    };

	RULE of 3 (if class owns resources, define 3 things):
	- if class manages resources (e.g., dynamic memory) with new:
    class Player {
    private:
        int* data;
    };
    then you must define:   1. Destructor: release resources, 
                            2. Copy constructor: deep copy resources, 
						    3. Copy assignment operator: deep copy resources.
    e.g.:
    Player(const Player& other) { deep copy }
    Player& operator=(const Player& other) { deep copy }
    ~Player() { delete data; }

	RULE of 5 (if class defines rule of 3, also define move versions):
    - If you manually manage memory, moving becomes important to avoid unnecessary copies.
		so define Move constructor and Move assignment operator.
        e.g.:
        Player(Player&& other) noexcept { steal pointer }
        Player& operator=(Player&& other) noexcept { steal pointer }

    EXAMPLES:
    Rule 0:
    class Person {
    public:
        std::string name; // std::string handles its own memory
        int age;
    };

	Rule 3:
    class Buffer {
    private:
        int* data;
        int size;

    public:
        Buffer(int s)
            : size(s), data(new int[s]) {}

        ~Buffer() {
            delete[] data;
        }

        Buffer(const Buffer& other)
            : size(other.size), data(new int[other.size]) {
            std::copy(other.data, other.data + size, data);
        }

        Buffer& operator=(const Buffer& other) {
            if (this != &other) {
                delete[] data;
                size = other.size;
                data = new int[size];
                std::copy(other.data, other.data + size, data);
            }
            return *this;
        }
    };

    Rule 5:
    Buffer(Buffer&& other) noexcept
    : size(other.size), data(other.data) {
    other.data = nullptr;
    other.size = 0;
    }

    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }


    C++20: Prefer Rule of 0. Avoid Rule of 3 and Rule of 5 unless you REALLY need raw pointers.
    Because modern C++ uses:
    - std::unique_ptr
    - std::shared_ptr
    - std::vector
    - std::string
    These automatically give you Rule of 5 behavior for free.

	Rule 0: rely on compiler-generated functions.
	Rule 3: define destructor, copy constructor, copy assignment operator. (when using new, delete, malloc, free)
	Rule 5: wtih rule 3 also define move constructor and move assignment operator. (when using new, delete, malloc, free)

    | Rule      | Meaning                                                 |
    | --------- | ------------------------------------------------------- |
    | Rule of 0 | “I don’t manage memory, C++ handles everything”         |
    | Rule of 3 | “I manage memory, so I must control copy & destruction” |
    | Rule of 5 | “I manage memory AND want fast moves”                   |

	you should stick with rule of 0 as much as possible.
	e.g. using std::unique_ptr instead of raw pointers.

    Raw pointer ownership → you must write Rule of 3/5
    RAII types (unique_ptr, vector, string) → Rule of 0
    Rule of 0 = “Let well-written standard types handle ownership”
*/




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

//int main()
//{
//    // Calculator calculator; // to create an object
//    std::unique_ptr<Calculator> calculator = std::make_unique<Calculator>(); // or use a pointer
//    std::cout << "Add: " << calculator->Add(3, 3) << std::endl;
//    std::cout << "Sub: " << calculator->Sub(9, 2) << std::endl;
//    std::cout << "Mul: " << calculator->Mul(6, 6) << std::endl;
//    std::cout << "Div Wrong: " << calculator->Div(9, 0) << std::endl;
//    std::cout << "Div Right: " << calculator->Div(9.0, 3.0) << std::endl;
//    return 0;
//}




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
    
//     Heap object: <-- acts like living in the house so manual "delete" necessay
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