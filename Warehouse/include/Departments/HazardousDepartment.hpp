#pragma once

#include <PicoJson/picojson.h>

#include <Interfaces/IDepartment.hpp>
#include <Interfaces/ProductFlags.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <memory>
#include <string>
#include <vector>

#include "BaseDepartment.hpp"

using namespace magic_enum::bitwise_operators;

namespace warehouse
{

class HazardousDepartment : public BaseDepartment
{
public:
    HazardousDepartment(float maxOccupancy) :
            BaseDepartment(
                    maxOccupancy,
                    std::numeric_limits<float>::max(),
                    warehouseInterface::ProductLabelFlags::fireHazardous | warehouseInterface::ProductLabelFlags::explosives)
    {}

    bool addItem(warehouseInterface::IProductPtr item) override
    {
        if (!canAddItem(item))
            return false;
        items_.push_back(std::move(item));
        occupancy_ += item->itemSize();
        return true;
    }

    warehouseInterface::IProductPtr getItem(const warehouseInterface::ProductDescriptionJson &description) override
    {
        if (items_.empty())
            return nullptr;

        picojson::value val;
        picojson::parse(val, description);
        const auto &obj = val.get<picojson::object>();

        // FIFO - check only the first element
        auto &front = items_.front();
        if (!front)
        {
            items_.pop_front();
            return nullptr;
        }

        bool matches = true;
        if (obj.count("class"))
        {
            auto *base = dynamic_cast<const BaseProduct *>(front.get());
            if (!base || obj.at("class").get<std::string>() != base->getClassName())
                matches = false;
        }
        if (obj.count("name"))
        {
            matches &= (obj.at("name").get<std::string>() == front->name());
        }

        if (!matches)
            return nullptr;

        auto result = std::move(front);
        items_.pop_front();
        occupancy_ -= result->itemSize();
        return result;
    }

    std::string departmentName() const override { return "HazardousDepartment"; }
};

}  // namespace warehouse