#include "enigmas.h"
#include "help_function.h"
#include<cstdio>
#include<map>
#include<cstring>

int charToInt(char character);
char intToChar(int integer);
int checkInput(char character);
int inputParaCheck(int argc, char *argv[]);


int main(int argc, char *argv[])
{
    
    /*Check if the input parameter is correct*/
    int error_check_status = inputParaCheck(argc, argv);
    if (error_check_status!=NO_ERROR)
        return error_check_status;
    
    /*Setup the Enigma*/
    Enigmas enigma;
    error_check_status = enigma.config(argv[1],argv[2],argv+3,argc-4,argv[argc-1]);
    if (error_check_status != NO_ERROR)
        return error_check_status;
    
    /*Encrypt message*/
    char character;
    int output_int;
    while(cin>>character)
    {
        error_check_status = checkInput(character);//Check if input is from 'A' to 'Z'
        if (error_check_status!= NO_ERROR)
            return error_check_status;
        else
        {
            output_int = enigma.get_output(charToInt(character));
            cout<<intToChar(output_int);
        }
    }
    
    return NO_ERROR;
}



/*Check if the input file parameter is correct for setup enigma*/
int inputParaCheck(int argc, char *argv[])
{
    /*0 for plugboard file, 1 for reflector, 2 for rotor, 3 for position. Defined in help_function.h*/

    bool file_exist[4];//bool value to store whether certain file type exist or not
    for(int index = 0; index<4; index++)
      file_exist[index] = false;
    
    for(int index = 1; index< argc; index++)
    {
        int file_type = fileTypeCheck(argv[index]);//function in help_function.h to return an int for certain file type
        file_exist[file_type] = true;
    }
    
    /*Return error if no .pb or no .rf or only one of .pos and .rot exists*/
    if ((!file_exist[0]||!file_exist[1])||(file_exist[2]&&!file_exist[3])||(!file_exist[2]&&file_exist[3]))
    {
        cerr<<"usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?"<<endl;
        return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    }
    
    return NO_ERROR;
    
}





/*Check if character is upper case character*/
int checkInput(char character)
{
    if (character<'A'||character>'Z')
    {
        cerr<<character<<" is not a valid input character (input characters must be upper case letters A-Z)!"<<endl;;
        return INVALID_INPUT_CHARACTER;
    }
    else return NO_ERROR;
}

/*Change an upper case character to a integer, 0 for A and 25 for Z*/
int charToInt(char character)
{
    return static_cast<int>(character-'A');
}

/*Change a integer to upper case character, A for 0 and Z for 25*/
char intToChar(int integer)
{
    return static_cast<char>(static_cast<int>('A')+integer);
}
