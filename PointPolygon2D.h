#ifndef POINT_POLYGON_2D_H
#define POINT_POLYGON_2D_H

#define _USE_MATH_DEFINES // for C++
#include <math.h>

#include "Point2D.h"
#include "Segment2D.h"
#include "CompareDouble.h"

namespace point_polygon_2D
{
	/**********************************************************************************************//**
	 * @enum	PointPolygon2D
	 *
	 * @brief	Valores que representan en que posición se encuentra un punto con respecto a un polígono.
	 **************************************************************************************************/
	enum PointPolygon2D 
	{
		///< Indica que el punto está dentro del polígono.
		INSIDE,

		///< Indica que el punto está fuera del polígono.
		OUTSIDE,	

		///< Indica que el punto está en uno de los vertices del polígono.
		VERTEX,		

		///< Indica que el punto está en un borde del polígono.
		BOUNDARY	
	};

	/**********************************************************************************************//**
	 * @fn	double degreesAxisX(Point2D *p1, Point2D *p2)
	 *
	 * @brief	Función que obtiene el ángulo de un segmento de línea con respecto al eje X.
	 *
	 * @author	Enrique Alonso
	 * @date	21/01/2014
	 *
	 * @param [in,out]	p1	Primer punto del segmento línea.
	 * @param [in,out]	p2	Segundo punto del segmento línea.
	 *
	 * @return	Un double.
	 **************************************************************************************************/
	double degreesAxisX(Point2D *p1, Point2D *p2) 
	{
		Point2D p = Point2D(p2->getX() - p1->getX(), p2->getY() - p1->getY());
		if (isEqual(p.getX(), 0.0)) 
		{
			return isGreaterThan(p.getY(), 0.0) ? 90.0 : 270.0;
		}
		if (isLowerThan(p.getX(), 0.0)) 
		{
			return (atan(p.getY() / p.getX()) + M_PI) * 180.0 / M_PI;
		}
		if (isLowerThan(p.getY(), 0.0)) 
		{
			return (atan(p.getY() / p.getX()) + 2 * M_PI) * 180.0 / M_PI;
		}
		return (atan(p.getY() / p.getX())) * 180.0 / M_PI;
	}

	/**********************************************************************************************//**
	 * @fn	double degreesAxisX(Segment2D *seg)
	 *
	 * @brief	Función que obtiene el ángulo de un segmento de línea con respecto al eje X.
	 *
	 * @author	Enrique Alonso
	 * @date	21/01/2014
	 *
	 * @param [in,out]	seg	Segmento de línea.
	 *
	 * @return	Un double.
	 **************************************************************************************************/
	double degreesAxisX(Segment2D *seg) 
	{
		return degreesAxisX(seg->getP1(), seg->getP1());
	}

	/**********************************************************************************************//**
	 * @fn	int checkSign(Point2D *p1, Point2D *p2, Point2D *p)
	 *
	 * @brief	Empleado para saber si el ángulo se va a sumar o a restar, esto depende del sentido
	 * 			que sigan los puntos.
	 *
	 * @author	Enrique Alonso
	 * @date	21/01/2014
	 *
	 * @param [in,out]	p1	
	 * @param [in,out]	p2	
	 * @param [in,out]	p 	
	 *
	 * @return	An int.
	 **************************************************************************************************/
	int checkSign(Point2D *p1, Point2D *p2, Point2D *p) 
	{
		double angleLine1 = degreesAxisX(p, p1);
		double angleLine2 = degreesAxisX(p, p2);

		if (isLowerThan((angleLine2 - angleLine1), 0.0)) 
		{
			angleLine2 = 360.0 - abs((long)(angleLine2 - angleLine1));
		}
		else 
		{
			angleLine2 -= angleLine1;
		}

		if (isLowerThan(angleLine2, 180.0)) 
		{
			return -1;
		}
		return 1;
	}

	/**********************************************************************************************//**
	 * @fn	PointPolygon2D pointInPolygon(std::vector<Point2D*> polygonVertex, Point2D *p)
	 *
	 * @brief	Método que nos devuelve un enumerable que nos indica en que parte se encuentra
	 * 			un punto dado con respecto a un polígono.
	 * 			Se utilizó el Algoritmo Radial para llevar a cabo este proceso.
	 *
	 * @author	Enrique Alonso
	 * @date	21/01/2014
	 *
	 * @param [in,out]	polygonVertex	Puntos que conforman el contorno del polígono.
	 * @param [in,out]	p			 	Punto.
	 *
	 * @return	Un PointPolygon2D.
	 **************************************************************************************************/
	PointPolygon2D pointInPolygon(std::vector<Point2D*> polygonVertex, Point2D *p)
	{
		if (!isEqual(polygonVertex.at(0)->getX(), polygonVertex.at(polygonVertex.size() - 1)->getX()) ||
			!isEqual(polygonVertex.at(0)->getY(), polygonVertex.at(polygonVertex.size() - 1)->getY()))
		{
			polygonVertex.push_back(polygonVertex.at(0));
		}

		for (size_t i = 0; i < polygonVertex.size(); i++) 
		{
			if (isEqual(p->getX(), polygonVertex.at(i)->getX()) && isEqual(p->getY(), polygonVertex.at(i)->getY())) 
			{
				return VERTEX;
			}
		}

		double angulo = 0.0, auxAngulo, a, b, c;

		for (size_t i = 0; i < polygonVertex.size() - 1; i++) 
		{
			b = sqrt(pow(p->getX() - polygonVertex.at(i)->getX(), 2) + pow(p->getY() - polygonVertex.at(i)->getY(), 2));
			c = sqrt(pow(p->getX() - polygonVertex.at(i + 1)->getX(), 2) + pow(p->getY() - polygonVertex.at(i + 1)->getY(), 2));
			a = sqrt(pow(polygonVertex.at(i)->getX() - polygonVertex.at(i + 1)->getX(), 2) + pow(polygonVertex.at(i)->getY() - polygonVertex.at(i + 1)->getY(), 2));

			auxAngulo = ((a * a) - (b * b) - (c * c)) / (-2 * b * c);

			if (isGreaterEqualThan(auxAngulo, 1.0))
			{
				continue;
			}

			if (isLowerEqualThan(auxAngulo, -1.0)) 
			{
				return BOUNDARY;
			}

			auxAngulo = (checkSign(polygonVertex.at(i), polygonVertex.at(i + 1), p)) * acos(auxAngulo) * 180.0 / M_PI;

			if (isEqual(round(abs((long)auxAngulo)), 180.0))
			{
				return BOUNDARY;
			} 
			else 
			{
				angulo += auxAngulo;
			}
		}

		if (isEqual(round(abs((long)angulo)), 360.0))
		{
			return INSIDE;
		} 
		else 
		{
			return OUTSIDE;
		}
	}

}

#endif