#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Class.h"
#include "Student.h"

using namespace std;

class AppX {
private:
    vector<Student *> studentVec;// student object collection
    vector<Class *> classVec;// class object collection

    void loadFiles();// to load students & classes from file
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
    // You can use the traditional loop, which is more clear.
    for (vector<Class *>::iterator it = classVec.begin();
         it != classVec.end();
         ++it) {
        if (*it) delete (*it);
    }
    // You can use modern and simpler loops only if you know what it is doing.
    for (const auto &s: studentVec) {
        if (s) delete (s);
    }
}

AppX::AppX()
{
    loadFiles();
    /* cout << classVec.size() << '\n'; 
    for (int i = 0; i < classVec.size(); i++)
        cout << classVec[i]->name << '\n';  */
}

void AppX::loadFiles()
{
    string line;
    size_t pos1, pos2;// what the **ck is size_t?
    vector<string> bufv;
    vector<string> ipmark;
    Student *st = nullptr;//
    string clsname;
    unsigned int point = (unsigned int)0;
    Class *cl = nullptr;//

    // Open a file as a input stream.
    ifstream stfile("./Students.txt");//Students.txt
    while (getline(stfile, line)) {
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;

        // The bufv vector stores each columnes in the line.
        bufv.clear();
        // Split the line into columes.
        //   pos1: begining the the column.
        //   pos2: end of the column.
        pos1 = 0;
        while (true) {
            pos2 = line.find(';', pos1 + 1);
            if (pos2 == string::npos) { // No more columns.
                // Save the last column (pos1 ~ eol).
                bufv.push_back(line.substr(pos1, string::npos));
                break;
            } else {
                // Save the column (pos1 ~ pos2).
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }

        // TODO: uncomment next lines after implementing class Undergraduate
        // and Graduate.
        
        if (bufv[3] == "U") {
            st = new Undergraduate(bufv[0], bufv[1], bufv[2]);
            //cout << bufv[1];
            //cout << st->name << 123;
        }
        else {
            st = new Graduate(bufv[0], bufv[1], bufv[2]);
            //cout << bufv[1];
        }
        studentVec.push_back(st);
    }
    stfile.close();

    // TODO: load data from ./Classes.txt and push objects to the vector.
    // Hint: how is student information read?
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
                /* bufv.clear(); */
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
    // TODO: implement inputScore.
    // Hint: Take a look at printAvgScore().
    string classname;
    string ID;
    double score;
    while (true) {
        int dd = 2;
        cout << "Input the name of course (or input q to quit): ";
        cin >> classname;
        if (classname == "q")
            break;
        for (unsigned int i = 0; i < classVec.size(); i++) {
            while (true)
            {   
                if (i == classVec.size()-1 && classVec[i]->name != classname) {
                cout << "No match class!\n";
                dd = 1;
                break;
                }
                if (classVec[i]->name == classname) {
                    while (true){
                        /* cout << classVec[i]->students.size(); */
                        /* for (int j = 0; j < classVec[i]->students.size(); j++)
                        cout << classVec[i]->students[j].id << endl; */
                        /*cout << classVec[i]->students.size();*/
                        cout << "Input the the student id (or input q to quit): ";
                        cin >> ID;
                        if (ID == "q"){
                            dd = 0;
                            break;
                        }
                        for (int j = 0; j < classVec[i]->students.size(); j++) {
                            if (ID == classVec[i]->students[j].id) {
                                cout << classVec[i]->getStudentWrapper(ID).toString();
                                while (true) {
                                    cout << "Input score:";
                                    cin >> score;
                                    if (score < 0 || score > 100) {
                                        cout << "Wrong score!\n";
                                        //continue;
                                        break;
                                    }
                                    else {
                                        classVec[i]->getStudentWrapper(ID).setScore(score);
                                        break;
                                    }
                                }
                                break;
                            }
                            else if (j == classVec[i]->students.size() - 1){
                                cout << "No match student!\n";
                                break;  
                            }
                        }
                    }

                    break;
                }
                break;
            }
            if (dd == 0)
            break;
            else 
            continue;
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
            cout << "No match class!\n";
            continue;
        }

        avg = cl->getAvgScore();
        cout << fixed << setprecision(2) << "The average score is: " << avg << endl;
    }
}
// TODO: implement printGpa.
        // Hint: Take a look at printAvgScore().
void AppX::printGpa()
{
    while (true){  
        string ID;
        cout << "Input the student id (or input q to quit):";
        cin>> ID;
        if (ID == "q") 
            break;
        for (unsigned int i = 0; i < studentVec.size(); i++) {
            if (studentVec[i]->id == ID) {
                cout << studentVec[i]->toString();
                //studentVec[i]->toString();
                cout << fixed << setprecision(2) << "GPA = " << studentVec[i]->getGrade() << '\n';
                break;
            }
            if (i == studentVec.size() - 1) {
                cout << "No match student!\n";
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
