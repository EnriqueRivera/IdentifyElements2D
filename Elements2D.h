#ifndef ELEMENTS_2D_H
#define ELEMENTS_2D_H

#include <vector>
#include "Point2D.h"
#include "Segment2D.h"
#include "Polygon2D.h"
#include "Ellipse2D.h"
#include "BezierCurve2D.h"
#include "Composed2D.h"

/**********************************************************************************************//**
 * @class	Elements2D
 *
 * @brief	Clase que almacena a todas las figuras en 2D para luego ser procesadas en las clases
 * 			de TotalPoints2D, Subdomains2D y Boundaries2D.
 *
 * @author	Enrique Alonso
 * @date	21/01/2014
 **************************************************************************************************/
class Elements2D
{
	public:

		/**********************************************************************************************//**
		 * @fn	inline Elements2D::Elements2D()
		 *
		 * @brief	Default constructor.
		 *
		 * @author	Enrique Alonso
		 * @date	21/01/2014
		 **************************************************************************************************/
		inline Elements2D() {}

		/**********************************************************************************************//**
		 * @fn	inline Elements2D::~Elements2D()
		 *
		 * @brief	Destructor.
		 *
		 * @author	Enrique Alonso
		 * @date	21/01/2014
		 **************************************************************************************************/
		inline ~Elements2D()
		{
			
		}

		inline std::vector<Point2D*> &getPoints() 
		{
			return points;
		}

		inline std::vector<Segment2D*> &getSegments() 
		{
			return segments;
		}

		inline std::vector<Polygon2D*> &getPolygons() 
		{
			return polygons;
		}

		inline std::vector<Ellipse2D*> &getEllipses() 
		{
			return ellipses;
		}

		inline std::vector<BezierCurve2D*> &getBeziers() 
		{
			return beziers;
		}

		inline std::vector<Composed2D*> &getComps()
		{
			return comps;
		}

		inline int getPtsCount()
		{
			return points.size();
		}

		inline int getSegCount()
		{
			return segments.size();
		}

		inline int getPolyCount()
		{
			return polygons.size();
		}

		inline int getElliCount()
		{
			return ellipses.size();
		}

		inline int getBezCount()
		{
			return beziers.size();
		}

		inline int getCompsCount()
		{
			return comps.size();
		}

		inline void setPoints(std::vector<Point2D*> points)
		{
			this->points = points;

			Point2D *aux;
			for (size_t i = 0; i < this->points.size(); i++)
			{
				aux = this->points[i];
				for (size_t j = (i + 1); j < this->points.size(); j++)
				{
					if (aux->equals(this->points[j]))
					{
						this->points.erase(this->points.begin() + j);
						j--;
					}
				}
			}
		}

		inline void setSegments(std::vector<Segment2D*> segments)
		{
			this->segments = segments;

			Segment2D *aux;
			for (size_t i = 0; i < this->segments.size(); i++)
			{
				aux = this->segments[i];
				for (size_t j = (i + 1); j < this->segments.size(); j++)
				{
					if (aux->equals(this->segments[j]))
					{
						this->segments.erase(this->segments.begin() + j);
						j--;
					}
				}
			}
		}

		inline void setPolygons(std::vector<Polygon2D*> polygons)
		{
			this->polygons = polygons;
		}

		inline void setEllipses(std::vector<Ellipse2D*> ellipses)
		{
			this->ellipses = ellipses;

			Ellipse2D *aux;
			for (size_t i = 0; i < this->ellipses.size(); i++)
			{
				aux = this->ellipses[i];
				for (size_t j = (i + 1); j < this->ellipses.size(); j++)
				{
					if (aux->equals(this->ellipses[j]))
					{
						this->ellipses.erase(this->ellipses.begin() + j);
						j--;
					}
				}
			}
		}

		inline void setBeziers(std::vector<BezierCurve2D*> beziers)
		{
			this->beziers = beziers;

			BezierCurve2D *aux;
			for (size_t i = 0; i < this->beziers.size(); i++)
			{
				aux = this->beziers[i];
				for (size_t j = (i + 1); j < this->beziers.size(); j++)
				{
					if (aux->equals(this->beziers[j]))
					{
						this->beziers.erase(this->beziers.begin() + j);
						j--;
					}
				}
			}
		}

		inline void setComps(std::vector<Composed2D*> comps)
		{
			this->comps = comps;

			Composed2D *aux;
			for (size_t i = 0; i < this->comps.size(); i++)
			{
				aux = this->comps[i];
				for (size_t j = (i + 1); j < this->comps.size(); j++)
				{
					if (aux->equals(this->comps[j]))
					{
						this->comps.erase(this->comps.begin() + j);
						j--;
					}
				}
			}
		}
		
		inline void clearElements()
		{
			this->points.clear();
			this->segments.clear();
			this->polygons.clear();
			this->ellipses.clear();
			this->beziers.clear();
			this->comps.clear();
		}
		
		inline void clearPoints()
		{
			this->points.clear();
		}
		
		inline void clearSegments()
		{
			this->segments.clear();
		}
		
		inline void clearPolygons()
		{
			this->polygons.clear();
		}
		
		inline void clearEllipses()
		{
			this->ellipses.clear();
		}
		
		inline void clearBeziers()
		{
			this->beziers.clear();
		}
		
		inline void clearComps()
		{
			this->comps.clear();
		}
		
		inline bool popPoint(int index)
		{
			this->points.erase(this->points.begin() + index);
		}
		
		inline bool popSegment(int index)
		{
			this->segments.erase(this->segments.begin() + index);
		}
		
		inline bool popPolygon(int index)
		{
			this->polygons.erase(this->polygons.begin() + index);
		}
		
		inline bool popEllipse(int index)
		{
			this->ellipses.erase(this->ellipses.begin() + index);
		}
		
		inline bool popBezier(int index)
		{
			this->beziers.erase(this->beziers.begin() + index);
		}
		
		inline bool popComp(int index)
		{
			this->comps.erase(this->comps.begin() + index);
		}

	private:

		/**********************************************************************************************//**
		 * @brief	Los puntos en 2D.
		 **************************************************************************************************/
		std::vector<Point2D*> points;

		/**********************************************************************************************//**
		 * @brief	Los segmentos de l�nea en 2D.
		 **************************************************************************************************/
		std::vector<Segment2D*> segments;

		/**********************************************************************************************//**
		 * @brief	Los pol�gonos en 2D.
		 **************************************************************************************************/
		std::vector<Polygon2D*> polygons;

		/**********************************************************************************************//**
		 * @brief	Las el�pses en 2D.
		 **************************************************************************************************/
		std::vector<Ellipse2D*> ellipses;

		/**********************************************************************************************//**
		 * @brief	Las curvas de Bezier en 2D.
		 **************************************************************************************************/
		std::vector<BezierCurve2D*> beziers;

		/**********************************************************************************************//**
		 * @brief	Las figuras compuestas en 2D.
		 **************************************************************************************************/
		std::vector<Composed2D*> comps;
};

#endif
