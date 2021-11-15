/**
 * FILE: helper.h
 * 
 * GROUP: C
 * Ross Coombs
 * Elliot Scott
 * Kai Uerlichs
 * 
 * This file ddefines some helper functions
 */



// Beginning of header guard
#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
using namespace std;

/**
 * @brief A function to tokenize a string based on a delimiter and return a corresponding vector
 * 
 * @param str The string to tokenize
 * @param c The delimter character
 * @return vector<string> A vector of string tokens
 * 
 * @authors https://stackoverflow.com/questions/53849/how-do-i-tokenize-a-string-in-c
 * @note Comments added by group members
 */
vector<string> strsplit(const char *str, char c = ' ');


// End of header guard
#endif