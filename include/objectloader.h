///////////////////////////////////////
/// Author: Jayson B. Abad          ///
/// Company: Noysoft                ///
/// Date Started: August 15, 2022   ///
/// Update: August 16, 2022         ///
/// Update: August 17, 2022         ///
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
typedef std::vector<unsigned int> uintvector;

typedef std::vector<glm::vec3> floatvector3;
typedef std::vector<glm::vec2> floatvector2;

class ObjectLDR
{
private:
  floatvector v;
  floatvector n;
  floatvector vt;

  floatvector3 vertices;
  floatvector2 textures;
  floatvector3 normals;

  floatvector3 indexed_vertices;
  floatvector2 indexed_textures;
  floatvector3 indexed_normals;

  uintvector index;


public:
  ObjectLDR();
  ~ObjectLDR();

  void parseOBJ(std::string);
  void parseMTL(std::string);


  floatvector3 getVertices();
  floatvector2 getTextures();
  floatvector3 getNormals();

  uintvector getIndex();

};

#endif
