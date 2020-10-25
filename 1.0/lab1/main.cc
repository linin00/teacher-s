#include <vector>
#include <iostream>
#include <fstream>
#include "Class.h"
#include "Student.h"

using namespace std;

class AppX {
private:
    vector<Student *> studentVec;
    vector<Class *> classVec;

    void loadFiles();
    void inputScore();
    void printAvgScore();
    void printGpa();

public:
    AppX();
    ~AppX();
    int run();
};

AppX::~AppX()
{
    for (vector<Class *>::iterator it = classVec.begin();
         it != classVec.end();
         ++it) {
        if (*it) delete (*it);
    }
    for (const auto &s: studentVec) {
        if (s) delete (s);
    }
}

AppX::AppX()
{
    loadFiles();
}

void AppX::loadFiles()
{
    string line;
    size_t pos1, pos2;
    vector<string> bufv;
    vector<string> ipmark;
    Student *st = nullptr;
    string clsname;
    unsigned int point = (unsigned int)0;
    Class *cl = nullptr;

    ifstream stfile("./Students.txt");
    while (getline(stfile, line)) {
        if (line.empty())
            continue;
        if (line[0] == '#')
            continue;
        bufv.clear();
        pos1 = 0;
        while (true) {
            pos2 = line.find(';', pos1 + 1);
            if (pos2 == string::npos) {
                bufv.push_back(line.substr(pos1, string::npos));
                break;
            } else {
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }  
        if (bufv[3] == "U") {
            st = new Undergraduate(bufv[0], bufv[1], bufv[2]);
        }
        else {
            st = new Graduate(bufv[0], bufv[1], bufv[2]);
        }
        studentVec.push_back(st);
    }
    stfile.close();
    ifstream stfile2("./Classes.txt");
    while (getline(stfile2, line)) {
        if (line[0] == '#')
            continue;
            else if (line.empty()) {
                cl = new Class(bufv[0], point);
                classVec.push_back(cl);
                for (unsigned int i = 0; i < ipmark.size(); i++) {
                    for (unsigned int j = 0; j < studentVec.size(); j++) {
                        if (studentVec[j]->id == ipmark[i]){
                            classVec.back()->addStudent(*studentVec[j]);//perfect!
                            studentVec[j]->addClass(classVec.back());
                            }
                    }
                }
                ipmark.clear();
                continue;
            }
                else if (line[0] == 'C') {
                    bufv[0].assign(line, 6, string::npos);
                }
                    else if (line[0] == 'P') {
                        bufv[1].assign(line, 7, 1);
                        if (bufv[1][0] == '0') point = 0;
                            else if (bufv[1][0] == '1') point = 1;
                                else if (bufv[1][0] == '2') point = 2;
                                    else if (bufv[1][0] == '3') point = 3;
                                        else if (bufv[1][0] == '4') point = 4;
                                            else if (bufv[1][0] == '5') point = 5;
            }
                        else ipmark.push_back(line);
    }  
    cl = new Class(bufv[0], point);
    classVec.push_back(cl);
    for (unsigned int i = 0; i < ipmark.size(); i++) {
        for (unsigned int j = 0; j < studentVec.size(); j++) {
            if (studentVec[j]->id == ipmark[i]){
                classVec.back()->addStudent(*studentVec[j]);//perfect!
                studentVec[j]->addClass(classVec.back());
            }
        }
    }
    bufv.clear(); 
    stfile2.close();
}

void AppX::inputScore()
{
    string classname;
    string ID;
    double score;
    while (true) {
        cout << "Input the name of course (or input q to quit): ";
        cin >> classname;
        if (classname == "q")
            break;
        for (unsigned int i = 0; i < classVec.size(); i++) {
            if (classVec[i]->name == classname) 
                while (true){
                    cout << "Input the the student id (or input q to quit): ";
                    cin >> ID;
                    if (ID == "q")
                    break;
                    cout << classVec[i]->getStudentWrapper(ID).toString();
                    cout << "Input score:\n";
                    cin >> score;
                    classVec[i]->getStudentWrapper(ID).setScore(score);
                }
            else if (i ==classVec.size())
                cout << "No match class!\n";  
        }     
    }
}

void AppX::printAvgScore()
{
    string sbuf;
    Class *cl;
    double avg;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;
        cl = nullptr;
        for (vector<Class *>::iterator it = classVec.begin();
             it != classVec.end();
             ++it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!" << endl;
            continue;
        }

        avg = cl->getAvgScore();
        cout << "The average score is: " << avg << endl;
    }
}
void AppX::printGpa()
{
    while (true){
        string ID;
        cout << "Input the student id (or input q to quit):\n";
        cin>> ID;
        if (ID == "q") 
            break;
        for (unsigned int i = 0; i < studentVec.size(); i++) {
            if (studentVec[i]->id == ID) {
                cout << studentVec[i]->toString();
                studentVec[i]->toString();
                cout << "The Gpa is " << studentVec[i]->getGrade() << '\n';
                break;
            }
        }
    }
}

int AppX::run()
{
    char cmd;
    while (true) {
        cout << "Command menu:\n"
            << "\ti: Input score\n"
            << "\ta: Compute average score of a class\n"
            << "\tg: Compute grade of a student\n"
            << "\tq: Quit\n"
            << "Please input the command: ";
        cin >> cmd;
        if (cmd == 'i') {
            inputScore();
        } else if (cmd == 'a') {
            printAvgScore();
        } else if (cmd == 'g') {
            printGpa();
        } else if (cmd == 'q') {
            break;
        } else {
            cout << "Invalid command!\n" << endl;
        }
    }
    return 0;
}

int main()
{
    AppX app;
    return app.run();
}
