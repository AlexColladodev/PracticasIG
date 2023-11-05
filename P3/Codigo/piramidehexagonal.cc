#include "auxiliar.h"
#include "malla.h"
#include "piramidehexagonal.h"

PiramideHexagonal::PiramideHexagonal(float h, float r, float r2)
{

   this->h = h;

   if(r != r2){
      this->r = r;
      this->r2 = r2;
   }

   createVertexArray();
   createTablaTriangulos();
   createColor();
   createLineasPuntosPiramide();
}

void PiramideHexagonal::createVertexArray(){
   
   //Para dibujar la piramide de pie, el radio de la base debe ser mayor al radio de la cima
   float radioBase = r;
   float radioCima = r2;

   if(r2 > r){
      radioBase = r2;
      radioCima = r;
   }

   //Seminario Trigonometria - PRIMER HEXAGONO

   float x, y, z;

    //Vertices del A al F
    for(int i = 0; i < 6; i++){

      x = radioBase * cos(RADIANES_HEXAGONO * i);
      y = 0;
      z = radioBase * sin(RADIANES_HEXAGONO * i);

      v.push_back({x, y, z});
    }

    //Seminario Trigonometria - SEGUNDO HEXAGONO

    //Vertices del A al F
    for(int i = 0; i < 6; i++){

      x = radioCima * cos(RADIANES_HEXAGONO * i);
      y = h;
      z = radioCima * sin(RADIANES_HEXAGONO * i);

      v.push_back({x, y, z});
    }
}

void PiramideHexagonal::createTablaTriangulos(){

   //Base
   f.push_back({5, 0, 1});
   f.push_back({4, 5, 1});
   f.push_back({4, 1, 2});
   f.push_back({4, 2, 3});

   //Cima
   f.push_back({8, 10, 9});
   f.push_back({8, 11, 10});
   f.push_back({8, 7, 11});
   f.push_back({7, 6, 11});

   //Lado 1
   f.push_back({1, 0, 7});
   f.push_back({0, 6, 7});

   //Lado 2
   f.push_back({0, 5, 6});
   f.push_back({5, 11, 6});

   //Lado 3
   f.push_back({5, 4, 11});
   f.push_back({4, 10, 11});

   //Lado 4
   f.push_back({2, 1, 8});
   f.push_back({1, 7, 8});

   //Lado 5
   f.push_back({3, 2, 9});
   f.push_back({2, 8, 9});

   //Lado 6
   f.push_back({4, 3, 10});
   f.push_back({3, 9, 10});

}

void PiramideHexagonal::createColor(){ //AMARILO p
   c.push_back({1.0f, 1.0f, 0.0f}); //0
   c.push_back({1.0f, 1.0f, 0.0f}); //1
   c.push_back({1.0f, 1.5f, 0.0f}); //2
   c.push_back({1.0f, 1.0f, 0.0f}); //3
   c.push_back({1.0f, 1.0f, 0.0f}); //4
   c.push_back({1.0f, 1.0f, 0.0f}); //5
   c.push_back({1.0f, 1.0f, 0.0f}); //6
   c.push_back({1.0f, 1.0f, 0.0f}); //7
   c.push_back({1.0f, 1.0f, 0.0f}); //8
   c.push_back({1.0f, 1.0f, 0.0f}); //9 
   c.push_back({1.0f, 1.0f, 0.0f}); //10
   c.push_back({1.0f, 1.0f, 0.0f}); //11
                        
}

void PiramideHexagonal::createLineasPuntosPiramide(){
   for(int i = 0; i < v.size(); i++){
      l.push_back({0.0f, 0.0f, 0.0f});
      p.push_back({1.0f, 0.0f, 0.0f});
   }
}

