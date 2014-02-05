#ifndef POLYGON_2D_H
#define POLYGON_2D_H

#include <vector>
#include <stdarg.h>
#include "Point2D.h"

/**********************************************************************************************//**
 * @class	Polygon2D
 *
 * @brief	Representa un Polígono arbitrario dibujado en el CAD 2D.
 *
 * @author	Enrique Alonso
 * @date	17/01/2014
 **************************************************************************************************/
class Polygon2D
{
	public:

		/**********************************************************************************************//**
		 * @fn	inline Polygon2D::Polygon2D(std::vector<Point2D*> contour)
		 *
		 * @brief	Constructor.
		 *
		 * @author	Enrique Alonso
		 * @date	17/01/2014
		 *
		 * @param [in,out]	contour		 	Vector que contiene un conjunto de puntos que forman el 
		 * 					contorno del polígono.
		 **************************************************************************************************/
		inline Polygon2D(std::vector<Point2D*> contour) : contour(contour) {}

		/**********************************************************************************************//**
		 * @fn	inline Polygon2D::Polygon2D(std::vector<Point2D*> contour, std::vector<Point2D*> controlPoints)
		 *
		 * @brief	Constructor.
		 *
		 * @author	Enrique Alonso
		 * @date	28/01/2014
		 *
		 * @param [in,out]	contour		 	Vector que contiene un conjunto de puntos que forman el 
		 * 					contorno del polígono.
		 * @param [in,out]	controlPoints	Vector que contiene un conjunto de puntos de control del polígono.
		 **************************************************************************************************/

		inline Polygon2D(std::vector<Point2D*> contour, std::vector<Point2D*> controlPoints) : 
							contour(contour), controlPoints(controlPoints) {}

		/**********************************************************************************************//**
		 * @fn	inline Polygon2D::~Polygon2D()
		 *
		 * @brief	Destructor.
		 *
		 * @author	Enrique Alonso
		 * @date	17/01/2014
		 **************************************************************************************************/
		inline ~Polygon2D()
		{
			size_t size = contour.size();
			for (size_t i = 0; i < size; i++)
			{
            	delete contour[i];
			}

			size = controlPoints.size();
			for (size_t i = 0; i < size; i++)
			{
				delete controlPoints[i];
			}

			size = holes.size();
			for (size_t i = 0; i < size; i++)
			{
				delete holes[i];
			}
        }

		//Utilizado para pruebas
		inline Polygon2D(int n, ...)
		{
			va_list vl;
			va_start(vl, n);
			for (int i = 0; i < n; i++)
			{
				contour.push_back(va_arg(vl, Point2D*));
			}
		}

		/**********************************************************************************************//**
		 * @fn	inline void Polygon2D::addHole(Polygon2D *poly)
		 *
		 * @brief	Agrega un polígono a este objeto, el cual representa un agujero.
		 *
		 * @author	Enrique Alonso
		 * @date	17/01/2014
		 *
		 * @param [in,out]	poly	Polígono que representa el agujero.
		 **************************************************************************************************/
		inline void addHole(Polygon2D *poly)
		{
			holes.push_back(poly);
		}

		inline std::vector<Point2D*> &getCountour()
		{
			return contour;
		}

		inline int getCountourSize()
		{
			return contour.size();
		}

		inline std::vector<Polygon2D*> &getHoles()
		{
			return holes;
		}

		inline int getHolesCount()
		{
			return holes.size();
		}

		/**********************************************************************************************//**
		 * @fn	inline bool Polygon2D::hasHoles()
		 *
		 * @brief	Nos indica si este polígono tiene agujeros.
		 *
		 * @author	Enrique Alonso
		 * @date	17/01/2014
		 *
		 * @return	true si tiene por lo menos un agujero, false si no tiene agujeros.
		 **************************************************************************************************/
		inline bool hasHoles()
		{
			return !(holes.empty());
		}

		inline std::vector<Point2D*> getCtrlPts()
		{
			return controlPoints;
		}

		inline int getCtrlPtsCount()
		{
			return controlPoints.size();
		}

		inline void setCtrlPts(std::vector<Point2D*> controlPoints)
		{
			this->controlPoints = controlPoints;
		}

		inline void setID(int id)
		{
			this->id = id;
		}

		inline int getID()
		{
			return id;
		}

	private:

		/**********************************************************************************************//**
		 * @brief	Vector que almacena cada agujero.
		 **************************************************************************************************/
		std::vector<Polygon2D*> holes;

		/**********************************************************************************************//**
		 * @brief	Vector que almacena los puntos que forman el contorno del polígono.
		 **************************************************************************************************/
		std::vector<Point2D*> contour;

		/**********************************************************************************************//**
		 * @brief	Vector que almacena los puntos de control del polígono.
		 * 			Esta propiedad se utiliza cuando alguna operación de clipping ha sido utilizada
		 * 			en este polígono.
		 **************************************************************************************************/
		std::vector<Point2D*> controlPoints;

		/**********************************************************************************************//**
		 * @brief	Identificador para cada polígono.
		 **************************************************************************************************/
		int id;

		/**********************************************************************************************//**
		 * @fn	friend std::ostream& Polygon2D::operator<< (std::ostream&, const Polygon2D&);
		 *
		 * @brief	Operador sobrecargado para poder imprimir en consola las propiedades de un polígono.
		 *
		 * @author	Enrique Alonso
		 * @date	17/01/2014
		 *
		 * @param [in,out]	parameter1	The first parameter.
		 * @param	parameter2		  	The second parameter.
		 *
		 * @return	The shifted result.
		 **************************************************************************************************/
		friend std::ostream& operator << (std::ostream&, const Polygon2D&);
};

std::ostream& operator << (std::ostream & strm, Polygon2D & poly)
{
	strm << "Polygon:\n[\n" ;
	size_t size = poly.getCountour().size();
	for (size_t i = 0; i < size; i++)
	{
		//strm << "\t";
		strm << *(poly.getCountour()[i]);
		strm << (i != (poly.getCountour().size() - 1) ? "\n " : "");
	}
	strm << "\n\t" << "Points = " << poly.getCountour().size() << "\t] {\n";

	size = poly.getHoles().size();
	for (size_t i = 0; i < size; i++)
	{
		strm << "\n   --->(Hole " << i + 1 << ")<---\n";
		for (size_t j = 0; j < poly.getHoles().at(i)->getCountour().size(); j++)
		{
			//strm << "\t";
			strm << *(poly.getHoles().at(i)->getCountour().at(j));
			strm << (j != (poly.getHoles().at(i)->getCountour().size() - 1) ? "\n " : "");
		}
		strm << "\n\t" << "Points = " << poly.getHoles().at(i)->getCountour().size();
	}

	return strm << "\n}";
}

#endif