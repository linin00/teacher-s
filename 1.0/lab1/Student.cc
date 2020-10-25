#include "Student.h"
#include <string>
#include <sstream>
#include <iostream>
#include "Class.h"

void Student::addClass(Class *c) {
    classes.push_back(c);
}

std::string Student::toString() const
{
    std::ostringstream oss; 
    oss << "Student Information:"
        << "\n\tid: " << this->id
        << "\n\tname: " << this->name
        << "\n\tenrollment year: " << this->year
        << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate")
        << std::endl;
    return oss.str();

    return "";
}

Graduate::Graduate( std::string bufv1, std::string bufv2, std::string bufv3 ) {
    id = bufv1;
    name = bufv2;
    year = bufv3;
}

double Graduate::getGrade() {
    double grade = 0;
        int numOfCourses = classes.size();
        int sumOfPoint = 0;
        for( int i = 0; i < numOfCourses; i++ ) 
            sumOfPoint += classes[i]->point;
        for( int i = 0; i < numOfCourses; i++ ) {
            if ( classes[i]->getStudentWrapper( id ).getScore() >= 90 && classes[i]->getStudentWrapper( id ).getScore() <=100 )
            grade += 4.0*classes[i]->point;
            else if ( classes[i]->getStudentWrapper( id ).getScore() >=80 && classes[i]->getStudentWrapper( id ).getScore() <89 )
                grade += 3.5*classes[i]->point;
                else if ( classes[i]->getStudentWrapper( id ).getScore() >= 70 && classes[i]->getStudentWrapper( id ).getScore() < 79 )
                    grade += 3.0*classes[i]->point;
                    else if ( classes[i]->getStudentWrapper( id ).getScore() >= 60 && classes[i]->getStudentWrapper( id ).getScore() < 69 )
                        grade += 2.5*classes[i]->point;
                        else if ( classes[i]->getStudentWrapper( id ).getScore() < 60 )
                            grade += 2.0*classes[i]->point;
        }
        grade /= sumOfPoint;
        return grade;
}

Undergraduate::Undergraduate( std::string bufv1, std::string bufv2, std::string bufv3 ) {
    id = bufv1;
    name = bufv2;
    year = bufv3;
}
double Undergraduate::getGrade() {
    double grade = 0;
    int numOfCourses = classes.size();
    int sumOfPoint = 0;
    for ( int i = 0; i < numOfCourses; i++ )
        sumOfPoint += classes[i]->point;
    for ( int i = 0; i < numOfCourses; i++ ) 
        grade += (classes[i]->getStudentWrapper( id ).getScore()*classes[i]->point)/20;
    grade /= sumOfPoint;
    return grade;
}