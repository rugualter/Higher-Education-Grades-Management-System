/*
 * enrollment.h
 * Classe que faz operacoes nas incricoes e notas
 *
 *  Created on: 18/12/2020
 *      Author: Rúdi Gualter
 */

#ifndef ENROLLMENT_H_
#define ENROLLMENT_H_

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include "input.h"
#include "uc.h"
#include "student.h"
#include "course.h"

namespace std {

class Enrollment {
private:
    int studentuid;
    int ucuid;
	string lectiveyear;
	int evaluationtype;
    float efolioa;
    float efoliob;
    float efolioc;
    float pfolio;
    float secondpfolio;
    float exam;
    float secondexam;
    void EnrollmentDatabaseUpdate(int);
    int GetEnrollmentCount();
    float GetGrade(int, int, string);
    int VerifyExistance(int, int, string);
public:
	Enrollment();
	~Enrollment();
    void AddEnrollment();
    void ShowEnrollments();
    void DeleteEnrollment(int, int, string);
    void UpdateEnrollment(int, int, string);
    void AddGrade(int, int , string);
    void GetStudentInfo(int);
    void GetUcInfo(int, string);
    bool operator == (const Enrollment & obj){
        return (studentuid == obj.studentuid) && (ucuid == obj.ucuid) && (lectiveyear == obj.lectiveyear) && (evaluationtype == obj.evaluationtype) && (efolioa == obj.efolioa) && (efoliob == obj.efoliob) && (efolioc == obj.efolioc) && (pfolio == obj.pfolio) && (secondpfolio == obj.secondpfolio) && (exam == obj.exam) && (secondexam == obj.secondexam);
    }
    friend ostream & operator << (ostream &out, const Enrollment & obj){

    out << obj.studentuid << "\n" << obj.ucuid << "\n" << obj.lectiveyear << "\n" << obj.evaluationtype << "\n" << obj.efolioa << "\n" << obj.efoliob << "\n" << obj.efolioc << "\n" << obj.pfolio << "\n" << obj.secondpfolio << "\n" << obj.exam << "\n" << obj.secondexam <<  endl;

    return out;
    }

    friend istream & operator >> (istream &in,  Enrollment &obj){
    
    in >> obj.studentuid;
    in.ignore();
    in >> obj.ucuid;
    in.ignore();
    getline( in, obj.lectiveyear);
    in >> obj.evaluationtype;
    in.ignore();
    in >> obj.efolioa;
    in.ignore();
    in >> obj.efoliob;
    in.ignore();
    in >> obj.efolioc;
    in.ignore();
    in >> obj.pfolio;
    in.ignore();
    in >> obj.secondpfolio;
    in.ignore();
    in >> obj.exam;
    in.ignore();
    in >> obj.secondexam;
    in.ignore();

    return in;

    }


};

} /* namespace std */
#endif /* ENROLLMENT_H_ */