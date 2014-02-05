#ifndef COMPOSED_2D_H
#define COMPOSED_2D_H

#include <iostream>
#include <vector>
#include "BezierCurve2D.h"
#include "Segment2D.h"
#include "Polygon2D.h"
#include "Point2D.h"

/**********************************************************************************************//**
 * @struct	CompositeFigure
 *
 * @brief	Estructura que almacena un segmento de línea o una curva de Bezier.
 *
 * @author	Enrique Alonso
 * @date	21/01/2014
 **************************************************************************************************/
struct CompositeFigure
{
	/**********************************************************************************************//**
	 * @brief	Representa un segmento de línea.
	 **************************************************************************************************/
	Segment2D* seg;

	/**********************************************************************************************//**
	 * @brief	Representa una curva de Bezier.
	 **************************************************************************************************/
	BezierCurve2D* bez;

	/**********************************************************************************************//**
	 * @fn	CompositeFigure(Segment2D* seg, BezierCurve2D* bez)
	 *
	 * @brief	Constructor.
	 *
	 * @author	Enrique Alonso
	 * @date	21/01/2014
	 *
	 * @param [in,out]	seg	El segmento de línea.
	 * @param [in,out]	bez	La curva de Bezier.
	 **************************************************************************************************/
	CompositeFigure(Segment2D* seg, BezierCurve2D* bez) : seg(seg), bez(bez) {}

	/**********************************************************************************************//**
	 * @fn	~CompositeFigure()
	 *
	 * @brief	Destructor.
	 *
	 * @author	Enrique Alonso
	 * @date	21/01/2014
	 **************************************************************************************************/
	~CompositeFigure()
	{
		delete seg;
		delete bez;
	}
};

/**********************************************************************************************//**
 * @class	Composed2D
 *
 * @brief	Figura compuesta por cualquier combinación de segmentos de línea y curvas de Bezier.
 *
 * @author	Enrique Alonso
 * @date	21/01/2014
 **************************************************************************************************/
class Composed2D 
{
	public:

		/**********************************************************************************************//**
		 * @fn	inline Composed2D::Composed2D(std::vector<CompositeFigure*> compositeFigures)
		 *
		 * @brief	Constructor.
		 *
		 * @author	Enrique Alonso
		 * @date	21/01/2014
		 *
		 * @param [in,out]	compositeFigures	Conjunto de figuras que pueden ser segmentos de línea o
		 * 					curvas de Bezier.
		 **************************************************************************************************/
		inline Composed2D(std::vector<CompositeFigure*> compositeFigures) : compositeFigures(compositeFigures) 
		{
			calculateApproach();
		}

		/**********************************************************************************************//**
		 * @fn	inline Composed2D::~Composed2D()
		 *
		 * @brief	Destructor.
		 *
		 * @author	Enrique Alonso
		 * @date	21/01/2014
		 **************************************************************************************************/
		inline ~Composed2D()
		{
			delete polyApproach;
		}	

		inline Polygon2D* getPolyApproach()
		{
			return polyApproach;
		}

		inline int compositeFiguresCount()
		{
			return compositeFigures.size();
		}

		inline std::vector<CompositeFigure*> getcompositeFigures()
		{
			return compositeFigures;
		}

		/**********************************************************************************************//**
		 * @fn	inline bool Composed2D::equals(Composed2D *c)
		 *
		 * @brief	Comprueba si esta figura compuesta es considerada igual a otra.
		 *
		 * @author	Enrique Alonso
		 * @date	21/01/2014
		 *
		 * @param [in,out]	c	La figura compuesta para comparar con este objeto.
		 *
		 * @return	true si el objeto es considerado igual, false en caso contrario.
		 **************************************************************************************************/
		inline bool equals(Composed2D *c) 
		{
			if (!c)			//checar que no sea nulo 
			{
				return false;
			}

			//checa que tenga la misma cantidad de figuras
			if (compositeFigures.size() == c->getcompositeFigures().size())
			{
				size_t size = compositeFigures.size();
				for (size_t i = 0; i < size; i++)
				{
					//Los segmentos y beziers de cada figura deben ser (nulos los dos) o (tener algun valor ambos)
					if (!((compositeFigures[i]->seg == NULL) ^ (c->getcompositeFigures()[i]->seg == NULL)) &&
						!((compositeFigures[i]->bez == NULL) ^ (c->getcompositeFigures()[i]->bez == NULL)))
					{
						if (compositeFigures[i]->seg)
						{
							if (!compositeFigures[i]->seg->equals(c->getcompositeFigures()[i]->seg))
							{
								return false;
							}
						}
						else if (compositeFigures[i]->bez)
						{
							if (!compositeFigures[i]->bez->equals(c->getcompositeFigures()[i]->bez))
							{
								return false;
							}
						}
					}
					else
					{
						return false;
					}
				}

				return true;
			}

			return false;
		}

	private:

		/**********************************************************************************************//**
		 * @brief	Conjunto de figuras que pueden ser segmentos de línea o curvas de Bezier.
		 **************************************************************************************************/
		std::vector<CompositeFigure*> compositeFigures; 

		/**********************************************************************************************//**
		 * @brief	Polígono que aproxima a la figura compuesta.
		 **************************************************************************************************/
		Polygon2D* polyApproach;

		/**********************************************************************************************//**
		 * @fn	void Composed2D::calculateApproach()
		 *
		 * @brief	Calcula el polígono de aproximación para la figura compuesta.
		 *
		 * @author	Enrique Alonso
		 * @date	21/01/2014
		 **************************************************************************************************/
		void calculateApproach()
		{
			std::vector<Point2D*> polyPoints;
			std::vector<Point2D*> auxPoints;

			size_t size = compositeFigures.size();
			for (size_t i = 0; i < size; i++)
			{
				auxPoints.clear();

				if (compositeFigures[i]->seg)
				{
					auxPoints.push_back(compositeFigures[i]->seg->getP1());
					auxPoints.push_back(compositeFigures[i]->seg->getP2());
				}
				else if (compositeFigures[i]->bez)
				{
					auxPoints = compositeFigures[i]->bez->getPolyApproach()->getCountour();
				}

				size_t sizePoints = auxPoints.size();
				for (size_t j = (0 + (i != 0 ? 1 : 0)); j < sizePoints; j++)
				{
					polyPoints.push_back(auxPoints[j]);
				}
			}

			polyApproach = new Polygon2D(polyPoints);
		}
};
#endif
