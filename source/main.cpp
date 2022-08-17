///////////////////////////////////////
/// Author: Jayson B. Abad          ///
/// Company: Noysoft                ///
/// Date Started: August 15, 2022   ///
/// Update: August 16, 2022         ///
/// Update: August 17, 2022         ///
///////////////////////////////////////

#include <objectloader.h>
#include <iostream>
#include <vector>

int main()
{

  ObjectLDR objectldr;

  objectldr.parseOBJ("assets/models/box_stack.obj");

  return 0;
}
