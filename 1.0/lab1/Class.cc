#include "Class.h"
#include <string>
#include "Student.h"
#include <iostream>

void Class::addStudent(const Student &st)
{
    StudentWrapper sw(st.id, st);
    students.push_back(sw);
}

StudentWrapper &Class::getStudentWrapper(const std::string &studentId)
{
    for (std::vector<StudentWrapper>::iterator it = students.begin();
         it != students.end();
         ++it) {
        if (it->id == studentId)
            return *it;
    }
    std::cout << "No match student!";
}

double Class::getAvgScore()
{
    int numOfStudents = students.size();
    double avgScore = 0;
    for ( int i =0;
    i < numOfStudents;
    i++ ) {
        avgScore += students[i].getScore();
    }
    avgScore /= numOfStudents;
    return avgScore;
}
