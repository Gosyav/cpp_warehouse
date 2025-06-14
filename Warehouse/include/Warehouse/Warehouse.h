#pragma once
#include <PicoJson/picojson.h>

#include <Interfaces/IWarehouse.hpp>
#include <memory>
#include <string>
#include <vector>

#include "Departments/ColdRoomDepartment.hpp"
#include "Departments/HazardousDepartment.hpp"
#include "Departments/OverSizeElectronicDepartment.hpp"
#include "Departments/SmallElectronicDepartment.hpp"
#include "Departments/SpecialDepartment.hpp"
#include "Factory/ProductFactory.hpp"

namespace warehouse
{
class Warehouse : public warehouseInterface::IWarehouse
{
public:
    Warehouse() : departments_() {}

    void addDepartment(warehouseInterface::IDepartmentPtr department) override
    {
        if (department)
        {
            departments_.push_back(std::move(department));
        }
    }

    warehouseInterface::DeliveryReportJson newDelivery(std::vector<warehouseInterface::IProductPtr> products) override
    {
        picojson::array report;

        for (auto &product : products)
        {
            if (!product)
                continue;

            picojson::object delivery;
            delivery["productName"] = picojson::value(product->name());

            bool delivered = false;
            for (const auto &department : departments_)
            {
                if (department->addItem(std::move(product)))
                {
                    delivery["status"] = picojson::value("Success");
                    delivery["assignedDepartment"] = picojson::value(department->departmentName());
                    delivery["errorLog"] = picojson::value("");
                    delivered = true;
                    break;
                }
            }

            if (!delivered)
            {
                delivery["status"] = picojson::value("Fail");
                delivery["assignedDepartment"] = picojson::value("None");
                delivery["errorLog"] = picojson::value("Warehouse cannot store this product. Lack of space in departments.");
            }

            report.push_back(picojson::value(delivery));
        }

        picojson::object result;
        result["deliveryReport"] = picojson::value(report);
        return picojson::value(result).serialize();
    }

    warehouseInterface::Order newOrder(const warehouseInterface::OrderJson &orderJson) override
    {
        warehouseInterface::Order order{std::vector<warehouseInterface::IProductPtr>{}, orderJson};

        picojson::value val;
        picojson::parse(val, orderJson);
        const auto &obj = val.get<picojson::object>();
        const auto &orderArray = obj.at("order").get<picojson::array>();

        for (const auto &item : orderArray)
        {
            const auto &itemObj = item.get<picojson::object>();
            std::string itemJson = picojson::value(itemObj).serialize();

            for (const auto &department : departments_)
            {
                auto product = department->getItem(itemJson);
                if (product)
                {
                    order.products.push_back(std::move(product));
                    break;
                }
            }
        }

        return order;
    }

    warehouseInterface::OccupancyReportJson getOccupancyReport() const override
    {
        picojson::array departmentsOccupancy;

        for (const auto &department : departments_)
        {
            picojson::object dept;
            dept["departmentName"] = picojson::value(department->departmentName());
            dept["maxOccupancy"] = picojson::value(department->getMaxOccupancy());
            dept["occupancy"] = picojson::value(department->getOccupancy());
            departmentsOccupancy.push_back(picojson::value(dept));
        }

        picojson::object result;
        result["departmentsOccupancy"] = picojson::value(departmentsOccupancy);
        return picojson::value(result).serialize();
    }

    warehouseInterface::WarehouseStateJson saveWarehouseState() const override
    {
        picojson::array departments;

        for (const auto &department : departments_)
        {
            picojson::value val;
            picojson::parse(val, department->serialize());
            departments.push_back(val);
        }

        picojson::object result;
        result["warehouseState"] = picojson::value(departments);
        return picojson::value(result).serialize();
    }

    bool loadWarehouseState(const warehouseInterface::WarehouseStateJson &stateJson) override
    {
        picojson::value val;
        picojson::parse(val, stateJson);

        if (!val.is<picojson::object>())
            return false;
        const auto &obj = val.get<picojson::object>();

        if (!obj.count("warehouseState"))
            return false;
        const auto &departments = obj.at("warehouseState").get<picojson::array>();

        departments_.clear();
        for (const auto &dept : departments)
        {
            if (!dept.is<picojson::object>())
                return false;
            const auto &deptObj = dept.get<picojson::object>();

            if (!deptObj.count("class"))
                return false;
            const std::string &className = deptObj.at("class").get<std::string>();

            if (!deptObj.count("maxOccupancy"))
                return false;
            float maxOccupancy = static_cast<float>(deptObj.at("maxOccupancy").get<double>());

            // Create department of required type
            if (className == "ColdRoomDepartment")
            {
                addDepartment(std::make_unique<ColdRoomDepartment>(maxOccupancy));
            }
            else if (className == "SmallElectronicDepartment")
            {
                addDepartment(std::make_unique<SmallElectronicDepartment>(maxOccupancy));
            }
            else if (className == "OverSizeElectronicDepartment")
            {
                addDepartment(std::make_unique<OverSizeElectronicDepartment>(maxOccupancy));
            }
            else if (className == "HazardousDepartment")
            {
                addDepartment(std::make_unique<HazardousDepartment>(maxOccupancy));
            }
            else if (className == "SpecialDepartment")
            {
                addDepartment(std::make_unique<SpecialDepartment>(maxOccupancy));
            }
            else
            {
                return false;
            }

            // Load products into department
            if (deptObj.count("items"))
            {
                const auto &items = deptObj.at("items").get<picojson::array>();
                for (const auto &item : items)
                {
                    std::string itemJson = picojson::value(item).serialize();
                    auto product = ProductFactory().createProduct(
                            item.get<picojson::object>().at("class").get<std::string>(),
                            item.get<picojson::object>().at("name").get<std::string>(),
                            static_cast<float>(item.get<picojson::object>().at("size").get<double>()));
                    if (product)
                    {
                        departments_.back()->addItem(std::move(product));
                    }
                }
            }
        }

        return true;
    }

private:
    std::vector<warehouseInterface::IDepartmentPtr> departments_;
};

}  // namespace warehouse