#pragma once

#include "format/cdr.h"
#include "format/dxf.h"
#include "format/svg.h"
#include "format/vsd.h"

namespace HW_05
{

/*!
\brief DATA_STORAGE namespace
\details Provide DATA_STORAGE::File controller class to operating with import and export function
*/
namespace DATA_STORAGE
{

/*!
\brief File controller
\details Save and load shapes
*/
class File
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
};

}

}
