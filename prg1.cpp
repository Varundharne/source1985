#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <algorithm>

using namespace std;

class Task {
private:
    int id;
    string title;
    string description;
    time_t creationTime;
    bool completed;

public:
    Task(int id, string title, string description)
        : id(id), title(title), description(description), completed(false) {
        creationTime = time(nullptr);
    }

    Task(int id, string title, string description, time_t time, bool completed)
        : id(id), title(title), description(description), creationTime(time), completed(completed) {}

    int getId() const { return id; }
    string getTitle() const { return title; }
    string getDescription() const { return description; }
    time_t getCreationTime() const { return creationTime; }
    bool isCompleted() const { return completed; }

    void markCompleted() { completed = true; }

    string toString() const {
        stringstream ss;
        ss << "ID: " << id << "\nTitle: " << title
           << "\nDescription: " << description
           << "\nCreated: " << ctime(&creationTime)
           << "Completed: " << (completed ? "Yes" : "No") << "\n";
        return ss.str();
    }

    string serialize() const {
        stringstream ss;
        ss << id << '|' << title << '|' << description << '|' << creationTime << '|' << completed;
        return ss.str();
    }

    static Task deserialize(const string &line) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, '|')) {
            tokens.push_back(token);
        }

        int id = stoi(tokens[0]);
        string title = tokens[1];
        string description = tokens[2];
        time_t time = static_cast<time_t>(stoll(tokens[3]));
        bool completed = stoi(tokens[4]) != 0;

        return Task(id, title, description, time, completed);
    }
};

class TaskManager {
private:
    vector<Task> tasks;
    int nextId;
    const string filename = "tasks.txt";

    void loadTasks() {
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            Task t = Task::deserialize(line);
            tasks.push_back(t);
            if (t.getId() >= nextId) {
                nextId = t.getId() + 1;
            }
        }

        file.close();
    }

    void saveTasks() const {
        ofstream file(filename);
        for (const Task &t : tasks) {
            file << t.serialize() << "\n";
        }
        file.close();
    }

public:
    TaskManager() : nextId(1) {
        loadTasks();
    }

    ~TaskManager() {
        saveTasks();
    }

    void addTask(const string &title, const string &desc) {
        Task t(nextId++, title, desc);
        tasks.push_back(t);
        cout << "Task added!\n";
    }

    void listTasks(bool showCompleted = true) const {
        cout << "\n===== Task List =====\n";
        for (const Task &t : tasks) {
            if (!showCompleted && t.isCompleted()) continue;
            cout << t.toString() << "-------------------\n";
        }
    }

    void completeTask(int id) {
        for (Task &t : tasks) {
            if (t.getId() == id) {
                t.markCompleted();
                cout << "Task marked as completed!\n";
                return;
            }
        }
        cout << "Task not found.\n";
    }

    void deleteTask(int id) {
        auto it = remove_if(tasks.begin(), tasks.end(),
                            [id](const Task &t) { return t.getId() == id; });

        if (it != tasks.end()) {
            tasks.erase(it, tasks.end());
            cout << "Task deleted.\n";
        } else {
            cout << "Task not found.\n";
        }
    }

    void clearCompleted() {
        auto it = remove_if(tasks.begin(), tasks.end(),
                            [](const Task &t) { return t.isCompleted(); });

        if (it != tasks.end()) {
            tasks.erase(it, tasks.end());
            cout << "Completed tasks cleared.\n";
        } else {
            cout << "No completed tasks to remove.\n";
        }
    }
};

void showMenu() {
    cout << "\n========= Task Manager =========\n";
    cout << "1. Add Task\n";
    cout << "2. List All Tasks\n";
    cout << "3. List Incomplete Tasks\n";
    cout << "4. Mark Task as Completed\n";
    cout << "5. Delete Task\n";
    cout << "6. Clear Completed Tasks\n";
    cout << "0. Exit\n";
    cout << "================================\n";
}

int main() {
    TaskManager manager;
    int choice;

    while (true) {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        string title, desc;
        int id;

        switch (choice) {
        case 1:
            cout << "Enter task title: ";
            getline(cin, title);
            cout << "Enter description: ";
            getline(cin, desc);
            manager.addTask(title, desc);
            break;
        case 2:
            manager.listTasks();
            break;
        case 3:
            manager.listTasks(false);
            break;
        case 4:
            cout << "Enter task ID to mark as completed: ";
            cin >> id;
            manager.completeTask(id);
            break;
        case 5:
            cout << "Enter task ID to delete: ";
            cin >> id;
            manager.deleteTask(id);
            break;
        case 6:
            manager.clearCompleted();
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }
    }

    cout << "Goodbye!\n";
    return 0;
}

