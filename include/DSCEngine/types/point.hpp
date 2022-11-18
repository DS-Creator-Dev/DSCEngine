/*!
* \file point.hpp
* \brief Generic point definition
 */

#pragma once

namespace DSC
{
	/*! \brief Generic point of two coordinates
	* 	\tparam T type of the X/Y dimensions
	 */
	template<typename T>
	struct Point
	{		
		T x; /*!< Point X-coordinate */
		T y; /*!< Point Y-coordinate */
	};
}