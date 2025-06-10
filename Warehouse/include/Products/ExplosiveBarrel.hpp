#pragma once

#include <PicoJson/picojson.h>

#include <Interfaces/IProduct.hpp>
#include <Interfaces/ProductFlags.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <Products/BaseProduct.hpp>

using namespace magic_enum::bitwise_operators;

namespace warehouse
{
class ExplosiveBarrel : public BaseProduct
{
public:
    ExplosiveBarrel(const std::string &name, float size) :
            BaseProduct(
                    name,
                    size,
                    warehouseInterface::ProductLabelFlags::explosives | warehouseInterface::ProductLabelFlags::handleWithCare)
    {}

    std::string getClassName() const override { return "ExplosiveBarrel"; }
};
}  // namespace warehouse