/*
 * course.h
 * Classe que faz operacoes sobre cursos
 *
 *  Created on: 18/12/2020
 *      Author: Rúdi Gualter
 */

#ifndef COURSES_H_
#define COURSES_H_

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "input.h"

namespace std {

class Course {
private:
	string name;
	int ects;
    void CourseDatabaseUpdate(int);
    int GetCourseCount();
    int VerifyExistance(string);
    int GetECTS(string);
public:
	Course();
	~Course();
    void AddCourse();
    void ShowCourses();
    void DeleteCourse(string);
    void UpdateCourse(string);
    friend class Student;
    friend class Uc;
    friend class Enrollment;
    bool operator == (const Course & obj){
        return (name == obj.name) && (ects == obj.ects);
    }
    friend ostream & operator << (ostream &out, const Course & obj){

    out << obj.name << "\n" << obj.ects <<  endl;

    return out;
    }

    friend istream & operator >> (istream &in,  Course &obj){
    
    getline( in, obj.name);
    in >> obj.ects;
    in.ignore();

    return in;

    }


};

} /* namespace std */
#endif /* COURSES_H_ */