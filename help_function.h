#ifndef HELPFUNCTION_H
#define HELPFUNCTION_H

#include"errors.h"
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<vector>
/*Number to represent certain file type*/
const int PB_FILE = 0;
const int RF_FILE = 1;
const int RT_FILE = 2;
const int POS_FILE = 3;
const int OTHER_FILE = -1;
const char FILE_NAME[][30] ={"plugboard", "reflector", "rotor", "position", "other"};

using namespace std;
/*Function to check if num_character represnt a number from '0' to '25' and dispaly error message duo to different file type*/
int validateNumCha(char * num_character, const char* if_name);
/*Return a code representing the file type of if_name*/
int fileTypeCheck(const char* if_name);

#endif


