/*
 * course.cpp
 * funcoes que faz operacoes sobre cursos
 *
 *  Created on: 18/12/2020
 *      Author: Rúdi Gualter
 */

#include "course.h"

namespace std {

Course::Course(){}

Course::~Course(){}

void Course::AddCourse(){

    int count = GetCourseCount();

    if(count==0){

        Input newinput;
        Course newcourse;

        cout << "Insira o nome do curso (ex.: Licenciatura em Gestao):" << endl;
        newcourse.name = newinput.GetString(100);

        if(VerifyExistance(newcourse.name)==1){
            cout << "\nATENCAO: Esse Curso ja existe, pode sempre modificar ou eleminar." << endl;
            return;
        }

        cout << "Insira o numero de ECTS do curso:" << endl;
        newcourse.ects = newinput.GetNumber(500);
        ofstream out("Courses.txt");
        
        out << newcourse;

        out.close();
        cout << "\nSUCESSO: Curso criado com sucesso"  << endl;
        CourseDatabaseUpdate(1);

    }else{

        Input newinput;
        Course newcourse[count+1];
        ifstream in("Courses.txt");

        for(int i=0; i<count; i++){
            in >> newcourse[i];
        }

        in.close();
        
        cout << "Insira o nome do curso (ex.: Licenciatura em Gestao):" << endl;
        newcourse[count].name = newinput.GetString(100);

        if(VerifyExistance(newcourse[count].name)==1){
            cout << "\nATENCAO: Esse Curso ja existe, pode sempre modificar ou eleminar." << endl;
            return;
        }

        cout << "Insira o numero de ECTS do curso:" << endl;
        newcourse[count].ects = newinput.GetNumber(500);

        ofstream out("Courses.txt");
        
        for(int i=0; i<count+1; i++){
            out << newcourse[i];
        }

        out.close();
        cout << "\nSUCESSO: Curso criado com sucesso"  << endl;
        CourseDatabaseUpdate(1);
    }

}

void Course::ShowCourses(){

    int count = GetCourseCount();

    cout << "\n" << string(130, '*') << std::endl;
	cout << string(51, ' ') << "Lista de Todos os Cursos" << std::endl;
	cout << string(130, '*') << std::endl;
	cout << left << setw(60) << "Nome" << setw(40) << "ECTS" <<endl;
    cout << string(130, '-') << std::endl;

    if(count==0){

        cout << "\nATENCAO: Sem cursos na base." << endl;
        return;

    }else{

        Course newcourse[count+1];
        ifstream in("Courses.txt");

        for(int i=0; i<count; i++){
            in >> newcourse[i];
        }

        in.close();
        
        for(int i=0; i<count; i++){
            cout << left << setw(60) << newcourse[i].name << setw(40) << newcourse[i].ects <<endl;
        }

    }

}

void Course::DeleteCourse(string name){

    int count = GetCourseCount();

    if(count==0){

        cout << "\nATENCAO: Nenhum curso na base para ser eliminado." << endl;
        return;

    }else{

        int courseexist=0;

        Course newcourse[count];

        ifstream in("Courses.txt");

        for(int i=0; i<count; i++){
            in >> newcourse[i];

            if(newcourse[i].name.compare(name)==0){
                courseexist=1;
            }
        }
        
        in.close();

        if(courseexist==0){
            cout << "\nATENCAO: Nenhum curso na base com esse nome" << endl;
            return;
        }
        
        ofstream out("Courses.txt");
        
        for(int i=0; i<count; i++){

            if(newcourse[i].name.compare(name)==0){
                
            }else{
                out << newcourse[i];
            }
        }

        out.close();

        cout << "\nSUCESSO: Curso " << name << " eliminado com sucesso." << endl;

        CourseDatabaseUpdate(0);
    }

}

void Course::UpdateCourse(string name){

    int count = GetCourseCount();
    string newname;
    int newects;

    if(count==0){

        cout << "\nATENCAO: Nenhum curso na base para ser modificado." << endl;
        return;

    }else{

        int courseexist=0;

        Course newcourse[count];

        ifstream in("Courses.txt");

        for(int i=0; i<count; i++){
            in >> newcourse[i];

            if(newcourse[i].name.compare(name)==0){

                newname = newcourse[i].name;
                newects = newcourse[i].ects;
                courseexist=1;

            }
        }
        
        in.close();

        if(courseexist==0){
            cout << "\nATENCAO: Nenhum curso na base com esse nome" << endl;
            return;
        }
        
        ofstream out("Courses.txt");
        
        for(int i=0; i<count; i++){

            if(newcourse[i].name.compare(name)==0){
                
            }else{
                out << newcourse[i];
            }
        }

        out.close();

        CourseDatabaseUpdate(0);
    }

    count = GetCourseCount();

    int option=0;

    Input newinput;
    Course newcourse[count+1];
    ifstream in("Courses.txt");

    for(int i=0; i<count; i++){
        in >> newcourse[i];
    }

    in.close();
    
    cout << "Pretende modificar o nome? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira o nome do curso (ex.: Licenciatura em Gestao):" << endl;
        newcourse[count].name = newinput.GetString(100);

        if(VerifyExistance(newcourse[count].name)==1){
        cout << "\nATENCAO: Um curso com esse nome ja existe, pode sempre eleminar ou tentar de novo com outro nome." << endl;
        newcourse[count].name = newname;
        newcourse[count].ects = newects;
        ofstream out("Courses.txt");
    
        for(int i=0; i<count+1; i++){
            out << newcourse[i];
        }

        out.close();
        return;
        }

    }else{
        newcourse[count].name = newname;
    }
    
    option=0;

    cout << "Pretende modificar os ECTS? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira o numero de ECTS do curso:" << endl;
        newcourse[count].ects = newinput.GetNumber(500);
    }else{
        newcourse[count].ects = newects;
    }

    ofstream out("Courses.txt");
    
    for(int i=0; i<count+1; i++){
        out << newcourse[i];
    }

    out.close();
    cout << "\nSUCESSO: Curso " << name << " modificado com sucesso." << endl;
    CourseDatabaseUpdate(1);
    

}

void Course::CourseDatabaseUpdate(int operation){

    ifstream in("Database.txt");
    bool empty = in.peek() == std::ifstream::traits_type::eof();
    
    ofstream out("Temp.txt");

    if(empty==true){
        out << 1 << "\n" << 0 << "\n" << 0 << "\n" << 0 << endl;
        out.close();
        remove("Database.txt");
        rename("temp.txt", "Database.txt"); 
        return;
    }

    string data;
    int line=1;
    int newdata[4];

    while(getline(in, data)){

        if(line==1){
            if(operation==1){
                newdata[0]=stoi(data)+1;
            }else{
                newdata[0]=stoi(data)-1;
            }
        }else if(line==2){
            newdata[1]=stoi(data);
        }else if(line==3){
            newdata[2]=stoi(data);
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

int Course::GetCourseCount(){

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

        if(line==1){
            int newdata=stoi(data);
            in.close();
            return newdata;
        }
        line=line+1;
    }

    in.close();
    return 0;
}

int Course::VerifyExistance(string name){

    int count = GetCourseCount();

    if(count==0){

        return 0;

    }else{

        int courseexist=0;

        Course newcourse[count];

        ifstream in("Courses.txt");

        for(int i=0; i<count; i++){
            in >> newcourse[i];

            if(newcourse[i].name.compare(name)==0){
                courseexist=1;
            }
        }
        
        in.close();
        return courseexist;

    }

}

int Course::GetECTS(string name){

    int count = GetCourseCount();

    if(count==0){

        cout << "\nATENCAO: Nenhum curso na base." << endl;
        return -1;

    }else{

        int courseexist=0;
        int passects;

        Course newcourse[count];

        ifstream in("Courses.txt");

        for(int i=0; i<count; i++){
            in >> newcourse[i];

            if(newcourse[i].name.compare(name)==0){
                courseexist=1;
                passects = newcourse[i].ects;
            }
        }
        
        in.close();

        if(courseexist==0){
            cout << "\nATENCAO: Nenhum curso na base com esse nome" << endl;
            return -1;
        }
        
        return passects;
    }

}

}