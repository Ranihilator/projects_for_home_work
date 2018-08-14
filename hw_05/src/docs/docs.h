#pragma once

#include "canvas/canvas.h"

namespace HW_05
{

/*!
\brief DOCUMENTS namespace
\details Provide DOCUMENTS::Canvas controller class and DOCUMENTS::Docs creator class
*/
namespace DOCUMENTS
{

/*!
\brief Docs creator pool class
\details provide one or multiple documents pool
*/
class Docs
{
public:

	/*!
	\brief create new documents
	\param[in] name - name of documents
	\param[in] path - pointer document to file
	*/
	void insert(std::string name, std::string path = std::string());

	/*!
	\brief delete existing documents
	\param[in] name - name of documents
	*/
	void remove(std::string name);

	/*!
	\brief Save the documents
	\param[in] name - name of documents
	\param[in] path - path to file
	*/
	void Save(std::string name, std::string path);

	/*!
	\brief Load the documents
	\param[in] name - name of documents
	\param[in] path - path to file
	*/
	void Load(std::string name, std::string path);

	/*!
	\brief Get canvas from document name
	\param[in] name - name of documents
	\return pointer to DOCUMENTS::Canvas
	*/
	Canvas* find(std::string name);
private:
	std::map<std::string, Canvas> canvas;						///< documents(DOCUMENTS::Canvas) pool
};

}

}
