#include "auxiliar.h"
#include "malla.h"
#include "cono.h"

Cono::Cono(int num_vertices, int num_instancias, float altura, float radio)
{

   this->radio = radio;
   this->altura = altura;
   createPerfil(num_vertices);   //Vertices

   crearMalla(this->v, num_instancias);

}

//Los Cono tienen tapas
void Cono::createPerfil(int num_vertices){
    float angulo = atan(altura / radio);
    float x, y, z;

    for(int i = 0; i < num_vertices ; i++){
        float at = altura * i /(num_vertices - 1);

        x = at;;
        y = - x;
        z = 0.0f;

        this->v.push_back({x, y, z});
    }
    //Tapa inferior
    this->v.push_back({0, -altura, 0});
}