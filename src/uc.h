/*
 * course.h
 * Classe que faz operacoes sobre unidades curriculares
 *
 *  Created on: 18/12/2020
 *      Author: Rúdi Gualter
 */

#ifndef UCS_H_
#define UCS_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include "input.h"
#include "course.h"

namespace std {

class Uc {
private:
    int uid;
	string name;
    string course;
    int year;
    int semester;
	int ects;
    int efolios;
    void UcDatabaseUpdate(int);
    int GetUcCount();
    int GetCourseECTS(string);
    int VerifyExistanceName(string);
    int VerifyExistanceUid(int);
    int GetECTS(int);
    int GetEfolios(int);
    string GetName(int);
    string GetCourse(int);
public:
	Uc();
	~Uc();
    void AddUc();
    void ShowUcs();
    void DeleteUc(int);
    void UpdateUc(int);
    friend class Enrollment;
	friend class Course;
    bool operator == (const Uc & obj){
        return (uid == obj.uid) && (name == obj.name) && (course == obj.course) && (year == obj.year) && (semester == obj.semester) && (ects == obj.ects) && (efolios == obj.efolios);
    }
    friend ostream & operator << (ostream &out, const Uc & obj){

    out << obj.uid << "\n" << obj.name << "\n" << obj.course << "\n" << obj.year << "\n" << obj.semester << "\n" << obj.ects << "\n" << obj.efolios << endl;

    return out;
    }

    friend std::istream & operator >> (std::istream &in,  Uc &obj){
    
    in >> obj.uid;
    in.ignore();
    getline( in, obj.name);
    getline( in, obj.course);
    in >> obj.year;
    in.ignore();
    in >> obj.semester;
    in.ignore();
    in >> obj.ects;
    in.ignore();
    in >> obj.efolios;
    in.ignore();

    return in;

    }
};

} /* namespace std */
#endif /* UCS_H_ */