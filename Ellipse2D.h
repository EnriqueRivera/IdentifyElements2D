#ifndef ELLIPSE_2D_H
#define ELLIPSE_2D_H

#include <vector>
#include "Point2D.h"
#include "Polygon2D.h"

/**********************************************************************************************//**
 * @class	Ellipse2D
 *
 * @brief	Representa una Elipse dibujado en el CAD 2D.
 *
 * @author	Enrique Alonso
 * @date	21/01/2014
 **************************************************************************************************/
class Ellipse2D
{
	public:

		/**********************************************************************************************//**
		 * @fn	inline Ellipse2D::Ellipse2D(Point2D *center, double r1, double r2, std::vector<Point2D*> pointsApproach, std::vector<Point2D*> controlPoints)
		 *
		 * @brief	Constructor.
		 * 			Si los dos radios son iguales, se puede formar un circulo.
		 *
		 * @author	Enrique Alonso
		 * @date	21/01/2014
		 *
		 * @param [in,out]	center		  	Representa el punto de la elípse.
		 * @param	r1					  	Radio horizontal de la elípse.
		 * @param	r2					  	Radio Vertical de la elípse.
		 * @param [in,out]	pointsApproach	Puntos que aproximan el contorno de la elípse.
		 * @param [in,out]	controlPoints 	Los cuatro puntos de control de la elípse.
		 **************************************************************************************************/
		inline Ellipse2D(Point2D *center, double r1, double r2, std::vector<Point2D*> pointsApproach, std::vector<Point2D*> controlPoints) :
			center(center), r1(r1), r2(r2), controlPoints(controlPoints)
		{
			polyApproach = new Polygon2D(pointsApproach);
		}

		/**********************************************************************************************//**
		 * @fn	inline Ellipse2D::~Ellipse2D()
		 *
		 * @brief	Destructor.
		 *
		 * @author	Enrique Alonso
		 * @date	21/01/2014
		 **************************************************************************************************/
		inline ~Ellipse2D()
		{
			size_t size = controlPoints.size();
			for (size_t i = 0; i < size; i++)
			{
				delete controlPoints[i];
			}

			delete polyApproach;
			delete center;
        }

		inline Polygon2D* getPolyApproach()
		{
			return polyApproach;
		}

		inline Point2D* getCenter()
		{
			return center;
		}

		inline double getR1()
		{
			return r1;
		}

		inline double getR2()
		{
			return r2;
		}

		inline std::vector<Point2D*> getCtrlPts()
		{
			return controlPoints;
		}

		inline int getCtrlPtsCount()
		{
			return controlPoints.size();
		}

		inline std::vector<Point2D*> getContour()
		{
			return this->polyApproach->getCountour();
		}

		/**********************************************************************************************//**
		 * @fn	inline bool Ellipse2D::equals(Ellipse2D *e)
		 *
		 * @brief	Comprueba si esta Elípse es considerada igual a otra.
		 *
		 * @author	Enrique Alonso
		 * @date	21/01/2014
		 *
		 * @param [in,out]	e	La Elípse para comparar con este objeto.
		 *
		 * @return	true si el objeto es considerado igual, false en caso contrario.
		 **************************************************************************************************/
		inline bool equals(Ellipse2D *e)
		{
			if (!e)
			{
				return false;
			}

			return (controlPoints[0]->equals(e->getCtrlPts()[0]) &&
					controlPoints[1]->equals(e->getCtrlPts()[1]) &&
					controlPoints[2]->equals(e->getCtrlPts()[2]) &&
					controlPoints[3]->equals(e->getCtrlPts()[3]));
		}

	private:
		/*
					   -0-
					 -  |   -
				   -	r2   -
				  3     +-r1--1
				   -	     -
					 -     -
					   -2-
		*/

		/**********************************************************************************************//**
		 * @brief	Los cuatro puntos de control de la elípse.
		 **************************************************************************************************/
		std::vector<Point2D*> controlPoints;

		/**********************************************************************************************//**
		 * @brief	Aproximación con puntos de una elípse.
		 **************************************************************************************************/
		Polygon2D* polyApproach;

		/**********************************************************************************************//**
		 * @brief	El centro de la elípse.
		 **************************************************************************************************/
		Point2D *center;

		/**********************************************************************************************//**
		 * @brief	Primer radio.
		 **************************************************************************************************/
		double r1;

		/**********************************************************************************************//**
		 * @brief	Segundo radio.
		 **************************************************************************************************/
		double r2;
};

#endif