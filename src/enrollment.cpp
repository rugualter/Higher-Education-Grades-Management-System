/*
 * cenrollment.cpp
 * funcoes que faz operacoes sobre cursos
 *
 *  Created on: 18/12/2020
 *      Author: Rúdi Gualter
 */

#include "enrollment.h"

namespace std {

Enrollment::Enrollment(){}

Enrollment::~Enrollment(){}

void Enrollment::AddEnrollment(){

    int count = GetEnrollmentCount();

    if(count==0){

        Input newinput;
        Enrollment newenrollment;
        Uc uc;
        Student student;

        cout << "Insira o identificador da unidade curricular:" << endl;
        newenrollment.ucuid = newinput.GetNumber(9999999);

        if(uc.VerifyExistanceUid(newenrollment.ucuid)==0){
            cout << "\nATENCAO: Esta unidade curricular nao existe, por favor crie em primeiro." << endl;
            return;
        }

        cout << "Insira o identificador do estudante:" << endl;
        newenrollment.studentuid = newinput.GetNumber(9999999);

        if(student.VerifyExistanceUid(newenrollment.studentuid)==0){
            cout << "\nATENCAO: Este estudante nao existe, por favor crie em primeiro." << endl;
            return;
        }

        cout << "Insira o ano letivo (ex.: 2020/2021):" << endl;
        newenrollment.lectiveyear = newinput.GetDachedYear();

        if(VerifyExistance(newenrollment.ucuid, newenrollment.studentuid, newenrollment.lectiveyear)==1){
            cout << "\nATENCAO: Este estudante já está incrito nessa unidade curricular nesse ano letivo, pode sempre modificar ou eliminar." << endl;
            return;
        }

        cout << "Insira o tipo de avaliacao (1-Continua 0-Exame):" << endl;
        newenrollment.evaluationtype = newinput.GetNumber(1);

        newenrollment.efolioa = -1;
        newenrollment.efoliob = -1;
        newenrollment.efolioc = -1;
        newenrollment.pfolio = -1;
        newenrollment.secondpfolio = -1;
        newenrollment.exam = -1;
        newenrollment.secondexam = -1;

        ofstream out("Enrollments.txt");
        
        out << newenrollment;

        out.close();
        cout << "\nSUCESSO: Incricao realizada com sucesso"  << endl;
        EnrollmentDatabaseUpdate(1);

    }else{

        Input newinput;
        Enrollment newenrollment[count+1];
        Uc uc;
        Student student;
        ifstream in("Enrollments.txt");

        for(int i=0; i<count; i++){
            in >> newenrollment[i];
        }

        in.close();
        
        cout << "Insira o identificador da unidade curricular:" << endl;
        newenrollment[count].ucuid = newinput.GetNumber(9999999);

        if(uc.VerifyExistanceUid(newenrollment[count].ucuid)==0){
            cout << "\nATENCAO: Esta unidade curricular nao existe, por favor crie em primeiro." << endl;
            return;
        }

        cout << "Insira o identificador do estudante:" << endl;
        newenrollment[count].studentuid = newinput.GetNumber(9999999);

        if(student.VerifyExistanceUid(newenrollment[count].studentuid)==0){
            cout << "\nATENCAO: Este estudante nao existe, por favor crie em primeiro." << endl;
            return;
        }

        cout << "Insira o ano letivo (ex.: 2020/2021):" << endl;
        newenrollment[count].lectiveyear = newinput.GetDachedYear();

        if(VerifyExistance(newenrollment[count].ucuid, newenrollment[count].studentuid, newenrollment[count].lectiveyear)==1){
            cout << "\nATENCAO: Este estudante já está incrito nessa unidade curricular nesse ano letivo, pode sempre modificar ou eliminar." << endl;
            return;
        }

        cout << "Insira o tipo de avaliacao (1-Continua 0-Exame):" << endl;
        newenrollment[count].evaluationtype = newinput.GetNumber(1);

        newenrollment[count].efolioa = -1;
        newenrollment[count].efoliob = -1;
        newenrollment[count].efolioc = -1;
        newenrollment[count].pfolio = -1;
        newenrollment[count].secondpfolio = -1;
        newenrollment[count].exam = -1;
        newenrollment[count].secondexam = -1;

        ofstream out("Enrollments.txt");
        
        for(int i=0; i<count+1; i++){
            out << newenrollment[i];
        }

        out.close();
        cout << "\nSUCESSO: Inscricao realizada com sucesso"  << endl;
        EnrollmentDatabaseUpdate(1);
    }

}

void Enrollment::ShowEnrollments(){

    int count = GetEnrollmentCount();

    cout << "\n" << string(130, '*') << std::endl;
	cout << string(53, ' ') << "Lista de Todas as Inscricoes" << std::endl;
	cout << string(130, '*') << std::endl;
	cout << left << setw(40) << "Identificador de Estudante" << setw(40) << "Numero da Unidade Curricular"<< setw(15) << "Ano Letivo" << setw(5) << "Nota" <<endl;
    cout << string(130, '-') << std::endl;

    if(count==0){

        cout << "\nATENCAO: Sem incricoes na base." << endl;
        return;

    }else{

        Enrollment newenrollment[count+1];
        ifstream in("Enrollments.txt");

        for(int i=0; i<count; i++){
            in >> newenrollment[i];
        }

        in.close();
        
        for(int i=0; i<count; i++){
            
            cout << left << setw(40) << newenrollment[i].ucuid << setw(40) << newenrollment[i].studentuid << setw(15) << newenrollment[i].lectiveyear;

            float grade=GetGrade(newenrollment[i].ucuid, newenrollment[i].studentuid, newenrollment[i].lectiveyear);

            if(grade==-1){
                cout << setw(5) << "Sem avaliacao final" <<endl;
            }else{
                cout << setw(5) << setprecision(4) << grade <<endl;
            }

        }

    }

}

void Enrollment::DeleteEnrollment(int ucuid, int studentuid, string lectiveyear){

    int count = GetEnrollmentCount();

    if(count==0){

        cout << "\nATENCAO: Nenhuma inscricao na base para ser eliminada." << endl;
        return;

    }else{

        int enrollmentexist=0;

        Enrollment newenrollment[count];

        ifstream in("Enrollments.txt");

        for(int i=0; i<count; i++){
            in >> newenrollment[i];

            if(newenrollment[i].ucuid==ucuid && newenrollment[i].studentuid==studentuid && newenrollment[i].lectiveyear.compare(lectiveyear)==0){
                enrollmentexist=1;
            }
        }
        
        in.close();

        if(enrollmentexist==0){
            cout << "\nATENCAO: Nenhuma inscricao com essa combinacao" << endl;
            return;
        }
        
        ofstream out("Enrollments.txt");
        
        for(int i=0; i<count; i++){

            if(newenrollment[i].ucuid==ucuid && newenrollment[i].studentuid==studentuid && newenrollment[i].lectiveyear.compare(lectiveyear)==0){
                
            }else{
                out << newenrollment[i];
            }
        }

        out.close();

        cout << "\nSUCESSO: Incricao eliminada com sucesso." << endl;

        EnrollmentDatabaseUpdate(0);
    }

}

void Enrollment::UpdateEnrollment(int ucuid, int studentuid, string lectiveyear){

    cout << "\nATENCAO: ESTA PRESTE A MODIFICAR UMA INSCRICAO TOTALMENTE" << endl;
    cout << "ONDE PODERA MUDAR OS DADOS DA BASE DIRETAMENTE SEM RESTRICOES E VERIFICACOES" << endl;
    cout << "SE QUER ADICIONAR OU ALTERAR NOTA USE A OPCAO PROPRIA PARA TAL PAR SUA SEGURANCA" << endl;

    int count = GetEnrollmentCount();
    int newucuid;
    int newstudentuid;
    string newlectiveyear;
    int newevaluationtype;
    float newefolioa;
    float newefoliob;
    float newefolioc;
    float newpfolio;
    float newsecondpfolio;
    float newexam;
    float newsecondexam;

    if(count==0){

        cout << "\nATENCAO: Nenhuma inscricao na base para ser modificada." << endl;
        return;

    }else{

        int enrollmentexist=0;

        Enrollment newenrollment[count];

        ifstream in("Enrollments.txt");

        for(int i=0; i<count; i++){
            in >> newenrollment[i];

            if(newenrollment[i].ucuid==ucuid && newenrollment[i].studentuid==studentuid && newenrollment[i].lectiveyear.compare(lectiveyear)==0){

                newucuid = newenrollment[i].ucuid;
                newstudentuid = newenrollment[i].studentuid;
                newlectiveyear = newenrollment[i].lectiveyear;
                newevaluationtype = newenrollment[i].evaluationtype;
                newefolioa = newenrollment[i].efolioa;
                newefoliob = newenrollment[i].efoliob;
                newefolioc = newenrollment[i].efolioc;
                newpfolio = newenrollment[i].pfolio;
                newsecondpfolio = newenrollment[i].secondpfolio;
                newexam = newenrollment[i].exam;
                newsecondexam = newenrollment[i].secondexam;
                enrollmentexist=1;

            }
        }
        
        in.close();

        if(enrollmentexist==0){
            cout << "\nATENCAO: Nenhuma inscricao na base com essa combinacao" << endl;
            return;
        }
        
        ofstream out("Enrollments.txt");
        
        for(int i=0; i<count; i++){

            if(newenrollment[i].ucuid==ucuid && newenrollment[i].studentuid==studentuid && newenrollment[i].lectiveyear.compare(lectiveyear)==0){
                
            }else{
                out << newenrollment[i];
            }
        }

        out.close();

        EnrollmentDatabaseUpdate(0);
    }

    count = GetEnrollmentCount();

    int option=0;

    Input newinput;
    Enrollment newenrollment[count+1];
    Uc uc;
    Student student;
    ifstream in("Enrollments.txt");

    for(int i=0; i<count; i++){
        in >> newenrollment[i];
    }

    in.close();
    
    cout << "Pretende modificar o identificador da uidade curricular? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira o identificador da unidade curricular:" << endl;
        newenrollment[count].ucuid = newinput.GetNumber(9999999);

        if(uc.VerifyExistanceUid(newenrollment[count].ucuid)==0){
            cout << "\nATENCAO: Esta unidade curricular nao existe, por favor crie em primeiro." << endl;
            newenrollment[count].efolioa = newefolioa;
            newenrollment[count].efoliob = newefoliob;
            newenrollment[count].efolioc = newefolioc;
            newenrollment[count].pfolio = newpfolio;
            newenrollment[count].secondpfolio = secondpfolio;
            newenrollment[count].exam = newexam;
            newenrollment[count].secondexam = newsecondexam;
            newenrollment[count].ucuid = newucuid;
            newenrollment[count].studentuid = newstudentuid;
            newenrollment[count].lectiveyear = newlectiveyear;
            newenrollment[count].evaluationtype = newevaluationtype;
            return;
        }

    }else{
        newenrollment[count].ucuid = newucuid;
    }
    
    option=0;

    cout << "Pretende modificar o identificador do estudante? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira o identificador do estudante:" << endl;
        newenrollment[count].studentuid = newinput.GetNumber(9999999);

        if(student.VerifyExistanceUid(newenrollment[count].studentuid)==0){
            cout << "\nATENCAO: Este estudante nao existe, por favor crie em primeiro." << endl;
            newenrollment[count].efolioa = newefolioa;
            newenrollment[count].efoliob = newefoliob;
            newenrollment[count].efolioc = newefoliob;
            newenrollment[count].pfolio = newpfolio;
            newenrollment[count].secondpfolio = secondpfolio;
            newenrollment[count].exam = newexam;
            newenrollment[count].secondexam = newsecondexam;
            newenrollment[count].ucuid = newucuid;
            newenrollment[count].studentuid = newstudentuid;
            newenrollment[count].lectiveyear = newlectiveyear;
            newenrollment[count].evaluationtype = newevaluationtype;
            return;
        }
    }else{
        newenrollment[count].studentuid = newstudentuid;
    }

    option=0;

    cout << "Pretende modificar o ano letivo? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira o ano letivo (ex.: 2020/2021):" << endl;
        newenrollment[count].lectiveyear = newinput.GetDachedYear();
    }else{
        newenrollment[count].lectiveyear = newlectiveyear;
    }

    if(VerifyExistance(newenrollment[count].ucuid, newenrollment[count].studentuid, newenrollment[count].lectiveyear)==1){
        cout << "\nATENCAO: Este estudante já está incrito nessa unidade curricular nesse ano letivo, pode sempre modificar ou eliminar." << endl;
        newenrollment[count].efolioa = newefolioa;
        newenrollment[count].efoliob = newefoliob;
        newenrollment[count].efolioc = newefolioc;
        newenrollment[count].pfolio = newpfolio;
        newenrollment[count].secondpfolio = secondpfolio;
        newenrollment[count].exam = newexam;
        newenrollment[count].secondexam = newsecondexam;
        newenrollment[count].ucuid = newucuid;
        newenrollment[count].studentuid = newstudentuid;
        newenrollment[count].lectiveyear = newlectiveyear;
        newenrollment[count].evaluationtype = newevaluationtype;
        return;
    }

    option=0;

    cout << "Pretende modificar o tipo de avaliacao? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira o tipo de avaliacao (1-Continua 0-Exame):" << endl;
        newenrollment[count].evaluationtype = newinput.GetNumber(1);
    }else{
        newenrollment[count].evaluationtype = newevaluationtype;
    }

    option=0;

    cout << "Pretende modificar a nota do e-Folio A? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira a nota (pode ser decimal):" << endl;
        newenrollment[count].efolioa = newinput.GetDecimal(8);
    }else{
        newenrollment[count].efolioa = newefolioa;
    }

    option=0;

    cout << "Pretende modificar a nota do e-Folio B? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira a nota (pode ser decimal):" << endl;
        newenrollment[count].efoliob = newinput.GetDecimal(8);
    }else{
        newenrollment[count].efoliob = newefoliob;
    }

    option=0;

    cout << "Pretende modificar a nota do e-Folio C? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira a nota (pode ser decimal):" << endl;
        newenrollment[count].efolioc = newinput.GetDecimal(8);
    }else{
        newenrollment[count].efolioc = newefolioc;
    }

    option=0;

    cout << "Pretende modificar a nota do p-Folio? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira a nota (pode ser decimal):" << endl;
        newenrollment[count].pfolio = newinput.GetDecimal(12);
    }else{
        newenrollment[count].pfolio = newpfolio;
    }

    option=0;

    cout << "Pretende modificar a nota do p-Folio de Recurso? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira a nota (pode ser decimal):" << endl;
        newenrollment[count].secondpfolio = newinput.GetDecimal(12);
    }else{
        newenrollment[count].secondpfolio = newsecondpfolio;
    }

    option=0;

    cout << "Pretende modificar a nota de exame? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira a nota (pode ser decimal):" << endl;
        newenrollment[count].exam = newinput.GetDecimal(20);
    }else{
        newenrollment[count].exam = newexam;
    }

    option=0;

    cout << "Pretende modificar a nota de Exame de Recurso? (1-Sim 0-Nao):" << endl;
    option=newinput.GetNumber(1);

    if(option==1){
        cout << "Insira a nota (pode ser decimal):" << endl;
        newenrollment[count].secondexam = newinput.GetDecimal(20);
    }else{
        newenrollment[count].secondexam = newsecondexam;
    }

    ofstream out("Enrollments.txt");
    
    for(int i=0; i<count+1; i++){
        out << newenrollment[i];
    }

    out.close();
    cout << "\nSUCESSO: Incricao modificada com sucesso." << endl;
    EnrollmentDatabaseUpdate(1);
    

}

void Enrollment::EnrollmentDatabaseUpdate(int operation){

    ifstream in("Database.txt");
    bool empty = in.peek() == std::ifstream::traits_type::eof();
    
    ofstream out("Temp.txt");

    if(empty==true){
        out << 0 << "\n" << 0 << "\n" << 0 << "\n" << 1 << endl;
        out.close();
        remove("Database.txt");
        rename("temp.txt", "Database.txt"); 
        return;
    }

    string data;
    int line=1;
    int newdata[4];

    while(getline(in, data)){

        if(line==4){
            if(operation==1){
                newdata[3]=stoi(data)+1;
            }else{
                newdata[3]=stoi(data)-1;
            }
        }else if(line==2){
            newdata[1]=stoi(data);
        }else if(line==3){
            newdata[2]=stoi(data);
        }else{
            newdata[0]=stoi(data);
        }

        line=line+1;
    }
    out << newdata[0] << "\n" << newdata[1] << "\n" << newdata[2] << "\n" << newdata[3] << endl;

    in.close();
    out.close();
    remove("Database.txt");
    rename("temp.txt", "Database.txt"); 

}

int Enrollment::GetEnrollmentCount(){

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

        if(line==4){
            int newdata=stoi(data);
            in.close();
            return newdata;
        }
        line=line+1;
    }

    in.close();
    return 0;
}

int Enrollment::VerifyExistance(int ucuid, int studentuid, string lectiveyear){

    int count = GetEnrollmentCount();

    if(count==0){

        return 0;

    }else{

        int enrollmentexist=0;

        Enrollment newenrollment[count];

        ifstream in("Enrollments.txt");

        for(int i=0; i<count; i++){
            in >> newenrollment[i];

            if(newenrollment[i].ucuid==ucuid && newenrollment[i].studentuid==studentuid && newenrollment[i].lectiveyear.compare(lectiveyear)==0){
                enrollmentexist=1;
            }
        }
        
        in.close();
        return enrollmentexist;

    }

}

void Enrollment::AddGrade(int ucuid, int studentuid, string lectiveyear){

    int count = GetEnrollmentCount();
    int newucuid=-1;
    int newstudentuid=-1;
    string newlectiveyear;
    int newevaluationtype=-1;
    float newefolioa=-1;
    float newefoliob=-1;
    float newefolioc=-1;
    float newpfolio=-1;
    float newsecondpfolio=-1;
    float newexam=-1;
    float newsecondexam=-1;
    int option=0;
    int improvement=0;

    if(count==0){

        cout << "\nATENCAO: Nenhuma inscricao na base para se poder adicionar ou atualizar nota." << endl;
        return;

    }else{

        Input newinput;

        int enrollmentexist=0;

        Enrollment newenrollment[count];

        ifstream in("Enrollments.txt");

        for(int i=0; i<count; i++){
            in >> newenrollment[i];

            if(newenrollment[i].ucuid==ucuid && newenrollment[i].studentuid==studentuid && newenrollment[i].lectiveyear.compare(lectiveyear)==0){

                newucuid = newenrollment[i].ucuid;
                newstudentuid = newenrollment[i].studentuid;
                newlectiveyear = newenrollment[i].lectiveyear;
                newevaluationtype = newenrollment[i].evaluationtype;
                newefolioa = newenrollment[i].efolioa;
                newefoliob = newenrollment[i].efoliob;
                newefolioc = newenrollment[i].efolioc;
                newpfolio = newenrollment[i].pfolio;
                newsecondpfolio = newenrollment[i].secondpfolio;
                newexam = newenrollment[i].exam;
                newsecondexam = newenrollment[i].secondexam;
                enrollmentexist=1;

            }
        }
  
        in.close();

        if(enrollmentexist==0){
            cout << "\nATENCAO: Nenhuma inscricao na base com essa combinacao" << endl;
            return;
        }

        cout << "\nQue nota pretende adicionar ou atualizar?" << endl;
        cout << string(50, '-') << std::endl;
        cout << setw(16) << "0 - e-folio A" << setw(16)  << "1 - e-folio B " << setw(16)  << "2 - e-folio C " << endl;
        cout << setw(16) << "3 - p-folio" << setw(16) << "4 - p-folio Recurso" << endl;
        cout << setw(16) << "5 - Exame" << setw(16) << "6 - Exame Recurso" << endl;
        cout << string(50, '-') << std::endl;
        option=newinput.GetNumber(5);

        if(newevaluationtype==1 && option>=5){
            cout << "\nATENCAO: Esta a tentar modificar uma nota de exame e o estudante e de avaliacao continua, pode sempre modificar o tipo de avaliacao na opcao Modificar Incricao" << endl;
            return;
        }

        if(newevaluationtype==0 && option<=4){
            cout << "\nATENCAO: Esta a tentar modificar uma nota de folio e o estudante e de avaliacao por exame, pode sempre modificar o tipo de avaliacao na opcao Modificar Incricao" << endl;
            return;
        }

        if(option==0){
            
            if(newefolioa>-1){
                cout << "\nATENCAO: Esta nota ja foi lancada deseja altera-la? (1-Sim 0-Nao)" << endl;
                int checkeroption = newinput.GetNumber(1);
                if(checkeroption==0){
                    return;
                }
            }
        }

        if(option==1){
            
            if(newefolioa==-1){
                cout << "\nATENCAO: Nao esta lacada a nota do e-folio A lance-a primeiro." << endl;
                return;
            }

            if(newefoliob>-1){
                cout << "\nATENCAO: Esta nota ja foi lancada deseja altera-la? (1-Sim 0-Nao)" << endl;
                int checkeroption = newinput.GetNumber(1);
                if(checkeroption==0){
                    return;
                }
            }

        }

        if(option==2){
            Uc uc;
            if(uc.GetEfolios(newucuid)!=3){
                cout << "\nATENCAO: Esta e uma unidade curricular de 2 e-folios, nao pode adiconar nota ao e-folio C." << endl;
                return;
            }
            
            if(newefoliob==-1 || newefolioa==-1){
                cout << "\nATENCAO: Nao estao lacadas notas de e-folios anteriores, lance-as primeiro." << endl;
                return;
            }

            if(newefolioc>-1){
                cout << "\nATENCAO: Esta nota ja foi lancada deseja altera-la? (1-Sim 0-Nao)" << endl;
                int checkeroption = newinput.GetNumber(1);
                if(checkeroption==0){
                    return;
                }
            }

        }

        if(option==3){
            Uc uc;
            if(uc.GetEfolios(newucuid)==3){
                if(newefolioa==-1 || newefoliob==-1 || newefolioc==-1 ){
                cout << "\nATENCAO: Notas de e-folios por lancar, lance-as primeiro." << endl;
                return;
                }
            }

            if(uc.GetEfolios(newucuid)==2){
                if(newefolioa==-1 || newefoliob==-1){
                cout << "\nATENCAO: Notas de e-folios por lancar, lance-as primeiro." << endl;
                return;
                }
            }

            float grade=0;

            if(uc.GetEfolios(newucuid)==3){
                grade=newefolioa+newefoliob+newefolioc+newpfolio;
            }

            if(uc.GetEfolios(newucuid)==2){
                grade=newefolioa+newefoliob+newpfolio;
            }

            if(newpfolio >=5.5 && grade>=9.5){
                cout << "\nATENCAO: Esta nota ja foi lancada. E melhoria? (1-Sim 0-Nao)" << endl;
                int checkeroption = newinput.GetNumber(1);
                if(checkeroption==0){
                    cout << "\nATENCAO: Assinalou que nao e melhoria deseja mesmo assim altera-la? (1-Sim 0-Nao)" << endl;
                    int checkeroptionagain = newinput.GetNumber(1);
                    if(checkeroptionagain==0){
                        return;
                    }else{
                        
                    }
                }else{
                    improvement =1;
                }
            }

            if(newpfolio >-1 && grade<9.5){
                cout << "\nATENCAO: Esta nota ja foi lancada, deseja altera-la? (1-Sim 0-Nao)" << endl;
                int checkeroption = newinput.GetNumber(1);
                if(checkeroption==0){
                    return;
                }
            }

        }

        if(option==4){
            
            Uc uc;
            float grade=0;

            if(uc.GetEfolios(newucuid)==3){
                grade=newefolioa+newefoliob+newefolioc+newpfolio;
            }

            if(uc.GetEfolios(newucuid)==2){
                grade=newefolioa+newefoliob+newpfolio;
            }

            if(newpfolio==-1){
                cout << "\nATENCAO: Nota de p-folio por lancar, lance-a primeiro." << endl;
                return;
            }

            if(newpfolio >=5.5 && grade>=9.5){
                cout << "\nATENCAO: O estudante ja esta aprovado nesta unidade curricular, as melhorias devem ser realizadas no p-folio e nao no seu recurso." << endl;
                return;
            }

            if(newsecondpfolio>-1){
                cout << "\nATENCAO: Esta nota ja foi lancada, Deseja altera-la? (1-Sim 0-Nao)" << endl;
                int checkeroption = newinput.GetNumber(1);
                if(checkeroption==0){
                    return;
                }
            }

        }

        if(option==5){
            
            if(newexam >=9.5){
                cout << "\nATENCAO: Esta nota ja foi lancada. E melhoria? (1-Sim 0-Nao)" << endl;
                int checkeroption = newinput.GetNumber(1);
                if(checkeroption==0){
                    cout << "\nATENCAO: Assinalou que nao e melhoria deseja mesmo assim altera-la? (1-Sim 0-Nao)" << endl;
                    int checkeroptionagain = newinput.GetNumber(1);
                    if(checkeroptionagain==0){
                        return;
                    }else{
                        
                    }
                }else{
                    improvement =1;
                }

            }

            if(newexam >-1 && newexam<9.5){
                cout << "\nATENCAO: Esta nota ja foi lancada, deseja altera-la? (1-Sim 0-Nao)" << endl;
                int checkeroption = newinput.GetNumber(1);
                if(checkeroption==0){
                    return;
                }
            }

        }

        if(option==6){
            
            if(newexam==-1){
                cout << "\nATENCAO: Nota de exame por lancar, lance-a primeiro." << endl;
                return;
            }

            if(exam>=9.5){
                cout << "\nATENCAO: Este estudante ja foi aprovado nesta unidade curricular, para melhoria deve usar a nota de exame e nao o recurso." << endl;
                return;
            }

            if(newsecondexam>-1){
                cout << "\nATENCAO: Esta nota ja foi lancada, Deseja altera-la? (1-Sim 0-Nao)" << endl;
                int checkeroption = newinput.GetNumber(1);
                if(checkeroption==0){
                    return;
                }
            }

        }

        ofstream out("Enrollments.txt");
        
        for(int i=0; i<count; i++){

            if(newenrollment[i].ucuid==ucuid && newenrollment[i].studentuid==studentuid && newenrollment[i].lectiveyear.compare(lectiveyear)==0){
                
            }else{
                out << newenrollment[i];
            }
        }

        out.close();

        EnrollmentDatabaseUpdate(0);
    }

    count = GetEnrollmentCount();

    Input newinput;
    Enrollment newenrollment[count+1];

    ifstream in("Enrollments.txt");

    for(int i=0; i<count; i++){
        in >> newenrollment[i];
    }

    in.close();
    
    if(option==0){

        cout << "Insira a nota do e-folio A (pode ser decimal):" << endl;
        newenrollment[count].efolioa = newinput.GetDecimal(8);
        newenrollment[count].efoliob = newefoliob;
        newenrollment[count].efolioc = newefolioc;
        newenrollment[count].pfolio = newpfolio;
        newenrollment[count].secondpfolio = newsecondpfolio;
        newenrollment[count].exam = newexam;
        newenrollment[count].secondexam = newsecondexam;

    }else if(option==1){

        cout << "Insira a nota do e-folio B (pode ser decimal):" << endl;
        Uc uc;
        bool valid=false;
        float efoliograde=0;
        do{

            if(uc.GetEfolios(newucuid)==3){
                efoliograde = newinput.GetDecimal(8);
                float gradecheck;
                if(newefolioc>-1){
                    gradecheck = newefolioa + efoliograde + newefolioc;
                    if(gradecheck<=8){
                        valid=true;
                    }
                }else{
                    gradecheck = newefolioa + efoliograde;
                    if(gradecheck<8){
                        valid=true;
                    }
                }
            }

            if(uc.GetEfolios(newucuid)==2){
                efoliograde = newinput.GetDecimal(8);
                float gradecheck = newefolioa + efoliograde;
                if(gradecheck<=8){
                        valid=true;
                }
            }
        cout << "\nATENCAO: O valor colocado excede o total de 8 valores para o conjunto de e-folios, insira de novo:" << endl;

        }while(!valid);

        newenrollment[count].efoliob = efoliograde;
        newenrollment[count].efolioa = newefolioa;
        newenrollment[count].efolioc = newefolioc;
        newenrollment[count].pfolio = newpfolio;
        newenrollment[count].secondpfolio = newsecondpfolio;
        newenrollment[count].exam = newexam;
        newenrollment[count].secondexam = newsecondexam;

    }else if(option==2){

        cout << "Insira a nota do e-folio C (pode ser decimal):" << endl;

        Uc uc;
        bool valid=false;
        float efoliograde=0;
        do{

            if(uc.GetEfolios(newucuid)==3){
                efoliograde = newinput.GetDecimal(8);
                float gradecheck;
                if(newefolioc>-1){
                    gradecheck = newefolioa + efoliograde + newefoliob;
                    if(gradecheck<=8){
                        valid=true;
                    }
                }
            }
        cout << "\nATENCAO: O valor colocado excede o total de 8 valores para o conjunto de e-folios, insira de novo:" << endl;

        }while(!valid);

        newenrollment[count].efolioc = efoliograde;
        newenrollment[count].efolioa = newefolioa;
        newenrollment[count].efoliob = newefoliob;
        newenrollment[count].pfolio = newpfolio;
        newenrollment[count].secondpfolio = newsecondpfolio;
        newenrollment[count].exam = newexam;
        newenrollment[count].secondexam = newsecondexam;

    }else if(option==3){

        cout << "Insira a nota do p-folio (pode ser decimal):" << endl;
        newenrollment[count].efolioa = newefolioa;
        newenrollment[count].efoliob = newefoliob;
        newenrollment[count].efolioc = newefolioc;
        if(improvement==1){
            float input = newinput.GetDecimal(12);
            if(input>newpfolio){
                newenrollment[count].pfolio = input;
            }else{
                newenrollment[count].pfolio = newpfolio;
            }
        }else{
            newenrollment[count].pfolio = newinput.GetDecimal(12);
        }
        newenrollment[count].secondpfolio = newsecondpfolio;
        newenrollment[count].exam = newexam;
        newenrollment[count].secondexam = newsecondexam;

    }else if(option==4){

        cout << "Insira a nota do p-folio de Recurso (pode ser decimal):" << endl;
        newenrollment[count].efolioa = newefolioa;
        newenrollment[count].efoliob = newefoliob;
        newenrollment[count].efolioc = newefolioc;
        newenrollment[count].pfolio = newpfolio;
        newenrollment[count].secondpfolio = newinput.GetDecimal(12);
        newenrollment[count].exam = newexam;
        newenrollment[count].secondexam = newsecondexam;

    }else if(option==5){

        cout << "Insira a nota do p-folio (pode ser decimal):" << endl;
        newenrollment[count].efolioa = newefolioa;
        newenrollment[count].efoliob = newefoliob;
        newenrollment[count].efolioc = newefolioc;
        if(improvement==1){
            float input = newinput.GetDecimal(20);
            if(input>exam){
                newenrollment[count].exam = input;
            }else{
                newenrollment[count].exam = newexam;
            }
        }else{
            newenrollment[count].exam = newinput.GetDecimal(20);
        }
        newenrollment[count].secondpfolio = newsecondpfolio;
        newenrollment[count].pfolio = newpfolio;
        newenrollment[count].secondexam = newsecondexam;

    }else{

        cout << "Insira a nota do p-folio de Recurso (pode ser decimal):" << endl;
        newenrollment[count].efolioa = newefolioa;
        newenrollment[count].efoliob = newefoliob;
        newenrollment[count].efolioc = newefolioc;
        newenrollment[count].pfolio = newpfolio;
        newenrollment[count].secondpfolio = newsecondpfolio;
        newenrollment[count].exam = newexam;
        newenrollment[count].secondexam = newinput.GetDecimal(12);

    }

    if(newevaluationtype==1){
        Uc uc;
        if(uc.GetEfolios(newucuid)==3){
            if(newenrollment[count].efolioa >-1 && newenrollment[count].efoliob >-1 && newenrollment[count].efoliob>-1){
                float checkvaluation = newenrollment[count].efolioa + newenrollment[count].efoliob + newenrollment[count].efoliob;

                if(checkvaluation < 3.5){
                    newenrollment[count].evaluationtype=0;
                }else{
                    newenrollment[count].evaluationtype = newevaluationtype;
                }
            }
        }
        if(uc.GetEfolios(newucuid)==2){
            if(newenrollment[count].efolioa >-1 && newenrollment[count].efoliob >-1){
                float checkvaluation = newenrollment[count].efolioa + newenrollment[count].efoliob;

                if(checkvaluation < 3.5){
                    newenrollment[count].evaluationtype=0;
                }else{
                    newenrollment[count].evaluationtype = newevaluationtype;
                }
            }
        }

    }

    newenrollment[count].ucuid = newucuid;
    newenrollment[count].studentuid = newstudentuid;
    newenrollment[count].lectiveyear = newlectiveyear;

    ofstream out("Enrollments.txt");
    
    for(int i=0; i<count+1; i++){
        out << newenrollment[i];
    }

    out.close();
    cout << "\nSUCESSO: Nota adicionada/alterada com sucesso." << endl;
    EnrollmentDatabaseUpdate(1);
    

}

float Enrollment::GetGrade(int ucuid, int studentuid, string lectiveyear){

    int count = GetEnrollmentCount();
    float grade = -1;

    if(count==0){

        return -2;

    }else{

        Enrollment newenrollment[count+1];
        Uc uc;
        ifstream in("Enrollments.txt");

        for(int i=0; i<count; i++){
            in >> newenrollment[i];
        }

        in.close();
        
        for(int i=0; i<count; i++){
            
           if(newenrollment[i].ucuid==ucuid && newenrollment[i].studentuid==studentuid && newenrollment[i].lectiveyear.compare(lectiveyear)==0){

               if(newenrollment[i].evaluationtype==1){

                   if(uc.GetEfolios(newenrollment[i].ucuid)==3 && newenrollment[i].efolioa>-1 && newenrollment[i].efoliob>-1 && newenrollment[i].efolioc>-1){
                        
                        float checkerefolios = newenrollment[i].efolioa + newenrollment[i].efoliob + newenrollment[i].efolioc;
                        if(newenrollment[i].secondpfolio > -1 && checkerefolios >= 3.5 && newenrollment[i].pfolio < 5.5){

                            grade = newenrollment[i].secondpfolio + newenrollment[i].efolioa + newenrollment[i].efoliob + newenrollment[i].efolioc;
                            
                        }

                        if(newenrollment[i].secondpfolio == -1 && newenrollment[i].pfolio >= 5.5 && newenrollment[i].pfolio <= 12){

                            grade = newenrollment[i].pfolio + newenrollment[i].efolioa + newenrollment[i].efoliob + newenrollment[i].efolioc;
                            
                        }
                   }

                   if(uc.GetEfolios(newenrollment[i].ucuid)==2 && newenrollment[i].efolioa>-1 && newenrollment[i].efoliob>-1 && newenrollment[i].efolioc==-1){
                        
                        float checkerefolios = newenrollment[i].efolioa + newenrollment[i].efoliob;
                        if(newenrollment[i].secondpfolio > -1 && checkerefolios >= 3.5 && newenrollment[i].pfolio < 5.5){

                            grade = newenrollment[i].secondpfolio + newenrollment[i].efolioa + newenrollment[i].efoliob;
                            
                        }

                        if(newenrollment[i].secondpfolio == -1 && newenrollment[i].pfolio >= 5.5 && newenrollment[i].pfolio <= 12){

                            grade = newenrollment[i].pfolio + newenrollment[i].efolioa + newenrollment[i].efoliob;
                            
                        }

                   }

               }else{

                if(newenrollment[i].secondexam > -1 && newenrollment[i].exam > -1 && newenrollment[i].exam < 9.5){

                    grade = newenrollment[i].secondexam;
                    
                }

                if(newenrollment[i].secondexam == -1 && newenrollment[i].exam >= 9.5 && newenrollment[i].exam <= 20){

                    grade = newenrollment[i].exam;
                    
                }

                float checkerefolios=-1;
                if(uc.GetEfolios(newenrollment[i].ucuid)==3){
                    checkerefolios = newenrollment[i].efolioa + newenrollment[i].efoliob + newenrollment[i].efolioc;
                    }

                if(uc.GetEfolios(newenrollment[i].ucuid)==2){
                    checkerefolios = newenrollment[i].efolioa + newenrollment[i].efoliob;
                }

                if(checkerefolios<3.5 && checkerefolios>-1 && newenrollment[i].secondexam > -1 && newenrollment[i].exam==-1){
                    grade = newenrollment[i].secondexam;
                }

               }

           }

        }

        return grade;

    }

    return grade;
}

void Enrollment::GetStudentInfo(int uid){
    
    Student student;
    Uc uc;
    Course courses;
    int count = GetEnrollmentCount();
    int enrollmentexist=0;
    Enrollment newenrollment[count];

    if(student.VerifyExistanceUid(uid)==0){
        cout << "\nATENCAO: Esse estudante nao existe, considere em cria-lo." << endl;
        return;
    }

    if(count==0){
        
        cout << "\nATENCAO: Sem incricoes na base." << endl;
        return;

    }else{
     
        ifstream in("Enrollments.txt");

        for(int i=0; i<count; i++){
            in >> newenrollment[i];
            if(newenrollment[i].studentuid==uid){
                enrollmentexist=1;
            }
        }
        in.close();
    }

    if(enrollmentexist==0){
        cout << "\nATENCAO: Sem incricoes para esse numero de aluno, considere increve-lo." << endl;
        return;
    }

    string name = student.GetName(uid);
    string location = student.GetLocation(uid);
    string course = student.GetCourse(uid);
    int courceects = courses.GetECTS(course);
    int doneects = 0;
    float avarage = 0;
    float avarageects = 0;
    int countavarage = 0;

    cout << "\n" << string(130, '*') << endl;
	cout << string(53, ' ') << "Informacoes de Estudante" << endl;
	cout << string(130, '*') << endl;
	cout << "\nNome: " << name << endl;
    cout << "Localizacao: " << location << endl;
    cout << "Curso: " << course << "\n" << endl;
    cout << string(130, '-') << endl;
    cout << string(48, ' ') << "Incricoes em Unidades Curriculares" << endl;
    cout << string(130, '-') << endl;
    cout << left << setw(30) << "" << setw(11) << ""<< setw(15) << "" << setw(18) << "e-folio" << setw(20) << "p-folio" << setw(20) << "Exame" <<endl;
    cout << left << setw(30) << "Nome" << setw(11) << "Ano Letivo"<< setw(15) << "Tipo Avaliacao" << setw(6) << "A" << setw(6) << "B" << setw(6) << "C" << setw(10) << "Normal" << setw(10) << "Recurso" << setw(10) << "Normal" << setw(10) << "Recuro" << setw(5) << "Nota" << setw(11) << "Estado" <<endl;
    cout << string(130, '-') << endl;

    for(int i=0; i<count; i++){
    if(newenrollment[i].studentuid==uid){
        string ucname = uc.GetName(newenrollment[i].ucuid);
        float grade = GetGrade(newenrollment[i].ucuid, newenrollment[i].studentuid, newenrollment[i].lectiveyear);

        if(grade >-1){
            avarage = avarage + grade;
            countavarage = countavarage + 1;
            int ectsc = uc.GetECTS(newenrollment[i].ucuid);
            float calcavarage = grade * ectsc;
            avarageects = avarageects + calcavarage;
            doneects = doneects + ectsc;
        }

        cout << left << setw(30) << ucname << setw(11) << newenrollment[i].lectiveyear;
        if(newenrollment[i].evaluationtype==1){
            cout << setw(15) << "Continua";
            if(newenrollment[i].efolioa==-1){
                cout << setw(6) << "-";
            }else{
                cout << setw(6) << setprecision(4) << newenrollment[i].efolioa;
            }
            if(newenrollment[i].efoliob==-1){
                cout << setw(6) << "-";
            }else{
                cout << setw(6) << setprecision(4) << newenrollment[i].efoliob;
            }

            if(uc.GetEfolios(newenrollment[i].ucuid)==3){
                if(newenrollment[i].efolioc==-1){
                    cout << setw(6) << "-";
                }else{
                    cout << setw(6) << setprecision(4) << newenrollment[i].efolioc;
                }
            }else{
                cout << setw(6) << "N/A";
            }

            if(newenrollment[i].pfolio==-1){
                cout << setw(10) << "-";
            }else{
                cout << setw(10) << setprecision(4) << newenrollment[i].pfolio;
            }
            if(newenrollment[i].secondpfolio==-1){
                cout << setw(10) << "-";
            }else{
                cout << setw(10) << setprecision(4) << newenrollment[i].secondpfolio;
            }
            cout << setw(10) << "N/A" << setw(10) << "N/A";
        }else{
            cout << setw(15) << "Exame";
            if(newenrollment[i].efolioa==-1){
                cout << setw(6) << "N/A";
            }else{
                cout << setw(6) << setprecision(4) << newenrollment[i].efolioa;
            }
            if(newenrollment[i].efoliob==-1){
                cout << setw(6) << "N/A";
            }else{
                cout << setw(6) << setprecision(4) << newenrollment[i].efoliob;
            }
            if(newenrollment[i].efolioc==-1){
                cout << setw(6) << "N/A";
            }else{
                cout << setw(6) << setprecision(4) << newenrollment[i].efolioc;
            }
            cout << setw(10) << "N/A" << setw(16) << "N/A";
            if(newenrollment[i].exam==-1){
                cout << setw(10) << "-";
            }else{
                cout << setw(10) << setprecision(4) << newenrollment[i].exam;
            }
            if(newenrollment[i].secondexam==-1){
                cout << setw(10) << "-";
            }else{
                cout << setw(10) << setprecision(4) << newenrollment[i].secondexam;
            }
        }

        if(grade==-1){
            cout << setw(5) << "-" << setw(11) << "-" <<endl;
        }else if(grade>=9.5){
            cout << setw(5) << setprecision(4) << grade << setw(11) << "Aprovado" << endl;
        }else{
            cout << setw(5) << setprecision(4) << grade << setw(11) << "Reprovado" <<endl;
        }
        
    }
    }

    avarage = avarage/countavarage;
    courceects = courceects-doneects;
    avarageects = avarageects/doneects;

    cout << "\n" << string(130, '-') << endl;
    if(isnan(avarage)){
        cout << "\nMedia (ECTS): " << "-" << endl;
    }else{
        cout << "\nMedia (ECTS): " << setprecision(4) << avarageects << endl;
    }
    if(isnan(avarage)){
        cout << "Media Ponderada: " << "-" << endl;
    }else{
        cout << "Media Ponderada: " << setprecision(4) << avarage << endl;
    }
    cout << "ECTS realizados: " << doneects << endl;
    cout << "ECTS por realizar: " << courceects << "\n" << endl;
    cout << string(130, '-') << endl;

    if(doneects==courceects){
        cout << "\n" << string(130, '*') << endl;
	    cout << string(47, ' ') << "Parabens o estudante acabou o curso!" << endl;
	    cout << string(130, '*') << endl;
    }
}

void Enrollment::GetUcInfo(int uid, string yearlective){
    
    Student student;
    Uc uc;
    Course courses;
    int count = GetEnrollmentCount();
    int enrollmentexist=0;
    int studentcount=0;
    Enrollment newenrollment[count];

    if(uc.VerifyExistanceUid(uid)==0){
        cout << "\nATENCAO: Essa unidade curricular nao existe, considere cria-la." << endl;
        return;
    }

    if(count==0){
        
        cout << "\nATENCAO: Sem incricoes na base." << endl;
        return;

    }else{
     
        ifstream in("Enrollments.txt");

        for(int i=0; i<count; i++){
            in >> newenrollment[i];
            if(newenrollment[i].ucuid==uid && newenrollment[i].lectiveyear==yearlective){
                enrollmentexist=1;
            }
        }
        in.close();
    }

    if(enrollmentexist==0){
        cout << "\nATENCAO: Sem incricoes para essa unidade curricular nesse ano letivo, considere increver alguem." << endl;
        return;
    }

    string name = uc.GetName(uid);
    string course = uc.GetCourse(uid);
    int ucects = uc.GetECTS(uid);
    float avarage = 0;
    int countavarage = 0;

    cout << "\n" << string(130, '*') << endl;
	cout << string(48, ' ') << "Informacoes de Unidade Curricular" << endl;
	cout << string(130, '*') << endl;
	cout << "\nNome: " << name << endl;
    cout << "Curso: " << course << endl;
    cout << "ECTS: " << ucects << endl;
    cout << "Ano Letivo: " << yearlective << "\n" << endl;
    cout << string(130, '-') << endl;
    cout << string(48, ' ') << "Incricoes na Unidades Curriculares" << endl;
    cout << string(130, '-') << endl;
    cout << left << setw(40) << "Nome" << setw(15) << "Tipo Avaliacao" << setw(18) << "e-folio" << setw(20) << "p-folio" << setw(20) << "Exame" <<endl;
    cout << left << setw(40) << "Nome" << setw(15) << "Tipo Avaliacao" << setw(6) << "A" << setw(6) << "B" << setw(6) << "C" << setw(10) << "Normal" << setw(10) << "Recurso" << setw(6) << "Normal" << setw(10) << "Recuro" << setw(5) << "Nota" << setw(12) << "Estado" <<endl;
    cout << string(130, '-') << endl;

    for(int i=0; i<count; i++){
    if(newenrollment[i].ucuid==uid && newenrollment[i].lectiveyear==yearlective){
        
        studentcount = studentcount+1;
        string studentname = student.GetName(newenrollment[i].studentuid);
        float grade = GetGrade(newenrollment[i].ucuid, newenrollment[i].studentuid, newenrollment[i].lectiveyear);

        if(grade >-1){
            avarage = avarage + grade;
            countavarage = countavarage + 1;
        }

        cout << left << setw(40) << studentname;
        if(newenrollment[i].evaluationtype==1){
            cout << setw(15) << "Continua";
            if(newenrollment[i].efolioa==-1){
                cout << setw(6) << "-";
            }else{
                cout << setw(6) << setprecision(4) << newenrollment[i].efolioa;
            }
            if(newenrollment[i].efoliob==-1){
                cout << setw(6) << "-";
            }else{
                cout << setw(6) << setprecision(4) << newenrollment[i].efoliob;
            }

            if(uc.GetEfolios(newenrollment[i].ucuid)==3){
                if(newenrollment[i].efolioc==-1){
                    cout << setw(6) << "-";
                }else{
                    cout << setw(6) << setprecision(4) << newenrollment[i].efolioc;
                }
            }else{
                cout << setw(6) << "N/A";
            }

            if(newenrollment[i].pfolio==-1){
                cout << setw(10) << "-";
            }else{
                cout << setw(10) << setprecision(4) << newenrollment[i].pfolio;
            }
            if(newenrollment[i].secondpfolio==-1){
                cout << setw(10) << "-";
            }else{
                cout << setw(10) << setprecision(4) << newenrollment[i].secondpfolio;
            }
            cout << setw(10) << "N/A" << setw(10) << "N/A";
        }else{
            cout << setw(15) << "Exame";
            if(newenrollment[i].efolioa==-1){
                cout << setw(6) << "N/A";
            }else{
                cout << setw(6) << setprecision(4) << newenrollment[i].efolioa;
            }
            if(newenrollment[i].efoliob==-1){
                cout << setw(6) << "N/A";
            }else{
                cout << setw(6) << setprecision(4) << newenrollment[i].efoliob;
            }
            if(newenrollment[i].efolioc==-1){
                cout << setw(6) << "N/A";
            }else{
                cout << setw(6) << setprecision(4) << newenrollment[i].efolioc;
            }
            cout << setw(10) << "N/A" << setw(10) << "N/A";
            if(newenrollment[i].exam==-1){
                cout << setw(10) << "-";
            }else{
                cout << setw(10) << setprecision(4) << newenrollment[i].exam;
            }
            if(newenrollment[i].secondexam==-1){
                cout << setw(10) << "-";
            }else{
                cout << setw(10) << setprecision(4) << newenrollment[i].secondexam;
            }
        }

        if(grade==-1){
            cout << setw(5) << "-" << setw(12) << "-" <<endl;
        }else if(grade>=9.5){
            cout << setw(5) << setprecision(4) << grade << setw(12) << "Aprovado" << endl;
        }else{
            cout << setw(5) << setprecision(4) << grade << setw(12) << "Reprovado" <<endl;
        }
        
    }
    }

    avarage = avarage/countavarage;

    cout << "\n" << string(130, '-') << endl;
    if(isnan(avarage)){
        cout << "\nMedia do Curso: " << "-" << endl;
    }else{
        cout << "\nMedia do Curso: " << setprecision(4) << avarage << endl;
    }
    cout << "Numero de estudantes aprovados: " << countavarage << endl;
    cout << "Numero total de estudantes: " << studentcount << "\n" << endl;
    cout << string(130, '-') << endl;

}

}