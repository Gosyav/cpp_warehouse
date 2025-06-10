#pragma once

#include <PicoJson/picojson.h>

#include <Interfaces/IProduct.hpp>
#include <Interfaces/ProductFlags.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <Products/BaseProduct.hpp>

using namespace magic_enum::bitwise_operators;

namespace warehouse
{
class GlassWare : public BaseProduct
{
public:
    GlassWare(const std::string &name, float size) :
            BaseProduct(name,
                        size,
                        warehouseInterface::ProductLabelFlags::fragile | warehouseInterface::ProductLabelFlags::upWard)
    {}

    std::string getClassName() const override { return "GlassWare"; }
};
}  // namespace warehouse