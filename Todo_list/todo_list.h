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
        // Function to mark a task as completed
        /*Procedure to implement this function
        1. Check if the input index is valid, if not, throw an exception
        2. If the input index is valid, change the  status of the task tocompleted and put it into the completed task list
        3. For the recurring 
            a. Keep the task in the list
            b. Automatically calculate the next happening date
            c. Reset the status of the task to not completed
        <tip> b and c we can do this by using the function in the recurring task class called markNextOccurance
        */
       void markTaskCompleted(int index){
            if(index < 0 || index >= tasks.size()){
                throw runtime_error("Invalid task index.");// After throw, it will stop executing this function
            }
            tasks[index]->set_completed(true); // Set the task as completed
            completedTasks.push_back(tasks[index]); // Add the task to the completed tasks list

            if(tasks[index]->isRecurring()){ //If the tasks we have completed is recurring task
                tasks[index]->markNectOccurance(); // Mark the next occurrence of the task
            }
            else{
                tasks.erase(tasks.begin()+index); // Remove the task from the list
            }

       }
       // Function to delee a task from the list
        /*Procedure to implement this function
        1. Check if the input index is valid, if not, throw an exception
        2. If the input index is valid, delete the task from the list and put it into the deleted task list
        */
       void deleteTask(int index){
        if(index < 0 || index >= tasks.size()){// If the index is invalid
            throw runtime_error("Invalid task index.");// Throw runtime_error
        }
        // Push the tak into deletedTasks
        deletedTasks.push_back(tasks[index]); // Add the task to the deleted tasks list
        // Remove the task from tasks
        tasks.erase(tasks.begin()+index); // Remove the task from the list
       }

       // Function to undo the last delete operation
       /* Procedure to implement this function
       1. If the deletedTasks isn't emptym pop out the last task from the deletedTasks..
       2. Put the pop_out task into the tasks list.
       */
      void undoDelete(){
        if(!deletedTasks.empty()){
            tasks.push_back(deletedTasks.back()); // Add the last deleted task back to the tasks list
            deletedTasks.pop_back(); // Remove the last deleted task from the deleted tasks list
        }
      }

      // Function to achieve the task in vector
      /*Reason why we don't just use tasks[index] are following
      1. More safety, we can check if the index is valid or not at the beginning
      2. Easier to manipualte multiple tasks, we can use the same function to achieve multiple tasks
      */ 
     Basic_task* getTask(int index) const{
        if(index < 0 || index >= tasks.size()){
            throw runtime_error("Invalid task index.");// If the index is invalid, throw runtime_error
        }
        else{
            return tasks[index]; // Return the task at the given index
        }
     }
    // Function to indicate the number of tasks in the list
    // The reason we use size_t as return type is
    // 1. size_t is an unsigned integer type, which means it can only store positive values
    // 2. The return type of vector.size() is size_t, so we can use size_t as the return type
    size_t getTaskCount() const{
        return tasks.size(); // Return the number of tasks in the list
    }
};
#endif TODO_LIST_H