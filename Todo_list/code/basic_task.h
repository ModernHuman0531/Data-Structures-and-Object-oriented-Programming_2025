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
3. Output type of normal_task [Normal]name|category|description|due date|is completed
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

/* Important task have the following properties
1. Important task have the highest priority, we must finish the important tasks before other tasks
2. Important task only allows have 3 in the same time.
3. The addition properties are priority and description
4. Since important tasks are the task we must finish first, we don't need to set the due date
5. The output format is [Important(priority)]name|category|description|is completed
*/
class ImportantTask : public Basic_task{
    private:
        string *description;
        int *priority;
    
    public:
        // Constructor, we need to allocate memory for the pointers
        ImportantTask(const string& name, const string& category, const string& description = "", int priority = 1):Basic_task(name, category), description(new string(description)), priority(new int(priority)) {}
        // Destructor, we need to free the memory allocated for the pointers
        ~ImportantTask(){
            delete description;
            delete priority;
        }
        // Getters
        string get_description() const{return *description;}
        int get_priority() const{return *priority;}

        // Setters
        void set_description(const string& New_description) {*description = New_description;}
        void set_priority(int New_priority) {
            if(New_priority >= 1 && New_priority <= 3){// Check if the priority is between 1 and 3
                *priority = New_priority;
            }
        }

        bool isImportance() const override {return true;}// To indicate if the task is important task or not
        // Display function for ImportantTask
        void display() const override{
            cout << "[Important(" << get_priority() << ")]" << get_name() << "| Category: " << get_category();
            if(!get_description().empty()){// If the description is not empty, display it
                cout << "| Description: " << get_description();
            }
            cout << "| Completed: " << (is_completed() ? "Completed" : "Pending") << endl;
        }
};

/*Following are the properties of the recurring task
1. Recurring task is a task that happen in same time interval, like every day,
 every week, every month, we can define the interval by the user
2. Recurring rask is inherited from the normal task, but have additiona; properoties 
 like the interval ofthe next task, and the date of the next task
3. The output format is [Recurring (every ...)]name|category|description|due date|is completed|next occurrence
4. In recurring task, we don't need to set the due date, because the due date is the next occurrence
*/
class RecurringTask : public Normal_task{
    private:
        int* recurrenceDays; // Number of days between each occurrence
        tm* nextOccurance; // Date of the next occurrence
    public:
        // Constructor, we need to allocate the memory for the pointers
        RecurringTask(const string& name, const string& category, const tm& startDate, const string& description = "",  int recurrenceDays = 1) :Normal_task(name, category, description, startDate), recurrenceDays(new int(recurrenceDays)), nextOccurance(new tm(startDate)) {}
        // Destructor, we need to free the memory allocated for the pointers
        ~RecurringTask(){
            delete recurrenceDays;
            delete nextOccurance;
        }

        // Getters
        int getRecurranceDays() const{return *recurrenceDays;}
        tm getNextOcurance() const{return *nextOccurance;}

        // Set the reccurance to true
        bool isRecurring() const override{return true;}

        // Indicate the next occurrence of the task
        void markNectOccurance() override{
            // Add todays date with the recurrence days, because we initial the next occurrence with the start date
            nextOccurance -> tm_mday += *recurrenceDays;
            // Use tm's built in function to check if the date is valid, mktime() helps us automatically adjust the date, for example: 1/32 -> 2/1
            // time_t mktime(tm* timeptr);The input us a tm pointer
            mktime(nextOccurance);// So we don't need to dereference nextOccurance
            // Have to reset the completed to false, because if we finish the task before the next occurrence, the completed is true and the next occurrence is also inherited to be true
            set_completed(false);
        }
        void display(){
            cout << "[Recurring (every " << getRecurranceDays() << "days)]";
            Normal_task::display();
            cout << "| Next Occurance: " << (nextOccurance->tm_mon+1) << "/" << (nextOccurance->tm_mday) <<"/" << (nextOccurance->tm_year+1900) << endl;
        }
};

#endif