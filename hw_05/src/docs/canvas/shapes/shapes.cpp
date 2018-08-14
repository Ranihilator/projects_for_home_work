#include "shapes.h"

namespace HW_05
{

namespace SHAPES
{

void Shapes::insert(std::unique_ptr<IShape> shape)
{
	uint32_t insert_id = this->shapes.size();
	this->shapes[insert_id] = std::move(shape);
}

bool Shapes::remove(uint64_t ID)
{
	this->shapes.erase(ID);
}

bool Shapes::remove(Coordinate_XY coordinate)
{
	for (auto &iter : this->shapes)
	{
		if (iter.second->Select(coordinate))
			return true;
	}

	return false;
}

IShape* Shapes::find(uint64_t ID)
{
	auto node = this->shapes.find(ID);
	if (node != this->shapes.end())
		return node->second.get();

	return nullptr;
}

IShape* Shapes::find(Coordinate_XY coordinate)
{
	for (auto &it : this->shapes)
	{
		if (it.second->Select(coordinate))
			return it.second.get();
	}

	return nullptr;
}

void Shapes::replace(uint64_t ID, IShape *shape)
{
        this->shapes[ID].reset(shape);
}

void Shapes::replace(Coordinate_XY coordinate, IShape *shape)
{
	for (auto &it : this->shapes)
	{
		if (it.second->Select(coordinate))
		{
			it.second.reset(shape);
			break;
		}
	}
}

size_t Shapes::size()
{
	this->shapes.size();
}

void Shapes::clear()
{
	this->shapes.clear();
}

}

}
