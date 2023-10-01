#include "auxiliar.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   this->lado = lado;
   createVertexArray(this->lado);   //Vertices
   createTablaTriangulos();         //Tabla de triangulos
   createColorCubo();
   visualizarLinea();
   visualizarPuntos();

}

//Son 9 vertices
   //Uno de sus vertices en el origen, es decir que el cubo no estara centrado con la escena
void Cubo::createVertexArray(float lado){

   v.push_back({0, 0, 0});         //0
   v.push_back({lado, 0, 0});      //1
   v.push_back({0, lado, 0});      //2
   v.push_back({lado, lado, 0});   //3
   v.push_back({lado, 0, -lado});   //4
   v.push_back({lado, lado, -lado});   //5
   v.push_back({0, lado, -lado});   //6
   v.push_back({0, 0, -lado});   //7
}

void Cubo::createTablaTriangulos(){

   //Cara frontal
   f.push_back({0, 1, 2});
   f.push_back({1, 3, 2});

   //Cara derecha
   f.push_back({1, 4, 3});
   f.push_back({4, 5, 3});

   //Cara trasera
   f.push_back({4, 7, 5});
   f.push_back({7, 6, 5});

   //Cara izquierda
   f.push_back({7, 0, 6});
   f.push_back({0, 2, 6});

   //Cara superior
   f.push_back({3, 5, 2});
   f.push_back({5, 6, 2});

   //Cara inferior
   f.push_back({0, 7, 1});
   f.push_back({7, 4, 1});  
}

void Cubo::createColorCubo(){//VERDE
   //Color segun vertice
   c.push_back({0.0f, 1.0f, 0.0f}); //0
   c.push_back({0.0f, 1.0f, 0.0f}); //1
   c.push_back({0.0f, 1.0f, 0.0f}); //2
   c.push_back({0.0f, 1.0f, 0.0f}); //3
   c.push_back({0.0f, 1.0f, 0.0f}); //4
   c.push_back({0.0f, 1.0f, 0.0f}); //5
   c.push_back({0.0f, 1.0f, 0.0f}); //6
   c.push_back({0.0f, 1.0f, 0.0f}); //7
   
}

