#pragma once

#include "iformat.h"

namespace HW_05
{

namespace DATA_STORAGE
{

class cdr : public IFORMAT
{
public:

	/*!
	\brief raw buffer
	\param[in] _buffer - corel draw raw data
	*/
	cdr(std::vector<uint8_t> &_buffer);

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
	std::vector<uint8_t> &buffer;
};

}

}
