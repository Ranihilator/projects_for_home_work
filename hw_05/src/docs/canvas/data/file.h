#pragma once

#include "format/cdr.h"
#include "format/dxf.h"
#include "format/svg.h"
#include "format/vsd.h"

#include "istore.h"
#include <fstream>

namespace HW_05
{

namespace DATA_STORAGE
{

/*!
\brief Database controller
\details Save and load shapes
*/
class File:
	public IStore
{
public:
	/*!
	\brief File controller
	\param[in] path - file shape container path
	\param[in] _shapes - pointer to SHAPES::Shapes class creator
	*/
	File(std::string path, SHAPES::Shapes *_shapes = nullptr);

	/*!
	\brief Export
	\param[in] path - file shape container path
	*/
	void Export(std::string &path);

	/*!
	\brief Import
	\param[in] path - file shape container path
	*/
	void Import(std::string &path);

private:

	/*!
	\brief Loading shapes from file
	*/
	void Load();

private:
	SHAPES::Shapes *shapes;									///< Current works SHAPES::Shapes creator

	std::unique_ptr<IFORMAT> format;						///< File format shapes

	std::fstream file_socket;								///< File socket

	std::vector<uint8_t> buffer;							///< Raw Buffer
};

}

}
