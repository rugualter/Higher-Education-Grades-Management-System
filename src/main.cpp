#include <iostream>
#include <iomanip>
#include "input.h"
#include "course.h"
#include "uc.h"
#include "student.h"
#include "enrollment.h"

using namespace std;

void MainMenu();

int main(){

	int option;
	Input input;
	Course course;
	Student student;
	Uc uc;
	Enrollment enroll;

	cout << string(130, '*') << std::endl;
	cout << string(51, ' ') << "Sistema de Gestao da UAb" << endl;
	cout << string(130, '*') << std::endl;

	MainMenu();
	cout << "\nInsira o numero da opcao:" << endl;
	string name;
	int uid, uida;
	option = input.GetNumber(19);

	while (option!=0){

		switch (option){
		case 1:
			cout << "\n" << string(50, '-') << std::endl;
			cout << string(15, ' ') << "Adicionar Estudante" << std::endl;
			cout << string(50, '-') << std::endl;
			student.AddStudent();
			break;
		
		case 2:
			student.ShowStudents();
			break;
		
		case 3:
			cout << "\n" << string(50, '-') << std::endl;
			cout << string(15, ' ') << "Modificar Estudante" << std::endl;
			cout << string(50, '-') << std::endl;
			cout << "Insira o numero do estudante a modificar:" << endl;
			uid = input.GetNumber(9999999);
			student.UpdateStudent(uid);
			break;

		case 4:
			cout << "\n" << string(50, '-') << std::endl;
			cout << string(15, ' ') << "Eliminar Estudante" << std::endl;
			cout << string(50, '-') << std::endl;
			cout << "Insira o numero do estudante a eliminar:" << endl;
			uid = input.GetNumber(9999999);
			student.DeleteStudent(uid);
			break;

		case 5:
			cout << "\n" << string(50, '-') << std::endl;
			cout << string(5, ' ') << "Obter informacoes de Estudante" << std::endl;
			cout << string(50, '-') << std::endl;
			cout << "Insira o numero do estudante para ver informacoes:" << endl;
			uid = input.GetNumber(9999999);
			enroll.GetStudentInfo(uid);
			break;
		
		case 6:
			cout << "\n" << string(50, '-') << std::endl;
			cout << string(5, ' ') << "Increver Estudante em Unidade Curricular" << std::endl;
			cout << string(50, '-') << std::endl;
			enroll.AddEnrollment();
			break;

		case 7:
			cout << "\n" << string(50, '-') << std::endl;
			cout << string(12, ' ') << "Adicionar/Atualizar Nota" << std::endl;
			cout << string(50, '-') << std::endl;
			cout << "Insira o numero da unidade curricular:" << endl;
			uid = input.GetNumber(9999999);
			cout << "Insira o numero do estudante:" << endl;
			uida = input.GetNumber(9999999);
			cout << "Insira o ano letivo:" << endl;
			name = input.GetDachedYear();
			enroll.AddGrade(uid, uida, name);
			break;

		case 8:
			cout << "\n" << string(50, '-') << std::endl;
			cout << string(15, ' ') << "Modificar Inscricao" << std::endl;
			cout << string(50, '-') << std::endl;
			cout << "Insira o numero da unidade curricular:" << endl;
			uid = input.GetNumber(9999999);
			cout << "Insira o numero do estudante:" << endl;
			uida = input.GetNumber(9999999);
			cout << "Insira o ano letivo:" << endl;
			name = input.GetDachedYear();
			enroll.UpdateEnrollment(uid, uida, name);
			break;
		
		case 9:
			cout << "\n" << string(50, '-') << std::endl;
			cout << string(15, ' ') << "Eliminar Inscricao" << std::endl;
			cout << string(50, '-') << std::endl;
			cout << "Insira o numero da unidade curricular:" << endl;
			uid = input.GetNumber(9999999);
			cout << "Insira o numero do estudante:" << endl;
			uida = input.GetNumber(9999999);
			cout << "Insira o ano letivo:" << endl;
			name = input.GetDachedYear();
			enroll.DeleteEnrollment(uid, uida, name);
			break;

		case 10:
			enroll.ShowEnrollments();
			break;

		case 11:
			cout << "\n" << string(50, '-') << std::endl;
			cout << string(11, ' ') << "Adicionar Unidade Curricular" << std::endl;
			cout << string(50, '-') << std::endl;
			uc.AddUc();
			break;

		case 12:
			uc.ShowUcs();
			break;

		case 13:
			cout << "\n" << string(50, '-') << std::endl;
			cout << string(11, ' ') << "Modificar Unidade Curricular" << std::endl;
			cout << string(50, '-') << std::endl;
			cout << "Insira o numero da unidade curricular a modificar:" << endl;
			uid = input.GetNumber(9999999);
			uc.UpdateUc(uid);
			break;
		
		case 14:
			cout << "\n" << string(50, '-') << std::endl;
			cout << string(11, ' ') << "Eliminar Unidade Curricular" << std::endl;
			cout << string(50, '-') << std::endl;
			cout << "Insira o numero da unidade curricular a eliminar:" << endl;
			uid = input.GetNumber(9999999);
			uc.DeleteUc(uid);
			break;
		
		case 15:
			cout << "\n" << string(50, '-') << std::endl;
			cout << string(5, ' ') << "Obter informacoes de Unidade Curricular" << std::endl;
			cout << string(50, '-') << std::endl;
			cout << "Insira o numero da unidade curricular:" << endl;
			uid = input.GetNumber(9999999);
			cout << "Insira o ano letivo:" << endl;
			name = input.GetDachedYear();
			enroll.GetUcInfo(uid,name);
			break;
		
		case 16:
			cout << "\n" << string(50, '-') << std::endl;
			cout << string(17, ' ') << "Adicionar Curso" << std::endl;
			cout << string(50, '-') << std::endl;
			course.AddCourse();
			break;
		
		case 17:
			course.ShowCourses();
			break;
		
		case 18:
			cout << "\n" << string(50, '-') << std::endl;
			cout << string(17, ' ') << "Modificar Curso" << std::endl;
			cout << string(50, '-') << std::endl;
			cout << "Insira o nome do curso a modificar (ex.: Licenciatura em Gestao):" << endl;
			name = input.GetString(100);
			course.UpdateCourse(name);
			break;

		case 19:
			cout << "\n" << string(50, '-') << std::endl;
			cout << string(17, ' ') << "Eliminar Curso" << std::endl;
			cout << string(50, '-') << std::endl;
			cout << "Insira o nome do curso a eleminar (ex.: Licenciatura em Gestao):" << endl;
        	name = input.GetString(100);
			course.DeleteCourse(name);
			break;
		}

		MainMenu();
		cout << "\nInsira o numero da opcao:" << endl;
		option = input.GetNumber(19);
	}
	
	cout << "\n" << string(25, '-') << std::endl;
	cout << string(4, ' ') << "Adeus e Obrigado" << std::endl;
	cout << string(25, '-') << std::endl;
	return 0;	

}

void MainMenu(){

	cout << "\n" << string(130, '*') << endl;
	cout << string(63, ' ') << "Menu" << endl;
	cout << string(130, '*') << endl;
	cout << "\nEscolha uma opcao (Insira o numero da opcao): "  << endl;
	cout << "\n" << left << setw(65) << "1 - Adicionar Estudante" << setw(50) << "11 - Adicionar Unidade Curricular" <<endl;
	cout << left << setw(65) << "2 - Ver Todos os Estudantes"<< setw(50) << "12 - Ver Todas as Unidades Curriculares" <<endl;
	cout << left << setw(65) << "3 - Modificar Estudante"<< setw(50) << "13 - Modificar Unidade Curricular" <<endl;
	cout << left << setw(65) << "4 - Eliminar Estudante"<< setw(50) << "14 - Eliminar Unidade Curricular" <<endl;
	cout << left << setw(65) << "5 - Obter Detalhes e Indicadores de Estudante"<< setw(50) << "15 - Obter Detalhes e Indicadores de Unidade Curricular" <<endl;
	cout << left << setw(65) << "6 - Inscrever Estudante em Unidade Curricular"<< setw(50) << "16 - Adicionar curso" <<endl;
	cout << left << setw(65) << "7 - Adicionar/Alterar Nota de Estudante a Unidade Curricular" << setw(50) << "17 - Ver todos os cursos" <<endl;
	cout << left << setw(65) << "8 - Modificar Inscricao (alteracoes nao controladas)" << setw(50) << "18 - Modificar Curso" <<endl;
	cout << left << setw(65) << "9 - Eliminar Inscricao de Estudante em Unidade Curricular" << setw(50) << "19 - Eliminar Curso" <<endl;
	cout << left << setw(65) << "10 - Ver Todas as Inscricoes" << setw(50) << "0 - Exit" <<endl;

	return;
}