///////////////////////////////////////
/// Author: Jayson B. Abad          ///
/// Company: Noysoft                ///
/// Date Started: August 15, 2022   ///
/// Update: August 16, 2022         ///
/// Update: August 17, 2022         ///
///////////////////////////////////////

#include <objectloader.h>

#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ObjectLDR::ObjectLDR(){}

void ObjectLDR::parseOBJ(std::string filepath)
{
  std::string faces;
  std::string line;
  std::ifstream file(filepath);
  if(file.is_open())
  {
    while(getline(file, line))
    {
      std::istringstream sline(line);
      std::string temp;
      while(sline >> temp)
      {
        if(line[0] == 'v' && line[1] == ' ')
        {
          if(temp != "v")
          {
            this->v.push_back(stof(temp));
          }
        }
        if(line[0] == 'v' && line[1] == 't')
        {
          if(temp != "vt")
          {
            this->vt.push_back(stof(temp));
          }
        }
        if(line[0] == 'v' && line[1] =='n')
        {
          if(temp != "vn")
          {
            this->n.push_back(stof(temp));
          }
        }
        if(line[0] == 'f' && line[1] == ' ')
        {
          if(temp != "f")
          {
            faces.append(temp+" ");
          }
        }
      }
    }
  }

  /// parsing faces
  std::string ftemp;

  for(int i = 0; i < faces.length(); i++)
  {
    if(faces[i] != '/')
    {
      ftemp.push_back(faces[i]);
    }
    else
    {
      ftemp.push_back(' ');
    }
  }

  std::istringstream sface(ftemp);
  std::string faceindex;
  int counter = 0;
  while(sface >> faceindex)
  {
    if(counter == 0)
    {
      this->index_of_vertices.push_back(stoi(faceindex) - 1);
    }
    if(counter == 1)
    {
      this->index_of_textures.push_back(stoi(faceindex) - 1);
    }
    if(counter == 2)
    {
      this->index_of_normals.push_back(stoi(faceindex) - 1);
    }
    counter++;
    if(counter == 3)
    {
      counter = 0;
    }
  }

  /// process the variables
  int k = 0;
  for(int i = 0; i < this->v.size() / 3; i++)
  {
    vector3 v = vector3(1.0f);
    for(int j = 0; j < 3; j++)
    {
      if(j == 0)
      {
        v.x = this->v[k];
      }
      if(j == 1)
      {
        v.y = this->v[k];
      }
      if(j == 2)
      {
        v.z = this->v[k];
      }
      k++;
    }
    this->vertices.push_back(v);
  }

  k = 0;
  for(int i = 0; i < this->n.size() / 3; i++)
  {
    vector3 n = vector3(1.0f);
    for(int j = 0; j < 3; j++)
    {
      if(j == 0)
      {
        n.x = this->n[k];
      }
      if(j == 1)
      {
        n.y = this->n[k];
      }
      if(j == 2)
      {
        n.z = this->n[k];
      }
      k++;
    }
    this->normals.push_back(n);
  }

  k = 0;
  for(int i = 0; i < this->vt.size() / 2; i++)
  {
    vector2 vt = vector2(1.0f);
    for(int j = 0; j < 2; j++)
    {
      if(j == 0)
      {
        vt.x = this->vt[k];
      }
      if(j == 1)
      {
        vt.y = this->vt[k];
      }
      k++;
    }
    this->textures.push_back(vt);
  }
}

void ObjectLDR::parseMTL(std::string filepath){}

floatvector3 ObjectLDR::getVertices()
{
  return this->vertices;
}

floatvector2 ObjectLDR::getTextures()
{
  return this->textures;
}

floatvector3 ObjectLDR::getNormals()
{
  return this->normals;
}

uintvector ObjectLDR::getIndexOfVertices()
{
  return this->index_of_vertices;
}

uintvector ObjectLDR::getIndexOfTextures()
{
  return this->index_of_textures;
}

uintvector ObjectLDR::getIndexOfNormals()
{
  return this->index_of_normals;
}

ObjectLDR::~ObjectLDR(){}
