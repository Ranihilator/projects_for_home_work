#pragma once

#include "docs/docs.h"

namespace HW_05
{

/*!
\brief Editor controller
*/
class Editor:
	private DOCUMENTS::Docs
{
public:

	/*!
	\brief Create document
	\param[in] name - name of documents
	*/
	void Create_Document(std::string name);

	/*!
	\brief Close document
	\param[in] name - name of documents
	*/
	void Close_Document(std::string name);

	/*!
	\brief Save document
	\param[in] name - name of documents
	\param[in] path - file to save
	*/
	void Save_Document(std::string name, std::string path);

	/*!
	\brief Load document
	\param[in] name - name of documents
	\param[in] path - file to save
	*/
	void Load_Document(std::string name, std::string path);

	/*!
	\brief Select workspace from name
	\param[in] name - name of documents
	*/
	void Select_Workspace(std::string name);

	/*!
	\brief Create shape into current workspace
	\param[in] _shape - allocate new SHAPES::Shape class
	*/
	void Create_Shape(std::unique_ptr<SHAPES::IShape> _shape);

	/*!
	\brief Create shape into current name documents
	\param[in] name - name of documents
	\param[in] _shape - allocate new SHAPES::Shape class
	*/
	void Create_Shape(std::string name, std::unique_ptr<SHAPES::IShape> _shape);

	/*!
	\brief Delete shape into current workspace
	\param[in] _coordinate - coordinate what shape need to delete
	*/
	void Delete_Shape(SHAPES::Coordinate_XY _coordinate);


	/*!
	\brief Delete shape into current name documents
	\param[in] name - name of documents
	\param[in] _coordinate - coordinate what shape need to delete
	*/
	void Delete_Shape(std::string name, SHAPES::Coordinate_XY _coordinate);

	/*!
	\brief Get pointer from current workspace shape primitive
	\param[in] _coordinate - coordinate of shape
	return Pointer to SHAPES::IShape primitive
	*/
	SHAPES::IShape* Select_Shape(SHAPES::Coordinate_XY _coordinate);

	/*!
	\brief Get pointer from current name documents shape primitive
	\param[in] name - name of documents
	\param[in] _coordinate - coordinate of shape
	return Pointer to SHAPES::IShape primitive
	*/
	SHAPES::IShape* Select_Shape(std::string name, SHAPES::Coordinate_XY _coordinate);

private:
	DOCUMENTS::Canvas* Current_Workspace = nullptr;											///< Pointer to current workspace (DOCUMENTS::Canvas)
};

}
