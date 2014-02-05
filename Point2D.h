#ifndef POINT_2D_H
#define POINT_2D_H

#include <iostream>
#include <vector>
#include "CompareDouble.h"

/**********************************************************************************************//**
 * @enum	EndPointType
 *
 * @brief	Valores utilizados en cada punto para llevar a cabo el Algoritmo de Bentley–Ottmann.
 **************************************************************************************************/
enum EndPointType
{
	///< Valor por defecto para el punto, para cuando no se utiliza el Algoritmo de Bentley–Ottmann.
	NONE,
	///< Indica el punto inicial de un segmento de línea.
	P1,	
	///< Indica el punto final de un segmento de línea.
	P2	
};

/**********************************************************************************************//**
 * @class	Point2D
 *
 * @brief	Representa un Punto dibujado en el CAD 2D.
 *
 * @author	Enrique Alonso
 * @date	17/01/2014
 **************************************************************************************************/
class Point2D
{
	public:

		/**********************************************************************************************//**
		 * @fn	inline Point2D::Point2D(double x, double y, EndPointType endPoint = NONE, Point2D *nextPoint = 0, int idSweepLine = -1)
		 *
		 * @brief	Constructor.
		 *
		 * @author	Enrique Alonso
		 * @date	17/01/2014
		 *
		 * @param	x				 	La coordenada en X.
		 * @param	y				 	La coordenada en Y.
		 * @param	endPoint		 	(Optional) the end point.
		 * @param [in,out]	nextPoint	(Optional) If non-null, (Optional) the next point.
		 * @param	idSweepLine		 	(Optional) the identifier sweep line.
		 **************************************************************************************************/
		inline Point2D(double x, double y, EndPointType endPoint = NONE, Point2D *nextPoint = 0, int idSweepLine = -1) :
						x(x), y(y), endPoint(endPoint), nextPoint(nextPoint), idSweepLine(idSweepLine) {}

		/**********************************************************************************************//**
		 * @fn	inline Point2D::~Point2D()
		 *
		 * @brief	Destructor.
		 *
		 * @author	Enrique Alonso
		 * @date	17/01/2014
		 **************************************************************************************************/
		inline ~Point2D()
		{
        	delete nextPoint;
		}

		inline double getX()
		{
			return x;
		}

		inline double getY()
		{
			return y;
		}

		inline int getIdSweepLine()
		{
			return idSweepLine;
		}

		inline int getID()
		{
			return id;
		}

		inline EndPointType getEndPointType()
		{
			return endPoint;
		}

		inline Point2D* getNextPoint()
		{
			return nextPoint;
		}

		inline void setIdSweepLine(int idSweepLine)
		{
			this->idSweepLine = idSweepLine;
		}

		inline void setID(int id)
		{
			this->id = id;
		}

		inline void setNextPoint(Point2D *nextPoint)
		{
			this->nextPoint = nextPoint;
		}

		inline void setEndPointType(EndPointType endPoint)
		{
			this->endPoint = endPoint;
		}

		inline void setX(double x)
		{
			this->x = x;
		}

		inline void setY(double y) {
			this->y = y;
		}

		/**********************************************************************************************//**
		 * @fn	inline bool Point2D::equals(Point2D *p)
		 *
		 * @brief	Comprueba si este Point2D es considerado igual a otro.
		 *
		 * @author	Enrique Alonso
		 * @date	17/01/2014
		 *
		 * @param [in,out]	p	El Point2D para comparar con este objeto.
		 *
		 * @return	true si el objeto es considerado igual, false en caso contrario.
		 **************************************************************************************************/
		inline bool equals(Point2D *p)
		{
			if (!p)
			{
				return false;
			}

			return (isEqual(this->getX(), p->getX())) && (isEqual(this->getY(), p->getY()));
		}

		/**********************************************************************************************//**
		 * @fn	inline double Point2D::distance(Point2D *p)
		 *
		 * @brief	Calcula la distancia que existe entre este y otro Point2D.
		 *
		 * @author	Enrique Alonso
		 * @date	17/01/2014
		 *
		 * @param [in,out]	p	El Point2D para calcular la distancia.
		 *
		 * @return	Un double.
		 **************************************************************************************************/
		inline double distance(Point2D *p)
		{
			double x = p->getX() - this->getX();
			double y = p->getY() - this->getY();
			return std::sqrt((x * x) + (y * y));
		}

	private:

		/**********************************************************************************************//**
		 * @brief	La coordenada en X.
		 **************************************************************************************************/
		double x;

		/**********************************************************************************************//**
		 * @brief	La coordenada en Y.
		 **************************************************************************************************/
		double y;

		/**********************************************************************************************//**
		 * @brief	Identificador que indica a que segmento de línea pertenece el punto.
		 **************************************************************************************************/
		int idSweepLine;

		/**********************************************************************************************//**
		 * @brief	Identificador para cada punto.
		 **************************************************************************************************/
		int id;

		/**********************************************************************************************//**
		 * @brief	Indica si es el punto inicial o final de un segmento de línea.
		 **************************************************************************************************/
		EndPointType endPoint;

		/**********************************************************************************************//**
		 * @brief	Indica quien es el siguiente punto que forma la línea (el nextPoint apunta a este 
		 * 			objeto).	P1 <---> P2
		 **************************************************************************************************/
		Point2D *nextPoint;

		/**********************************************************************************************//**
		 * @fn	friend std::ostream& Point2D::operator<< (std::ostream&, const Point2D&);
		 *
		 * @brief	Operador sobrecargado para poder imprimir en consola las propiedades de un punto.
		 *
		 * @author	Enrique Alonso
		 * @date	17/01/2014
		 *
		 * @param [in,out]	parameter1	The first parameter.
		 * @param	parameter2		  	The second parameter.
		 *
		 * @return	The shifted result.
		 **************************************************************************************************/
		friend std::ostream& operator << (std::ostream&, const Point2D&);
};

std::ostream& operator << (std::ostream & strm, const Point2D & p)
{
	return strm << p.x << ", " << p.y;
}

#endif
