#ifndef BASIC_TASK_H
#define BASIC_TASK_H

#include <iostream>
#include <string>
#include <ctime> //Handle time and date in the type of tm
#include <stdexcept>// Handle exceptions

using namespace std;

class Basic_task{
    protected:
        string *name;
        string *category;
        bool *completed;
    
    public:
        // Constructor, all the member are pointers, so we need to allocate memory for them
        Basic_task(const string& name, const string& category):name(new string(name)), category(new string(category)), completed(new bool(false)){}

        // Destructor, we need to free the memory allocated for the pointers
        virtual ~Basic_task(){
            delete name;
            delete category;
            delete completed;
        }

        // Getters
        string get_name() const{return *name;}
        string get_category() const{return *category;}
        bool is_completed() const{return *completed;}

        // Setters
        void set_name(const string& New_name) {*name = New_name;}
        void set_category(const string& New_category) {*category = New_category;}
        void set_completed(bool status) {*completed = status;}

        // Virtual function to be implemented in the derived classes
        // Use = 0 to represent Pure virtual function, for abstract class, forced to implement in derived classes
        virtual void display() const = 0;
        virtual bool isImportance() const {return false;} //To indicate if the task is important task or not
        virtual bool isRecurring() const {return false;} //To indicate if the task is recurring task or not
        virtual void markNectOccurance() {} //To mark the next occurrence of the task

};
/*Implemented the normal class, just normal task the priority isn't first. The following is the important point of implementation:
1. tm is a structure taht contains sec, min, hour, day, month, year etc., we use this in set date 
2. We additionally add two private members, one sis the description of the task another is due day
3. Output type of normal_task |name|category|description|due date|is completed
*/
class Normal_task : public Basic_task{

    private:
        string *description;
        tm *dueDate;
    
    public:
        // Constructor, we need to allocate memory for the pointers, due_date = tm() means to create a struct tm with default values
        Normal_task(const string& name, const string& category, const string& description = "", const tm& dueDate = tm()):Basic_task(name, category), description(new string(description)), dueDate(new tm(dueDate)) {}
        // Destructor, we need to free the memory allocated for the pointers
        ~Normal_task(){
            delete description;
            delete dueDate;
        }
        // Getters
        string get_descripition() const{return *description;}
        tm get_due_time() const {return *dueDate;}

        // Setters
        void set_decription(const string& New_description) {*description = New_description;}
        void set_due_time(const tm& New_due_time) {*dueDate = New_due_time;}

        // Display function for Normal_task
        void display() const override{
            cout << "[Normal] " << get_name() << "| Category: " << get_category();
            if(!get_descripition().empty()){// If the description is not empty, display it
                cout << "| Description: " << get_descripition();
            }
            // dueDate-> tm_year>0 is to check if the date is set, tm_year = 0 means the date is not set(the default value), tm_year = 0 means 1900
            if(dueDate->tm_year > 0){// If the dueDate is correctly set, disp[lay it ]
                /*
                Range of tm_mon is 0-11, so we need to add 1 to it to display the correct month
                tm_mda is the day of the month, so we can display it directly
                tm_year is the year since 1900, so we need to add 1900 to it to display the correct year
                */
                cout << "| Due: " << (dueDate->tm_mon+1) << "/" << dueDate->tm_mday << "/" << (dueDate->tm_year + 1900);
            }
            cout << "| Completed: " << (is_completed() ? "Completed" : "Pending") << endl;
        }

};




#endif // BASIC_TASK_H