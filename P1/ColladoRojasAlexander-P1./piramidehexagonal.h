// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: piramidehexagonal.h

//
// #############################################################################

#ifndef PIRAMIDE_HEXAGONAL_H_INCLUDED
#define PIRAMIDE_HEXAGONAL_H_INCLUDED

#include "auxiliar.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Pirámide de base hexagonal con base centrada en el origen 

class PiramideHexagonal: public Malla3D
{

   private:
      float h;
      float r;
      float r2;
      const float GRADOS_HEXAGONO = 60.0;
      const float RADIANES_HEXAGONO = GRADOS_HEXAGONO * (M_PI / 180);

   public:
      PiramideHexagonal(float h=1.0,float r=0.5, float r2=1.0);

   private: 
      void createVertexArray();
      void createTablaTriangulos();
      void createColor();
} ;




#endif
