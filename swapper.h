#ifndef SWAPPER_H
#define SWAPPER_H


#include"errors.h"
#include"help_function.h"
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>


using namespace std;
/*Class used to describe the plugboards and reflectorss*/
class Swapper
{
private:
    int map_list[26];
public:
    Swapper();
    int config(const char*);
    int get_output(int abs_loc){return map_list[abs_loc];}
    /*Function to check if either element in pair has been mapped to another number*/
    int ifValidMapping(int * pair, int file_type);
    
};




#endif 
