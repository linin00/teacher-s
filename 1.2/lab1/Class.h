#ifndef CLASS_H_
#define CLASS_H_

#include "Student.h"
#include <string>
#include <vector>

class Class {
private:
    

public:
    std::vector<StudentWrapper> students;// 选课学生清单,from private
    const std::string name;// name of course
    const int point;// point of course
    Class(const std::string &name, const int point)
        : name(name), point(point) { }// 

    void addStudent(const Student &st);
    StudentWrapper &getStudentWrapper(const std::string &studentId);
    double getAvgScore();
};

#endif // CLASS_H_
