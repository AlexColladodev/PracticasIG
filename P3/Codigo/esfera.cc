#include "auxiliar.h"
#include "malla.h"
#include "esfera.h"

Esfera::Esfera(int num_vertices, int num_instancias, float radio)
{

   this->radio = radio;
   createPerfil(num_vertices);   //Vertices

   crearMalla(this->v, num_instancias);

}

void Esfera::createPerfil(int num_vertices){
    float x, y, z;
    float angulo = (M_PI)/ num_vertices;

   for(int i = num_vertices; i >= 0; i--){
         x = radio * sin(angulo * i);
         y = radio * cos(angulo * i);
         z = 0 ;

         this->v.push_back({x, y, z});
   }
}