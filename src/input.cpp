/*
 * input.cpp
 * Funcoes que obtem dados do terminal dos utilizadores
 *
 *  Created on: 30/11/2020
 *      Author: Rúdi Gualter
 */

#include "input.h"

namespace std {

//define o construtor
Input::Input(){}

//define o destrutor
Input::~Input(){}

string Input::GetString(int stringSize){
    
    bool valid=false;
    string fullstring;
    do{
        getline(cin, fullstring);
        int length = fullstring.length();
        if (cin.good()){
            if(length <= stringSize){
            valid = true;
            }else{
            cin.clear();
            cout << "Apenas pode conter " << stringSize << " caracteres, insira de novo:" << endl;
            }
        }else{
            cin.clear();
            cout << "Apenas pode conter " << stringSize << " caracteres, insira de novo:" << endl;
        }
    }while (!valid);

    return fullstring;
}

int Input::GetNumber(int numberSize){

    bool valid=false;
    int number;

    do{
        cin >> number;
        if (cin.good()){
            if(number<=numberSize){
                valid = true;
                cin.ignore();
            }else{
            cout << "Numero invalido este deve ser menor que " << numberSize << " por favor volte a inserir:" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }else{
            cout << "Numero invalido este deve ser menor que " << numberSize << " por favor volte a inserir:" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }while (!valid);

    return number;
}

float Input::GetDecimal(float numberSize){
    
    bool valid=false;
    float decimal;

    do{
        cin >> decimal;
         if (cin.good()){
            if(decimal<=numberSize){
                valid = true;
                cin.ignore();
            }else{
            cout << "Numero invalido este deve ser menor que " << numberSize << " por favor volte a inserir:" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }else{
            cout << "Numero invalido este deve ser menor que " << numberSize << " por favor volte a inserir:" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }while (!valid);

    return decimal;
}

string Input::GetDachedYear(){

    bool valid=false;
    string year;

    do{
        getline(cin, year);
        if (cin.good()){
            if(validateString(year)==1){
            valid = true;
            }else{
            cin.clear();
            cout << "O formata inserido ao e valido, insira de novo:" << endl;
            }
        }else{
            cin.clear();
            cout << "O formata inserido ao e valido, insira de novo:" << endl;
        }
    }while (!valid);

    return year;
    
}

int Input::validateString(string s){
    
    int n = s.length();
    int validation=1;

    char char_array[n + 1];

    strcpy(char_array, s.c_str());
 
    for (int i = 0; i < n; i++)
        if(i<4){
            if(!isdigit(char_array[i])){
                validation=0;
            }
        }else if(i==4){
            if(char_array[i]!='/'){
                validation=0;
            }
        }else{
            if(!isdigit(char_array[i])){
                validation=0;
            }
        }
 
    return validation;
}

}