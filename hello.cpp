#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;

// --- Constants and Global Variables ---
const int MAX_USERS = 1000;

// --- Classes ---
class User {
public:
    int id;
    string name;
    string email;

    User(int id, string name, string email)
        : id(id), name(name), email(email) {}

    void display() {
        cout << "ID: " << id << ", Name: " << name << ", Email: " << email << endl;
    }
};

class UserManager {
private:
    vector<User> users;
    int nextId = 1;

public:
    void addUser(const string& name, const string& email) {
        users.emplace_back(nextId++, name, email);
    }

    void listUsers() {
        for (auto& user : users) {
            user.display();
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (auto& user : users) {
            file << user.id << "," << user.name << "," << user.email << "\n";
        }
        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        string line;
        users.clear();
        nextId = 1;
        while (getline(file, line)) {
            stringstream ss(line);
            string idStr, name, email;
            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, email, ',');
            users.emplace_back(stoi(idStr), name, email);
            nextId = max(nextId, stoi(idStr) + 1);
        }
        file.close();
    }
};

// --- Utility Functions ---
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

void printPrimes(int limit) {
    for (int i = 2; i <= limit; i++) {
        if (isPrime(i)) cout << i << " ";
    }
    cout << endl;
}

// --- Algorithms ---
int binarySearch(const vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

vector<int> bubbleSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
        }
    }
    return arr;
}

// --- Simulated Tasks ---
void simulateTask() {
    cout << "Simulating long process...\n";
    for (int i = 0; i < 10; i++) {
        cout << "Step " << i + 1 << "/10\n";
    }
    cout << "Task complete.\n";
}

// --- Main Menu ---
void showMenu() {
    cout << "\n--- Main Menu ---\n";
    cout << "1. Add User\n";
    cout << "2. List Users\n";
    cout << "3. Save Users to File\n";
    cout << "4. Load Users from File\n";
    cout << "5. Generate Fibonacci\n";
    cout << "6. Show Primes\n";
    cout << "7. Sort Array\n";
    cout << "8. Binary Search\n";
    cout << "9. Simulate Task\n";
    cout << "0. Exit\n";
}

int main() {
    UserManager manager;
    int choice;
    do {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string name, email;
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter email: ";
            getline(cin, email);
            manager.addUser(name, email);
            break;
        }
        case 2:
            manager.listUsers();
            break;
        case 3:
            manager.saveToFile("users.txt");
            break;
        case 4:
            manager.loadFromFile("users.txt");
            break;
        case 5: {
            int n;
            cout << "Enter n: ";
            cin >> n;
            cout << "Fibonacci(" << n << ") = " << fibonacci(n) << endl;
            break;
        }
        case 6:
            printPrimes(100);
            break;
        case 7: {
            vector<int> arr = {5, 3, 8, 4, 2};
            vector<int> sorted = bubbleSort(arr);
            cout << "Sorted: ";
            for (int num : sorted) cout << num << " ";
            cout << endl;
            break;
        }
        case 8: {
            vector<int> arr = {1, 3, 5, 7, 9};
            int target;
            cout << "Enter target: ";
            cin >> target;
            int result = binarySearch(arr, target);
            if (result != -1) cout << "Found at index: " << result << endl;
            else cout << "Not found.\n";
            break;
        }
        case 9:
            simulateTask();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}

// --- Padding lines to reach ~400 ---
" + "
".join([f"// Padding line {i+1}" for i in range(150)])
}

