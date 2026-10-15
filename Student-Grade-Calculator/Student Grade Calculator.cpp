#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

struct Subject
{
    string name;
    double mark;
    double maximumMark;
};

int GetIntegerInput()
{
    int number;

    while (!(cin >> number) || number <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a valid positive number: ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return number;
}

double GetPositiveMark(string message)
{
    double mark;

    cout << message;

    while (!(cin >> mark) || mark <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a valid positive number: ";
    }

    return mark;
}

double GetStudentMark(double maximumMark)
{
    double mark;

    cout << "Enter student mark: ";

    while (!(cin >> mark) || mark < 0 || mark > maximumMark)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter a mark between 0 and "
            << maximumMark << ": ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return mark;
}

string GetSubjectName()
{
    string name;

    cout << "Enter subject name: ";
    getline(cin, name);

    while (name.empty())
    {
        cout << "Subject name cannot be empty. Enter again: ";
        getline(cin, name);
    }

    return name;
}

Subject ReadSubject()
{
    Subject subject;

    subject.name = GetSubjectName();

    subject.maximumMark =
        GetPositiveMark("Enter maximum mark: ");

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    subject.mark = GetStudentMark(subject.maximumMark);

    return subject;
}

vector<Subject> ReadSubjects()
{
    vector<Subject> subjects;

    cout << "Enter number of subjects: ";
    int numberOfSubjects = GetIntegerInput();

    for (int i = 0; i < numberOfSubjects; i++)
    {
        cout << "\nSubject " << i + 1 << endl;

        Subject subject = ReadSubject();

        subjects.push_back(subject);
    }

    return subjects;
}

double CalculateTotalMarks(const vector<Subject>& subjects)
{
    double total = 0;

    for (const Subject& subject : subjects)
        total += subject.mark;

    return total;
}

double CalculateMaximumMarks(const vector<Subject>& subjects)
{
    double total = 0;

    for (const Subject& subject : subjects)
        total += subject.maximumMark;

    return total;
}

double CalculatePercentage(double totalMarks, double maximumMarks)
{
    return (totalMarks / maximumMarks) * 100;
}

char CalculateGrade(double percentage)
{
    if (percentage >= 90)
        return 'A';
    else if (percentage >= 80)
        return 'B';
    else if (percentage >= 70)
        return 'C';
    else if (percentage >= 60)
        return 'D';
    else
        return 'F';
}

void DisplaySubjects(const vector<Subject>& subjects)
{
    cout << "\n=== Subject Results ===\n";

    for (const Subject& subject : subjects)
    {
        double percentage =
            CalculatePercentage(subject.mark, subject.maximumMark);

        cout << "Subject: " << subject.name << endl;
        cout << "Mark: " << subject.mark
            << " / " << subject.maximumMark << endl;
        cout << "Percentage: " << percentage << "%\n\n";
    }
}

void DisplayResults(const vector<Subject>& subjects)
{
    double totalMarks = CalculateTotalMarks(subjects);
    double maximumMarks = CalculateMaximumMarks(subjects);

    double percentage =
        CalculatePercentage(totalMarks, maximumMarks);

    char grade = CalculateGrade(percentage);

    cout << fixed << setprecision(2);

    DisplaySubjects(subjects);

    cout << "Total Marks: " << totalMarks
        << " / " << maximumMarks << endl;

    cout << "Overall Percentage: " << percentage << "%\n";
    cout << "Final Grade: " << grade << endl;
}

int main()
{
    cout << "=== Student Grade Calculator ===\n";

    vector<Subject> subjects = ReadSubjects();

    DisplayResults(subjects);

    return 0;
}