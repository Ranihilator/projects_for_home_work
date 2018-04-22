#pragma once

#include <string>

/// Home work #5 (simple uml)
namespace HW_05
{

namespace FORMAT
{

using std::string;

class IFormat
{
public:
    virtual void read(string path) = 0;
    virtual void write(string path) = 0;
};

class svg : public IFormat
{
	void read(string path) override
	{}

	void write(string path) override
	{}
};

class vsd : public IFormat
{
	void read(string path) override
	{}

	void write(string path) override
	{}
};

class cdr : public IFormat
{
	void read(string path) override
	{}

	void write(string path) override
	{}
};

class dxf : public IFormat
{
	void read(string path) override
	{}

	void write(string path) override
	{}
};

}

}
