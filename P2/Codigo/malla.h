// #############################################################################
//
// Informática Gráfica D (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "auxiliar.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   // función que dibuja el objeto en modo diferido (usando VBOs)
   void draw(visualizacion vis) ;
   void habilitarUsarTriangulos();
   void crearColorLineaPuntos();

   protected:

   //Crear vbo y metodo asociado
   GLuint id_vbo_tri = 0;
   GLuint id_vbo_ver = 0;
   GLuint id_vbo_c = 0;
   GLuint id_vbo_lineas = 0;
   GLuint id_vbo_puntos = 0;
   GLuint CrearVBO( GLuint tipo_vbo , GLuint tam , GLvoid * puntero_ram );
   

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo

   // completar P1: tabla de colores
   std::vector<Tupla3f> c;
   std::vector<Tupla3f> p;
   std::vector<Tupla3f> l;
   
} ;


#endif
