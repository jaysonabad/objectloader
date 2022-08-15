///////////////////////////////////////
/// Author: Jayson B. Abad          ///
/// Company: Noysoft                ///
/// Date Started: August 15, 2022   ///
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

const char* ObjectLDR::read(std::string filepath)
{
  const char* data;
  std::string temp;
  std::string line;

  std::ifstream file(filepath);
  if(file.is_open())
  {
    while(getline(file, line))
    {
      temp += line + "\n";
    }
  }
  else
  {
    std::cout << "error opening the file.." << std::endl;
  }
  data = temp.c_str();
  return data;
}

void ObjectLDR::parseOBJ(std::string filepath)
{
  std::string vertices;
  std::string normals;
  std::string textures;
  std::string indices;
  const char* data = this->read(filepath);
  for(int i = 0; i < strlen(data); i++)
  {
    // vertices parsing phase
    if(data[i] == 'v' && data[i+1] == ' ')
    {
      std::string v;
      for(int j = i; data[j] != '\n'; j++)
      {
        if(data[j] != ' ' && data[j] != 'v')
        {
          v.push_back(data[j]);
        }
        else
        {
          v.push_back(' ');
        }
      }
      vertices.append(v);
    }
    // normals
    if(data[i] == 'v' && data[i+1] == 'n' && data[i+2] == ' ')
    {
      std::string vn;
      for(int j = i; data[j] != '\n'; j++)
      {
        if(data[j] != 'v')
        {
          if(data[j] != 'n')
          {
            if(data[j] != ' ')
            {
              vn.push_back(data[j]);
            }
            else
            {
              vn.push_back(' ');
            }
          }
        }
      }
      normals.append(vn);
    }
    // textures
    if(data[i] == 'v' && data[i+1] == 't' && data[i+2] == ' ')
    {
      std::string vt;
      for(int j = i; data[j] != '\n'; j++)
      {
        if(data[j] != 'v')
        {
          if(data[j] != 't')
          {
            if(data[j] != ' ')
            {
              vt.push_back(data[j]);
            }
            else
            {
              vt.push_back(' ');
            }
          }
        }
      }
      textures.append(vt);
    }
    // indices
    if(data[i] == 'f' && data[i+1] == ' ')
    {
      std::string f;
      for(int j = i; data[j] != '\n'; j++)
      {
        if(data[j] != 'f')
        {
          if(data[j] != ' ')
          {
            if(data[j] != '/')
            {
              f.push_back(data[j]);
            }
            else
            {
              f.push_back(' ');
            }
          }
          else
          {
            f.push_back(' ');
          }
        }
      }
      indices.append(f);
    }

  }
  // vertices collection
  std::istringstream svertices(vertices);
  std::string vert;
  while(svertices>>vert)
  {
    this->v.push_back(stof(vert));
  }
  // normals collection
  std::istringstream snormals(normals);
  std::string norm;
  while(snormals>>norm)
  {
    this->n.push_back(stof(norm));
  }
  // textures collection
  std::istringstream stexture(textures);
  std::string text;
  while(stexture>>text)
  {
    this->vt.push_back(stof(text));
  }
  // normals
  std::istringstream sindices(indices);
  std::string ind;
  while(sindices>>ind)
  {
    this->f.push_back(stoi(ind));
  }
}

void ObjectLDR::parseMTL(std::string filepath){}

floatvector ObjectLDR::processOBJ()
{
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

  std::cout << "Organized Data" << std::endl;
  for(int i = 0; i < this->final.size(); i++)
  {
    std::cout << this->final[i] << std::endl;
  }
}

ObjectLDR::~ObjectLDR(){}
