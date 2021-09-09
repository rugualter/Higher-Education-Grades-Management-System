/*
 * input.h
 * Classe que obtem dados do terminal dos utilizadores
 *
 *  Created on: 18/12/2020
 *      Author: Rúdi Gualter
 */

#ifndef INPUTS_H_
#define INPUTS_H_

#include <iostream>
#include <string>
#include <limits>
#include <cstring>
//#include <iomanip>
//#include <fstream>

namespace std {

class Input {

private:
	int validateString(string);
public:
	Input();
	~Input();
    string GetString(int);
	int GetNumber(int);
	float GetDecimal(float);
	string GetDachedYear();

};

} /* namespace std */
#endif /* INPUTS_H_ */