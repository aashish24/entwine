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
#include <memory>
#include <string>
#include <vector>

#include <entwine/tree/point-info.hpp>

namespace pdal
{
    class PointView;
}

namespace Json
{
    class Value;
}

namespace entwine
{

class BBox;
class Registry;
class Schema;

class SleepyTree
{
public:
    SleepyTree(
            const std::string& path,
            const BBox& bbox,
            const Schema& schema,
            std::size_t dimensions,
            std::size_t baseDepth,
            std::size_t flatDepth,
            std::size_t diskDepth);
    SleepyTree(const std::string& path);
    ~SleepyTree();

    // Insert the points from a PointView into this index.
    void insert(const pdal::PointView& pointView, Origin origin);

    // Finalize the tree so it may be queried.  No more pipelines may be added.
    void save();

    // Awaken the tree so more pipelines may be added.  After a load(), no
    // queries should be made until save() is subsequently called.
    void load();

    // Get bounds of the quad tree.
    const BBox& getBounds() const;

    // Return all points at depth levels between [depthBegin, depthEnd).
    // A depthEnd value of zero will return all points at levels >= depthBegin.
    std::vector<std::size_t> query(
            std::size_t depthBegin,
            std::size_t depthEnd);

    // Return all points within the bounding box, searching at tree depth
    // levels from [depthBegin, depthEnd).
    // A depthEnd value of zero will return all points within the query range
    // that have a tree level >= depthBegin.
    std::vector<std::size_t> query(
            const BBox& bbox,
            std::size_t depthBegin,
            std::size_t depthEnd);

    // Get the constituent bytes of a point by its index, with bytes arranged
    // in accordance with the requested schema.
    //
    // TODO Document.
    std::vector<char> getPointData(std::size_t index, const Schema& schema);

    const Schema& schema() const;

    std::size_t numPoints() const;
    std::string path() const;

private:
    std::string metaPath() const;

    const std::string m_path;
    std::unique_ptr<BBox> m_bbox;
    std::unique_ptr<Schema> m_schema;
    std::size_t m_dimensions;
    std::size_t m_numPoints;
    std::size_t m_numTossed;

    std::unique_ptr<Registry> m_registry;

    SleepyTree(const SleepyTree&);
    SleepyTree& operator=(const SleepyTree&);
};

} // namespace entwine

