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
void Malla3D::draw(visualizacion vis)
{

   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   if(id_vbo_ver == 0 && id_vbo_tri == 0 && id_vbo_c == 0){
      
         id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), v.data());

         id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*3*sizeof(int), f.data());

         id_vbo_c = CrearVBO(GL_ARRAY_BUFFER, c.size()*3*sizeof(float), c.data());

         id_vbo_lineas = CrearVBO(GL_ARRAY_BUFFER, l.size()*3*sizeof(float), l.data());

         id_vbo_puntos = CrearVBO(GL_ARRAY_BUFFER, p.size()*3*sizeof(float), p.data());
   }

   //Habilitar uso ArrayVertices y ArrayColores
   glEnableClientState( GL_VERTEX_ARRAY );
   glEnableClientState( GL_COLOR_ARRAY );

   //Especificar VBO para ArrayVertices
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   //Solido
   if(vis.SOLIDO){
      // especifícar cual es el VBO que vamos a usar
      glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_c );
      // Usar el buffer activo para el color
      glColorPointer ( 3 , GL_FLOAT , 0 , 0 );
      //desactivar buffer: VBO de colore
      glBindBuffer ( GL_ARRAY_BUFFER , 0 );
      //Relleno Solido
      glPolygonMode(GL_FRONT, GL_FILL);
      //Dibujar los triangulos
      this->habilitarUsarTriangulos();

   }

   //Linea
   if(vis.LINEA){
      // especifícar cual es el VBO que vamos a usar
      glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_lineas );
      // Usar el buffer activo para el color
      glColorPointer ( 3 , GL_FLOAT , 0 , 0 );
      //desactivar buffer: VBO de colore
      glBindBuffer ( GL_ARRAY_BUFFER , 0 );
      //Relleno Solido
      glPolygonMode(GL_FRONT, GL_LINE);
      //Dibujar los triangulos
      this->habilitarUsarTriangulos();
   }

   //Linea
   if(vis.PUNTOS){
      // especifícar cual es el VBO que vamos a usar
      glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_puntos );
      // Usar el buffer activo para el color
      glColorPointer ( 3 , GL_FLOAT , 0 , 0 );
      //desactivar buffer: VBO de coloCUBOre
      glBindBuffer ( GL_ARRAY_BUFFER , 0 );
      //Relleno Solido
      glPolygonMode(GL_FRONT, GL_POINT);
      //Aumentar tamaño de puntos para que se vean
      glPointSize(5);
      //Dibujar los triangulos
      this->habilitarUsarTriangulos();
   }
   
}

void Malla3D::visualizarLinea(){
   for(int i = 0; i < v.size(); i++){
      l.push_back({0.0f, 0.0f, 0.0f });//Negro
   }
}

void Malla3D::visualizarPuntos(){
   for(int i = 0; i < v.size(); i++){
      p.push_back({1.0f, 0.0f, 0.0f });//Rojo
   }
}

void Malla3D::createColor(){//Para objetos .ply
   for(int i = 0; i < v.size(); i++){
      c.push_back({1.0f, 0.0f, 1.0f});//Morado
   }
}

void Malla3D::habilitarUsarTriangulos(){
      // activar buffer: VBO de triángulos
      glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri );
      // dibujar con el buffer de índices activo
      glDrawElements ( GL_TRIANGLES , 3*f. size () , GL_UNSIGNED_INT , 0 ) ;
      // desactivar buffer: VBO de triángulos
      glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 );
}

