/*
 * student.cpp
 * funcoes que faz operacoes sobre estudantes
 *
 *  Created on: 18/12/2020
 *      Author: Rúdi Gualter
 */

#include "student.h"

namespace std {

Student::Student(){}

Student::~Student(){}

void Student::AddStudent(){

    int count = GetStudentCount();

    if(count==0){

        Input newinput;
        Student newstudent;
        Course course;

        cout << "Insira o numero identificador do estudante:" << endl;
        newstudent.uid = newinput.GetNumber(9999999);

        if(VerifyExistanceUid(newstudent.uid)==1){
            cout << "\nATENCAO: Ja existe um estudante com esse numero, pode sempre modificar ou eleminar." << endl;
            return;
        }
        
        cout << "Insira o nome do estudante:" << endl;
        newstudent.name = newinput.GetString(100);

        cout << "Insira o curso a que pertence a que o estudante pertence (ex. Licenciatura em Engenharia):" << endl;
        newstudent.course = newinput.GetString(100);

        if(course.VerifyExistance(newstudent.course)==0){
            cout << "\nATENCAO: Esse curso nao existe, deve criar-lo em primeiro." << endl;
            return;
        }

        cout << "Insira a localizacao do estudante:" << endl;
        newstudent.location = newinput.GetString(100);

        ofstream out("Students.txt");
        
        out << newstudent;

        out.close();
        cout << "\nSUCESSO: Estudante criado com sucesso"  << endl;
        StudentDatabaseUpdate(1);

    }else{

        Input newinput;
        Student newstudent[count+1];
        Course course;
        ifstream in("Students.txt");

        for(int i=0; i<count; i++){
            in >> newstudent[i];
        }

        in.close();
        
        cout << "Insira o numero identificador do estudante:" << endl;
        newstudent[count].uid = newinput.GetNumber(9999999);

        if(VerifyExistanceUid(newstudent[count].uid)==1){
            cout << "\nATENCAO: Ja existe um estudante com esse numero, pode sempre modificar ou eleminar." << endl;
            return;
        }
        
        cout << "Insira o nome do estudante:" << endl;
        newstudent[count].name = newinput.GetString(100);

        cout << "Insira o curso a que pertence a que o estudante pertence (ex. Licenciatura em Engenharia):" << endl;
        newstudent[count].course = newinput.GetString(100);

        if(course.VerifyExistance(newstudent[count].course)==0){
            cout << "\nATENCAO: Esse curso nao existe, deve criar-lo em primeiro." << endl;
            return;
        }

        cout << "Insira a localizacao do estudante:" << endl;
        newstudent[count].location = newinput.GetString(100);

        ofstream out("Students.txt");
        
        for(int i=0; i<count+1; i++){
            out << newstudent[i];
        }

        out.close();
        cout << "\nSUCESSO: Unidade Curricular criada com sucesso"  << endl;
        StudentDatabaseUpdate(1);
    }

}

void Student::ShowStudents(){

    int count = GetStudentCount();

    cout << "\n" << string(130, '*') << std::endl;
	cout << string(51, ' ') << "Lista de Todos os Alunos" << std::endl;
	cout << string(130, '*') << std::endl;
	cout << left << setw(20) << "Numero Matricula" << setw(40) << "Nome"<< setw(40) << "Curso" << setw(40) << "Localizacao" <<endl;
    cout << string(130, '-') << std::endl;

    if(count==0){

        cout << "\nATENCAO: Sem estudantes na base." << endl;
        return;

    }else{

        Student newstudent[count+1];
        ifstream in("Students.txt");

        for(int i=0; i<count; i++){
            in >> newstudent[i];
        }

        in.close();
        
        for(int i=0; i<count; i++){
            cout << left << setw(20) << newstudent[i].uid << setw(40) << newstudent[i].name << setw(40) << newstudent[i].course << setw(40) << newstudent[i].location <<endl;
        }

    }

}

void Student::DeleteStudent(int uid){

    int count = GetStudentCount();

    if(count==0){

        cout << "\nATENCAO: Nenhum estudante na base para ser eliminado." << endl;
        return;

    }else{

        int studentexist=0;

        Student newstudent[count];

        ifstream in("Students.txt");

        for(int i=0; i<count; i++){
            in >> newstudent[i];

            if(newstudent[i].uid==uid){
                studentexist=1;
            }
        }
        
        in.close();

        if(studentexist==0){
            cout << "\nATENCAO: Nenhum estudante na base com esse numero" << endl;
            return;
        }
        
        ofstream out("Students.txt");
        
        for(int i=0; i<count; i++){

            if(newstudent[i].uid==uid){
                
            }else{
                out << newstudent[i];
            }
        }

        out.close();

        cout << "\nSUCESSO: Estudante " << uid << " eliminado com sucesso." << endl;

        StudentDatabaseUpdate(0);
    }

}

void Student::UpdateStudent(int uid){

    int count = GetStudentCount();
    int newuid;
    string newname;
    string newcourse;
    string newlocation;

    if(count==0){

        cout << "\nATENCAO: Nenhum estudante na base para ser modificado." << endl;
        return;

    }else{

        int studentexist=0;

        Student newstudent[count];

        ifstream in("Students.txt");

        for(int i=0; i<count; i++){
            in >> newstudent[i];

            if(newstudent[i].uid==uid){

                newuid = newstudent[i].uid;
                newname = newstudent[i].name;
                newcourse = newstudent[i].course;
                newlocation = newstudent[i].location;
                studentexist=1;

            }
        }
        
        in.close();

        if(studentexist==0){
            cout << "\nATENCAO: Nenhum estudante na base com esse numero" << endl;
            return;
        }
        
        ofstream out("Students.txt");
        
        for(int i=0; i<count; i++){

            if(newstudent[i].uid==uid){
                
            }else{
                out << newstudent[i];
            }
        }

        out.close();

        StudentDatabaseUpdate(0);
    }

    count = GetStudentCount();

    int option=0;

    Input newinput;
    Course course;
    Student newstudent[count+1];
    ifstream in("Students.txt");

    for(int i=0; i<count; i++){
        in >> newstudent[i];
    }

    in.close();
    
    cout << "Pretende modificar o numero identificador? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira o numero identificador do estudante:" << endl;
        newstudent[count].uid = newinput.GetNumber(9999999);

        if(VerifyExistanceUid(newstudent[count].uid)==1){
            cout << "\nATENCAO: Ja existe um estudante com esse numero, pode sempre modificar ou eleminar." << endl;
            newstudent[count].uid = newuid;
            newstudent[count].name = newname;
            newstudent[count].course = newcourse;
            newstudent[count].location = newlocation;
            ofstream out("Students.txt");
    
            for(int i=0; i<count+1; i++){
                out << newstudent[i];
            }

            out.close();
            return;
        }

    }else{
        newstudent[count].uid = newuid;
    }
    
    option=0;

    cout << "Pretende modificar o nome? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){

        cout << "Insira o nome do estudante:" << endl;
        newstudent[count].name = newinput.GetString(100);

    }else{
        newstudent[count].name = newname;
    }

    option=0;

    cout << "Pretende modificar o Curso? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira o curso a que pertence o estudante:" << endl;
        newstudent[count].course = newinput.GetString(100);

        if(course.VerifyExistance(newstudent[count].course)==0){
            cout << "\nATENCAO: Esse curso nao existe, deve criar-lo em primeiro." << endl;
            newstudent[count].uid = newuid;
            newstudent[count].name = newname;
            newstudent[count].course = newcourse;
            newstudent[count].location = newlocation;
            ofstream out("Students.txt");
    
            for(int i=0; i<count+1; i++){
                out << newstudent[i];
            }

            out.close();
            return;
        }
    }else{
        newstudent[count].course = newcourse;
    }

    option=0;

    cout << "Pretende modificar a localizacao? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira a localizacao:" << endl;
        newstudent[count].location = newinput.GetString(100);
    }else{
        newstudent[count].location = newlocation;
    }

    ofstream out("Students.txt");
    
    for(int i=0; i<count+1; i++){
        out << newstudent[i];
    }

    out.close();
    cout << "\nSUCESSO: Estudante " << uid << " modificado com sucesso." << endl;
    StudentDatabaseUpdate(1);

}

void Student::StudentDatabaseUpdate(int operation){

    ifstream in("Database.txt");
    bool empty = in.peek() == std::ifstream::traits_type::eof();
    
    ofstream out("Temp.txt");

    if(empty==true){
        out << 0 << "\n" << 0 << "\n" << 1 << "\n" << 0 << endl;
        out.close();
        remove("Database.txt");
        rename("temp.txt", "Database.txt"); 
        return;
    }

    string data;
    int line=1;
    int newdata[4];

    while(getline(in, data)){

        if(line==3){
            if(operation==1){
                newdata[2]=stoi(data)+1;
            }else{
                newdata[2]=stoi(data)-1;
            }
        }else if(line==1){
            newdata[0]=stoi(data);
        }else if(line==2){
            newdata[1]=stoi(data);
        }else{
            newdata[3]=stoi(data);
        }

        line=line+1;
    }
    out << newdata[0] << "\n" << newdata[1] << "\n" << newdata[2] << "\n" << newdata[3] << endl;

    in.close();
    out.close();
    remove("Database.txt");
    rename("temp.txt", "Database.txt"); 

}

int Student::GetStudentCount(){

    ifstream in("Database.txt");
    bool empty = in.peek() == std::ifstream::traits_type::eof();

    if(!in){
        return 0;
    }

    if(empty==true){
        return 0;
    }

    string data;
    int line=1;
    
    while(getline(in, data)){

        if(line==3){
            int newdata=stoi(data);
            in.close();
            return newdata;
        }
        line=line+1;
    }

    in.close();
    return 0;
}

int Student::VerifyExistanceUid(int uid){

    int count = GetStudentCount();

    if(count==0){

        return 0;

    }else{

        int studentexist=0;

        Student newstudent[count];

        ifstream in("Students.txt");

        for(int i=0; i<count; i++){
            in >> newstudent[i];

            if(newstudent[i].uid==uid){
                studentexist=1;
            }
        }
        
        in.close();
        return studentexist;

    }

}

string Student::GetName(int uid){

    int count = GetStudentCount();

    if(count==0){

        return "null";

    }else{

        int studentexist=0;
        string passname;

        Student newstudent[count];

        ifstream in("Students.txt");

        for(int i=0; i<count; i++){
            in >> newstudent[i];

            if(newstudent[i].uid==uid){
                studentexist=1;
                passname = newstudent[i].name;
            }
        }
        
        in.close();

        if(studentexist==0){

            return "null";
        }

        return passname;
    }

}

string Student::GetLocation(int uid){

    int count = GetStudentCount();

    if(count==0){

        return "null";

    }else{

        int studentexist=0;
        string passlocation;

        Student newstudent[count];

        ifstream in("Students.txt");

        for(int i=0; i<count; i++){
            in >> newstudent[i];

            if(newstudent[i].uid==uid){
                studentexist=1;
                passlocation = newstudent[i].location;
            }
        }
        
        in.close();

        if(studentexist==0){

            return "null";
        }

        return passlocation;
    }

}

string Student::GetCourse(int uid){

    int count = GetStudentCount();

    if(count==0){

        return "null";

    }else{

        int studentexist=0;
        string passcourse;

        Student newstudent[count];

        ifstream in("Students.txt");

        for(int i=0; i<count; i++){
            in >> newstudent[i];

            if(newstudent[i].uid==uid){
                studentexist=1;
                passcourse = newstudent[i].course;
            }
        }
        
        in.close();

        if(studentexist==0){

            return "null";
        }

        return passcourse;
    }

}

}