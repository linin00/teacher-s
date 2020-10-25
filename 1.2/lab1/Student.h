#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>

class Class;

enum Degree {
    undergraduate,
    graduate
};

class Student {
    // TODO: implement class Student.
private:
    //std::string name;
    //std::string year;
    //Degree degree; 
protected:
    std::vector<Class*> classes;
public:
    std::string name;
    std::string year;
    Degree degree;
    std::string id;
    virtual double getGrade() = 0;
    void addClass(Class *c);
    std::string toString() const;
};

// TODO: implement class Graduate.
class Graduate: public Student {
private:
    //std::string name;
    //std::string year;
    //Degree degree = graduate;
protected:
public:
    //std::string name;
    //std::string year;
    //Degree degree;
    Graduate( std::string bufv1, std::string bufv2, std::string bufv3 );
    double getGrade();
};

// TODO: implement class Undergraduate.
class Undergraduate: public Student {
private:
    //std::string name;
    //std::string year;
    //Degree degree = undergraduate;
protected:
public:
    //std::string name;
    //std::string year;
    //Degree degree;
    Undergraduate( std::string bufv1, std::string bufv2, std::string bufv3 );
    double getGrade();
};

class StudentWrapper {
private:
    const Student &student;
    double score = 0.0;
public:
    const std::string id;
    // TODO: fix error
    StudentWrapper(const std::string &id, const Student &student) : id(id),student(student) {}/* {
        this->id = id;
        this->student = student;
    } */

    void setScore(double score)
    {
        if (score < 0 || score > 100)
            throw "Invalid Score!";
        this->score = score;
    }

    double getScore() const
    {
        return this->score;
    }

    std::string toString() const
    {
        return student.toString();
    }
};

#endif // STUDENT_H_
