#include <iostream>
using namespace std;

class Example {
private:
    int* data;  // Pointer to dynamically allocated memory

public:
    // **1. Constructor**
    Example(int value) {
        data = new int(value);  // Allocate memory
        cout << "Constructor: Allocated memory for " << value << endl;
    }

    // **2. Copy Constructor (Deep Copy)**
    Example(const Example& source) {
        data = new int(*source.data);  // Allocate new memory and copy value
        cout << "Copy Constructor: Deep copied " << *data << endl;
    }

    // **3. Shallow Copy (Demonstration)**
    Example& shallowCopy(const Example& source) {
        this->data = source.data;  // Just copy the pointer (not the memory)
        cout << "Shallow Copy: Copying pointer, not memory" << endl;
        return *this;
    }

    // **4. Move Constructor**
    Example(Example&& source) noexcept {
        data = source.data;  // Transfer ownership
        source.data = nullptr;  // Nullify source pointer to avoid double deletion
        cout << "Move Constructor: Transferred ownership" << endl;
    }

    // **5. Destructor**
    ~Example() {
        if (data) {  
            cout << "Destructor: Deleting memory for " << *data << endl;
            delete data;
        } else {
            cout << "Destructor: No memory to delete" << endl;
        }
    }

    // **Function to display value**
    void show() const {
        if (data)
            cout << "Value: " << *data << endl;
        else
            cout << "Value: null (moved)" << endl;
    }
};

int main() {
    Example obj1(10);  // Constructor
    obj1.show();

    Example obj2 = obj1;  // Copy Constructor (Deep Copy)
    obj2.show();

    Example obj3(0);
    obj3.shallowCopy(obj1);  // Shallow Copy (Warning: shares memory)
    obj3.show();

    Example obj4 = move(obj1);  // Move Constructor
    obj4.show();
    obj1.show();  // Moved-from object

    return 0;
}
