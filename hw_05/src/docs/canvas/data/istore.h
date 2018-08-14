#pragma once

namespace HW_05
{

namespace DATA_STORAGE
{

class IStore
{
public:
	/*!
	\brief Export
	\param[in] path - shape container path
	*/
	virtual void Export(std::string &path) = 0;

	/*!
	\brief Import
	\param[in] path - shape container path
	*/
	virtual void Import(std::string &path) = 0;
};

}

}
