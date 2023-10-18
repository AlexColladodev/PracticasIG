#include "auxiliar.h"
#include "objrevolucion.h"
#include "ply_reader.h"




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   //Leer vertices
   ply::read_vertices(archivo, this->v);
   
   Tupla3f auxTop;
   
   //Si tiene tapa superior e inferior debo comprobar cual es la de arriba y cual es la de abajo
   if(tapa_sup && tapa_inf){

      //Las tapas estan al final del vector
      auxTop = this->v[0];
      this->v.erase(v.begin());
      this->v.push_back(auxTop);

   }

   crearMalla(this->v, num_instancias, tapa_sup, tapa_inf);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
    
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf) {

   Tupla3f polo_norte;
   Tupla3f polo_sur;

   
   bool ascendente = false;//Orden descendente
   bool descendente = false;//Orden ascendente

   if(tapa_sup && tapa_inf){

      if(this->v[v.size() - 2][1] > this->v[v.size() - 1][1]){
         ascendente = true;
         polo_norte = v[v.size() - 2];
         polo_sur = v[v.size() - 1];
      }else{
         descendente = true;
         polo_norte = v[v.size() - 1];
         polo_sur = v[v.size() - 2];
      }

      v.erase(v.end() - 2, v.end());   
   }

   if(tapa_sup && !tapa_inf){
      if(v[v.size() - 1][1] > v[0][1]){
         polo_norte = v[v.size() - 1];
         ascendente = true;
         v.erase(v.end());
      }else{
         polo_norte = v[0];
         descendente=true;
         v.erase(v.begin());
      }
   }else if(!tapa_sup && tapa_inf){
      if(v[v.size() - 1][1] > v[0][1]){
         polo_sur = v[0];
         ascendente = true;
         v.erase(v.begin());
      }else{
         polo_sur = v[v.size() - 1];
         descendente = true;
         v.erase(v.end() - 1);
      }
   }

   int tamanioM = v.size();
   float x, y, z;
   float angulo;
   float radianes;

   std::cout << "INICIO TAM VER " << tamanioM << std::endl;

   //Crear vertices
   for(int i = 1; i < num_instancias; i++){
      angulo = (2 * M_PI)/ num_instancias;
      for(int j = 0; j < tamanioM; j++){
         x = v[j][0] * cos(angulo * i);
         y = v[j][1];
         z = -1 * v[j][0] * sin(angulo * i);

         v.push_back({x, y, z});
      }
   }

   std::cout << "VERTICES " << v.size() << std::endl;

   for(int i = 13; i < 26; i++){
      std::cout << v[i] << std::endl;
   }

   //Crear tabla de triangulos 
   /*
   for(int i = 0; i < num_instancias; i++){
      for(j = 0; j < )
   }*/








}

   /*
   std::cout << "VERTICES " << std::endl;

   for(int i = 0; i < v.size(); i++){
      std::cout << v[i];
   }*/
