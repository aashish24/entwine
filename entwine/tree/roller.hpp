/******************************************************************************
* Copyright (c) 2016, Connor Manning (connor@hobu.co)
*
* Entwine -- Point cloud indexing
*
* Entwine is available under the terms of the LGPL2 license. See COPYING
* for specific license text and more information.
*
******************************************************************************/

#pragma once

#include <cstddef>

#include <entwine/types/bbox.hpp>

namespace entwine
{

class Point;

// Maintains the state of the current point as it traverses the virtual tree.
class Roller
{
public:
    Roller(const BBox& bbox, std::size_t dimensions);
    Roller(const Roller& other);

    void magnify(const Point& point);
    std::size_t depth() const;
    uint64_t index() const;
    const BBox& bbox() const;

    void goNw();
    void goNe();
    void goSw();
    void goSe();

    void goNwu();
    void goNwd();
    void goNeu();
    void goNed();
    void goSwu();
    void goSwd();
    void goSeu();
    void goSed();

    Roller getNw() const;
    Roller getNe() const;
    Roller getSw() const;
    Roller getSe() const;

    enum Dir
    {
        nw = 0,
        ne = 1,
        sw = 2,
        se = 3
    };

private:
    std::size_t m_dimensions;

    uint64_t m_index;
    BBox m_bbox;

    std::size_t m_depth;

    void step(Dir dir);
};

} // namespace entwine

