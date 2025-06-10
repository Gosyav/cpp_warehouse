#pragma once

#include <PicoJson/picojson.h>

#include <Interfaces/IDepartment.hpp>
#include <deque>
#include <memory>
#include <string>

namespace warehouse
{

/**
 * @brief Base class for all warehouse departments
 *
 * Provides common functionality for all departments including:
 * - Product storage and retrieval
 * - Occupancy management
 * - Size restrictions
 * - Flag-based product filtering
 * - JSON serialization
 */
class BaseDepartment : public warehouseInterface::IDepartment
{
protected:
    std::deque<warehouseInterface::IProductPtr> items_;     ///< Stored products
    float occupancy_;                                       ///< Current occupancy
    float maxOccupancy_;                                    ///< Maximum allowed occupancy
    float maxItemSize_;                                     ///< Maximum allowed item size
    warehouseInterface::ProductLabelFlags supportedFlags_;  ///< Supported product flags

public:
    /**
     * @brief Construct a new Base Department
     * @param maxOccupancy Maximum allowed occupancy
     * @param maxItemSize Maximum allowed item size
     * @param supportedFlags Supported product flags
     */
    BaseDepartment(float maxOccupancy, float maxItemSize, warehouseInterface::ProductLabelFlags supportedFlags) :
            items_(), occupancy_(0.0f), maxOccupancy_(maxOccupancy), maxItemSize_(maxItemSize), supportedFlags_(supportedFlags)
    {}

    float getOccupancy() const override { return occupancy_; }
    float getMaxOccupancy() const override { return maxOccupancy_; }
    float getMaxItemSize() const override { return maxItemSize_; }
    warehouseInterface::ProductLabelFlags getSupportedFlags() const override { return supportedFlags_; }

    picojson::object asJson() const override
    {
        picojson::object obj;
        obj["class"] = picojson::value(departmentName());
        obj["maxOccupancy"] = picojson::value(maxOccupancy_);
        obj["occupancy"] = picojson::value(occupancy_);
        obj["items"] = picojson::value(serializedItems());
        return obj;
    }

    warehouseInterface::DepartmentStateJson serialize() const override { return picojson::value(asJson()).serialize(); }

    picojson::array serializedItems() const override
    {
        picojson::array items;
        for (const auto &item : items_)
        {
            if (item)
            {
                picojson::value val;
                picojson::parse(val, item->serialize());
                items.push_back(val);
            }
        }
        return items;
    }

protected:
    /**
     * @brief Check if a product can be added to the department
     *
     * Verifies that:
     * - Product pointer is valid
     * - Product size is within limits
     * - Department has enough space
     * - Product flags are supported
     *
     * @param item Product to check
     * @return true if product can be added, false otherwise
     */
    bool canAddItem(const warehouseInterface::IProductPtr &item) const
    {
        if (!item)
            return false;
        if (item->itemSize() > maxItemSize_)
            return false;
        if (occupancy_ + item->itemSize() > maxOccupancy_)
            return false;
        if ((static_cast<int>(item->itemFlags()) & static_cast<int>(supportedFlags_)) != static_cast<int>(item->itemFlags()))
            return false;
        return true;
    }
};

}  // namespace warehouse