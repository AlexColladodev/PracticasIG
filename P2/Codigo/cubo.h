// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef CUBO_H_INCLUDED
#define CUBO_H_INCLUDED

#include "auxiliar.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class Cubo : public Malla3D
{

   private:
      float lado;

   public:
      Cubo(float lado=1.0f) ;

   private:
      void createVertexArray(float lado);
      void createTablaTriangulos();
      void createColorCubo();
      void createLineasPuntosCubo();

} ;




#endif
