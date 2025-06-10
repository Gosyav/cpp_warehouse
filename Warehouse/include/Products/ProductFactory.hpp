#pragma once

#include <Interfaces/IProduct.hpp>
#include <memory>
#include <string>

#include "AcetoneBarrel.hpp"
#include "AstronautsIceCream.hpp"
#include "ElectronicParts.hpp"
#include "ExplosiveBarrel.hpp"
#include "GlassWare.hpp"
#include "IndustrialServerRack.hpp"
#include "TV.hpp"

namespace warehouse
{

/**
 * @brief Factory class for creating warehouse products
 *
 * Provides a centralized way to create different types of products
 * based on their class name, name, and size.
 */
class ProductFactory
{
public:
    /**
     * @brief Creates a new product instance
     *
     * @param className Type of product to create
     * @param name Name of the product
     * @param size Size of the product
     * @return Unique pointer to the created product, or nullptr if class is unknown
     */
    warehouseInterface::IProductPtr createProduct(const std::string &className, const std::string &name, const float size) const
    {
        // Map of product types to their creation functions
        if (className == "IndustrialServerRack")
        {
            return std::make_unique<IndustrialServerRack>(name, size);
        }
        else if (className == "GlassWare")
        {
            return std::make_unique<GlassWare>(name, size);
        }
        else if (className == "ExplosiveBarrel")
        {
            return std::make_unique<ExplosiveBarrel>(name, size);
        }
        else if (className == "ElectronicParts")
        {
            return std::make_unique<ElectronicParts>(name, size);
        }
        else if (className == "AstronautsIceCream")
        {
            return std::make_unique<AstronautsIceCream>(name, size);
        }
        else if (className == "AcetoneBarrel")
        {
            return std::make_unique<AcetoneBarrel>(name, size);
        }
        else if (className == "TV")
        {
            return std::make_unique<TV>(name, size);
        }

        return nullptr;
    }
};

}  // namespace warehouse