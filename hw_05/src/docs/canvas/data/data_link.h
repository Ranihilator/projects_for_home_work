#pragma once

#include "database.h"
#include "file.h"

namespace HW_05
{

/*!
\brief DATA_STORAGE namespace
\details Provide DATA_STORAGE::File controller class to operating with import and export function
*/
namespace DATA_STORAGE
{

/*!
\brief Data_Link controller
\details Save and load shapes
*/
class Data_Link
{
public:
	/*!
	\brief File controller
	\param[in] path - file shape container path
	\param[in] _shapes - pointer to SHAPES::Shapes class creator
	*/
	Data_Link(std::string path, SHAPES::Shapes *_shapes = nullptr);

	/*!
	\brief DataBase controller
	\param[in] path - url path to database
	\param[in] name - name of database
	\param[in] user - user of database
	\param[in] password - password of database
	\param[in] _shapes - pointer to SHAPES::Shapes class creator
	*/
	Data_Link(std::string path, std::string name, std::string user, std::string password, SHAPES::Shapes *_shapes = nullptr);

	/*!
	\brief Export
	\param[in] path - shape container path
	*/
	void Export(std::string &path);

	/*!
	\brief Import
	\param[in] path - shape container path
	*/
	void Import(std::string &path);

private:
	std::unique_ptr<IStore> socket;							///< Link socket
};

}

}
