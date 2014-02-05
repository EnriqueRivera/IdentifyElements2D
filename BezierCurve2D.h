#ifndef BEZIER_CURVE_2D_H
#define BEZIER_CURVE_2D_H

#include <vector>
#include "Point2D.h"
#include "Polygon2D.h"
#include "agg_curves.h"

/**********************************************************************************************//**
 * @enum	Degree
 *
 * @brief	Valores que representan el grado de la curva de Bezier.
 **************************************************************************************************/
enum Degree
{
	///< No aplica el grado, ya que la curva no es de segundo o tercer grado.
	DONTAPPLY = 0,

	///< Indica que la curva es de segundo grado (tiene 3 puntos de control).
	DEGREE2 = 2,

	///< Indica que la curva es de tercer grado (tiene 4 puntos de control).
	DEGREE3 = 3
};

class BezierCurve2D
{
	public:

		/**********************************************************************************************//**
		 * @fn	inline BezierCurve2D::BezierCurve2D(std::vector<Point2D*> controlPoints)
		 *
		 * @brief	Constructor.
		 *
		 * @author	Enrique Alonso
		 * @date	21/01/2014
		 *
		 * @param [in,out]	controlPoints	Puntos de control de la curva de Bezier.
		 **************************************************************************************************/
		inline BezierCurve2D(std::vector<Point2D*> controlPoints) : controlPoints(controlPoints)
		{
			deg = getDegree();
			polyApproach = new Polygon2D(calculateApproach(this));
		}

		/**********************************************************************************************//**
		 * @fn	inline BezierCurve2D::~BezierCurve2D()
		 *
		 * @brief	Destructor.
		 *
		 * @author	Enrique Alonso
		 * @date	21/01/2014
		 **************************************************************************************************/
		inline ~BezierCurve2D()
		{
			size_t size = controlPoints.size();
			for (size_t i = 0; i < size; i++)
			{
				delete controlPoints[i];
			}

			delete polyApproach;
		}

		inline Polygon2D* getPolyApproach()
		{
			return polyApproach;
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

		inline Degree getDegree()
		{
			if (controlPoints.size() == 3)
			{
				return DEGREE2;
			}
			else if (controlPoints.size() == 4)
			{
				return DEGREE3;
			}
			return  DONTAPPLY;
		}

		/**********************************************************************************************//**
		 * @fn	inline bool BezierCurve2D::equals(BezierCurve2D *b)
		 *
		 * @brief	Comprueba si esta curva de Bezier es considerada igual a otra.
		 *
		 * @author	Enrique Alonso
		 * @date	21/01/2014
		 *
		 * @param [in,out]	b	La curva de Bezier para comparar con este objeto.
		 *
		 * @return	true si el objeto es considerado igual, false en caso contrario.
		 **************************************************************************************************/
		inline bool equals(BezierCurve2D *b)
		{
			if (!b)
			{
				return false;
			}

			if (deg == DEGREE2)
			{
				return (controlPoints[0]->equals(b->getCtrlPts()[0]) &&
						controlPoints[1]->equals(b->getCtrlPts()[1]) &&
						controlPoints[2]->equals(b->getCtrlPts()[2]));
			}

			if (deg == DEGREE3)
			{
				return (controlPoints[0]->equals(b->getCtrlPts()[0]) &&
						controlPoints[1]->equals(b->getCtrlPts()[1]) &&
						controlPoints[2]->equals(b->getCtrlPts()[2]) &&
						controlPoints[3]->equals(b->getCtrlPts()[3]));
			}

			return false;
		}

		/**********************************************************************************************//**
		 * @fn	static std::vector<Point2D*> BezierCurve2D::calculateApproach(BezierCurve2D* bez)
		 *
		 * @brief	Calcula la aproximación en puntos de una curva de Bezier.
		 *
		 * @author	Enrique Alonso
		 * @date	21/01/2014
		 *
		 * @param [in,out]	El Bezier del que se obtendrá la aproximación.
		 *
		 * @return	Los puntos que forman la aproximación.
		 **************************************************************************************************/
		static std::vector<Point2D*> calculateApproach(BezierCurve2D* bez)
		{
			//Calcular la escala
			int scale = 100;
			std::vector<Point2D*> pointsApproach;

			if (bez->getDegree() == DEGREE2)
			{
				/*
				
				agg::curve3_div bezierGrade2(bez->controlPoints[0]->getX(), bez->controlPoints[0]->getY(),
										     bez->controlPoints[1]->getX(), bez->controlPoints[1]->getY(),
											 bez->controlPoints[2]->getX(), bez->controlPoints[2]->getY(),
											 scale);

				size_t size = bezierGrade2.get_m_points().size();
				for (size_t i = 0; i < size; i++)
				{
					pointsApproach.push_back(new Point2D(bezierGrade2.get_m_points()[i].x, bezierGrade2.get_m_points()[i].y));
				}

				*/

				double x1, y1, x2, y2;
				x1 = bez->controlPoints[0]->getX();
				y1 = bez->controlPoints[0]->getY();

				for (double t = 0.001; t <= 1 + 0.001; t += 0.01) {
					// use Bernstein  polynomials
					x2 = (bez->controlPoints[0]->getX() + t *
					(-(bez->controlPoints[0]->getX()) * 3 + t * (3 * bez->controlPoints[0]->getX() -
							(bez->controlPoints[0]->getX()) * t))) + t *
					(3 * bez->controlPoints[1]->getX() + t * (-6 * bez->controlPoints[1]->getX() + bez->controlPoints[1]->getX()
						* 3 * t)) + t * t * (bez->controlPoints[2]->getX() * 3 - bez->controlPoints[2]->getX
					() * 3 * t) + bez->controlPoints[2]->getX() * t * t * t;

					y2 = (bez->controlPoints[0]->getY() + t *
					(-(bez->controlPoints[0]->getY()) * 3 + t * (3 * bez->controlPoints[0]->getY() -
							(bez->controlPoints[0]->getY()) * t))) + t *
					(3 * bez->controlPoints[1]->getY() + t * (-6 * bez->controlPoints[1]->getY() + bez->controlPoints[1]->getY()
						* 3 * t)) + t * t * (bez->controlPoints[2]->getY() * 3 - bez->controlPoints[2]->getY
					() * 3 * t) + bez->controlPoints[2]->getY() * t * t * t;

					pointsApproach.push_back(new Point2D(x1, y1));

					x1 = x2;
					y1 = y2;
				}

				pointsApproach.push_back(bez->controlPoints.back());

				return pointsApproach;
			}
			else if (bez->getDegree() == DEGREE3)
			{
				agg::curve4_div bezierGrade3(bez->controlPoints[0]->getX(), bez->controlPoints[0]->getY(),
										     bez->controlPoints[1]->getX(), bez->controlPoints[1]->getY(),
											 bez->controlPoints[2]->getX(), bez->controlPoints[2]->getY(),
											 bez->controlPoints[3]->getX(), bez->controlPoints[3]->getY(),
											 scale);

				size_t size = bezierGrade3.get_m_points().size();
				for (size_t i = 0; i < size; i++)
				{
					pointsApproach.push_back(new Point2D(bezierGrade3.get_m_points()[i].x,
															bezierGrade3.get_m_points()[i].y));
				}

				return pointsApproach;
			}

			return pointsApproach;
		}

	private:

		/**********************************************************************************************//**
		 * @brief	Puntos de control de la curva de Bezier.
		 **************************************************************************************************/
		std::vector<Point2D*> controlPoints;

		/**********************************************************************************************//**
		 * @brief	Polígono que aproxima a la curva de Bezier.
		 **************************************************************************************************/
		Polygon2D* polyApproach;

		/**********************************************************************************************//**
		 * @brief	Grado de la curva de Bezier.
		 **************************************************************************************************/
		Degree deg;

};

#endif