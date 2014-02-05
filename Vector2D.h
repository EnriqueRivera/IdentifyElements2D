#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#include <iostream>
#include <vector>
#include "Point2D.h"

/**********************************************************************************************//**
 * @enum	VectorType
 *
 * @brief	Valores que representan de que tipo es el vector, recto o curvo.
 **************************************************************************************************/
enum VectorType
{
	///< Indica que el vector es recto.
	STRAIGHT,

	///< Indica que el vector es curvo.
	CURVE
};

class Vector2D
{
	public:

		/**********************************************************************************************//**
		 * @fn	inline Vector2D::Vector2D(std::vector<Point2D*> points)
		 *
		 * @brief	Constructor.
		 *
		 * @author	Enrique Alonso
		 * @date	21/01/2014
		 *
		 * @param [in,out]	Puntos que forman el vector.
		 **************************************************************************************************/
		inline Vector2D(std::vector<Point2D*> points) : points(points)
		{
			type = points.size() == 2 ? STRAIGHT : CURVE;
		}

		/**********************************************************************************************//**
		 * @fn	inline Vector2D::~Vector2D()
		 *
		 * @brief	Destructor.
		 *
		 * @author	Enrique Alonso
		 * @date	21/01/2014
		 **************************************************************************************************/
		inline ~Vector2D()
		{
			size_t size = points.size();
			for (size_t i = 0; i < size; i++)
			{
				delete points[i];
			}
        }

		inline VectorType getType()
		{
			return type;
		}

		inline std::vector<Point2D*> &getPoints()
		{
			return points;
		}

		inline int getPtsCount()
		{
			return points.size();
		}

		/**********************************************************************************************//**
		 * @fn	inline bool Vector2D::equals(Vector2D *vector)
		 *
		 * @brief	Comprueba si este vector es considerada igual a otro.
		 *
		 * @author	Enrique Alonso
		 * @date	21/01/2014
		 *
		 * @param [in,out]	vector	El vector para comparar con este objeto.
		 *
		 * @return	true si el objeto es considerado igual, false en caso contrario.
		 **************************************************************************************************/
		inline bool equals(Vector2D *vector)
		{
			if (!vector)
			{
				return false;
			}

			if (type == STRAIGHT)
			{
				return points[0]->equals(vector->getPoints()[0]) && points[1]->equals(vector->getPoints()[1]);
			}
			else
			{
				if (points.size() != vector->getPtsCount())
				{
					return false;
				}
				else
				{
					size_t size = points.size();
					for (size_t i = 0; i < size; i++)
					{
						if(!points[i]->equals(vector->getPoints()[i]))
						{
							return false;
						}
					}

					return true;
				}
			}
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
		 * @brief	Tipo de vector, recto o curvo.
		 **************************************************************************************************/
		VectorType type;

		/**********************************************************************************************//**
		 * @brief	Puntos que forman al vector.
		 **************************************************************************************************/
		std::vector<Point2D*> points;

		/**********************************************************************************************//**
		 * @brief	Identificador para cada polígono.
		 **************************************************************************************************/
		int id;

		/**********************************************************************************************//**
		 * @fn	friend std::ostream& Vector2D::operator<< (std::ostream&, const Vector2D&);
		 *
		 * @brief	Operador sobrecargado para poder imprimir en consola las propiedades de un Vector2D.
		 *
		 * @author	Enrique Alonso
		 * @date	21/01/2014
		 *
		 * @param [in,out]	parameter1	The first parameter.
		 * @param	parameter2		  	The second parameter.
		 *
		 * @return	The shifted result.
		 **************************************************************************************************/
		friend std::ostream& operator << (std::ostream&, const Vector2D&);
};

std::ostream& operator << (std::ostream & strm, const Vector2D & vector)
{
	size_t size = vector.points.size();
	for (size_t i = 0; i < size; i++)
	{
		strm << *vector.points[i] << std::endl;
	}

	return strm;
}

#endif
