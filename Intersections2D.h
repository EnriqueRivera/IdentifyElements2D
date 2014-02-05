#ifndef INTERSECTIONS_2D_H
#define INTERSECTIONS_2D_H

#include "Point2D.h"
#include "Segment2D.h"
#include "CompareDouble.h"
#include "SortPoints2D.h"

namespace intersection_2D
{
	/**********************************************************************************************//**
	 * @class	Intersection2D
	 *
	 * @brief	Clase con una serie de métodos que nos indican si se intersectan un par de segmentos de
	 * 			línea.
	 *
	 * @author	Enrique Alonso
	 * @date	21/01/2014
	 **************************************************************************************************/
	class Intersection2D 
	{
		private:

			/**********************************************************************************************//**
			 * @fn	static inline void Intersection2D::checkForEqualsPoints(Point2D *p1, Point2D *p2, Point2D *p3, Point2D *p4, Point2D *p)
			 *
			 * @brief	Checamos si las líneas se intersectan en los puntos que las conforman.
			 *
			 * @author	Enrique Alonso
			 * @date	21/01/2014
			 *
			 * @param [in,out]	p1	Primer punto del primer segmento de línea.
			 * @param [in,out]	p2	Segundo punto del primer segmento de línea.
			 * @param [in,out]	p3	Primer punto del segundo segmento de línea.
			 * @param [in,out]	p4	Segundo punto del segundo segmento de línea.
			 * @param [in,out]	p 	Punto de intersección.
			 **************************************************************************************************/
			static inline void checkForEqualsPoints(Point2D *p1, Point2D *p2, Point2D *p3, Point2D *p4, Point2D *p)
			{
				if (p1->equals(p3) || p1->equals(p4))
				{
					p = p1;
				}
				else if (p2->equals(p4) || p2->equals(p3))
				{
					p = p2;
				}
			}

			 /**
			 * Returns an indicator of where the specified point (PX,&nbsp;PY) lies with
			 * respect to the line segment from (X1,&nbsp;Y1) to (X2,&nbsp;Y2). The
			 * return value can be either 1, -1, or 0 and indicates in which direction
			 * the specified line must pivot around its first endpoint, (X1,&nbsp;Y1),
			 * in order to point at the specified point (PX,&nbsp;PY).
			 * <p>
			 * A return value of 1 indicates that the line segment must turn in the
			 * direction that takes the positive X axis towards the negative Y axis. In
			 * the default coordinate system used by Java 2D, this direction is
			 * counterclockwise.
			 * <p>
			 * A return value of -1 indicates that the line segment must turn in the
			 * direction that takes the positive X axis towards the positive Y axis. In
			 * the default coordinate system, this direction is clockwise.
			 * <p>
			 * A return value of 0 indicates that the point lies exactly on the line
			 * segment. Note that an indicator value of 0 is rare and not useful for
			 * determining colinearity because of floating point rounding issues.
			 * <p>
			 * If the point is colinear with the line segment, but not between the
			 * endpoints, then the value will be -1 if the point lies
			 * "beyond (X1,&nbsp;Y1)" or 1 if the point lies "beyond (X2,&nbsp;Y2)".
			 *
			 * @param pX1
			 *            ,&nbsp;Y1 the coordinates of the beginning of the specified
			 *            line segment
			 * @param pX2
			 *            ,&nbsp;Y2 the coordinates of the end of the specified line
			 *            segment
			 * @param pPX
			 *            ,&nbsp;PY the coordinates of the specified point to be
			 *            compared with the specified line segment
			 * @return an integer that indicates the position of the third specified
			 *         coordinates with respect to the line segment formed by the first
			 *         two specified coordinates.
			 */
			static int relativeCCW(double x1, double y1, double x2, double y2, double px, double py)
			{
				x2 -= x1;
				y2 -= y1;
				px -= x1;
				py -= y1;
				double ccw = px * y2 - py * x2;
				if (isEqual(ccw, 0.0)) {
					// The point is colinear, classify based on which side of
					// the segment the point falls on.  We can calculate a
					// relative value using the projection of px,py onto the
					// segment - a negative value indicates the point projects
					// outside of the segment in the direction of the particular
					// endpoint used as the origin for the projection.
					ccw = px * x2 + py * y2;
					if (isGreaterThan(ccw, 0.0)) {
						// Reverse the projection to be relative to the original x2,y2
						// x2 and y2 are simply negated.
						// px and py need to have (x2 - x1) or (y2 - y1) subtracted
						//    from them (based on the original values)
						// Since we really want to get a positive answer when the
						//    point is "beyond (x2,y2)", then we want to calculate
						//    the inverse anyway - thus we leave x2 & y2 negated.
						px -= x2;
						py -= y2;
						ccw = px * x2 + py * y2;
						if (isLowerThan(ccw, 0.0)) {
							ccw = 0.0;
						}
					}
				}
				return (isLowerThan(ccw, 0.0)) ? -1 : (isGreaterThan(ccw, 0.0) ? 1 : 0);
			}

			/**********************************************************************************************//**
			 * @fn	static bool Intersection2D::isALinePoint(Point2D *p1, Point2D *p2, Point2D *p3, Point2D *p4, Point2D *p)
			 *
			 * @brief	Checamos si el punto de intersección es igual a alguno de los extremos de cada 
			 * 			segmento de línea.
			 *
			 * @author	Enrique Alonso
			 * @date	21/01/2014
			 *
			 * @param [in,out]	p1	Primer punto del primer segmento de línea.
			 * @param [in,out]	p2	Segundo punto del primer segmento de línea.
			 * @param [in,out]	p3	Primer punto del segundo segmento de línea.
			 * @param [in,out]	p4	Segundo punto del segundo segmento de línea.
			 * @param [in,out]	p 	Punto de intersección.
			 *
			 * @return	true if a line point, false if not.
			 **************************************************************************************************/
			static bool isALinePoint(Point2D *p1, Point2D *p2, Point2D *p3, Point2D *p4, Point2D *p)
			{
				return p->equals(p1) || p->equals(p2) || p->equals(p3) || p->equals(p4);
			}

			/**********************************************************************************************//**
			 * @fn	static bool Intersection2D::areP1AndP2Equals(Point2D *p1, Point2D *p2, Point2D *p3, Point2D *p4)
			 *
			 * @brief	Checamos si el primer punto de cada línea no es igual al segundo punto de esa misma
			 * 			línea.
			 *
			 * @author	Enrique Alonso
			 * @date	21/01/2014
			 *
			 * @param [in,out]	p1	Primer punto del primer segmento de línea.
			 * @param [in,out]	p2	Segundo punto del primer segmento de línea.
			 * @param [in,out]	p3	Primer punto del segundo segmento de línea.
			 * @param [in,out]	p4	Segundo punto del segundo segmento de línea.
			 * 					
			 * @return	true if p 1 and p 2 equals, false if not.
			 **************************************************************************************************/
			static bool areP1AndP2Equals(Point2D *p1, Point2D *p2, Point2D *p3, Point2D *p4)
			{
				return p1->equals(p2) || p3->equals(p4);
			}

		public:

			/**********************************************************************************************//**
			 * @fn	static Point2D* Intersection2D::lineIntersection(Segment2D *line1, Segment2D *line2)
			 *
			 * @brief	Calcula el punto de intersección entre dos segmentos de línea.
			 *
			 * @author	Enrique Alonso
			 * @date	21/01/2014
			 *
			 * @param [in,out]	line1	Primer segmento de línea.
			 * @param [in,out]	line2	Segundo segmento de línea.
			 *
			 * @return	null si no se encontró una intersección, sino se retorna la intersección.
			 **************************************************************************************************/
			static Point2D* lineIntersection(Segment2D *line1, Segment2D *line2)
			{
				return lineIntersection(line1->getP1(), line1->getP2(), line2->getP1(), line2->getP2());
			}

			/**********************************************************************************************//**
			 * @fn	static Point2D* Intersection2D::lineIntersection(Point2D *p1, Point2D *p2, Point2D *p3, Point2D *p4)
			 *
			 * @brief	Calcula el punto de intersección entre dos segmentos de línea.
			 *
			 * @author	Enrique Alonso
			 * @date	21/01/2014
			 *
			 * @param [in,out]	p1	Primer punto del primer segmento de línea.
			 * @param [in,out]	p2	Segundo punto del primer segmento de línea.
			 * @param [in,out]	p3	Primer punto del segundo segmento de línea.
			 * @param [in,out]	p4	Segundo punto del segundo segmento de línea.
			 *
			 * @return	null si no se encontró una intersección, sino se retorna la intersección.
			 **************************************************************************************************/
			static Point2D* lineIntersection(Point2D *p1, Point2D *p2, Point2D *p3, Point2D *p4)
			{
				Point2D* p = 0;
				double mL1, mL2, bLine1, bLine2;

				double x1 = p1->getX();
				double y1 = p1->getY();
				double x2 = p2->getX();
				double y2 = p2->getY();

				double x3 = p3->getX();
				double y3 = p3->getY();
				double x4 = p4->getX();
				double y4 = p4->getY();

				Segment2D::calculateSlopeAndB(p1, p2, mL1, bLine1);
				Segment2D::calculateSlopeAndB(p3, p4, mL2, bLine2);

				if ( !isEqual(mL1, mL2) &&
					((relativeCCW(x1, y1, x2, y2, x3, y3) * relativeCCW(x1, y1, x2, y2, x4, y4) <= 0) && 
					(relativeCCW(x3, y3, x4, y4, x1, y1) * relativeCCW(x3, y3, x4, y4, x2, y2) <= 0)))
				{
					if (isEqual(mL1, INF))
					{
						if (isEqual(mL2, 0.0))
						{
							p = new Point2D(p1->getX(), p3->getY());
						}

						double y = mL2 * p1->getX() + bLine2;
						p = new Point2D(p1->getX(), y);
					}
					else if (isEqual(mL2, INF))
					{
						if (isEqual(mL1, 0.0))
						{
							p = new Point2D(p3->getX(), p1->getY());
						}

						double y = mL1 * p3->getX() + bLine1;
						p = new Point2D(p3->getX(), y);
					}
					else
					{
						double x = (bLine2 - bLine1) / (mL1 - mL2);
						double y = mL1 * x + bLine1;

						p = new Point2D(x, y);
					}
				}
				
				if (p && !isALinePoint(p1, p2, p3, p4, p))
				{
					return p;
				}

				return 0;
			}
	};
}

#endif