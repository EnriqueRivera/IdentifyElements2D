#ifndef SORT_POINTS_2D_H
#define SORT_POINTS_2D_H

#include "Point2D.h"

namespace sort_points
{
	/**********************************************************************************************//**
	 * @fn	void sortPointsX(Point2D* &p1, Point2D* &p2)
	 *
	 * @brief	Ordena los puntos con respecto a la coordenada en X, de forma ascendente (izquierda a derecha).
	 *
	 * @author	Enrique Alonso
	 * @date	21/01/2014
	 *
	 * @param [in,out]	p1	Primer punto.
	 * @param [in,out]	p2	Segudno punto.
	 **************************************************************************************************/
	inline void sortPointsX(Point2D* &p1, Point2D* &p2) 
	{
			Point2D *pAux = 0;

			if (isGreaterThan(p1->getX(), p2->getX())) 
			{
				pAux = p2;
				p2 = p1;
				p1 = pAux;
			}
			else if (isEqual(p1->getX(), p2->getX())) 
			{
				if (isGreaterThan(p1->getY(), p2->getY())) 
				{
					pAux = p2;
					p2 = p1;
					p1 = pAux;
				}
			}
		}

	/**********************************************************************************************//**
	 * @fn	void sortPointsY(Point2D* &p1, Point2D* &p2)
	 *
	 * @brief	Ordena los puntos con respecto a la coordenada en Y, de forma ascendente (abajo hacia arriba).
	 *
	 * @author	Enrique Alonso
	 * @date	21/01/2014
	 *
	 * @param [in,out]	p1	Primer punto.
	 * @param [in,out]	p2	Segudno punto.
	 **************************************************************************************************/
	inline void sortPointsY(Point2D* &p1, Point2D* &p2) 
	{
		Point2D *pAux = 0;

		if (isGreaterThan(p1->getY(), p2->getY())) 
		{
			pAux = p2;
			p2 = p1;
			p1 = pAux;
		}
		else if (isEqual(p1->getY(), p2->getY())) 
		{
			if (isGreaterThan(p1->getX(), p2->getX())) 
			{
				pAux = p2;
				p2 = p1;
				p1 = pAux;
			}
		}
	}
}

#endif