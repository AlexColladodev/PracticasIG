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
   f.push_back({5, 1, 0});
   f.push_back({5, 2, 1});
   f.push_back({5, 4, 2});
   f.push_back({4, 3, 2});

   //Cima
   f.push_back({10, 8, 9});
   f.push_back({10, 7, 8});
   f.push_back({10, 11, 7});
   f.push_back({11, 6, 7});

   //Lado 1
   f.push_back({4, 5, 10});
   f.push_back({5, 11, 10});

   //Lado 2
   f.push_back({5, 0, 11});
   f.push_back({0, 6, 11});

   //Lado 3
   f.push_back({0, 1, 6});
   f.push_back({1, 7, 6});

   //Lado 4
   f.push_back({1, 2, 7});
   f.push_back({2, 8, 7});

   //Lado 5
   f.push_back({2, 3, 8});
   f.push_back({3, 9, 8});

   //Lado 6
   f.push_back({3, 4, 9});
   f.push_back({4, 10, 9});

}

void PiramideHexagonal::createColor(){ //ROJA pero con variaciones para que se note la piramide
   c.push_back({1.0f, 0.05, 0.0f}); //0
   c.push_back({1.0f, 0.0f, 0.5f}); //1
   c.push_back({1.0f, 0.2f, 0.0f}); //2
   c.push_back({1.0f, 0.0f, 0.2f}); //3
   c.push_back({1.0f, 0.7f, 0.0f}); //4
   c.push_back({1.0f, 0.0f, 0.7f}); //5
   c.push_back({1.0f, 0.8f, 0.0f}); //6
   c.push_back({1.0f, 0.0f, 0.8f}); //7
   c.push_back({1.0f, 0.1f, 0.0f}); //8
   c.push_back({1.0f, 0.0f, 0.1f}); //9 
   c.push_back({1.0f, 0.4f, 0.0f}); //10
   c.push_back({1.0f, 0.0f, 0.4f}); //11
                        
}

