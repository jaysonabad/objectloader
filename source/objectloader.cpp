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
#include <regex>
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
            faces.append(temp);
          }
        }
      }
    }
  }

  /// process the variables
  for(int i = 0; i < this->v.size(); i+=3)
  {
    vector3 v;
    v.x = this->v[i];
    v.y = this->v[i+1];
    v.z = this->v[i+2];
    this->vertices.push_back(v);
  }

  for(int i = 0; i < this->vt.size(); i+=2)
  {
    vector2 vt;
    vt.x = this->vt[i];
    vt.y = 1 - this->vt[i+1];
    this->textures.push_back(vt);
  }

  for(int i = 0; i < this->n.size(); i+=3)
  {
    vector3 n;
    n.x = this->n[i];
    n.y = this->n[i+1];
    n.z = this->n[i+2];
    this->normals.push_back(n);
  }

  /// parsing faces
  for(string face : faces) {
    istringstream sface(regex_replace(face, regex("/"), " "));
    string f_index;
    while(sface >> f_index) {
      this->f.push_back(stoi(f_index) - 1);
    }
  }
  
    // indexing the variables
  for(int i = 0; i < this->f.size(); i+=3)
  {
    this->indexed_vertices.push_back(this->vertices[this->f[i]]);
    this->indexed_textures.push_back(this->textures[this->f[i+1]]);
    this->indexed_normals.push_back(this->normals[this->f[i+2]]);
  }
  // value of vertices
  for(int i = 0; i < this->indexed_vertices.size(); i++) {
    this->vertex_final.push_back(this->indexed_vertices[i].x);
    this->vertex_final.push_back(this->indexed_vertices[i].y);
    this->vertex_final.push_back(this->indexed_vertices[i].z);
    this->vertex_final.push_back(this->indexed_textures[i].x);
    this->vertex_final.push_back(this->indexed_textures[i].y);
    this->vertex_final.push_back(this->indexed_normals[i].x);
    this->vertex_final.push_back(this->indexed_normals[i].y);
    this->vertex_final.push_back(this->indexed_normals[i].z);
    this->indices.push_back(i);
  }
}

void ObjectLDR::parseMTL(std::string filepath){}

floatvector NLoader::get_vertices()
{
  return this->vertex_final;
}

floatvector3 ObjectLDR::getVertices()
{
  return this->indexed_vertices;
}

floatvector2 ObjectLDR::getTextures()
{
  return this->indexed_textures;
}

floatvector3 ObjectLDR::getNormals()
{
  return this->indexed_normals;
}

uintvector ObjectLDR::getIndex()
{
  return this->indices;
}

unsigned int ObjectLDR::get_indices_size() {
  return this->indices.size();
}

unsigned int ObjectLDR::get_vertex_size() {
  return this->vertex_final.size();
}

ObjectLDR::~ObjectLDR(){}
