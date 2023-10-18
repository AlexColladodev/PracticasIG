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

//El bool tapa_sup y bo
ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias) {
   //Leer vertices
   ply::read_vertices(archivo, this->v);

   crearMalla(this->v, num_instancias);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias) {
    
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {

   Tupla3f polo_norte;
   Tupla3f polo_sur;
   Tupla3f auxiliar;
   bool tapa_sup = false;
   bool tapa_inf = false;
   bool ascendente = false;
   bool descendente = false;
   float epsilon = 0.00000007;

   //Verificar si v[0][Y] y v[v.size() - 1][Y] para ver cual esta arriba de cual
      //Esto me indicara el orden ascendente o descendente
   if(v[0][1] > v[v.size() - 1][1]){
      descendente = true;
   }else{
      ascendente = true;
   }

   //Identificacion de existencia de tapas (polos)
   if(v[0][0] < epsilon){
      if(descendente){
         tapa_sup = true;
      } else if(ascendente){
         tapa_inf = true;
      }
   } else if (v[v.size() - 1][0] < epsilon){
      if(descendente){
         tapa_inf = true;
      }else if(ascendente){
         tapa_sup = true;
      }
   }

   if(tapa_sup && tapa_inf){

      auxiliar = this->v[0];
      this->v.erase(v.begin());
      this->v.push_back(auxiliar);

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

   //Crear vertices
   for(int i = 1; i < num_instancias; i++){
      angulo = (2 * M_PI)/ num_instancias;
      for(int j = 0; j < tamanioM; j++){
         x = v[j][0] * cos(angulo * i);
         y = v[j][1];
         z = -1 * v[j][0] * sin(angulo * i); //Multiplicarlo para girar bien

         v.push_back({x, y, z});
      }
   }

   //Crear tabla de triangulos 
      //Cuidado con el sentido horario / antihorario
   
   for(int i = 0; i < num_instancias; i++){
      for(int j = 0; j < tamanioM; j++){
         int a, b;
         a = tamanioM * i + j;
         b = tamanioM * ((i + 1) % num_instancias) + j;

         f.push_back({a, b+1, b});
         f.push_back({a, a+1, b+1});
      }
   }

   std::cout << f.size() << std::endl;

   //Crear triangulos con tapas









}

   /*
   std::cout << "VERTICES " << std::endl;

   for(int i = 0; i < v.size(); i++){
      std::cout << v[i];
   }*/

   /*
      Tupla3f auxTop;
   bool tapa_sup = false;
   bool tapa_inf = false;
   float epsilon = 0.0000007;

   if(v[0][0] < epsilon){
   }
   
   //Si tiene tapa superior e inferior debo comprobar cual es la de arriba y cual es la de abajo
   if(tapa_sup && tapa_inf){

      //Las tapas estan al final del vector
      auxTop = this->v[0];
      this->v.erase(v.begin());
      this->v.push_back(auxTop);

   }
   */
