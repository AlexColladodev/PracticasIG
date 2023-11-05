#include "auxiliar.h"
#include "malla.h"
#include "cilindro.h"

Cilindro::Cilindro(int num_vertices, int num_instancias, float altura, float radio)
{

   this->radio = radio;
   this->altura = altura;
   createPerfil(num_vertices);   //Vertices

   crearMalla(this->v, num_instancias);

}

//Los cilindros tienen tapas
void Cilindro::createPerfil(int num_vertices){
    float x, y, z;
    float angulo = (M_PI)/ num_vertices;

    //Tapa inferior
    this->v.push_back({0, -altura / 2, 0});
    this->v.push_back({radio, -altura / 2, 0});

    int segmentos = num_vertices - 3;

    std::cout << "SEGMENTOS " << segmentos;

    float tam_segmento = altura / segmentos;

   for(int i = 1; i < segmentos ; i++){

         x = radio;
         y = (-altura / 2) + (i * tam_segmento);
         z = 0 ;

         this->v.push_back({x, y, z});
   }

   this->v.push_back({radio, altura / 2, 0});

    //Tapa superior
    this->v.push_back({0, altura / 2, 0});

}