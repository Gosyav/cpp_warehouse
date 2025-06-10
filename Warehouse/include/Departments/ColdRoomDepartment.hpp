#pragma once

#include "BaseDepartment.hpp"
#include "Products/BaseProduct.hpp"

namespace warehouse
{

/**
 * @brief Department for storing frozen products
 *
 * This department is designed to store products that require
 * frozen storage conditions. It accepts products with the
 * keepFrozen flag and has no size restrictions.
 */
class ColdRoomDepartment : public BaseDepartment
{
public:
    /**
     * @brief Construct a new Cold Room Department
     * @param maxOccupancy Maximum allowed occupancy
     */
    ColdRoomDepartment(float maxOccupancy) :
            BaseDepartment(maxOccupancy, std::numeric_limits<float>::max(), warehouseInterface::ProductLabelFlags::keepFrozen)
    {}

    /**
     * @brief Add a product to the department
     *
     * The product will be added if it has the keepFrozen flag
     * and there is enough space in the department.
     *
     * @param item Product to add
     * @return true if product was added, false otherwise
     */
    bool addItem(warehouseInterface::IProductPtr item) override
    {
        if (!canAddItem(item))
            return false;
        items_.push_back(std::move(item));
        occupancy_ += item->itemSize();
        return true;
    }

    /**
     * @brief Retrieve a product from the department
     *
     * Searches for a product matching the provided description.
     * The product is removed from the department if found.
     *
     * @param description JSON description of the product to find
     * @return Pointer to the found product, or nullptr if not found
     */
    warehouseInterface::IProductPtr getItem(const warehouseInterface::ProductDescriptionJson &description) override
    {
        picojson::value val;
        picojson::parse(val, description);
        const auto &obj = val.get<picojson::object>();

        auto it = std::find_if(items_.begin(), items_.end(), [&obj](const auto &item) {
            if (!item)
                return false;
            if (obj.count("class"))
            {
                auto *base = dynamic_cast<const BaseProduct *>(item.get());
                if (!base || obj.at("class").get<std::string>() != base->getClassName())
                    return false;
            }
            if (obj.count("name") && obj.at("name").get<std::string>() != item->name())
                return false;
            return true;
        });

        if (it == items_.end())
            return nullptr;

        auto result = std::move(*it);
        items_.erase(it);
        occupancy_ -= result->itemSize();
        return result;
    }

    std::string departmentName() const override { return "ColdRoomDepartment"; }
};

}  // namespace warehouse