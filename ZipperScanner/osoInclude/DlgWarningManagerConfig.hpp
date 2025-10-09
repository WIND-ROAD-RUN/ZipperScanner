#pragma once

#include"oso_core.h"
#include <string>

namespace cdm {
    class DlgWarningManagerConfig
    {
    public:
        DlgWarningManagerConfig() = default;
        ~DlgWarningManagerConfig() = default;

        DlgWarningManagerConfig(const rw::oso::ObjectStoreAssembly& assembly);
        DlgWarningManagerConfig(const DlgWarningManagerConfig& obj);

        DlgWarningManagerConfig& operator=(const DlgWarningManagerConfig& obj);
        operator rw::oso::ObjectStoreAssembly() const;
        bool operator==(const DlgWarningManagerConfig& obj) const;
        bool operator!=(const DlgWarningManagerConfig& obj) const;
    public:
        bool findIsOpen(int id);
    public:
        bool yigongweixiangjiduanlian{ false };
        bool ergongweixiangjiduanlian{ false };
        bool zmotionduanlian{ false };
        bool lalianlawan{ false };
    };

    inline DlgWarningManagerConfig::DlgWarningManagerConfig(const rw::oso::ObjectStoreAssembly& assembly)
    {
        auto isAccountAssembly = assembly.getName();
        if (isAccountAssembly != "$class$DlgWarningManagerConfig$")
        {
            throw std::runtime_error("Assembly is not $class$DlgWarningManagerConfig$");
        }
        auto yigongweixiangjiduanlianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$yigongweixiangjiduanlian$"));
        if (!yigongweixiangjiduanlianItem) {
            throw std::runtime_error("$variable$yigongweixiangjiduanlian is not found");
        }
        yigongweixiangjiduanlian = yigongweixiangjiduanlianItem->getValueAsBool();
        auto ergongweixiangjiduanlianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$ergongweixiangjiduanlian$"));
        if (!ergongweixiangjiduanlianItem) {
            throw std::runtime_error("$variable$ergongweixiangjiduanlian is not found");
        }
        ergongweixiangjiduanlian = ergongweixiangjiduanlianItem->getValueAsBool();
        auto zmotionduanlianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zmotionduanlian$"));
        if (!zmotionduanlianItem) {
            throw std::runtime_error("$variable$zmotionduanlian is not found");
        }
        zmotionduanlian = zmotionduanlianItem->getValueAsBool();
        auto lalianlawanItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$lalianlawan$"));
        if (!lalianlawanItem) {
            throw std::runtime_error("$variable$lalianlawan is not found");
        }
        lalianlawan = lalianlawanItem->getValueAsBool();
    }

    inline DlgWarningManagerConfig::DlgWarningManagerConfig(const DlgWarningManagerConfig& obj)
    {
        yigongweixiangjiduanlian = obj.yigongweixiangjiduanlian;
        ergongweixiangjiduanlian = obj.ergongweixiangjiduanlian;
        zmotionduanlian = obj.zmotionduanlian;
        lalianlawan = obj.lalianlawan;
    }

    inline DlgWarningManagerConfig& DlgWarningManagerConfig::operator=(const DlgWarningManagerConfig& obj)
    {
        if (this != &obj) {
            yigongweixiangjiduanlian = obj.yigongweixiangjiduanlian;
            ergongweixiangjiduanlian = obj.ergongweixiangjiduanlian;
            zmotionduanlian = obj.zmotionduanlian;
            lalianlawan = obj.lalianlawan;
        }
        return *this;
    }

    inline DlgWarningManagerConfig::operator rw::oso::ObjectStoreAssembly() const
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$class$DlgWarningManagerConfig$");
        auto yigongweixiangjiduanlianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        yigongweixiangjiduanlianItem->setName("$variable$yigongweixiangjiduanlian$");
        yigongweixiangjiduanlianItem->setValueFromBool(yigongweixiangjiduanlian);
        assembly.addItem(yigongweixiangjiduanlianItem);
        auto ergongweixiangjiduanlianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        ergongweixiangjiduanlianItem->setName("$variable$ergongweixiangjiduanlian$");
        ergongweixiangjiduanlianItem->setValueFromBool(ergongweixiangjiduanlian);
        assembly.addItem(ergongweixiangjiduanlianItem);
        auto zmotionduanlianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        zmotionduanlianItem->setName("$variable$zmotionduanlian$");
        zmotionduanlianItem->setValueFromBool(zmotionduanlian);
        assembly.addItem(zmotionduanlianItem);
        auto lalianlawanItem = std::make_shared<rw::oso::ObjectStoreItem>();
        lalianlawanItem->setName("$variable$lalianlawan$");
        lalianlawanItem->setValueFromBool(lalianlawan);
        assembly.addItem(lalianlawanItem);
        return assembly;
    }

    inline bool DlgWarningManagerConfig::operator==(const DlgWarningManagerConfig& obj) const
    {
        return yigongweixiangjiduanlian == obj.yigongweixiangjiduanlian && ergongweixiangjiduanlian == obj.ergongweixiangjiduanlian && zmotionduanlian == obj.zmotionduanlian && lalianlawan == obj.lalianlawan;
    }

    inline bool DlgWarningManagerConfig::operator!=(const DlgWarningManagerConfig& obj) const
    {
        return !(*this == obj);
    }

    inline bool DlgWarningManagerConfig::findIsOpen(int id)
    {
        switch (id)
        {
        case 0:
            return lalianlawan;
        case 1:
            return yigongweixiangjiduanlian;
        case 2:
            return ergongweixiangjiduanlian;
        case 3:
            return zmotionduanlian;
        }
        return true;
    }
}

