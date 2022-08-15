///////////////////////////////////////
/// Author: Jayson B. Abad          ///
/// Company: Noysoft                ///
/// Date Started: August 15, 2022   ///
///////////////////////////////////////

#include <objectloader.h>
#include <iostream>
#include <vector>

int main()
{

  ObjectLDR objectldr;

  std::vector<float> final;

  objectldr.parseOBJ("assets/models/box_stack.obj");

  final = objectldr.processOBJ();

  for(float i: final)
  {
    std::cout << i << std::endl;
  }

  return 0;
}
