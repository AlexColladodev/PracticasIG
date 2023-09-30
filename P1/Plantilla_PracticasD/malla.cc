#include "auxiliar.h"
#include "malla.h"

// *****************************************************************************
//
// IG_D Clase Malla3D
//
// *****************************************************************************
// -----------------------------------------------------------------------------
// Función de visualización de la malla,

//De P1.pdf
GLuint Malla3D::CrearVBO( GLuint tipo_vbo , GLuint tam , GLvoid * puntero_ram ){
   GLuint id_vbo ; // resultado: identificador de VBO
   glGenBuffers ( 1 , & id_vbo ); // crear nuevo VBO, obtener identificador
   glBindBuffer ( tipo_vbo , id_vbo ); // activar el VBO usando su identificador

   // esta instrucción hace la transferencia de datos desde RAM hacia GPU
   glBufferData ( tipo_vbo , tam , puntero_ram , GL_STATIC_DRAW );
   glBindBuffer ( tipo_vbo , 0 ); // desactivación del VBO (activar 0)

   return id_vbo ; // devolver el identificador resultado
}

//De P1.pdf
void Malla3D::draw()
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   if(id_vbo_ver == 0 && id_vbo_tri == 0 && id_vbo_c == 0){
         id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size() * 3 * GL_FLOAT, v.data());

         id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size() * 3 * GL_UNSIGNED_INT, f.data());

         id_vbo_c = CrearVBO(GL_ARRAY_BUFFER, c.size() * 3 * GL_FLOAT, c.data());
   }


   if(id_vbo_c != 0){
      // habilitar uso de array de colores
      glEnableClientState ( GL_COLOR_ARRAY );
      // especifícar cual es el VBO que vamos a usar
      glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_c );
      // Usar el buffer activo para el color
      glColorPointer ( 3 , GL_FLOAT , 0 , 0 );
      //desactivar buffer: VBO de colore
      glBindBuffer ( GL_ARRAY_BUFFER , 0 );
   }

   if(id_vbo_ver != 0){
      // activar buffer: VBO de vértices
      glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_ver );
      // usar como buffer de vertices el actualmente activo
      glVertexPointer ( 3 , GL_FLOAT , 0 , 0 );
      // deactivar buffer: VBO de vértices.
      glBindBuffer ( GL_ARRAY_BUFFER , 0 );
      // habilitar el uso de tabla de vértices
      glEnableClientState ( GL_VERTEX_ARRAY );
   }
   
   if(id_vbo_tri != 0){
      // activar buffer: VBO de triángulos
      glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri );
      // dibujar con el buffer de índices activo
      glDrawElements ( GL_TRIANGLES , 3*f. size () , GL_UNSIGNED_INT , 0 ) ;
      // desactivar buffer: VBO de triángulos
      glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 );
      // desactivar uso de array de vértices
      glDisableClientState ( GL_VERTEX_ARRAY );
   }
   
}

