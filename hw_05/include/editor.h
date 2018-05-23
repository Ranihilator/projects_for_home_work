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
		UNKNOWN = 0,			/// Unknown format
		SVG = 1,			/// SVG format
		VSD = 2,			/// VSD format
		DXF = 3,			/// DXF format
		CDR = 4,			/// CDR format

		AUTO = 0xFF			/// Auto detect format
	};

	void Create_Documents()
	{
		auto count = 1;
		std::string unamed = "unamed";

		while (this->documents.find(unamed) != this->documents.end())
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
		auto result = this->documents.find(path);
		if (result == this->documents.end())
			return;

                switch (type)
                {
			case Type_File::SVG:
				result->second.save(new svg(path));

			case Type_File::VSD:
				result->second.save(new vsd(path));

			case Type_File::DXF:
				result->second.save(new dxf(path));

			case Type_File::CDR:
				result->second.save(new cdr(path));

			default:{}
                }
	}

	Document_Pool* Draw_Element(std::string path)
	{
		return &documents[path];
	}

private:
	std::map <std::string, Document_Pool> documents;
};

}
