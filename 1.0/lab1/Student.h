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
private:
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

class Graduate: public Student {
private:
protected:
public:
    Graduate( std::string bufv1, std::string bufv2, std::string bufv3 );
    double getGrade();
};

class Undergraduate: public Student {
private:
protected:
public:
    Undergraduate( std::string bufv1, std::string bufv2, std::string bufv3 );
    double getGrade();
};

class StudentWrapper {
private:
    const Student &student;
    double score = 0.0;
public:
    const std::string id;
    StudentWrapper(const std::string &id, const Student &student) : id(id),student(student) {}

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

#endif
