#pragma once

#include "BaseDepartment.hpp"

namespace warehouse
{

class OverSizeElectronicDepartment : public BaseDepartment
{
public:
    OverSizeElectronicDepartment(float maxOccupancy) :
            BaseDepartment(maxOccupancy, std::numeric_limits<float>::max(), warehouseInterface::ProductLabelFlags::esdSensitive)
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

    std::string departmentName() const override { return "OverSizeElectronicDepartment"; }
};

}  // namespace warehouse