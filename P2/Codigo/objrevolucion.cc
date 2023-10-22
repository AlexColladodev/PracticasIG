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
   std::vector<Tupla3f> vert;
   ply::read_vertices(archivo, vert);

   crearMalla(vert, num_instancias);
   
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias) {
   std::vector<Tupla3f> vert;
   vert = archivo;

   crearMalla(vert, num_instancias);
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {

   Tupla3f polo_norte = {-1, -1, -1};
   Tupla3f polo_sur = {-1, -1, -1};
   Tupla3f auxiliar;
   bool tapa_sup = false;
   bool tapa_inf = false;
   bool ascendente = false;
   bool descendente = false;
   float epsilon = 0.000007;
   //Verificar si v[0][Y] y v[v.size() - 1][Y] para ver cual esta arriba de cual
      //Esto me indicara el orden ascendente o descendente
   if(perfil_original[0][1] > perfil_original[perfil_original.size() - 1][1]){
      descendente = true;
   }else{
      ascendente = true;
   }


   //Identificacion de existencia de tapas (polos)
   if(perfil_original[0][0] < epsilon){
      if(descendente){
         tapa_sup = true;
      } else if(ascendente){
         tapa_inf = true;
      }
   }

   if (perfil_original[perfil_original.size() - 1][0] < epsilon){
      if(descendente){
         tapa_inf = true;
      }else if(ascendente){
         tapa_sup = true;
      }
   }

   if(tapa_sup && tapa_inf){

      if(descendente){
         if(perfil_original[perfil_original.size() - 2][1] > perfil_original[perfil_original.size() - 1][1]){
            polo_norte = perfil_original[perfil_original.size() - 1];
            polo_sur = perfil_original[0];
         }else{
            polo_norte = perfil_original[0];
            polo_sur = perfil_original[perfil_original.size() - 1];
         }
      }
      if(ascendente){
         if(perfil_original[perfil_original.size() - 2][1] > perfil_original[perfil_original.size() - 1][1]){
            polo_sur = perfil_original[perfil_original.size() - 1];
            polo_norte = perfil_original[0];
         }else{
            polo_sur = perfil_original[0];
            polo_norte = perfil_original[perfil_original.size() - 1];
         }
      }  
      perfil_original.erase(perfil_original.begin()); //Elimino el primero
      perfil_original.erase(perfil_original.end() - 1);  //Elimino el ultimo 
   }

   if(tapa_sup && !tapa_inf){
      if(perfil_original[perfil_original.size() - 1][1] > perfil_original[0][1]){
         polo_norte = perfil_original[perfil_original.size() - 1];
         ascendente = true;
         perfil_original.erase(perfil_original.end() - 1);
      }else{
         polo_norte = perfil_original[0];
         descendente=true;
         perfil_original.erase(perfil_original.begin());
      }
   }else if(!tapa_sup && tapa_inf){
      if(perfil_original[perfil_original.size() - 1][1] > perfil_original[0][1]){
         polo_sur = perfil_original[0];
         ascendente = true;
         perfil_original.erase(perfil_original.begin());
      }else{
         polo_sur = perfil_original[perfil_original.size() - 1];
         descendente = true;
         perfil_original.erase(perfil_original.end() - 1);
      }
   }

   int tamanioM = perfil_original.size();
   float x, y, z;
   float angulo;
   float radianes;

   std::vector<Tupla3f> vertices_completos;

   //Crear vertices
   for(int i = 0; i < num_instancias; i++){
      angulo = (2 * M_PI)/ num_instancias;
      for(int j = 0; j < tamanioM; j++){
         x = perfil_original[j][0] * cos(angulo * i);
         y = perfil_original[j][1];
         z = -1 * perfil_original[j][0] * sin(angulo * i); //Multiplicarlo para girar bien

         vertices_completos.push_back({x, y, z});
      }
   }


   //SI tengo ambas tapas primero la inferior y luego superior
   if(tapa_sup && tapa_inf){
      vertices_completos.push_back(polo_sur);
      vertices_completos.push_back(polo_norte);
   }

   //Sino inserto la que existe
   if(tapa_sup && !tapa_inf){
      vertices_completos.push_back(polo_norte);
   }else if(!tapa_sup && tapa_inf){
      vertices_completos.push_back(polo_sur);
   }


   //Crear tabla de triangulos 
      //Cuidado con el sentido horario / antihorario
   
   
   std::cout << "TAPA SUP "  <<  tapa_sup << std::endl;
   std::cout << "TAPA INF " << tapa_inf << std::endl;
   std::cout << "DESCENDENTE "  <<  descendente << std::endl;
   std::cout << "ASCENDENTE " << ascendente << std::endl;
   std::cout << "POLO NORTE " << polo_norte << std::endl;
   std::cout << "POLO SUR " << polo_sur << std::endl;
   

   for(int i = 0; i < num_instancias; i++){
      for(int j = 0; j < tamanioM - 1; j++){
         int a, b;
         a = tamanioM * i + j;
         b = tamanioM * ((i + 1) % num_instancias) + j;

         if(descendente){
            f.push_back({a, b+1, b});
            f.push_back({a, a+1, b+1});
         }else if (ascendente){
            f.push_back({a, b, b+1});
            f.push_back({a, b+1, a+1});
         }
      }
   }


   //Crear triangulos con tapas

   int indicePoloUnico = vertices_completos.size() - 1;
   int indicePoloNorte = indicePoloUnico;
   int indicePoloSur = vertices_completos.size() - 2;

   if(ascendente){
      if(tapa_sup && !tapa_inf){
         for(int i = 0; i < num_instancias; i++){
            f.push_back({(tamanioM * (i + 2) - 1)%(tamanioM * num_instancias), indicePoloUnico, (tamanioM * (i + 1) - 1)});
         }
      }

      if(tapa_inf && !tapa_sup){
         for(int i = 0; i < num_instancias; i++){
            f.push_back({tamanioM * (i), indicePoloUnico, tamanioM * (i + 1) % (tamanioM * (num_instancias))});
         }
      }
      
      if(tapa_sup && tapa_inf){
         for(int i = 0; i < num_instancias; i++){
            f.push_back({(tamanioM * (i + 2) - 1)%(tamanioM * num_instancias), indicePoloNorte, (tamanioM * (i + 1) - 1)});
         }

         for(int i = 0; i < num_instancias; i++){
            f.push_back({tamanioM * (i), indicePoloSur, tamanioM * (i + 1) % (tamanioM * (num_instancias))});
         }
      }
   }

   if(descendente){
      if(tapa_sup && !tapa_inf){
         for(int i = 0; i < num_instancias; i++){
            f.push_back({tamanioM * (i + 1) % (tamanioM * (num_instancias)), indicePoloUnico, tamanioM * (i)});
         }
      }
   
      if(tapa_inf && !tapa_sup){
         for(int i = 0; i < num_instancias; i++){
            f.push_back({(tamanioM * (i + 1) - 1), indicePoloUnico, (tamanioM * (i + 2) - 1)%(tamanioM * num_instancias) });
         }
      }
      
      if(tapa_sup && tapa_inf){
         for(int i = 0; i < num_instancias; i++){
            f.push_back({tamanioM * (i + 1) % (tamanioM * (num_instancias)), indicePoloNorte, tamanioM * (i)});
         }

         for(int i = 0; i < num_instancias; i++){
            f.push_back({(tamanioM * (i + 1) - 1), indicePoloSur, (tamanioM * (i + 2) - 1)%(tamanioM * num_instancias) });
         }

      }
      
   }

   this->v = vertices_completos;
}

   /*
   for(int i = 0; i < 3; i++){
      std::cout << perfil_original[perfil_original.size() - 3]
   }
   */

   /*
   std::cout << "VERTICES " << std::endl;

   for(int i = 0; i < v.size(); i++){
      std::cout << v[i];
   }
   */

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
