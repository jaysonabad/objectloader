///////////////////////////////////////
/// Author: Jayson B. Abad          ///
/// Company: Noysoft                ///
/// Date Started: August 15, 2022   ///
/// Update: August 16, 2022         ///
///////////////////////////////////////

#include <objectloader.h>
#include <iostream>
#include <vector>

int main()
{

  ObjectLDR objectldr;

  std::vector<float> final = objectldr.parseOBJ("assets/models/stall.obj");

  objectldr.printOBJData();

  return 0;
}
