#ifndef ROTORS_H
#define ROTORS_H
#include"errors.h"
#include"help_function.h"
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<set>

using namespace std;
class Rotors
{
 private:
  int rotor_map_list[26];
  int rever_map_list[26];
  int shifted_number = 0;//used to stored how many the Rotors shifts away from the absolute position.
  set<int> notch = {};//use set so that no repeated notch stored
  Rotors* left_rotor = nullptr;
  Rotors* right_rotor = nullptr;
  
 public:

  Rotors();
  /*Function to set up the Rotors mapping list as in file if_name*/
  int config(const char* if_name);
  /*Function to increase the Rotors' shifted number. If shift to notch, call this function for the Rotors on the left automatically*/
  void shift_up();
  void set_shifted(int number){shifted_number = number%26;}
  /*Get the output of rotor by giving input abs_loc at the right side*/
  int get_output(int abs_loc);
  /*Get the output of rotor by giving input abs_loc at the right side*/
  int get_revers_output(int abs_loc);
  Rotors* get_left_rotor(){return left_rotor;}
  Rotors* get_right_rotor(){return right_rotor;}
  void set_left_rotor(Rotors* left_r){left_rotor = left_r;}
  void set_right_rotor(Rotors* right_r){right_rotor = right_r;}
};

#endif
