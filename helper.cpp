/**
 * FILE: helper.cpp
 * 
 * GROUP: C
 * Ross Coombs
 * Elliot Scott
 * Kai Uerlichs
 * 
 * This file includes the implementation for the helper functions of helper.h
 */



// Required std includes and namespace setting
#include "helper.h"
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
vector<string> strsplit(const char *str, char c){
    // A vector to hold the tokens
    vector<string> result;

    // Iterate over string and push-back when delimiter found
    do
    {
        const char *begin = str;

        while(*str != c && *str)
            str++;

        result.push_back(string(begin, str));
    } while (0 != *str++);

    // Return the results
    return result;
}