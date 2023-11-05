#ifndef _TRIGONOMETRIA_H
#define _TRIGONOMETRIA_H

class Trigonometria {

private:
	float axisSize;
	float vertexArray[18];
	float vertexArrayV[18];
	//float vertexArrayVI[45];

    float radio = 2.0;
    float angulo = 60.0;


	float colorArray[18];
	//float colorArrayVI[45];

	float Vx1, Vy1, Vz1, Vx2, Vy2, Vz2;

public:
	Trigonometria();
	void draw();

private:
	void createArrayData();
	void createArrayDataVI();
	double medirSegmento(double x1, double x2, double y1, double y2);
	void calculoAnguloSegmentos();
	void calculoLongitudCD();
	void productoVectorial();
	
};
#endif
