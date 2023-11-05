// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Esfera.h

//
// #############################################################################

#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Esfera con centro en el origen y radio

class Esfera : public ObjRevolucion
{

   private:
      float radio;

   public:
      //Constructor de la esfera con valores por defecto
      Esfera(int num_vertices = 10, int num_instancias = 20, float radio = 20) ;//Mientras mas vertices mas definida se ve la esfera

   private:
      void createPerfil(int num_vertices);

} ;




#endif
