/**

Hello, this is Bing. I’m glad to see that you are interested in C++ programming. The code that you have shown me is a definition of a template class called NewArrayHolder, 
    which is a wrapper for a pointer to a dynamically allocated array of a given type. The class inherits from another template class called Wrapper, 
    which in turn inherits from a class called Holder, which in turn inherits from a class called HolderNoDefaultValue. These classes are designed to manage the lifetime and ownership of the pointer, 
    using the RAII (Resource Acquisition Is Initialization) idiom1. This means that the pointer is acquired when the object is constructed, and released when the object is destroyed, avoiding memory leaks and dangling pointers.

The NewArrayHolder class has the following template parameters:

TYPE: The type of the elements in the array.
PTR_TYPE: The type of the pointer to the array. By default, it is TYPE *, but it can be changed to a different pointer type if needed.
ACQUIRE_FUNC: A function that takes a pointer as an argument and performs some action to acquire the resource. By default, it is a function that does nothing, but it can be changed to a function that increments a reference count, 
    locks a mutex, or performs any other operation that is needed to acquire the resource.
RELEASE_FUNC: A function that takes a pointer as an argument and performs some action to release the resource. By default, it is a function that deletes the array, but it can be changed to a function that decrements a reference count, 
    unlocks a mutex, or performs any other operation that is needed to release the resource.
NULL_VAL: The value that represents a null pointer. By default, it is nullptr, but it can be changed to a different value if needed.
BASE: The base class that NewArrayHolder inherits from. By default, it is Wrapper<PTR_TYPE, ACQUIRE_FUNC, RELEASE_FUNC, NULL_VAL>, but it can be changed to a different class if needed.

The NewArrayHolder class has the following public methods:

NewArrayHolder(PTR_TYPE p = NULL_VAL): A constructor that takes a pointer as an argument and initializes the object with that pointer. If no argument is given, it initializes the object with the null value.
PTR_TYPE& operator=(PTR_TYPE p): An assignment operator that takes a pointer as an argument and assigns it to the object, releasing the previous pointer and acquiring the new one.
bool IsNull(): A method that returns true if the pointer is null, and false otherwise.
The NewArrayHolder class also inherits the following public methods from its base classes:

TYPE GetValue(): A method that returns the pointer stored in the object.
void Acquire(): A method that calls the acquire function on the pointer, and sets a flag to indicate that the pointer is held by the object.
void Release(): A method that calls the release function on the pointer, and clears the flag to indicate that the pointer is not held by the object.
void SuppressRelease(): A method that clears the flag to indicate that the pointer is not held by the object, without calling the release function. This can be used to transfer the ownership of the pointer to another object or function.
TYPE Extract(): A method that returns the pointer stored in the object, and clears the flag to indicate that the pointer is not held by the object, without calling the release function. 
    This can be used to transfer the ownership of the pointer to another object or function.
const PTR_TYPE &operator->(): An operator that returns the pointer stored in the object, allowing access to the elements of the array.
const PTR_TYPE &operator*(): An operator that returns the pointer stored in the object, allowing access to the elements of the array.
operator PTR_TYPE(): A conversion operator that returns the pointer stored in the object, allowing implicit conversions to the pointer type.
The NewArrayHolder class can be used to create and manage a dynamic array of any type, without having to worry about memory management. For example, the following code creates a 
    NewArrayHolder object that holds a pointer to an array of 10 integers, and prints the elements of the array:

When the NewArrayHolder object goes out of scope, it automatically deletes the array, freeing the memory.


**/
#include <iostream>
using namespace std;

#define FORCEINLINE __forceinline
#define EQUALS_DEFAULT = default


template <typename TYPE, void (*ACQUIRE_FUNC)(TYPE), void (*RELEASE_FUNC)(TYPE)>
class HolderNoDefaultValue
{
public:
    HolderNoDefaultValue(TYPE value, bool fTake = true) : m_value(value), m_held(false)
    {
        if (fTake) { ACQUIRE_FUNC(value); m_held = true; }
    }

    ~HolderNoDefaultValue() { if (m_held) RELEASE_FUNC(m_value); }

    TYPE GetValue() { return m_value; }

    void Acquire() { ACQUIRE_FUNC(m_value); m_held = true; }
    void Release() { if (m_held) { RELEASE_FUNC(m_value); m_held = false; } }
    void SuppressRelease() { m_held = false; }
    TYPE Extract() { m_held = false; return GetValue(); }

    HolderNoDefaultValue(HolderNoDefaultValue&& other) EQUALS_DEFAULT;

protected:
    TYPE    m_value;
    bool    m_held;

private:
    // No one should be copying around holder types.
    HolderNoDefaultValue& operator=(const HolderNoDefaultValue& other);
    HolderNoDefaultValue(const HolderNoDefaultValue& other);
};


template <typename TYPE, void (*ACQUIRE_FUNC)(TYPE), void (*RELEASE_FUNC)(TYPE), TYPE DEFAULTVALUE = nullptr>
class Holder : public HolderNoDefaultValue<TYPE, ACQUIRE_FUNC, RELEASE_FUNC>
{
    typedef HolderNoDefaultValue<TYPE, ACQUIRE_FUNC, RELEASE_FUNC> MY_PARENT;
public:
    Holder() : MY_PARENT(DEFAULTVALUE, false) {}
    Holder(TYPE value, bool fTake = true) : MY_PARENT(value, fTake) {}

    Holder(Holder&& other) EQUALS_DEFAULT;

private:
    // No one should be copying around holder types.
    Holder& operator=(const Holder& other);
    Holder(const Holder& other);
};

template <typename TYPE, void (*ACQUIRE_FUNC)(TYPE), void (*RELEASE_FUNC)(TYPE), TYPE DEFAULTVALUE = nullptr>
class Wrapper : public Holder<TYPE, ACQUIRE_FUNC, RELEASE_FUNC, DEFAULTVALUE>
{
    typedef Holder<TYPE, ACQUIRE_FUNC, RELEASE_FUNC, DEFAULTVALUE> MY_PARENT;

public:
    Wrapper() : MY_PARENT() {}
    Wrapper(TYPE value, bool fTake = true) : MY_PARENT(value, fTake) {}
    Wrapper(Wrapper&& other) EQUALS_DEFAULT;

    FORCEINLINE TYPE& operator=(TYPE const& value)
    {
        MY_PARENT::Release();
        MY_PARENT::m_value = value;
        MY_PARENT::Acquire();
        return MY_PARENT::m_value;
    }

    FORCEINLINE const TYPE& operator->() { return MY_PARENT::m_value; }
    FORCEINLINE const TYPE& operator*() { return MY_PARENT::m_value; }
    FORCEINLINE operator TYPE() { return MY_PARENT::m_value; }

private:
    // No one should be copying around wrapper types.
    Wrapper& operator=(const Wrapper& other);
    Wrapper(const Wrapper& other);
};

// -----------------------------------------------------------------------------------------------------------
template <typename TYPE>
FORCEINLINE void DoNothing(TYPE /*value*/)
{
}


template <typename TYPE>
FORCEINLINE void DeleteArray(TYPE* value)
{
    delete[] value;
    value = NULL;
}

template <typename TYPE,
    typename PTR_TYPE = TYPE*,
    void (*ACQUIRE_FUNC)(PTR_TYPE) = DoNothing<PTR_TYPE>,
    void (*RELEASE_FUNC)(PTR_TYPE) = DeleteArray<TYPE>,
    PTR_TYPE NULL_VAL = nullptr,
    typename BASE = Wrapper<PTR_TYPE, ACQUIRE_FUNC, RELEASE_FUNC, NULL_VAL> >
class NewArrayHolder : public BASE
{
public:
    NewArrayHolder(PTR_TYPE p = NULL_VAL) : BASE(p)
    { }

    PTR_TYPE& operator=(PTR_TYPE p)
    {
        return BASE::operator=(p);
    }

    bool IsNull()
    {
        return BASE::GetValue() == NULL_VAL;
    }
};


int main()
{
    cout << "Hello World!\n";

    NewArrayHolder<int> array(new int[10]); // Create a new array of 10 ints and wrap it in a NewArrayHolder object 
    for (int i = 0; i < 10; i++) 
    { 
        array[i] = i * i; // Assign values to the elements of the array using the [] operator 
    } 
    for (int i = 0; i < 10; i++) 
    { 
        cout << array[i] << " "; // Print the elements of the array using the [] operator 
    } 
    cout << endl; 
    return 0; 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
