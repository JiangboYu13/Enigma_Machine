#ifndef ENIGMAS_H
#define ENIGMAS_H

#include"rotors.h"
#include"swapper.h"
#include"errors.h"
#include"help_function.h"
class Enigmas
{
 private:
  Swapper plugboard;
  Swapper reflector;
  Rotors* rotor = nullptr;
 public:
  Enigmas()=default;
  ~Enigmas();
  /*Function to configure all the component for Enigma*/
  int config(const char*plug_file, const char* ref_file, char* rotor_file[],int rotor_count, const char* pos_file);
  /*Function to encrypt an number from 0 to 25 to produce another number from 0 to 25*/
  int get_output(int input_num);
};

#endif
