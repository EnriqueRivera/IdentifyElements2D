#ifndef LINE2D_H
#define LINE2D_H

#include <vector>
#include <iostream>
#include "Point2D.h"
#include "CompareDouble.h"
#include "SortPoints2D.h"

/**********************************************************************************************//**
 * @class	Segment2D
 *
 * @brief	Representa un Segmento de línea dibujado en el CAD 2D.
 *
 * @author	Enrique Alonso
 * @date	17/01/2014
 **************************************************************************************************/
class Segment2D
{
	public:

		/**********************************************************************************************//**
		 * @fn	inline Segment2D::Segment2D(Point2D *p1, Point2D *p2)
		 *
		 * @brief	Constructor.
		 *
		 * @author	Enrique Alonso
		 * @date	17/01/2014
		 *
		 * @param [in,out]	p1	Primer punto que forma el segmento de línea.
		 * @param [in,out]	p2	Segundo punto que forma el segmento de línea.
		 **************************************************************************************************/
		inline Segment2D(Point2D *p1, Point2D *p2)  : p1(p1), p2(p2)
		{
			//Ordenamos los puntos de izquierda a derecha y de abajo hacia arriba
			sort_points::sortPointsX(this->p1, this->p2);
			sort_points::sortPointsY(this->p1, this->p2);
		}

		/**********************************************************************************************//**
		 * @fn	inline Segment2D::~Segment2D()
		 *
		 * @brief	Destructor.
		 *
		 * @author	Enrique Alonso
		 * @date	17/01/2014
		 **************************************************************************************************/
		inline ~Segment2D()
		{
			delete p1;
			delete p2;
        }

		/**********************************************************************************************//**
		 * @fn	inline void Segment2D::calculateSlopeAndB(double &m, double &b)
		 *
		 * @brief	Calcula la pendiente y la ordenada al origen de este segmento de línea.
		 *
		 * @author	Enrique Alonso
		 * @date	17/01/2014
		 *
		 * @param [in,out]	m	Cualquier valor double; La pendiente calculada.
		 * @param [in,out]	b	Cualquier valor double; La ordenada al origen calculada.
		 **************************************************************************************************/
		inline void calculateSlopeAndB(double &m, double &b)
		{
			calculateSlopeAndB(p1, p2, m, b);
		}

		/**********************************************************************************************//**
		 * @fn	static inline void Segment2D::calculateSlopeAndB(Point2D *p1, Point2D *p2, double &m, double &b)
		 *
		 * @brief	Calcula la pendiente y la ordenada al origen.
		 *
		 * @author	Enrique Alonso
		 * @date	17/01/2014
		 *
		 * @param [in,out]	p1	Primer punto del segmento de línea.
		 * @param [in,out]	p2	Segundo punto del segmento de línea.
		 * @param [in,out]	m	Cualquier valor double; La pendiente calculada.
		 * @param [in,out]	b	Cualquier valor double; La ordenada al origen calculada.
		 **************************************************************************************************/
		static inline void calculateSlopeAndB(Point2D *p1, Point2D *p2, double &m, double &b)
		{
			// Si son iguales las coordenadas en X, entonces la pendiente es infinita
			if (isEqual(p1->getX(), p2->getX())) {
				m = INF;
				b = 0.0;
			}
			// Si son iguales las coordenadas en Y, entonces la pendiente es 0
			else if (isEqual(p1->getY(), p2->getY())) {
				m = 0.0;
				b = p1->getY();
			}
			else {
				// Calculamos la pendiente
				m = (p2->getY() - p1->getY()) / (p2->getX() - p1->getX());

				// Calculamos el punto de interseccion en la ordenada
				b = (m * -1.0 * p1->getX()) + p1->getY();
			}
		}

		inline Point2D *getP1()
		{
			return p1;
		}

		inline Point2D *getP2()
		{
			return p2;
		}

		inline double getX1() {
			return p1->getX();
		}

		inline double getX2() {
			return p2->getX();
		}

		inline double getY1() {
			return p1->getY();
		}

		inline double getY2() {
			return p2->getY();
		}

		/**********************************************************************************************//**
		 * @fn	inline bool Segment2D::equals(Segment2D *s)
		 *
		 * @brief	Comprueba si este Segment2D es considerado igual a otro.
		 *
		 * @author	Enrique Alonso
		 * @date	17/01/2014
		 *
		 * @param [in,out]	s	El Segment2D para comparar con este objeto.
		 *
		 * @return	true si el objeto es considerado igual, false en caso contrario.
		 **************************************************************************************************/
		inline bool equals(Segment2D *s)
		{
			if (!s)
			{
				return false;
			}

			return (s->getP1()->equals(this->getP1()) && s->getP2()->equals(this->getP2()));
		}

	private:

		/**********************************************************************************************//**
		 * @brief	Primer punto del segmento de línea.
		 **************************************************************************************************/
		Point2D *p1;

		/**********************************************************************************************//**
		 * @brief	Segundo punto del segmento de línea.
		 **************************************************************************************************/
		Point2D *p2;

		/**********************************************************************************************//**
		 * @fn	friend std::ostream& Segment2D::operator<< (std::ostream&, const Segment2D&);
		 *
		 * @brief	Operador sobrecargado para poder imprimir en consola las propiedades de un segmento
		 * 			de línea.
		 *
		 * @author	Enrique Alonso
		 * @date	17/01/2014
		 *
		 * @param [in,out]	parameter1	The first parameter.
		 * @param	parameter2		  	The second parameter.
		 *
		 * @return	The shifted result.
		 **************************************************************************************************/
		friend std::ostream& operator << (std::ostream&, const Segment2D&);
};

std::ostream& operator << (std::ostream & strm, const Segment2D & line)
{
	return strm << "[(" << line.p1->getX() << ", " << line.p1->getY()
		<< "), (" << line.p2->getX() << ", " << line.p2->getY()
		<< ")]";
}

#endif