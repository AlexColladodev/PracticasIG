#include "auxiliar.h"
#include "trigonometria.h"
#include "math.h"
#include "cmath"
#include "stdio.h"

/* Alexander Collado Rojas*/

// -----------------------------------------------------------------------------

Trigonometria::Trigonometria()
{
    createArrayData();
    calculoAnguloSegmentos();
    calculoLongitudCD();
    productoVectorial();

}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


/*
La distancia entre el vertice A y el centro nos viene dada de 2 unidades
Esta distancia sera el RADIO de la circunferencia
Un hexagono no esta inscrito en una circunferencia de radio R y que sus vertices tocan a la circunferencia

Al ser un hexagono (6) lados habria que dividir la circunferencia entera entre 6.
    360 / 6 = 60

Cada 60 grados habra un nuevo vertice

Radianes = Grados * (Pi / 180)

X = Radio * cos(Radianes)
Y = Radio * sen(Radianes)
*/
void Trigonometria::createArrayData()
{
    
	for(int i = 0; i < 18; i++){
        colorArray[i] = 0;
    }
    

    float Radianes = this->angulo * (M_PI / 180);
    float angulo_vertices = Radianes;

    //Vertice A (2, 0, 0)
	vertexArray[0] = radio; vertexArray[1] = 0; vertexArray[2] = 0;

    //Vertices del B al F
    for(int i = 3; i < 18; i+=3){
        vertexArray[i] = radio * cos(angulo_vertices); //X
        vertexArray[i+1] = radio * sin(angulo_vertices); //Y
        vertexArray[i+2] = 0; //Z, ya que estoy solamente haciendo un hexagono en 2D no hace falta calcularla

        angulo_vertices += Radianes;
    }

    //Cout de los segmentos
    std::cout << std::endl << "VERTICES EJERCICIO 2" << std::endl;
    std::cout << vertexArray[0] << ", " <<  vertexArray[1] << ", " << vertexArray[2] << std::endl;

    for(int i = 3; i < 18; i+=3){
        std::cout << vertexArray[i] << ", " <<  vertexArray[i+1] << ", " << vertexArray[i+2] << std::endl;
    }

    //EJERCICIO 5

    angulo_vertices = Radianes;

    //Vertice A (2, 0, 0)
	vertexArrayV[0] = vertexArray[6] + radio; vertexArrayV[1] = vertexArray[7]; vertexArrayV[2] = vertexArray[8];

    //Vertices del B al F
    for(int i = 3; i < 18; i+=3){
        vertexArrayV[i] = vertexArray[6] + radio * cos(angulo_vertices); //X
        vertexArrayV[i+1] = vertexArray[7] + radio * sin(angulo_vertices); //Y
        vertexArrayV[i+2] = 0; //Z, ya que estoy solamente haciendo un hexagono en 2D no hace falta calcularla

        angulo_vertices += Radianes;
    }

    //Cout de los segmentos
    std::cout << std::endl << "VERTICES EJERCICIO 5" << std::endl;
    std::cout << vertexArrayV[0] << ", " <<  vertexArray[1] << ", " << vertexArray[2] << std::endl;

    for(int i = 3; i < 18; i+=3){
        std::cout << vertexArrayV[i] << ", " <<  vertexArrayV[i+1] << ", " << vertexArrayV[i+2] << std::endl;
    }

    std::cout << std::endl;

}



/*
Ejercicio 4
Para calcular la longitud de un segmento usaremos el teorema de pitagoras respecto a la posicion de los vertices
Por ejemplo
Vertice C
    -1,    1.73205,     0
Vertice D
    -2, -1.74846e-07,   0
*/
double Trigonometria::medirSegmento(double x1, double x2, double y1, double y2){
    float segmento;

    segmento = sqrt(pow((x2 - x1),2) + pow((y2 - y1),2));

    return segmento;
}

/*
Ejercio 3
    Si unimos los 3 vertices nos da un triangulo no rectangulo pero si dividimos este triangulo no rectangulo en 2 partes respecto a su altura
    tenemos 2 triangulos rectangulos.
        Habria entonces que calcular el angulo de este triangulo sumarlo al lado recto (90 grados) y restarle 180 (ya que la suma de los angulos de un triangulo es 180)
        Como ambos triangulos son simetricos solo habria que hacer el calculo de uno de estos triangulos y multiplicarlo x2
        
    El segmento AB se calcula medidante teorema de pitagoras 
    El segmento CB medira lo mismo que el segmento AB ya que se trata de un hexagono regular y todos sus lados miden lo mismo

    El segmento AC se calcula mediante teorema de pitagoras

    Calculo la altura del triangulo tambien mediante pitagoras ya que tengo hipotenusa y lado adyacente
        hipotenusa = segmento AB o semento CB
        lado adyacente = secmento AC / 2. --> Recordar que se dividio el triangulo en 2 para hacerlo rectangulo

    De tal forma que
        altura = sqrt(hipotenusa2 - lado adyacente2)

    Por ultimo
        tan-1(altura / lado adyacente) nos da el angulo que toca sumarle a 90, restarle a 180 y multiplicarlo x2
*/
void Trigonometria::calculoAnguloSegmentos(){

    float segmentoAB;
    float segmentoAC;
    float altura;
    float anguloRad;
    float anguloGrad;
    float resultado;

    std::cout << "EJERCICIO 3" << std::endl;

    std::cout << "SEGMENTO AB: ";
    segmentoAB = this->medirSegmento(vertexArray[3], vertexArray[0], vertexArray[4], vertexArray[1]);
    std::cout << segmentoAB << std::endl;


    std::cout << "SEGMENTO AC: ";
    segmentoAC = this->medirSegmento(vertexArray[6], vertexArray[0], vertexArray[7], vertexArray[1]);
    std::cout << segmentoAC << std::endl;


    std::cout << "ALTURA: ";
    altura = sqrt(pow(segmentoAB, 2) - pow(segmentoAC/2, 2));
    std::cout << altura << std::endl;

    anguloRad = atan(altura / (segmentoAC / 2));//Esto esta en radiantes, pasarlo a grados

    anguloGrad = anguloRad * (180 / M_PI);

    std::cout << "ANGULO ENTRE SEGMENTO AB Y CB: ";
    resultado = 2 * (180-(90+anguloGrad));
    std::cout << resultado << " grados " << std::endl << std::endl;

}

void Trigonometria::calculoLongitudCD(){

    float longitud;
    
    std::cout << "EJERCICIO 4 " << std::endl;
    std::cout << "LONGITUD DEL SEGMENTO CD: ";
    longitud = this->medirSegmento(vertexArray[9], vertexArray[6], vertexArray[10], vertexArray[7]);
    std::cout << longitud << std::endl << std::endl;

}

/*
Ejercicio 6 --> Probablemente incorrecto

EL producto vectorial de AB x AF
    Primero sacar la magnitud del vector resultante
        AB = Avectorial
        AF = Bvectorial
        
        Avectorial x Bvectorial = Vvectorial

        |Avectorial x Bvectorial | = |Avectorial| x |Bvectorial| * sin(angulo)
            El angulo en este caso se ha calculado en el ejercicio anterior que es de 120 grados
        
        De tal forma que la magnitud de Vvectorial
            |Vvectorial| = 2 * 2 * sin(120)

    Ahora toca calcular las coordenadas de este vector

    Avectorial x Bvectorial = determinante de la matriz

        |  i   j   k  |
        | Ax   Ay  Az |
        | Bx   By  Bz |

    Las coordenadas de A seran las coordenadas del vertice B y las coordenadas de B seran las coordenadas del vertice F

        |  i      j     k  |
        | 1   1.73205   Az |
        | 1   -1.73205  Bz |  

    Avectorial x Bvectorial = i(Ay*Bz - Az*By) - j(Ax*Bz - Az*Bx) + k(AxBy - Ay*Bx)

    Esto nos da las coordenadas del vector y podemos añadir este vertice en el plano

    Nota: Casi lo mismo se hace con AF * AB pero hay cambia la matriz y el angulo sera en este caso 240
    Nota2: Me hace falta dibujarlo
*/
void Trigonometria::productoVectorial(){

    //Se puede representar como matriz
    float Ax = vertexArray[3];
    float Ay = vertexArray[4];
    float Az = vertexArray[5];
    float Bx = vertexArray[15];
    float By = vertexArray[16]; 
    float Bz = vertexArray[17]; 

    const float ANGULO = 120.0; //Podria hacer llamada
    const float RADIANES = 2.0944;

    float longitudAB = this->medirSegmento(Ax, vertexArray[0], Ay, vertexArray[1]);
    float longitudAF = this->medirSegmento(Bx, vertexArray[0], By, vertexArray[1]);
    
    float longitudVectorResultante = longitudAB * longitudAF * sin(RADIANES);

    Vx1 = (Ay * Bz) - (Az * By);
    Vy1 = (Ax * Bz) - (Az * Bx);
    Vz1 = (Ax * By) - (Ay * Bx);

    std::cout << "EJERCICIO 6 " << std::endl;

    std::cout << "PARA AB x AF " << std::endl;
    std::cout << "El vertice V estara en las coordenadas " << Vx1 << ", " << Vy1 << ", " << Vz1 << std::endl; //Comprobacion
    std::cout << "Con magnitud " << longitudVectorResultante << std::endl;

    Vx2 = (By * Az) - (Bz * Ay);
    Vy2 = (Bx * Az) - (Bz * Ax);
    Vz2 = (Bx * Ay) - (By * Ax);

    std::cout << "PARA AF x AB " << std::endl;
    std::cout << "El vertice V estara en las coordenadas " << Vx2 << ", " << Vy2 << ", " << Vz2 << std::endl; //Comprobacion
    std::cout << "Con magnitud " << longitudVectorResultante << std::endl;
}

void Trigonometria::draw()
{   // Se dibuja en modo inmediato, a modo de ejemplo para que veais la diferencia con los VBO

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertexArray );
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colorArray );
	glDrawArrays( GL_LINE_LOOP, 0, 6 ) ;

    //Preguntar por que no cierra el segundo hexagono
    /*
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertexArrayV );
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colorArray );
	glDrawArrays( GL_LINE_LOOP, 0, 6 ) ;
    */
}

/*
SALIDAS

VERTICES EJERCICIO 2
    2, 0, 0
    1, 1.73205, 0
    -1, 1.73205, 0
    -2, -1.74846e-07, 0
    -1, -1.73205, 0
    1, -1.73205, 0

VERTICES EJERCICIO 5
    1, 0, 0
    -1.78814e-07, 3.4641, 0
    -2, 3.4641, 0
    -3, 1.73205, 0
    -2, -1.19209e-07, 0
    -2.98023e-07, -1.19209e-07, 0

EJERCICIO 3
    SEGMENTO AB: 2
    SEGMENTO AC: 3.4641
    ALTURA: 1
    ANGULO ENTRE SEGMENTO AB Y CB: 120 grados 

EJERCICIO 4 
    LONGITUD DEL SEGMENTO CD: 2

EJERCICIO 6 
PARA AB x AF 
    El vertice V estara en las coordenadas 0, 0, -3.4641
    Con magnitud 3.46409
PARA AF x AB 
    El vertice V estara en las coordenadas -0, 0, 3.4641
    Con magnitud 3.46409

*/
