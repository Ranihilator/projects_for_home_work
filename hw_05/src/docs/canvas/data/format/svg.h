#pragma once

#include "iformat.h"

namespace HW_05
{

namespace DATA_STORAGE
{

class svg : public IFORMAT
{
public:

	/*!
	\brief file path
	\param[in] _file - path to svg file
	*/
	svg(std::fstream &_file);

	/*!
	\brief Import parser
	\details read file, doing parse and create shapes to SHAPES::Shapes creator from pointer
	\param[in] shape - pointer to SHAPES::Shapes creator class
	*/
	void Import(SHAPES::Shapes *shape);

	/*!
	\brief Export parser
	\details write file, save all shapes from SHAPES::Shapes creator
	\param[in] shape - pointer to SHAPES::Shapes creator class
	*/
	void Export(SHAPES::Shapes *shape);

private:
	std::fstream &file;
};

}

}
