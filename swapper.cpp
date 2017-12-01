#include "swapper.h"
#include <map>


Swapper::Swapper()
{
    for(int index=0; index<26; index++)
        map_list[index] = index;
}




int Swapper::config(const char* if_name)
{
    int file_type =fileTypeCheck(if_name);
     
    ifstream input_s(if_name);
    if(!input_s)
    {
        cerr<<"Fail to open file "<<if_name;
        return ERROR_OPENING_CONFIGURATION_FILE;
    }
    
    char num_character[128];
    int number;
    int index=0;
    int pair[2];//To store two adjacent numbers in file which describe the numbers to be swapped

    /*To cumstomize the error output for different file type*/
    map<int, const char*>prt_form;
    prt_form[PB_FILE] = "";
    prt_form[RF_FILE] =" (odd)";
    
    while(input_s>>num_character)
    {
        int error_check_status = validateNumCha(num_character, if_name);
        if(error_check_status!=NO_ERROR)
            return error_check_status;   
        number = stoi(num_character);
        pair[index%2] = number;

	/*Swap the two numbers in map_list*/
        if (index%2 == 1)
        {
	  error_check_status = ifValidMapping(pair,file_type);
            if (error_check_status!= NO_ERROR) return error_check_status;
            swap(map_list[pair[0]],map_list[pair[1]]);
        }
        index++;
	/*Check if the number in file exceeds 26*/
        if (index>26)
        {
            cerr<<"Incorrect"<<prt_form[file_type]<<" number of parameters in "<<FILE_NAME[file_type]<<" file "<<if_name<<endl;
            if (file_type == 0)
                return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
            else if(file_type == 1)
                return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
        }
    }
    
    if (index%2==1)//Odd number of numbers in file
    {
        cerr<<"Incorrect"<<prt_form[file_type]<<" number of parameters in "<<FILE_NAME[file_type]<<" file "<<if_name<<endl;
        if (file_type == PB_FILE)
            return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
        else if(file_type == RF_FILE)
            return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
    
    if (index<26 && file_type == RF_FILE)//Less than 26 numbers in file
    {
        cerr<<"Insufficient number of mappings in reflector file: "<<if_name<<endl;
        return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
    return NO_ERROR;
}




int Swapper::ifValidMapping(int * pair, int file_type)
{
    bool error = false;
    if (map_list[pair[0]]!=pair[0])//The first number in the pair has been mapped
    {
        cerr<<"Invalid mapping of input "<<pair[1]<< " to output "<<pair[0]<<" (output "<<pair[0]<<" is already mapped to from input "<<map_list[pair[0]]<<")"<<endl;
        error = true;
        
    }
    else if (map_list[pair[1]]!=pair[1])//The second number in the paid has been mapped
    {
        cerr<<"Invalid mapping of input "<<pair[0]<< " to output "<<pair[1]<<" (output "<<pair[1]<<" is already mapped to from input "<<map_list[pair[1]]<<")"<<endl;
        error = true;
    }
    else if (pair[1]==pair[0])//Try to map itself
    {
        cerr<<"Invalid mapping of input "<<pair[0]<< " to itself"<<endl;;
        error = true;
    }
    if(error == true)
    {
        if (file_type == PB_FILE)
            return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
        else if(file_type == RF_FILE)
            return INVALID_REFLECTOR_MAPPING;
    }
    return NO_ERROR;
}

