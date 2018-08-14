#pragma once

#include "format/cdr.h"
#include "format/dxf.h"
#include "format/svg.h"
#include "format/vsd.h"

#include "istore.h"

namespace HW_05
{

namespace DATA_STORAGE
{

/*!
\brief It's just empty struct
*/
struct db_type
{};

/*!
\brief Database controller
\details Save and load shapes
*/
class DataBase:
	public IStore
{
public:
	/*!
	\brief DataBase controller
	\param[in] path - file shape container path
	\param[in] _shapes - pointer to SHAPES::Shapes class creator
	*/
	DataBase(std::string path, std::string name, std::string user, std::string password, SHAPES::Shapes *_shapes = nullptr);

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
	\brief Loading shapes from DataBase
	*/
	void Load();

private:
	SHAPES::Shapes *shapes;									///< Current works SHAPES::Shapes creator

	std::unique_ptr<IFORMAT> format;						///< DataBase format shapes

	db_type db_socket;										///< DataBase socket

	std::vector<uint8_t> buffer;							///< Raw Buffer
};

}

}
