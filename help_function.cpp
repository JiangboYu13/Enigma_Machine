#include "help_function.h"

/*Variable to customize the non-numeric and exceed-range error message for different files types*/
const char ERR_DIS [][30]{"in plugboard", "in reflector", "for mapping in rotor", "in rotor positions", "in other"};


/*To check if a certain string can represent a number from 0 to 25*/
int validateNumCha(char * num_character, const char* if_name)
{
    int index = 0;
    int file_type = fileTypeCheck(if_name);
    while(num_character[index]!='\0')
        if (!isdigit(num_character[index++]))
        {
            cerr<<"Non-numeric character "<<ERR_DIS[file_type]<<" file "<<if_name<<endl;
            return NON_NUMERIC_CHARACTER;
        }
    
    int number = stoi(num_character);
    if (number<0||number>25)
    {
        cerr<<"Invalid index "<<ERR_DIS[file_type]<<" file "<<if_name<<endl;
        return INVALID_INDEX;
    }
    
    return NO_ERROR;
}


/*Get the code representing certain file type*/
int fileTypeCheck(const char* if_name)
{
    for(int index = 0; if_name[index]!='\0'; index++)
    {
        if (if_name[index]=='.')
        {
            if (strcmp(if_name+index, ".pb") == 0) return PB_FILE;
            else if (strcmp(if_name+index, ".rf") == 0) return RF_FILE;
            else if (strcmp(if_name+index, ".pos") == 0) return POS_FILE;
            else if (strcmp(if_name+index, ".rot") == 0) return RT_FILE;
        }
        
    }
    return OTHER_FILE;
}

