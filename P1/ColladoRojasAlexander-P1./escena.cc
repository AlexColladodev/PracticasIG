

#include "auxiliar.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    cubo = new Cubo(50);
    piramide = new PiramideHexagonal(100, 25, 50);

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );

   glEnable( GL_CULL_FACE );

   obj = {0, 0}; //CUBO - PIRAMIDE
   vis = {0, 0, 1}; // PUNTOS - LINEAS - SOLIDO
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
    ejes.draw();
    
    // COMPLETAR
    //   Dibujar los diferentes elementos de la escena
    // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
    // y hacer 
    // cubo->draw()
    // o    piramide->draw()

   /*Esto es posible ya que Cubo y Piramide heredan de Malla3D
   cubo->draw();
    piramide->draw();
    Para poder dibujarlos simultaneamente
    */
    
      if(obj.CUBO){
         cubo->draw(vis);
      }
      if (obj.PIRAMIDE){
         piramide->draw(vis);
      }
   
    
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;

   switch(modoMenu){
      case SELOBJETO:
         switch(toupper(tecla)){
         case 'C':
            obj.CUBO = (obj.CUBO + 1) % 2;
            break;

         case 'P':
            obj.PIRAMIDE = (obj.PIRAMIDE + 1) % 2;
            break;
         }
         break;//SELOBJETO
      
      case SELVISUALIZACION:
         switch(toupper(tecla)){ 
            case 'D':
               vis.PUNTOS = (vis.PUNTOS + 1) % 2;
               break;

            case 'L':
               vis.LINEA = (vis.LINEA + 1) % 2;
               break;

            case 'S':
               vis.SOLIDO = (vis.SOLIDO + 1) % 2;
               break;
         }
         break;//SELVIS
   }


   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
         cout << "SALIENDO " << endl;
         break ;
      case 'O' :

         modoMenu=SELOBJETO; 
         std::cout << "MODO SELECCION DE OBJETO" << std::endl;
         std::cout << "\tC - DIBUJAR/BORRAR CUBO" << std::endl;
         std::cout << "\tP - DIBUJAR/BORRAR PIRAMIDE HEXAGONAL" << std::endl;
         std::cout << "\tQ - VOLVER AL MENU PRINCIPAL" << std::endl;

         break ;

        case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         std::cout << "MODO SELECCION DE VISUALIZACION" << std::endl;
         std::cout << "\tD - VER/OCULTAR PUNTOS" << std::endl;
         std::cout << "\tL - VER/OCULTAR LINEAS" << std::endl;
         std::cout << "\tS - VER/OCULTAR SOLIDO" << std::endl;
         std::cout << "\tQ - VOLVER AL MENU PRINCIPAL" << std::endl;

         break ;

            
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}

