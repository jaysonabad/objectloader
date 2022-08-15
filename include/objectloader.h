///////////////////////////////////////
/// Author: Jayson B. Abad          ///
/// Company: Noysoft                ///
/// Date Started: August 15, 2022   ///
///////////////////////////////////////

#ifndef OBJECT_LOADER_H
#define OBJECT_LOADER_H

#include <string>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef glm::vec3 vector3;
typedef glm::vec2 vector2;
typedef std::vector<float> floatvector;

class ObjectLDR
{
private:
  floatvector v;
  floatvector n;
  floatvector vt;
  floatvector f;

  std::map<int, vector3> vertices;
  std::map<int, vector2> textures;
  std::map<int, vector3> normals;

  floatvector final;

public:
  ObjectLDR();
  ~ObjectLDR();

  const char* read(std::string);
  void parseOBJ(std::string);
  void parseMTL(std::string);
  floatvector processOBJ();

  void printOBJData();

};

#endif
