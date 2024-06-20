#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace std::filesystem;

struct Student {
    string name;
    int age;
    float CGPA;
    string gender;
};

// Function to read data from a CSV file and store it in a vector of vectors
vector<vector<string>> readCSV(const path& filepath) {
    vector<vector<string>> data;
    
    ifstream file(filepath);
    if (!file.is_open()) {
        cout << "Error opening file: " << filepath << endl;
        return data;
    }

    string line;
    bool firstLine = true;
    while (getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue;
        }

        vector<string> row;
        regex csvRegex(R"(([^,]+))");
        auto it = sregex_iterator(line.begin(), line.end(), csvRegex);
        auto end = sregex_iterator();

        while (it != end) {
            row.push_back((*it).str());
            ++it;
        }

        data.push_back(row);
    }

    file.close();
    return data;
}

bool compareCGPA(const Student &a, const Student &b) {
    return a.CGPA > b.CGPA; // Descending order
}

int main() {
    path csvPath = "phi.csv";
    vector<vector<string>> data = readCSV(csvPath);

    vector<Student> students;

    for (const auto& row : data) {
        if (row.size() < 4) continue;

        string name = row[0];
        int age = stoi(row[1]);
        float cgpa = stof(row[2]);
        string gender = row[3];

        students.push_back({name, age, cgpa, gender});
    }

    path numberOfStudentsPath = "number_of_students.csv";
    vector<vector<string>> studentData = readCSV(numberOfStudentsPath);
    for (const auto& row : studentData) {
        for (const auto& col : row) {
            cout << col << " ";
        }
        cout << endl;
    }

    cout << endl;

    path meanAgePath = "age.csv";
    vector<vector<string>> mean_age = readCSV(meanAgePath);
    for (const auto& row : mean_age) {
        if (row.size() > 1 && row[0] == "Mean") {
            cout << "Mean age: " << row[1] << endl;
            break;
        }
    }

    path meanCgpaPath = "cgpa.csv";
    vector<vector<string>> mean_cgpa = readCSV(meanCgpaPath);
    for (const auto& row : mean_cgpa) {
        if (row.size() > 1 && row[0] == "Mean") {
            cout << "Mean CGPA: " << row[1] << endl;
            break;
        }
    }

    cout << "\n";
    sort(students.begin(), students.end(), compareCGPA);

    vector<Student> topTwo(students.begin(), students.begin() + min(size_t(2), students.size()));

    for (const auto& student : topTwo) {
        cout << student.name << " with CGPA: " << student.CGPA << endl;
    }

    return 0;
}








#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

struct Student {
    string name;
    int age;
    float CGPA;
    string gender;
};

// Function to read data from a CSV file and store it in a vector of vectors
vector<vector<string>> readCSV(const fs::path& filename) {
    vector<vector<string>> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return data; // Return empty vector if file can't be opened
    }

    string line;
    bool firstLine = true;

    // Read data line by line
    while (getline(file, line)) {
        if (firstLine) {
            firstLine = false; // Skip the header row
            continue;
        }

        vector<string> row;
        stringstream ss(line);
        string value;

        // Split line by commas and store each value in 'row'
        while (getline(ss, value, ',')) {
            row.push_back(value);
        }

        data.push_back(row);
    }

    return data;
}

bool compareCGPA(const Student& a, const Student& b) {
    return a.CGPA > b.CGPA; // Descending order
}

int main() {
    const fs::path phiFile = "phi.csv";
    const fs::path numberOfStudentsFile = "number_of_students.csv";
    const fs::path ageFile = "age.csv";
    const fs::path cgpaFile = "cgpa.csv";

    vector<vector<string>> data = readCSV(phiFile);

    vector<Student> students;

    // Iterate over data rows
    for (const auto& row : data) {
        if (row.size() < 4) continue; // Ensure row has enough columns

        string name = row[0];
        string gender = row[3];
        int age = stoi(row[1]);
        float cgpa = stof(row[2]);

        students.push_back({name, age, cgpa, gender});
    }

    // Number of students
    vector<vector<string>> studentData = readCSV(numberOfStudentsFile);
    for (const auto& row : studentData) {
        for (const auto& col : row) {
            cout << col << " ";
        }
        cout << endl;
    }

    cout << endl;

    // MEAN AGE
    vector<vector<string>> meanAgeData = readCSV(ageFile);
    for (const auto& row : meanAgeData) {
        if (row.size() >= 2 && row[0] == "Mean") {
            cout << "Mean age: " << row[1] << endl;
            break;
        }
    }

    // MEAN CGPA
    vector<vector<string>> meanCgpaData = readCSV(cgpaFile);
    for (const auto& row : meanCgpaData) {
        if (row.size() >= 2 && row[0] == "Mean") {
            cout << "Mean CGPA: " << row[1] << endl;
            break;
        }
    }

    cout << "\n";
    sort(students.begin(), students.end(), compareCGPA);

    vector<Student> topTwo(students.begin(), students.begin() + min(2, (int)students.size()));

    // Output the top two students
    for (const auto& student : topTwo) {
        cout << student.name << " with CGPA: " << student.CGPA << endl;
    }

    return 0;
}
