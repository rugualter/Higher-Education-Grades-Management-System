/*
 * student.h
 * Classe que faz operacoes sobre os estudantes
 *
 *  Created on: 18/12/2020
 *      Author: Rúdi Gualter
 */

#ifndef STUDENTS_H_
#define STUDENTS_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include "input.h"
#include "course.h"

namespace std {

class Student {
private:
    int uid;
	string name;
    string course;
    string location;
    void StudentDatabaseUpdate(int);
    int GetStudentCount();
    int VerifyExistanceUid(int);
    string GetName(int);
    string GetLocation(int);
    string GetCourse(int);
public:
	Student();
	~Student();
    void AddStudent();
    void ShowStudents();
    void DeleteStudent(int);
    void UpdateStudent(int);
    friend class Enrollment;
	friend class Course;
    bool operator == (const Student & obj){
        return (uid == obj.uid) && (name == obj.name) && (course == obj.course) && (location == obj.location);
    }
    friend ostream & operator << (ostream &out, const Student & obj){

    out << obj.uid << "\n" << obj.name << "\n" << obj.course << "\n" << obj.location << endl;

    return out;
    }

    friend std::istream & operator >> (std::istream &in,  Student &obj){
    
    in >> obj.uid;
    in.ignore();
    getline( in, obj.name);
    getline( in, obj.course);
    getline( in, obj.location);

    return in;

    }
};

} /* namespace std */
#endif /* STUDENTS_H_ */