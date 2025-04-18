#include <iostream>
#include <string>
#include <vector>
#include <ctime> // Handle time and date in the type of tm
#include <limits> //
#include "basic_task.h"
#include "todo_list.h"

using namespace std;
// Function to display the menu
void displayMenu(){
    cout << endl << "===== To-Do List Menu =====" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. View Tasks" << endl;
    cout << "3. Edit Task" << endl;
    cout << "4. Delete Task" << endl;
    cout << "5. Mark Task as Completed" << endl;
    cout << "6. Undo Last Delete" << endl;
    cout << "7. Exit" << endl;
    cout << "===========================" << endl;
    cout << "Enter your choice: ";
}

// Function to handle the input for due date
tm getDateInput(){
    tm date = {};// Set the date to default values
    char seperator;
    cout << "Enter due date (MM/DD/YYYY): ";
    cin >> date.tm_mon >> seperator >> date.tm_mday >> seperator >> date.tm_year;
    date.tm_mon -= 1; // Adjust month to 0-11 range
    date.tm_year -= 1900; // Adjust year to 1900-based
    mktime(&date); // Normalize the date
    return date;
}

void addTask(ToDoList& todolist){
    string name, category, desciription;
    int TaskType, priority, recurrenceDays;
    cout << endl << "---Add New Task---" << endl;
    cout << "Enter task name: ";\
    cin.ignore();// Ignore the newline character('\n') left in the buffer
    getline(cin, name);// Read the whole line until meet '\n'

    cout << "Enter category: ";
    cin.ignore();
    getline(cin, category);

    cout << endl << "Select task type: " << endl;
    cout << "1. Normal Task" << endl;
    cout << "2. Important Task (max 3 uncompleted)" << endl;
    cout << "3. Recurring Task" << endl;
    cout << "Enter your choice: ";
    cin >> TaskType;

    try{
        Basic_task* task = nullptr;

        if(TaskType == 1){// Normal task
            cout << "Enter description (optional): ";
            cin.ignore();
            getline(cin, desciription);

            cout << "Add due date? (1 for Yes, 0 for No): ";
            int addDueDate;
            cin >> addDueDate;

            if(addDueDate){
                tm dueDate = getDateInput();
                task = new Normal_task(name, category, desciription, dueDate);
            }
            else{
                task = new Normal_task(name, category, desciription);
            }
        }
        else if(TaskType == 2){ // Important task
            cout << "Enter description (optional): ";
            cin.ignore();
            getline(cin, desciription);

            cout << "Enter priority (1-3): ";
            cin >> priority;
            task = new ImportantTask(name, category, desciription, priority);
        }

        else if(TaskType == 3){// Recurring task
            cout << "Enter description (optional): ";
            cin.ignore();
            getline(cin, desciription);

            cout << "Enter recurrence in days: ";
            cin >> recurrenceDays;

            cout << "Enter start date (MM/DD/YYYY): ";
            tm startDate = getDateInput();

            task = new RecurringTask(name, category, desciription, startDate, recurrenceDays);
        }
        else{
            cout << "Invalid task type." << endl;
            return;
        }
        // Add the task to the list
        todolist.addTask(task);
        cout << "Task added successfully!" << endl;
    }
    catch(const runtime_error& e){
        cout << "Error: " << e.what() << endl;
    }
}

void viewTasks(ToDoList& todolist){
    if(todolist.getTaskCount() == 0){
        cout << "No tasks available." << endl;
        return;
    }

    int filterChoice;
    string categoryFilter;
    bool showCompleted, importantOnly;

    cout << endl << "---View Tasks---" << endl;
    cout << "1. View all tasks" << endl;
    cout << "2. Filter by category" << endl;
    cout << "3. View completed tasks" << endl;
    cout << "4. View important tasks only" << endl;
    cout << "Enter your choice: ";
    cin >> filterChoice;

    switch(filterChoice){
        case 1: //View all tasks
            todolist.viewTasks();
            break;
        case 2: //Filter by category
            cout << "Rnter category to filter: ";
            cin.ignore();
            getline(cin, categoryFilter);
            todolist.viewTasks(categoryFilter);
            break;
        case 3: //View completed Tasks
            categoryFilter = "";
            showCompleted = true;
            todolist.viewTasks(categoryFilter, showCompleted);
            break;
        case 4: // view important tasks only
            categoryFilter = "";
            showCompleted = false;
            importantOnly = true;
            todolist.viewTasks(categoryFilter, showCompleted, importantOnly);
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
    }

}

void editTask(ToDoList& todolist){
    if(todolist.getTaskCount() == 0){
        cout << "No tasks available." << endl;
        return;
    }
    todolist.viewTasks();
    int index;
    cout << "Enter task number to edit: ";
    cin >> index;
    if(index < 1 || index > todolist.getTaskCount()){
        cout << "Invalid task number." << endl;
        return;
    }

    string newName, newCategory;
    cout << "Enter new task name: ";
    cin.ignore();
    getline(cin, newName);

    cout << "Enter new category: ";
    cin.ignore();
    getline(cin, newCategory);

    try{
        todolist.editTask(index-1, newName, newCategory);
        cout << "Task edited successfully!" << endl;
    }
    catch(const exception& e){
        cout << "Error: " << e.what() << endl;
    }
}
void deleteTask(ToDoList& todolist){
    if(todolist.getTaskCount() == 0){
        cout << endl << "No tasks available to delete." << endl;
    }
    todolist.viewTasks();
    cout << "Enter task number to delete: ";
    int index;
    cin >> index;

    if(index < 1 || index > todolist.getTaskCount()){
        cout << "Invalid task number." << endl;
        return;
    }
    try{
        todolist.deleteTask(index-1);
        cout << "Task deleted successfully." << endl;
    }
    catch(const exception &e){
        cout << "Error: " << e.what() << endl;
    }
}

void markTaskCompleted(ToDoList& todolist){
    if(todolist.getTaskCount() == 0){
        cout << endl << "No tasks available to mark as completed." << endl;
        return ;
    }
    todolist.viewTasks();
    cout << "Enter task number to mark as completed: ";
    int index;
    cin >> index;

    if(index < 1 || index > todolist.getTaskCount()){
        cout << "Invalid task number." << endl;
    }
    try{
        todolist.markTaskCompleted(index-1);
        cout << "Task marked completed" << endl;
    }
    catch(const exception& e){
        cout << "Error: " << e.what() << endl;
    }
}


int main(){
    ToDoList todolist;
    int choice;

    do{
        displayMenu();
        cin >> choice;

        switch(choice){
            case 1:
                addTask(todolist);
                break;
            case 2:
                viewTasks(todolist);
                break;
            case 3:
                editTask(todolist);
                break;
            case 4:
                deleteTask(todolist);
                break;
            case 5:
                markTaskCompleted(todolist);
                break;
            case 6:
                todolist.undoDelete();
                cout << "Last deleted task restored." << endl;
                break;
            case 7:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 7);
    return 0;
}
