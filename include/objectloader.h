///////////////////////////////////////
/// Author: Jayson B. Abad          ///
/// Company: Noysoft                ///
/// Date Started: August 15, 2022   ///
/// Update: August 16, 2022         ///
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
typedef std::vector<int> intvector;

class ObjectLDR
{
private:
  floatvector v;
  floatvector n;
  floatvector vt;
  intvector f;

  std::map<int, vector3> vertices;
  std::map<int, vector2> textures;
  std::map<int, vector3> normals;

  floatvector final;

public:
  ObjectLDR();
  ~ObjectLDR();

  floatvector parseOBJ(std::string);
  void parseMTL(std::string);

  floatvector getV();
  floatvector getN();
  floatvector getVT();
  intvector getF();

  void printOBJData();

};

#endif
