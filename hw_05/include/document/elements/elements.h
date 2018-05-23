#pragma once

#include <map>
#include <memory>

#include "basics/lines.h"
#include "basics/polygons.h"
#include "basics/circles.h"

namespace HW_05
{

class Elements_Pool
{
public:
    uint32_t insert(IElement* element)
    {
        uint32_t insert_id = this->pool.size();
        this->pool[insert_id].reset(element);

        return insert_id;
    }

    void remove(Point coordinate)
    {
        auto it = this->pool.begin();
        while (it != this->pool.end())
        {
            if (it->second->Get_Coordinate() == coordinate)
                this->pool.erase(it++);
            else
                ++it;
        }
    }

    void clear()
    {
        this->pool.clear();
    }

    uint64_t size() const
    {
    	return pool.size();
    }

    IElement* get(uint64_t pos)
    {
    	return pool[pos].get();
    }

private:
    std::map <uint32_t, std::unique_ptr<IElement>> pool;
};

}
