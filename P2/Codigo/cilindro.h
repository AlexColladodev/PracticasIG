// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cilindro.h

//
// #############################################################################

#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cilindo con centro en el origen y radio

class Cilindro : public ObjRevolucion
{

   private:
      float radio;
      float altura;

   public:
      //Constructor de la esfera con valores por defecto
      Cilindro(int num_vertices = 4, int num_instancias = 20, float altura = 20, float radio = 20) ;//Mientras mas vertices mas definida se ve la esfera

   private:
      void createPerfil(int num_vertices);

} ;




#endif
