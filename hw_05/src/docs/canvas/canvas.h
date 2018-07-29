#pragma once

#include "shapes/shapes.h"
#include "data/file.h"

namespace HW_05
{

namespace DOCUMENTS
{

/*!
\brief Canvas workspace controller
\details Canvas workspace provide:
- SHAPES::Shapes creator pool shapes into canvas
- DATA_STORAGE::File import and export shapes into canvas
- Canvas parameters such (size of canvas and center)
*/
class Canvas:
	public SHAPES::Shapes
{
public:

	/*!
	\brief Canvas file path
	\param[in] path - path to file
	*/
	Canvas(std::string path = std::string());

	/*!
	\brief Export
	\param[in] path - path to save file (Export), saveAs new file
	*/
	void Export(std::string path);

	/*!
	\brief Import
	\param[in] path - path to load file (Import), current shape will be clear
	*/
	void Import(std::string path);

private:
	DATA_STORAGE::File file;														///< file handler

private:
	SHAPES::Coordinate_XY canvas_size;												///< size of canvas
	SHAPES::Coordinate_XY canvas_center;											///< center coordinate of canvas
};

}

}
