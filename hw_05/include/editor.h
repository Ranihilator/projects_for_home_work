#pragma once

#include <iostream>
#include <deque>

#include "document/document.h"

/// Home work #5 (simple uml)
namespace HW_05
{

class Editor
{
public:

	enum class Type_File : uint8_t
	{
		UNKNOWN = 0,
		SVG = 1,
		VSD = 2,
		DXF = 3,
		CDR = 4,

		AUTO = 0xFF
	};

	void Create_Documents()
	{
		auto count = 1;
		std::string unamed = "unamed";

		while (this->documents.find(unamed) == this->documents.end())
			unamed = "unamed" + std::to_string(count++);

		this->documents.insert(std::make_pair(unamed, Document_Pool()));
	}

	void Close_Documents(std::string path)
	{
		auto result = this->documents.find(path);
		if (result == this->documents.end())
			this->documents.erase(result);
	}

	void Import_Documents(std::string path, Type_File type = Type_File::AUTO)
	{
		if (this->documents.find(path) != this->documents.end())
			return;

                switch (type)
                {
		case Type_File::SVG:
			this->documents.insert(std::make_pair(path, Document_Pool(new svg(path))));

		case Type_File::VSD:
			this->documents.insert(std::make_pair(path, Document_Pool(new vsd(path))));

		case Type_File::DXF:
			this->documents.insert(std::make_pair(path, Document_Pool(new dxf(path))));

		case Type_File::CDR:
			this->documents.insert(std::make_pair(path, Document_Pool(new cdr(path))));

		default:{}
                }
	}

	void Export_Documents(std::string path, Type_File type = Type_File::AUTO)
	{

	}

	Draw& Draw_Element(std::string path)
	{
		return documents[path];
	}

private:
	std::map <std::string, Document_Pool> documents;
};

}
