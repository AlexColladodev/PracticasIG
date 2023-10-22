// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cono.h

//
// #############################################################################

#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cono con centro en el origen y radio

class Cono : public ObjRevolucion
{

   private:
      float radio;
      float altura;

   public:
      //Constructor de la esfera con valores por defecto
      Cono(int num_vertices = 3, int num_instancias = 20, float altura = 20, float radio = 20) ;//Mientras mas vertices mas definida se ve la esfera

   private:
      void createPerfil(int num_vertices);

} ;




#endif
