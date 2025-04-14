#include <iostream>
#include <string>

using namespace std;

// Class syntax in C++ 
class complex{
    public:
        complex(double r, double i):rm{r}, im{i}{}
        ~complex(); // Destructor
        // Overloading operator +
        const complex operator+(const complex& rhs)const;
        double real() const {return rm} // Constant at the front, means the return value is constant, const plase at the back means we don't want to change the data inside.
        double image() const {}
        void set_rm(double value);

    private:
        double rm, im;

}
/* Operator overloading Syntax
1. operator[operator]
2. Not necessarily be the member function.
3. "this" pointer help the program know, we want to find now's object's data member instead of global parameter or else. 
*/
// Member function version
const complex complex::operator+(const complex& rhs)const{ // complex::operator is declaring the operator+ is the member function
    complex reault = rhs; // Use copy constructor
    result.rm = result.rm + rm;
    result.im = result.im + im;
    return result;

}
// Not member function version
const complex operator+(const complex& lhs, const complex &rhs){ // Can;t not access the private member, write public function to get the data
    return complex{lhs.real() + rhs.real(), lhs.image()+rhs.image()}
}

void complex::set_rm(double value){
    this->rm = value;
}


// Template, class template
template <class T>
class CSample{
    public:
        T max() const{

        }
}

//  Dynamic memory allocation
// 1. Have to have a pointer, and use new to allocate a new memory
// 2. Use destructor to clean up the redundant memory, use delete to do this job.