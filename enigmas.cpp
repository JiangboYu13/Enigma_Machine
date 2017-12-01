#include"enigmas.h"

int Enigmas::config(const char*plug_file, const char* ref_file,char* rotor_file[],int rotor_count, const char* pos_file)
{
    /*Check if the file type match the component to be configured*/
    if (fileTypeCheck(plug_file)!=0)
      {
        cerr<<"Wrong file type for plugboard: "<<plug_file<<endl;;
        return ERROR_OPENING_CONFIGURATION_FILE;
      }
    if (fileTypeCheck(ref_file)!=1)
      {
	cerr<<"Wrong file type for reflector: "<<ref_file<<endl;;
        return ERROR_OPENING_CONFIGURATION_FILE;
      }
    if (rotor_count>0&&fileTypeCheck(pos_file)!=3)
      {
	cerr<<"Wrong file type for rotor position: "<<pos_file<<endl;;
        return ERROR_OPENING_CONFIGURATION_FILE;
      }
    for (int index = 0; index<rotor_count; index++)
      if (fileTypeCheck(rotor_file[index])!=2)
	{
	  cerr<<"Wrong file type for rotor: "<<rotor_file[index]<<endl;
	  return ERROR_OPENING_CONFIGURATION_FILE;
	}
  
    /*Setup the Plugboard*/
    int error_check_status = plugboard.config(plug_file);
    if (error_check_status!=NO_ERROR)
        return error_check_status;
    
    /*Setup the Reflector*/
    error_check_status = reflector.config(ref_file);
    if (error_check_status!=NO_ERROR)
        return error_check_status;
    
    
    /*Setup the Rotors*/
    char num_character[128];
    int number;
    if (rotor_count>0)
    {
        ifstream input_s(pos_file);
        if(!input_s)
        {
            cerr<<"Fail open file "<<pos_file;
            return ERROR_OPENING_CONFIGURATION_FILE;
        }
        
        /*Setup the left most rotor*/
        Rotors* rotor_cp = new Rotors;
        error_check_status = rotor_cp->config(rotor_file[0]);
        if (error_check_status!= NO_ERROR)
            return error_check_status;
        
        for(int index = 1; index<=rotor_count; index++)
        {
            
            /*Setup the start position for rotor */
            input_s>>num_character;//read one position number for rotor
            if (!input_s)
            {
                cerr<< "No starting position for rotor "<<index-1<<" in rotor position file: "<<pos_file<<endl;
                return NO_ROTOR_STARTING_POSITION;
            }
            error_check_status =validateNumCha(num_character,pos_file);
            if(error_check_status!=NO_ERROR)
                return error_check_status;
            number = stoi(num_character);
            rotor_cp->set_shifted(number);
            
            
            /*Setup the rotor on the right and link it to the left*/
            if (index!=rotor_count)
            {
                rotor_cp->set_right_rotor(new Rotors);
                error_check_status = rotor_cp->get_right_rotor()->config(rotor_file[index]);
                if(error_check_status!=NO_ERROR)
                    return error_check_status;
                rotor_cp->get_right_rotor()->set_left_rotor(rotor_cp);
                rotor_cp = rotor_cp->get_right_rotor();
            }
            
        }
        rotor = rotor_cp;//set class attribute rotor to the right most rotor 
    }
    return NO_ERROR;
}





int Enigmas::get_output(int input)
{
    int temp_output;
    Rotors* rotor_cp = rotor;//The right most rotor

    temp_output = plugboard.get_output(input);
    
    /*If there is at least 1 rotor, the right most one rotate for one position for each encryption*/
    if (rotor!=nullptr)
        rotor->shift_up();
    
    /*Forward encrypting through rotors*/
    while(rotor_cp)
    {
        temp_output = rotor_cp->get_output(temp_output);
        if (rotor_cp->get_left_rotor()==nullptr)
            break;
        rotor_cp = rotor_cp->get_left_rotor();
    }
    
    temp_output = reflector.get_output(temp_output);
    
    /*Forward encrypting through rotors*/
    while(rotor_cp)
    {
        temp_output = rotor_cp->get_revers_output(temp_output);
        rotor_cp = rotor_cp->get_right_rotor();
    }
    temp_output = plugboard.get_output(temp_output);
    return temp_output;
}


Enigmas::~Enigmas()
{
    if(rotor!=nullptr)
    {
        Rotors* rotor_cp = rotor;
	/*Release memory for the rotor from the right most one to the left*/
        while(rotor_cp->get_left_rotor()!=nullptr)
	  {
            rotor_cp = rotor_cp->get_left_rotor();
	    delete rotor_cp->get_right_rotor();
	  }
	delete rotor_cp;
    }
}
