/*
 * uc.cpp
 * funcoes que faz operacoes sobre unidades curriculares
 *
 *  Created on: 18/12/2020
 *      Author: Rúdi Gualter
 */

#include "uc.h"

namespace std {

Uc::Uc(){}

Uc::~Uc(){}

void Uc::AddUc(){

    int count = GetUcCount();

    if(count==0){

        Input newinput;
        Uc newuc;
        Course course;

        cout << "Insira o numero identificador da unidade curricular:" << endl;
        newuc.uid = newinput.GetNumber(9999999);

        if(VerifyExistanceUid(newuc.uid)==1){
            cout << "\nATENCAO: Ja existe uma unidade curricular com esse numero, pode sempre modificar ou eleminar." << endl;
            return;
        }
        
        cout << "Insira o nome da unidade curricular:" << endl;
        newuc.name = newinput.GetString(100);

        if(VerifyExistanceName(newuc.name)==1){
            cout << "\nATENCAO: Ja existe uma unidade curricular com esse nome, pode sempre modificar ou eleminar." << endl;
            return;
        }

        cout << "Insira o curso a que pertence a unidade curricular:" << endl;
        newuc.course = newinput.GetString(100);

        if(course.VerifyExistance(newuc.course)==0){
            cout << "\nATENCAO: Esse curso nao existe, deve criar-lo em primeiro." << endl;
            return;
        }

        cout << "Insira o ano curricular a que pertence (1,2,3,4):" << endl;
        newuc.year = newinput.GetNumber(4);

        cout << "Insira o semestre curricular a que pertence (1,2):" << endl;
        newuc.semester = newinput.GetNumber(2);

        cout << "Insira o numero de ECTS que a unidade vale:" << endl;
        newuc.ects = newinput.GetNumber(500);

        cout << "Insira o numero de e-folios que a unidade tem (2,3):" << endl;
        bool validation=false;
        int numberefolios;
        do{
            numberefolios = newinput.GetNumber(3);
            if(numberefolios>=2 && numberefolios <=3){
                validation=true;
            }
            cout << "\nATENCAO: Insira um valor de 2 ou 3 e-folios, insira de novo:" << endl;

        }while(!validation);
        newuc.efolios = numberefolios;

        int courseects = course.GetECTS(newuc.course);
        int totalucects = GetCourseECTS(newuc.course);
        int esctscheck = totalucects + newuc.ects;

        if(esctscheck>courseects){
            cout << "\nATENCAO: Execedeu o limite de ECTS do curso, verifique o total de ECTS do curso e tente de novo." << endl;
            return;
        }

        ofstream out("Ucs.txt");
        
        out << newuc;

        out.close();
        cout << "\nSUCESSO: Unidade Curricular criada com sucesso"  << endl;
        UcDatabaseUpdate(1);

    }else{

        Input newinput;
        Uc newuc[count+1];
        Course course;
        ifstream in("Ucs.txt");

        for(int i=0; i<count; i++){
            in >> newuc[i];
        }

        in.close();
        
        cout << "Insira o numero identificador da unidade curricular:" << endl;
        newuc[count].uid = newinput.GetNumber(9999999);

        if(VerifyExistanceUid(newuc[count].uid)==1){
            cout << "\nATENCAO: Ja existe uma unidade curricular com esse numero, pode sempre modificar ou eleminar." << endl;
            return;
        }
        
        cout << "Insira o nome da unidade curricular:" << endl;
        newuc[count].name = newinput.GetString(100);

        if(VerifyExistanceName(newuc[count].name)==1){
            cout << "\nATENCAO: Ja existe uma unidade curricular com esse nome, pode sempre modificar ou eleminar." << endl;
            return;
        }

        cout << "Insira o curso a que pertence a unidade curricular:" << endl;
        newuc[count].course = newinput.GetString(100);

        if(course.VerifyExistance(newuc[count].course)==0){
            cout << "\nATENCAO: Esse curso nao existe, deve criar-lo em primeiro." << endl;
            return;
        }

        cout << "Insira o ano curricular a que pertence (1,2,3,4):" << endl;
        newuc[count].year = newinput.GetNumber(4);

        cout << "Insira o semestre curricular a que pertence (1,2):" << endl;
        newuc[count].semester = newinput.GetNumber(2);

        cout << "Insira o numero de ECTS que a unidade vale:" << endl;
        newuc[count].ects = newinput.GetNumber(500);

        cout << "Insira o numero de e-folios que a unidade tem (2,3):" << endl;
        bool validation=false;
        int numberefolios;
        do{
            numberefolios = newinput.GetNumber(3);
            if(numberefolios>=2 && numberefolios <=3){
                validation=true;
            }
            cout << "\nATENCAO: Insira um valor de 2 ou 3 e-folios, insira de novo:" << endl;

        }while(!validation);
        newuc[count].efolios = numberefolios;

        int courseects = course.GetECTS(newuc[count].course);
        int totalucects = GetCourseECTS(newuc[count].course);
        int esctscheck = totalucects + newuc[count].ects;

        if(esctscheck>courseects){
            cout << "\nATENCAO: Execedeu o limite de ECTS do curso, verifique o total de ECTS do curso e tente de novo." << endl;
            return;
        }

        ofstream out("Ucs.txt");
        
        for(int i=0; i<count+1; i++){
            out << newuc[i];
        }

        out.close();
        cout << "\nSUCESSO: Unidade Curricular criada com sucesso"  << endl;
        UcDatabaseUpdate(1);
    }

}

void Uc::ShowUcs(){

    int count = GetUcCount();

    cout << "\n" << string(130, '*') << std::endl;
	cout << string(45, ' ') << "Lista de Todas as Unidades Curriculares" << std::endl;
	cout << string(130, '*') << std::endl;
	cout << left << setw(26) << "Numero Unidade Curricular" << setw(30) << "Nome"<< setw(40) << "Curso" << setw(4) << "Ano" << setw(9) << "Semestre" << setw(5) << "ECTS" << setw(16) << "Numero e-folios" <<endl;
    cout << string(130, '-') << std::endl;

    if(count==0){

        cout << "\nATENCAO: Sem unidades curriculares na base." << endl;
        return;

    }else{

        Uc newuc[count+1];
        ifstream in("Ucs.txt");

        for(int i=0; i<count; i++){
            in >> newuc[i];
        }

        in.close();
        
        for(int i=0; i<count; i++){
            cout << left << setw(26) << newuc[i].uid << setw(30) << newuc[i].name << setw(40) << newuc[i].course << setw(4) << newuc[i].year << setw(9) << newuc[i].semester << setw(5) << newuc[i].ects << setw(16) << newuc[i].efolios <<endl;
        }

    }

}

void Uc::DeleteUc(int uid){

    int count = GetUcCount();

    if(count==0){

        cout << "\nATENCAO: Nenhuma unidade curricular na base para ser eliminada." << endl;
        return;

    }else{

        int ucexist=0;

        Uc newuc[count];

        ifstream in("Ucs.txt");

        for(int i=0; i<count; i++){
            in >> newuc[i];

            if(newuc[i].uid==uid){
                ucexist=1;
            }
        }
        
        in.close();

        if(ucexist==0){
            cout << "\nATENCAO: Nenhuma unidade curricular na base com esse numero" << endl;
            return;
        }
        
        ofstream out("Ucs.txt");
        
        for(int i=0; i<count; i++){

            if(newuc[i].uid==uid){
                
            }else{
                out << newuc[i];
            }
        }

        out.close();

        cout << "\nSUCESSO: Unidade Curricular " << uid << " eliminada com sucesso." << endl;

        UcDatabaseUpdate(0);
    }

}

void Uc::UpdateUc(int uid){

    int count = GetUcCount();
    int newuid;
    string newname;
    string newcourse;
    int newyear;
    int newsemester;
    int newects;
    int newefolios;

    if(count==0){

        cout << "\nATENCAO: Nenhuma unidade curricular na base para ser modificada." << endl;
        return;

    }else{

        int ucexist=0;

        Uc newuc[count];

        ifstream in("Ucs.txt");

        for(int i=0; i<count; i++){
            in >> newuc[i];

            if(newuc[i].uid==uid){

                newuid = newuc[i].uid;
                newname = newuc[i].name;
                newcourse = newuc[i].course;
                newyear = newuc[i].year;
                newsemester = newuc[i].semester;
                newefolios = newuc[i].efolios;
                newects = newuc[i].ects;
                ucexist=1;

            }
        }
        
        in.close();

        if(ucexist==0){
            cout << "\nATENCAO: Nenhuma unidade curricular na base com esse numero" << endl;
            return;
        }
        
        ofstream out("Ucs.txt");
        
        for(int i=0; i<count; i++){

            if(newuc[i].uid==uid){
                
            }else{
                out << newuc[i];
            }
        }

        out.close();

        UcDatabaseUpdate(0);
    }

    count = GetUcCount();

    int option=0;

    Input newinput;
    Course course;
    Uc newuc[count+1];
    ifstream in("Ucs.txt");

    for(int i=0; i<count; i++){
        in >> newuc[i];
    }

    in.close();
    
    cout << "Pretende modificar o numero identificador? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira o numero identificador da unidade curricular:" << endl;
        newuc[count].uid = newinput.GetNumber(9999999);

        if(VerifyExistanceUid(newuc[count].uid)==1){
            cout << "\nATENCAO: Ja existe uma unidade curricular com esse numero, pode sempre modificar ou eleminar." << endl;
            newuc[count].uid = newuid;
            newuc[count].name = newname;
            newuc[count].course = newcourse;
            newuc[count].year = newyear;
            newuc[count].semester = newsemester;
            newuc[count].ects = newects;
            newuc[count].efolios = newefolios;
            ofstream out("Ucs.txt");
    
            for(int i=0; i<count+1; i++){
                out << newuc[i];
            }

            out.close();
            return;
        }

    }else{
        newuc[count].uid = newuid;
    }
    
    option=0;

    cout << "Pretende modificar o nome? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira o nome da unidade curricular:" << endl;
        newuc[count].name = newinput.GetString(100);

        if(VerifyExistanceName(newuc[count].name)==1){
            cout << "\nATENCAO: Ja existe uma unidade curricular com esse nome, pode sempre modificar ou eleminar." << endl;
            newuc[count].uid = newuid;
            newuc[count].name = newname;
            newuc[count].course = newcourse;
            newuc[count].year = newyear;
            newuc[count].semester = newsemester;
            newuc[count].efolios = newefolios;
            newuc[count].ects = newects;
            ofstream out("Ucs.txt");
    
            for(int i=0; i<count+1; i++){
                out << newuc[i];
            }

            out.close();
            return;
        }
    }else{
        newuc[count].name = newname;
    }

    option=0;

    cout << "Pretende modificar o Curso? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira o curso a que pertence a unidade curricular:" << endl;
        newuc[count].course = newinput.GetString(100);

        if(course.VerifyExistance(newuc[count].course)==0){
            cout << "\nATENCAO: Esse curso nao existe, deve criar-lo em primeiro." << endl;
            newuc[count].uid = newuid;
            newuc[count].name = newname;
            newuc[count].course = newcourse;
            newuc[count].year = newyear;
            newuc[count].semester = newsemester;
            newuc[count].efolios = newefolios;
            newuc[count].ects = newects;
            ofstream out("Ucs.txt");
    
            for(int i=0; i<count+1; i++){
                out << newuc[i];
            }

            out.close();
            return;
        }
    }else{
        newuc[count].course = newcourse;
    }

    option=0;

    cout << "Pretende modificar o ano curricular? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira o ano curricular a que pertence (1,2,3,4):" << endl;
        newuc[count].year = newinput.GetNumber(4);
    }else{
        newuc[count].year = newyear;
    }

    option=0;

    cout << "Pretende modificar o semestre curricular? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira o semestre curricular a que pertence (1,2):" << endl;
        newuc[count].semester = newinput.GetNumber(2);
    }else{
        newuc[count].semester = newsemester;
    }

    option=0;

    cout << "Pretende modificar o numero de e-folios? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira o numero de e-folios (1,2,3):" << endl;
        newuc[count].efolios = newinput.GetNumber(3);
    }else{
        newuc[count].efolios = newefolios;
    }

    option=0;

    cout << "Pretende modificar o numero de ECTS? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira o numero de ECTS que a unidade vale:" << endl;
        newuc[count].ects = newinput.GetNumber(500);

        int courseects = course.GetECTS(newuc[count].course);
        int totalucects = GetCourseECTS(newuc[count].course);
        int esctscheck = totalucects + newuc[count].ects;
        esctscheck =  esctscheck - newects;

    if(esctscheck>courseects){
        cout << "\nATENCAO: Execedeu o limite de ECTS do curso, verifique o total de ECTS do curso e tente de novo." << endl;
        newuc[count].uid = newuid;
        newuc[count].name = newname;
        newuc[count].course = newcourse;
        newuc[count].year = newyear;
        newuc[count].semester = newsemester;
        newuc[count].efolios = newefolios;
        newuc[count].ects = newects;
        ofstream out("Ucs.txt");

        for(int i=0; i<count+1; i++){
            out << newuc[i];
        }

        out.close();
        return;
    }

    }else{
        newuc[count].ects = newects;
    }

    ofstream out("Ucs.txt");
    
    for(int i=0; i<count+1; i++){
        out << newuc[i];
    }

    out.close();
    cout << "\nSUCESSO: Curso " << uid << " modificado com sucesso." << endl;
    UcDatabaseUpdate(1);
    
}

void Uc::UcDatabaseUpdate(int operation){

    ifstream in("Database.txt");
    bool empty = in.peek() == std::ifstream::traits_type::eof();
    
    ofstream out("Temp.txt");

    if(empty==true){
        out << 0 << "\n" << 1 << "\n" << 0 << "\n" << 0 << endl;
        out.close();
        remove("Database.txt");
        rename("temp.txt", "Database.txt"); 
        return;
    }

    string data;
    int line=1;
    int newdata[4];

    while(getline(in, data)){

        if(line==2){
            if(operation==1){
                newdata[1]=stoi(data)+1;
            }else{
                newdata[1]=stoi(data)-1;
            }
        }else if(line==1){
            newdata[0]=stoi(data);
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

int Uc::GetUcCount(){

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

        if(line==2){
            int newdata=stoi(data);
            in.close();
            return newdata;
        }
        line=line+1;
    }

    in.close();
    return 0;
}

int Uc::VerifyExistanceName(string name){

    int count = GetUcCount();

    if(count==0){

        return 0;

    }else{

        int ucexist=0;

        Uc newuc[count];

        ifstream in("Ucs.txt");

        for(int i=0; i<count; i++){
            in >> newuc[i];

            if(newuc[i].name.compare(name)==0){
                ucexist=1;
            }
        }
        
        in.close();
        return ucexist;

    }

}

int Uc::VerifyExistanceUid(int uid){

    int count = GetUcCount();

    if(count==0){

        return 0;

    }else{

        int ucexist=0;

        Uc newuc[count];

        ifstream in("Ucs.txt");

        for(int i=0; i<count; i++){
            in >> newuc[i];

            if(newuc[i].uid==uid){
                ucexist=1;
            }
        }
        
        in.close();
        return ucexist;

    }

}

int Uc::GetECTS(int uid){

    int count = GetUcCount();

    if(count==0){

        return 0;

    }else{

        int ucexist=0;
        int passects;

        Uc newuc[count];

        ifstream in("Ucs.txt");

        for(int i=0; i<count; i++){
            in >> newuc[i];

            if(newuc[i].uid==uid){
                ucexist=1;
                passects = newuc[i].ects;
            }
        }
        
        in.close();

        if(ucexist==0){
            return 0;
        }

        return passects;
    }

}

string Uc::GetName(int uid){

    int count = GetUcCount();

    if(count==0){

        return "null";

    }else{

        int ucexist=0;
        string passname;

        Uc newuc[count];

        ifstream in("Ucs.txt");

        for(int i=0; i<count; i++){
            in >> newuc[i];

            if(newuc[i].uid==uid){
                ucexist=1;
                passname = newuc[i].name;
            }
        }
        
        in.close();

        if(ucexist==0){

            return "null";
        }

        return passname;
    }

}

string Uc::GetCourse(int uid){

    int count = GetUcCount();

    if(count==0){

        return "null";

    }else{

        int ucexist=0;
        string passcourse;

        Uc newuc[count];

        ifstream in("Ucs.txt");

        for(int i=0; i<count; i++){
            in >> newuc[i];

            if(newuc[i].uid==uid){
                ucexist=1;
                passcourse = newuc[i].course;
            }
        }
        
        in.close();

        if(ucexist==0){

            return "null";
        }

        return passcourse;
    }

}

int Uc::GetCourseECTS(string course){

    int count = GetUcCount();

    if(count==0){

        return 0;

    }else{

        int ucexist=0;
        int passects =0;

        Uc newuc[count];

        ifstream in("Ucs.txt");

        for(int i=0; i<count; i++){
            in >> newuc[i];

            if(newuc[i].course==course){
                ucexist=1;
                passects = passects + newuc[i].ects;
            }
        }
        
        in.close();

        if(ucexist==0){
            return 0;
        }

        return passects;
    }

}

int Uc::GetEfolios(int uid){

    int count = GetUcCount();

    if(count==0){

        return 0;

    }else{

        int ucexist=0;
        int passefolios;

        Uc newuc[count];

        ifstream in("Ucs.txt");

        for(int i=0; i<count; i++){
            in >> newuc[i];

            if(newuc[i].uid==uid){
                ucexist=1;
                passefolios = newuc[i].efolios;
            }
        }
        
        in.close();

        if(ucexist==0){
            return 0;
        }

        return passefolios;
    }

}

}