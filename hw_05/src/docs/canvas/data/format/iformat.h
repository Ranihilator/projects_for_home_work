#pragma once

#include <string>
#include "shapes.h"
#include <fstream>


namespace HW_05
{

namespace DATA_STORAGE
{

/*!
\brief File Formats
*/
enum class FORMATS
{
	NUL,						///< Unknown file format
	CDR,						///< Corel Draw file format
	DXF,						///< AutoCad file format
	SVG,						///< SVG file format
	VSD							///< Visio file format
};

/*!
\brief IFORMAT Polymorphism class
\details provide pure virtual method to file format class
*/
class IFORMAT
{
public:

	/*!
	\brief Import
	\param[in] shape - pointer to SHAPES::Shapes creator class
	*/
	virtual void Import(SHAPES::Shapes *shape) = 0;

	/*!
	\brief Export
	\param[in] shape - pointer to SHAPES::Shapes creator class
	*/
	virtual void Export(SHAPES::Shapes *shape) = 0;
};

}

}
