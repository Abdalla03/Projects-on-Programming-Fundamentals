#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
using namespace std;

struct Task
{
    string description;
    bool completed;
};

vector<Task> tasks;

int GetIntegerInput()
{
    int number;

    while (!(cin >> number))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a number: ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return number;
}

void LoadTasks()
{
    ifstream file("tasks.txt");

    if (!file.is_open())
        return;

    Task task;
    string status;

    while (getline(file, task.description))
    {
        if (!getline(file, status))
            break;

        task.completed = (status == "1");
        tasks.push_back(task);
    }

    file.close();
}

void SaveTasks()
{
    ofstream file("tasks.txt");

    for (const Task& task : tasks)
    {
        file << task.description << '\n';
        file << (task.completed ? 1 : 0) << '\n';
    }

    file.close();
}

void AddTask()
{
    Task task;

    cout << "Enter task description: ";
    getline(cin, task.description);

    if (task.description.empty())
    {
        cout << "Task description cannot be empty.\n";
        return;
    }

    task.completed = false;
    tasks.push_back(task);

    SaveTasks();

    cout << "Task added successfully.\n";
}

void ViewTasks()
{
    if (tasks.empty())
    {
        cout << "No tasks available.\n";
        return;
    }

    cout << "\n=== All Tasks ===\n";

    for (int i = 0; i < tasks.size(); i++)
    {
        cout << i + 1 << ". "
            << tasks[i].description
            << " - "
            << (tasks[i].completed ? "Completed" : "Pending")
            << endl;
    }
}

void MarkTaskCompleted()
{
    ViewTasks();

    if (tasks.empty())
        return;

    cout << "Enter task number: ";
    int taskNumber = GetIntegerInput();

    if (taskNumber < 1 || taskNumber > tasks.size())
    {
        cout << "Invalid task number.\n";
        return;
    }

    tasks[taskNumber - 1].completed = true;

    SaveTasks();

    cout << "Task marked as completed.\n";
}

void DeleteTask()
{
    ViewTasks();

    if (tasks.empty())
        return;

    cout << "Enter task number to delete: ";
    int taskNumber = GetIntegerInput();

    if (taskNumber < 1 || taskNumber > tasks.size())
    {
        cout << "Invalid task number.\n";
        return;
    }

    tasks.erase(tasks.begin() + taskNumber - 1);

    SaveTasks();

    cout << "Task deleted successfully.\n";
}

void DisplayMenu()
{
    cout << "\n=== To-Do List Manager ===\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Delete Task\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

void RunMenu()
{
    int choice;

    do
    {
        DisplayMenu();
        choice = GetIntegerInput();

        switch (choice)
        {
        case 1:
            AddTask();
            break;

        case 2:
            ViewTasks();
            break;

        case 3:
            MarkTaskCompleted();
            break;

        case 4:
            DeleteTask();
            break;

        case 5:
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);
}

int main()
{
    LoadTasks();

    RunMenu();

    return 0;
}