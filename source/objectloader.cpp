///////////////////////////////////////
/// Author: Jayson B. Abad          ///
/// Company: Noysoft                ///
/// Date Started: August 15, 2022   ///
/// Update: August 16, 2022         ///
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


floatvector ObjectLDR::parseOBJ(std::string filepath)
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
  std::string face;
  while(sface >> face)
  {
    this->f.push_back(stoi(face));
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
    this->vertices[i] = v;
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
    this->normals[i] = n;
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
    this->textures[i] = vt;
  }

  k = 0;
  for(int i = 0; i < this->f.size() / 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      if(j == 0)
      {
        this->final.push_back(this->vertices[this->f[k] - 1].x);
        this->final.push_back(this->vertices[this->f[k] - 1].y);
        this->final.push_back(this->vertices[this->f[k] - 1].z);
      }
      if(j == 1)
      {
        this->final.push_back(this->textures[this->f[k] - 1].x);
        this->final.push_back(this->textures[this->f[k] - 1].y);
      }
      if(j == 2)
      {
        this->final.push_back(this->normals[this->f[k] - 1].x);
        this->final.push_back(this->normals[this->f[k] - 1].y);
        this->final.push_back(this->normals[this->f[k] - 1].z);
      }
      k++;
    }
  }

  return this->final;
}

void ObjectLDR::parseMTL(std::string filepath){}

void ObjectLDR::printOBJData()
{
  std::cout << "Vertices" << std::endl;
  for(int i = 0; i < this->vertices.size(); i++)
  {
    std::cout << "Mapped V: " << this->vertices[i].x << " "
                              << this->vertices[i].y << " "
                              << this->vertices[i].z << std::endl;
  }
  std::cout << "Normals" << std::endl;
  for(int i = 0; i < this->normals.size(); i++)
  {
    std::cout << "mapped vn: " << this->normals[i].x << " "
                              << this->normals[i].y << " "
                              << this->normals[i].z << std::endl;
  }
  std::cout << "Texture" << std::endl;
  for(int i = 0; i < this->textures.size(); i++)
  {
    std::cout << "mapped vt: " << this->textures[i].x << " "
                              << this->textures[i].y << " "
                              << std::endl;
  }
}

floatvector ObjectLDR::getV()
{
  return this->v;
}

floatvector ObjectLDR::getN()
{
  return this->n;
}

floatvector ObjectLDR::getVT()
{
  return this->vt;
}

intvector ObjectLDR::getF()
{
  return this->f;
}

ObjectLDR::~ObjectLDR(){}
