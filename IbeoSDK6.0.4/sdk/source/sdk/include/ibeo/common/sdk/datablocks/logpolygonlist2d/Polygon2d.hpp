//==============================================================================
//!\file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date May 15, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/Vector2.hpp>

#include <vector>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

template<typename T>
class Polygon2d : public std::vector<Vector2<T>>
{
public:
    using value_type = T;

public:
    Polygon2d() : std::vector<Vector2<value_type>>() {}

    Polygon2d(const Vector2<value_type>& p1) : std::vector<Vector2<value_type>>(1, p1) {}

    Polygon2d(const Vector2<value_type>& p1, const Vector2<value_type>& p2) : std::vector<Vector2<value_type>>()
    {
        this->reserve(2);
        push_back(p1);
        push_back(p2);
    }

    Polygon2d(const Vector2<value_type>& p1, const Vector2<value_type>& p2, const Vector2<value_type>& p3)
      : std::vector<Vector2<value_type>>()
    {
        this->reserve(3);
        push_back(p1);
        push_back(p2);
        push_back(p3);
    }

    Polygon2d(const Vector2<value_type>& p1,
              const Vector2<value_type>& p2,
              const Vector2<value_type>& p3,
              const Vector2<value_type>& p4)
      : std::vector<Vector2<value_type>>()
    {
        this->reserve(4);
        push_back(p1);
        push_back(p2);
        push_back(p3);
        push_back(p4);
    }

    virtual ~Polygon2d() = default;

public:
    virtual std::streamsize getSerializedSize() const
    {
        return std::streamsize(sizeof(uint16_t))
               + std::streamsize(this->size()) * ibeo::common::sdk::serializedSize(Vector2<value_type>());
    }

    virtual bool deserialize(std::istream& is)
    {
        const int64_t startPos = streamposToInt64(is.tellg());

        uint16_t sz;
        readBE(is, sz);
        this->resize(sz);

        for (Vector2<value_type>& element : *this)
        {
            readBE(is, element);
        }

        return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == getSerializedSize());
    }

    virtual bool serialize(std::ostream& os) const
    {
        const int64_t startPos = streamposToInt64(os.tellp());

        const uint16_t sz = uint16_t(this->size());
        writeBE(os, sz);

        for (const Vector2<value_type>& element : *this)
        {
            writeBE(os, element);
        }

        return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == getSerializedSize());
    }
}; // Polygon2d

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
