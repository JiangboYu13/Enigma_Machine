#include"rotors.h"


Rotors::Rotors()
{
    for(int index=0; index<26; index++)
    {
        rever_map_list[index] = index;
        rotor_map_list[index] = index;
    }
}

void Rotors::shift_up()
{
    shifted_number = (shifted_number+1)%26;
    /*If rotated to notch, call shift_up() recursively for the rotor on the left*/
    for (auto element : notch)
        if (element == shifted_number)
            if(left_rotor)
                left_rotor->shift_up();
}

int Rotors::get_output(int abs_loc)
{
    int rela_output = rotor_map_list[(abs_loc+shifted_number)%26];
    return (rela_output+26-shifted_number)%26;
}

int Rotors::get_revers_output(int abs_loc)
{
    int output_num = (abs_loc+shifted_number)%26;
    int index = rever_map_list[output_num];
    return (index+26-shifted_number)%26;
}



int  Rotors::config(const char* if_name)
{
    ifstream input_s(if_name);
    if(!input_s)
    {
        cerr<<"Fail to open file "<<if_name;
        return ERROR_OPENING_CONFIGURATION_FILE;
    }
    char num_character[128];
    int number;
    bool mapped[26];//List to store if certain number has been mapped
    int index = 0;
    for(auto &element:mapped)
        element = false;
    
    while(input_s>>num_character)
    {
        int error_check_status =validateNumCha(num_character, if_name);
        if(error_check_status!=NO_ERROR)
            return error_check_status;
        
        number = stoi(num_character);
        /*Construct the mapping list for rotor*/
        if(index<26)
        {
	    if (mapped[number] == true)//Another input has been mapped to output 'number'
            {
	      cerr<<"Invalid mapping of input "<<index<<" to output "<<number<<" (output "<<number<<" is already mapped to from input "<<rever_map_list[number]<<")  "<<endl;;
                return INVALID_ROTOR_MAPPING;
            }
            else mapped[number] = true;
            rever_map_list[number] = index;
            rotor_map_list[index] = number;
            index++;
        }
        else
            notch.insert(number);
    }
    if (index<26)
    {
        cerr<<"Not all inputs mapped in rotor file: "<<if_name<<endl;
        return INVALID_ROTOR_MAPPING;
    }
    return NO_ERROR;
}




