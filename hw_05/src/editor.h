#pragma once

#include "docs/docs.h"

namespace HW_05
{

/*!
\brief Editor controller
*/
class Editor
{
public:
	Editor();
	~Editor();

	void Create_Document();
	void Close_Document();

	void Save_Document();
	void Load_Document();

	void Create_Shape();
	void Delete_Shape();
	void Select_Shape();
};

}
