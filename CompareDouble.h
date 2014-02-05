#ifndef COMPARE_DOUBLE_H
#define COMPARE_DOUBLE_H

#include <math.h>

/**********************************************************************************************//**
 * @def	INF
 *
 * @brief	Macro que define el valor infinito para una pendiente.
 *
 * @author	Enrique Alonso
 * @date	21/01/2014
 **************************************************************************************************/
#define INF 1e100

/**********************************************************************************************//**
 * @def	ZERO
 *
 * @brief	Error definido para comparar doubles.
 *
 * @author	Enrique Alonso
 * @date	21/01/2014
 **************************************************************************************************/
#define ZERO 1e-8 //1e-8

/**********************************************************************************************//**
 * @def	isEqual(a, b) (fabs((a) - (b)) < ZERO)
 *
 * @brief	Macro que define si dos valores de tipo double son iguales.
 *
 * @author	Enrique Alonso
 * @date	21/01/2014
 *
 * @param	a	Primer valor double.
 * @param	b	Segundo valor double.
 **************************************************************************************************/
#define isEqual(a, b)				(fabs((a) - (b)) < ZERO)

/**********************************************************************************************//**
 * @def	isGreaterThan(a, b) (!isEqual(a, b) ? ((a > b) ? true : false) : false)
 *
 * @brief	Macro que define si el valor 'a' es mayor al valor de 'b'.
 *
 * @author	Enrique Alonso
 * @date	21/01/2014
 *
 * @param	a	Primer valor double.
 * @param	b	Segundo valor double.
 **************************************************************************************************/
#define isGreaterThan(a, b)			(!isEqual(a, b) ? ((a > b) ? true : false) : false)

/**********************************************************************************************//**
 * @def	isLowerThan(a, b) (!isEqual(a, b) ? ((a < b) ? true : false) : false)
 *
 * @brief	Macro que define si el valor 'a' es menor al valor de 'b'.
 *
 * @author	Enrique Alonso
 * @date	21/01/2014
 *
 * @param	a	Primer valor double.
 * @param	b	Segundo valor double.
 **************************************************************************************************/
#define isLowerThan(a, b)			(!isEqual(a, b) ? ((a < b) ? true : false) : false)

/**********************************************************************************************//**
 * @def	isGreaterEqualThan(a, b) (isEqual(a, b) ? true : ((a > b) ? true : false))
 *
 * @brief	Macro que define si el valor 'a' es mayor o igual al valor de 'b'.
 *
 * @author	Enrique Alonso
 * @date	21/01/2014
 *
 * @param	a	Primer valor double.
 * @param	b	Segundo valor double.
 **************************************************************************************************/
#define isGreaterEqualThan(a, b)	(isEqual(a, b) ? true : ((a > b) ? true : false))

/**********************************************************************************************//**
 * @def	isLowerEqualThan(a, b) (isEqual(a, b) ? true : ((a < b) ? true : false))
 *
 * @brief	Macro que define si el valor 'a' es menor o igual al valor de 'b'.
 *
 * @author	Enrique Alonso
 * @date	21/01/2014
 *
 * @param	a	Primer valor double.
 * @param	b	Segundo valor double.
 **************************************************************************************************/
#define isLowerEqualThan(a, b)		(isEqual(a, b) ? true : ((a < b) ? true : false))

/**********************************************************************************************//**
 * @def	round(fp) (int)((fp) >= 0 ? (fp) + 0.5 : (fp) - 0.5)
 *
 * @brief	Macro que redondea un valor double.
 *
 * @author	Enrique Alonso
 * @date	21/01/2014
 *
 * @param	fp	Valor double.
 **************************************************************************************************/
#define round(fp)					(int)((fp) >= 0 ? (fp) + 0.5 : (fp) - 0.5)

#endif