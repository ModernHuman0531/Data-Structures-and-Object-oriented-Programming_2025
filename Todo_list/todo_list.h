/*todo_list.h helps us to store, operate, and control status for every task*/
#ifndef TODO_LIST_H
#define TODO_LIST_H

// All the header files we need
#include "basic_task.h"
#include <iostream>
#include <vector> // Container to store the tasks
#include <algorithm> // For sorting the tasks
#include <memory> // For smart pointers
#include <string> // For string manipulation

using namespace std;

class ToDoList{
    private:
        vector<Basic_task*> tasks; // Vector to store the tasks
        vector<Basic_task*> completedTasks; // Vector to store the completed tasks
        vector<Basic_task*> deletedTasks; // Vector to store the deleted tasks, to implement the undo function
    public:
        // Destructor
        ~ToDoList(){cleanTasks();}
        void cleanTasks(){
            for(auto task : tasks){
                delete task; // Free the memory allocated for the tasks
            }
            for(auto task : completedTasks){
                delete task; // Free the memory allocated for the completed tasks
            }
            for(auto task : deletedTasks){
                delete task; // Free the memory allocated for the deleted tasks
            }
            // Empty the verctors
            tasks.clear();
            completedTasks.clear();
            deletedTasks.clear();
        }

        // Function to add a task to the list
        /* Process of implementing this function
        1. Check if the task is important or not
        2. If the task is important, check if the number of important tasks is less than 3
        3. If the task is important and the number of important tasks is less than 3, add the task to the list
        4. If the task is not important, add the task to the list
        5. If the task is important and the number of important tasks is greater than 3, throw an exception
        */
        void addTask(Basic_task* task){
            if(task->isImportance()){
                // Check if the number of important tasks is less than 3
                /* Introduce the usage of count_if function in detail
                1. count_if is a function in the algorithm library that counts the number 
                    of elements in a range that satisfy a given condition
                2. count_if(begin, end, condition) where begin and end are the iterators that define the range
                3. In this case, we are using a lambda function as the condition
                4. The format of lambda funciton is [capture](parameters) -> return_type { function body }
                5. This lambda function checks if the task is important and not completed
                    a. [capture] means we can capture the variables from the outer scope 
                    b. (variables) means we need to pass in when we call the function
                */
                int importantTaskCount = count_if(tasks.begin(), tasks.end(), [](Basic_task* t) {
                    return t->isImportance() && !t->is_completed();
                }
                );
                if(importantTaskCount >= 3){
                    throw runtime_error("You can only have 3 important tasks at a time.");
                }
            }
            tasks.push_back(task);
        }
        // Function to check every task in the list
        /*
        1. We can determine what kind of task we want to display.ADJ_FREQUENCY
        2. We can display 
            a. Base on the category
            b. Base on completed or not
            c. Only show the important tasks
        3. Based on the above conditions, we can display the tasks, and the input parameters are the condition
        4. The input parameter means
            a. categoryFilter: the category we want to display, if it is empty, we display all the tasks
            b. showCompleted: If we show the completed tasks or not
            c.importantOnly: If only show the important tasks or not
        */
        void viewTasks(const string& categoryFilter = "", bool showCompleted =false, bool importantOnly = false) const{
            cout << endl << "---- Task List ----" << endl;
            int count = 0; // Count for the matching tasks
            for(auto task : tasks){
                // The filter condition for the tasks
                bool categoryMatch = categoryFilter.empty()||task->get_category() == categoryFilter; //If the category is empty or the task category is the same as the filter category
                bool completedMatch = showCompleted || !task->is_completed(); //Show already completed or tasks isn't completed
                bool importantMatch = !importantOnly || task->isImportance(); //Show donb't select important task or is important task
                if(categoryMatch && completedMatch && importantMatch){
                    cout << count+1 << ". ";
                    task->display();
                    count++; // Increase the count for the matching tasks
                }
                
            }
            if(count == 0){// No matching tasks
                cout << "No tasks found matching the criteria." << endl;
            }
        }
};
#endif TODO_LIST_H