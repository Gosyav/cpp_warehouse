#pragma once

#include <PicoJson/picojson.h>

#include <Interfaces/IProduct.hpp>
#include <Interfaces/ProductFlags.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <Products/BaseProduct.hpp>

using namespace magic_enum::bitwise_operators;

namespace warehouse
{
class IndustrialServerRack : public BaseProduct
{
public:
    IndustrialServerRack(const std::string &name, float size) :
            BaseProduct(name, size, warehouseInterface::ProductLabelFlags::esdSensitive)
    {}

    std::string getClassName() const override { return "IndustrialServerRack"; }
};
}  // namespace warehouse