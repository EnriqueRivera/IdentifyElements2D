#ifndef BOUNDARIES_2D_H
#define BOUNDARIES_2D_H

#include <vector>
#include "SortPoints2D.h"
#include "Vector2D.h"
#include "Elements2D.h"
#include "Subdomains2D.h"
#include "TotalPoints2D.h"

#include <iostream>      //ofstream myfile
#include <fstream>       //ofstream myfile;

namespace boundaries_2D
{
	/**********************************************************************************************//**
	 * @class	Boundaries2D
	 *
	 * @brief	Clase que obtiene todos los límites (curvos y rectos) que se forman en el CAD 2D.
	 *
	 * @author	Enrique Alonso
	 * @date	28/01/2014
	 **************************************************************************************************/
	class Boundaries2D 
	{
		private:

			/**********************************************************************************************//**
			 * @fn	static bool Boundaries2D::isPointInVector(Point2D* p, std::vector<Point2D*> totalPoints)
			 *
			 * @brief	Revisamos si el punto está contenido en la estructura de datos que almacena los puntos.
			 *
			 * @author	Enrique Alonso
			 * @date	28/01/2014
			 *
			 * @param [in,out]	p		   	Punto que se busca.
			 * @param [in,out]	totalPoints	Estructura que almacena los puntos.
			 *
			 * @return	true si el punto se encuentra en la estructura, false sino se encuentra.
			 **************************************************************************************************/
			static bool isPointInVector(Point2D* p, std::vector<Point2D*> totalPoints)
			{
				size_t size = totalPoints.size();
				for (size_t i = 0; i < size; i++)
				{
					if (isLowerThan(totalPoints[i]->getX(), p->getX()))
					{
						continue;
					}	
					else if (isGreaterThan(totalPoints[i]->getX(), p->getX()))
					{
						return false;
					}
					else if (isLowerThan(totalPoints[i]->getY(), p->getY()))
					{
						continue;
					}
					else if (isGreaterThan(totalPoints[i]->getY(), p->getY()))
					{
						return false;
					}
					
					return true;
				}

				return false;
			}

			/**********************************************************************************************//**
			 * @fn	static void Boundaries2D::sortCurveVector(Vector2D *vector)
			 *
			 * @brief	Método que ordena los puntos de un vector curvo.
			 *
			 * @author	Enrique Alonso
			 * @date	28/01/2014
			 *
			 * @param [in,out]	vector	Vector a ordenar.
			 **************************************************************************************************/
			static void sortCurveVector(Vector2D *vector)
			{
				Point2D *p1 = vector->getPoints()[0];
				Point2D *p2 = vector->getPoints()[vector->getPtsCount() - 1];
				bool sort = false;

				//Falta
				if (isGreaterThan(p1->getX(), p2->getX())) 
				{
					sort = true;
				}
				else if (isEqual(p1->getX(), p2->getX())) 
				{
					if (isGreaterThan(p1->getY(), p2->getY())) 
					{
						sort = true;
					}
				}

				if (sort)
				{
					Vector2D *vectorAux = new Vector2D(vector->getPoints());
					vector->getPoints().clear();

					int size = vectorAux->getPtsCount();
					for (int i = size - 1; i >= 0; i--)
					{
						vector->getPoints().push_back(vectorAux->getPoints()[i]);
					}
				}
			}

			/**********************************************************************************************//**
			 * @fn	static void Boundaries2D::sortStrightVector(Vector2D *vector)
			 *
			 * @brief	Método que ordena los puntos de un vector recto.
			 *
			 * @author	Enrique Alonso
			 * @date	28/01/2014
			 *
			 * @param [in,out]	vector	Vector a ordenar.
			 **************************************************************************************************/
			static void sortStrightVector(Vector2D *vector)
			{
				sort_points::sortPointsX(vector->getPoints()[0], vector->getPoints()[1]);
			}

			static int pointToAdd(Point2D *listPoint, Point2D *p)
			{
				if (isGreaterThan(listPoint->getX(), p->getX()))
				{
					return 1;
				}

				if (isEqual(p->getX(), listPoint->getX()) && isGreaterThan(listPoint->getY(), p->getY()))
				{
					return 1;
				}

				if (p->equals(listPoint))
				{
					return 0;
				}

				return -1;
			}

			/**********************************************************************************************//**
			 * @fn	static void Boundaries2D::addToVector(Vector2D *vectorToAdd, std::vector<Vector2D*> &vectorOfVector2D)
			 *
			 * @brief	Agregamos el vector (curvo o recto) a la posición correspondiente en la estructura
			 * 			de datos, para que queden ordenados todos los vectores.
			 *
			 * @author	Enrique Alonso
			 * @date	28/01/2014
			 *
			 * @param [in,out]	vectorToAdd			Vector que se agregará a la estructura de datos.
			 * @param [in,out]	vectorOfVector2D	Estructura donde se almacenará el vector.
			 **************************************************************************************************/
			static void addToVector(Vector2D *vectorToAdd, std::vector<Vector2D*> &vectorOfVector2D)
			{
				size_t size = vectorOfVector2D.size();

				//Agregamos a la posición que corresponde, para que quede ordenado el vector de vectores2D
				if (size == 0)
				{
					vectorOfVector2D.push_back(vectorToAdd);
				}
				else
				{
					for (size_t i = 0; i < size; i++)
					{
						if (vectorToAdd->equals(vectorOfVector2D[i]))
						{
							break;
						}
						else
						{
							int addToVector = pointToAdd(vectorOfVector2D[i]->getPoints()[0], vectorToAdd->getPoints()[0]);
							if (addToVector == 1)
							{
								vectorOfVector2D.insert(vectorOfVector2D.begin() + i, vectorToAdd);
								break;
							}
							else if (addToVector == 0)
							{
								addToVector = pointToAdd(vectorOfVector2D[i]->getPoints()[vectorOfVector2D[i]->getPtsCount() - 1], vectorToAdd->getPoints()[vectorToAdd->getPtsCount() - 1]);
								if (addToVector != -1)
								{
									vectorOfVector2D.insert(vectorOfVector2D.begin() + i, vectorToAdd);
									break;
								}
							}
						}

						if (i == size - 1)
						{
							vectorOfVector2D.push_back(vectorToAdd);
						}
					}
				}
			}

			/**********************************************************************************************//**
			 * @fn	static void Boundaries2D::identifyVectorsOfPolygons(std::vector<Point2D*> totalPoints, Polygon2D* polygon, std::vector<Vector2D*> &straightVectors, std::vector<Vector2D*> &curveVectors)
			 *
			 * @brief	Método principal utilizado para formar los vectores curvos y rectos.
			 *
			 * @author	Enrique Alonso
			 * @date	28/01/2014
			 *
			 * @param [in,out]	totalPoints	   	Puntos obtenidos en la clase TotalPoints2D.
			 * @param [in,out]	polygon		   	Polígono al cual se le obtendrán los vectores.
			 * @param [in,out]	straightVectors	Almacena los vectores rectos que se van formando.
			 * @param [in,out]	curveVectors   	Almacena los vectores curvos que se van formando.
			 **************************************************************************************************/
			static void identifyVectorsOfPolygons(std::vector<Point2D*> totalPoints, Polygon2D* polygon, std::vector<Vector2D*> &straightVectors, std::vector<Vector2D*> &curveVectors)
			{
				std::vector<Point2D*> contour = polygon->getCountour();
				std::vector<Point2D*> pointsVector;
				size_t size = contour.size();

				for (size_t i = 0, j; i <= size; i++)
				{
					j = (i == size) ? 0 : i;
					if (isPointInVector(contour[j], totalPoints))
					{
						if (pointsVector.empty())
						{
							pointsVector.push_back(contour[j]);
						}
						else
						{
							pointsVector.push_back(contour[j]);
							Vector2D *vector = new Vector2D(pointsVector);

							if (vector->getType() == STRAIGHT)
							{
								sortStrightVector(vector);
								findVectorDivisions(vector->getPoints()[0], vector->getPoints()[1], totalPoints, straightVectors);
							}
							else
							{
								sortCurveVector(vector);
								findVectorDivisions(vector, totalPoints, curveVectors);
							}
							
							pointsVector.clear();

							pointsVector.push_back(contour[j]);
						}
					}
					else
					{
						pointsVector.push_back(contour[j]);
					}
				}

				//Para los Holes
				size = polygon->getHolesCount();
				for (size_t i = 0; i < size; i++) 
				{
					identifyVectorsOfPolygons(totalPoints, polygon->getHoles()[i], straightVectors, curveVectors);
				}
			}

			/**********************************************************************************************//**
			 * @fn	static void Boundaries2D::sortPolyPoints(Polygon2D *poly, std::vector<Point2D*> totalPoints)
			 *
			 * @brief	Ordena los puntos de un polígono iniciando con alguno que se encuentre en 'totalPoints'.
			 *
			 * @author	Enrique Alonso
			 * @date	28/01/2014
			 *
			 * @param [in,out]	poly	   	Polígono al cual se le ordenan los puntos del contorno.
			 * @param [in,out]	totalPoints	Puntos obtenidos por la clase TotalPoints2D.
			 **************************************************************************************************/
			static void sortPolyPoints(Polygon2D *poly, std::vector<Point2D*> totalPoints)
			{
				std::vector<Point2D*> polyAux = poly->getCountour();
				size_t size = polyAux.size();
				size_t i = 0;
				for (; i < size; i++)
				{
					if (isPointInVector(polyAux[i], totalPoints))
					{
						break;
					}
				}

				if (i != 0 && i != size)
				{
					poly->getCountour().clear();
					size_t j = i;
					do
					{
						poly->getCountour().push_back(polyAux[j]);
						j = (j == size - 1) ? 0 : j + 1;
					} while(j != i);
				}
			}

			/**********************************************************************************************//**
			 * @fn	static void Boundaries2D::identifyVectorsOfPolygons(std::vector<Point2D*> totalPoints, std::vector<Polygon2D*> subdomains, std::vector<Vector2D*> &straightVectors, std::vector<Vector2D*> &curveVectors)
			 *
			 * @brief	Método que itera todos los polígonos para utilizar en cada uno el método
			 * 			identifyVectorsOfPolygons que está sobrecargado.
			 *
			 * @author	Enrique Alonso
			 * @date	28/01/2014
			 *
			 * @param [in,out]	totalPoints	   	Puntos obtenidos en la clase TotalPoints2D.
			 * @param [in,out]	polygon		   	Polígono al cual se le obtendrán los vectores.
			 * @param [in,out]	straightVectors	Almacena los vectores rectos que se van formando.
			 * @param [in,out]	curveVectors   	Almacena los vectores curvos que se van formando.
			 **************************************************************************************************/
			static void identifyVectorsOfPolygons(std::vector<Point2D*> totalPoints, std::vector<Polygon2D*> subdomains, std::vector<Vector2D*> &straightVectors, std::vector<Vector2D*> &curveVectors)
			{
				size_t size = subdomains.size();
				for (size_t i = 0; i < size; i++)
				{
					sortPolyPoints(subdomains[i], totalPoints);
					identifyVectorsOfPolygons(totalPoints, subdomains[i], straightVectors, curveVectors);
				}
			}

			/**********************************************************************************************//**
			 * @fn	static void Boundaries2D::fillBoundariesVector(std::vector<Vector2D*> &boundaries, std::vector<Vector2D*> straightVectors, std::vector<Vector2D*> curveVectors)
			 *
			 * @brief	Método que junta los vectores rectos y curvos en una sola estructura de datos.
			 *
			 * @author	Enrique Alonso
			 * @date	28/01/2014
			 *
			 * @param [in,out]	boundaries	   	Estructura donde se almacenan los vectores.
			 * @param [in,out]	straightVectors	Vectores rectos.
			 * @param [in,out]	curveVectors   	Vectores curvos.
			 **************************************************************************************************/
			static void fillBoundariesVector(std::vector<Vector2D*> &boundaries, std::vector<Vector2D*> straightVectors, std::vector<Vector2D*> curveVectors)
			{
				size_t size = straightVectors.size();
				for (size_t i = 0; i < size; i++)
				{
					boundaries.push_back(straightVectors[i]);
				}

				size = curveVectors.size();
				for (size_t i = 0; i < size; i++)
				{
					boundaries.push_back(curveVectors[i]);
				}
			}

			/**********************************************************************************************//**
			 * @fn	static bool Boundaries2D::isPointInSegment(Point2D *p1, Point2D *p2, Point2D *p)
			 *
			 * @brief	Método que checa si un punto está en medio de un segmento de línea.
			 *
			 * @author	Enrique Alonso
			 * @date	28/01/2014
			 *
			 * @param [in,out]	p1	Punto inicial del segmento de línea.
			 * @param [in,out]	p2	Punto final del segmento de línea.
			 * @param [in,out]	p 	Punto que se checa si está dentro del segmento de línea.
			 *
			 * @return	true if point in segment, false if not.
			 **************************************************************************************************/
			static bool isPointInSegment(Point2D *p1, Point2D *p2, Point2D *p)
			{
				if (p1->equals(p) || p2->equals(p))
				{
					return false;
				}
				else
				{
					double m, b;
					Segment2D::calculateSlopeAndB(p1, p2, m, b);

					if (isEqual(m, INF) &&		//Si el segmento es vertical
						isEqual(p->getX(), p1->getX()) && //Si el punto esta en la misma X que el segmento
						(isGreaterThan(p->getY(), p1->getY() && isLowerThan(p->getY(), p2->getY()))))  //El punto está en medio de los dos puntos de la línea
					{
						return true;
					}

					if (isEqual(m, 0.0) &&		//Si el segmento es horizontal
						isEqual(p->getY(), p1->getY()) && //Si el punto esta en la misma Y que el segmento
						(isGreaterThan(p->getX(), p1->getX() && isLowerThan(p->getX(), p2->getX()))))  //El punto está en medio de los dos puntos de la línea
					{
						return true;
					}

					return isEqual(p->getY(), (m * p->getX() + b)) && 
							(isGreaterThan(p->getX(), p1->getX() && isLowerThan(p->getX(), p2->getX())));

				}
			}

			/**********************************************************************************************//**
			 * @fn	static bool Boundaries2D::obtainPointsInSegment(Point2D *p1, Point2D *p2, std::vector<Point2D*> totalPoints, std::vector<Point2D*> &pointsInSegment)
			 *
			 * @brief	Se obtienen todos los puntos que están dentro de un segmento de línea.
			 * 			Esto hace que se generen subdivisiones del vector.
			 *
			 * @author	Enrique Alonso
			 * @date	28/01/2014
			 *
			 * @param [in,out]	p1			   	Punto inicial del segmento de línea.
			 * @param [in,out]	p2			   	Punto final del segmento de línea.
			 * @param [in,out]	totalPoints	   	Todos los puntos calculados en la clase TotalPoints2D.
			 * @param [in,out]	pointsInSegment	Conjunto de puntos que estuvieron dentro del vector.
			 *
			 * @return	true si existieron puntos dentro del vector, false en caso contrario.
			 **************************************************************************************************/
			static bool obtainPointsInSegment(Point2D *p1, Point2D *p2, std::vector<Point2D*> totalPoints, std::vector<Point2D*> &pointsInSegment)
			{
				pointsInSegment.clear();
				pointsInSegment.push_back(p1);

				size_t size = totalPoints.size();
				for (size_t i = 0; i < size; i++)
				{
					if (isPointInSegment(p1, p2, totalPoints[i]))
					{
						pointsInSegment.push_back(totalPoints[i]);
					}
				}

				pointsInSegment.push_back(p2);

				if (pointsInSegment.size() == 2)
				{
					return false;
				}

				return true;
			}

			/**********************************************************************************************//**
			 * @fn	static void Boundaries2D::findVectorDivisions(Vector2D *vector, std::vector<Point2D*> totalPoints, std::vector<Vector2D*> &curveVectors)
			 *
			 * @brief	Buscamos si un vector curvo se subdivide en más vectores. 
			 * 			Esto sucede cuando un punto toca el contorno del vector.
			 *
			 * @author	Enrique Alonso
			 * @date	28/01/2014
			 *
			 * @param [in,out]	vector			Vector que se revisa para encontrar subdivisiones.
			 * @param [in,out]	totalPoints 	Todos los puntos calculados en la clase TotalPoints2D.
			 * @param [in,out]	curveVectors	Estructura que almacena los vectores rectos.
			 **************************************************************************************************/
			static void findVectorDivisions(Vector2D *vector, std::vector<Point2D*> totalPoints, std::vector<Vector2D*> &curveVectors)
			{
				std::vector<Point2D*> pointsInSegment, pointsVector;
				Point2D *pAux = 0;

				size_t size = vector->getPtsCount();
				for (size_t i = 0; i < size; i++)
				{
					if (pointsVector.empty())
					{
						pointsVector.push_back(vector->getPoints()[i]);
					}
					else
					{
						//Dividimos el vector curvo si se encuentran puntos que lo corten.
						if (obtainPointsInSegment(pointsVector[pointsVector.size() - 1], vector->getPoints()[i], 
													totalPoints, pointsInSegment))
						{
							size_t sizePointsInSeg = pointsInSegment.size();
							for (size_t j = 1; j < sizePointsInSeg; j++)
							{
								pointsVector.push_back(pointsInSegment[j]);
								Vector2D *vector = new Vector2D(pointsVector);
								addToVector(vector, curveVectors);

								pointsVector.clear();
								pointsVector.push_back(pointsInSegment[j]);
							}
						}
						else
						{
							pointsVector.push_back(vector->getPoints()[i]);
						}
					}
				}

				if (pointsVector.size() > 1)
				{
					Vector2D *vector = new Vector2D(pointsVector);
					addToVector(vector, curveVectors);
				}

			}

			/**********************************************************************************************//**
			 * @fn	static void Boundaries2D::findVectorDivisions(Point2D *p1, Point2D *p2, std::vector<Point2D*> totalPoints, std::vector<Vector2D*> &straightVectors)
			 *
			 * @brief	A partir de 2 puntos de un segmento, se obtienen los puntos que están 
			 * 			dentro de ese segmento, para formar más vectores.
			 *
			 * @author	Enrique Alonso
			 * @date	28/01/2014
			 *
			 * @param [in,out]	p1			   	Punto inicial del segmento.
			 * @param [in,out]	p2			   	Punto final del segmento.
			 * @param [in,out]	totalPoints	   	Todos los puntos calculados en la clase TotalPoints2D.
			 * @param [in,out]	straightVectors	Estructura que almacena los vectores rectos.
			 **************************************************************************************************/

			static void findVectorDivisions(Point2D *p1, Point2D *p2, std::vector<Point2D*> totalPoints, std::vector<Vector2D*> &straightVectors)
			{
				std::vector<Point2D*> pointsInSegment, pointsVector;

				obtainPointsInSegment(p1, p2, totalPoints, pointsInSegment);

				size_t size = pointsInSegment.size();
				for (size_t j = 0; j < size; j++)
				{
					if (pointsVector.empty())
					{
						pointsVector.push_back(pointsInSegment[j]);
					}
					else
					{
						pointsVector.push_back(pointsInSegment[j]);
						Vector2D *vector = new Vector2D(pointsVector);

						addToVector(vector, straightVectors);
							
						pointsVector.clear();

						pointsVector.push_back(pointsInSegment[j]);
					}
				}
			}

			/**********************************************************************************************//**
			 * @fn	static void Boundaries2D::findVectorDivisions(std::vector<Point2D*> totalPoints, std::vector<Vector2D*> &straightVectors, Elements2D elements)
			 *
			 * @brief	Buscamos si los segmentos de línea son intersectados por puntos, para así formar
			 * 			más vectores.
			 *
			 * @author	Enrique Alonso
			 * @date	28/01/2014
			 *
			 * @param [in,out]	totalPoints	   	Todos los puntos calculados en la clase TotalPoints2D.
			 * @param [in,out]	straightVectors	Estructura que almacena los vectores rectos.
			 * @param	elements			   	The elements.
			 **************************************************************************************************/
			static void findVectorDivisions(std::vector<Point2D*> totalPoints, std::vector<Vector2D*> &straightVectors, Elements2D elements)
			{
				size_t size = elements.getSegCount();

				for (size_t i = 0; i < size; i++)
				{
					findVectorDivisions(elements.getSegments()[i]->getP1(), elements.getSegments()[i]->getP2(), totalPoints, straightVectors);
				}
			}

		public:

			/**********************************************************************************************//**
			 * @fn	static std::vector<Vector2D*> Boundaries2D::obtainBoundaries(Elements2D elements)
			 *
			 * @brief	Obtenemos todas los vectores formadas en el CAD.
			 *
			 * @author	Enrique Alonso
			 * @date	28/01/2014
			 *
			 * @param	elements	Todos los elementos en 2D dibujados en el CAD.
			 *
			 * @return	Conjunto de Vectores.
			 **************************************************************************************************/
			static std::vector<Vector2D*> obtainBoundaries(Elements2D elements)
			{
				std::vector<Point2D*> totalPoints = total_points_2D::TotalPoints2D::obtainTotalPoints(elements);
				std::vector<Polygon2D*> subdomains = subdomains_2D::Subdomains2D::obtainSubdomains(elements);

				return obtainBoundaries(totalPoints, subdomains, elements);
			}

			/**********************************************************************************************//**
			 * @fn	static std::vector<Vector2D*> Boundaries2D::obtainBoundaries(std::vector<Point2D*> totalPoints, Elements2D elements)
			 *
			 * @brief	Obtenemos todas los vectores formadas en el CAD.
			 *
			 * @author	Enrique Alonso
			 * @date	29/01/2014
			 *
			 * @param [in,out]	totalPoints	Los puntos calculados por la clase TotalPoints2D.
			 * @param	elements	Todos los elementos en 2D dibujados en el CAD.
			 *
			 * @return	Conjunto de Vectores.
			 **************************************************************************************************/
			static std::vector<Vector2D*> obtainBoundaries(std::vector<Point2D*> totalPoints, Elements2D elements)
			{
				std::vector<Polygon2D*> subdomains = subdomains_2D::Subdomains2D::obtainSubdomains(elements);

				return obtainBoundaries(totalPoints, subdomains, elements);
			}

			/**********************************************************************************************//**
			 * @fn	static std::vector<Vector2D*> Boundaries2D::obtainBoundaries(std::vector<Polygon2D*> subdomains, Elements2D elements)
			 *
			 * @brief	Obtenemos todas los vectores formadas en el CAD.
			 *
			 * @author	Enrique Alonso
			 * @date	29/01/2014
			 *
			 * @param [in,out]	subdomains 	Las áreas calculadas por la clase Subdomains2D.
			 * @param	elements	Todos los elementos en 2D dibujados en el CAD.
			 *
			 * @return	Conjunto de Vectores.
			 **************************************************************************************************/
			static std::vector<Vector2D*> obtainBoundaries(std::vector<Polygon2D*> subdomains, Elements2D elements)
			{
				std::vector<Point2D*> totalPoints = total_points_2D::TotalPoints2D::obtainTotalPoints(elements);

				return obtainBoundaries(totalPoints, subdomains, elements);
			}

			/**********************************************************************************************//**
			 * @fn	static std::vector<Vector2D*> Boundaries2D::obtainBoundaries(std::vector<Point2D*> totalPoints, std::vector<Polygon2D*> subdomains, Elements2D elements)
			 *
			 * @brief	Obtenemos todas los vectores formadas en el CAD.
			 *
			 * @author	Enrique Alonso
			 * @date	28/01/2014
			 *
			 * @param [in,out]	totalPoints	Los puntos calculados por la clase TotalPoints2D.
			 * @param [in,out]	subdomains 	Las áreas calculadas por la clase Subdomains2D.
			 * @param	elements	Todos los elementos en 2D dibujados en el CAD.
			 *
			 * @return	Conjunto de Vectores.
			 **************************************************************************************************/
			static std::vector<Vector2D*> obtainBoundaries(std::vector<Point2D*> totalPoints, std::vector<Polygon2D*> subdomains, Elements2D elements)
			{
				//std::ofstream result;
				//result.open("Boundaries.txt");

				std::vector<Vector2D*> boundaries;
				std::vector<Vector2D*> straightVectors;
				std::vector<Vector2D*> curveVectors;

				findVectorDivisions(totalPoints, straightVectors, elements);
				identifyVectorsOfPolygons(totalPoints, subdomains, straightVectors, curveVectors);

				fillBoundariesVector(boundaries, straightVectors, curveVectors);

				//result << "------------>Boundaries: ("<< boundaries.size() <<")<------------------" << std::endl;
				size_t size = boundaries.size();
				for (size_t i = 0; i < size; i++)
				{
					//result << (i + 1) << ":" << std::endl;
					//result << *boundaries[i] << std::endl;
					boundaries[i]->setID(i);
				}

				return boundaries;
			}
	};
}

#endif