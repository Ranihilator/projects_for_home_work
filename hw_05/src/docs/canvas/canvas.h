#pragma once

#include "shapes/shapes.h"
#include "data/data_link.h"

namespace HW_05
{

namespace DOCUMENTS
{

/*!
\brief Canvas workspace controller
\details Canvas workspace provide:
- SHAPES::Shapes creator pool shapes into canvas
- DATA_STORAGE::Data_Link import and export shapes into canvas
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
	DATA_STORAGE::Data_Link link;														///< link handler

private:
	SHAPES::Coordinate_XY canvas_size;												///< size of canvas
	SHAPES::Coordinate_XY canvas_center;											///< center coordinate of canvas
};

}

}
