#pragma once

#include"oso_core.h"
#include <string>

namespace cdm {
    class ScoreConfig
    {
    public:
        ScoreConfig() = default;
        ~ScoreConfig() = default;

        ScoreConfig(const rw::oso::ObjectStoreAssembly& assembly);
        ScoreConfig(const ScoreConfig& obj);

        ScoreConfig& operator=(const ScoreConfig& obj);
        operator rw::oso::ObjectStoreAssembly() const;
        bool operator==(const ScoreConfig& obj) const;
        bool operator!=(const ScoreConfig& obj) const;

    public:
        bool queYa{ false };
        double queYaScore{ 0 };
        double queYaArea{ 0 };
        bool tangShang{ false };
        double tangShangScore{ 0 };
        double tangShangArea{ 0 };
        bool zangWu{ false };
        double zangWuScore{ 0 };
        double zangWuArea{ 0 };
        bool suoXiao{ false };
        double suoXiaoScore{ 0 };
        double suoXiaoArea{ 0 };
        bool huaWen{ false };
        double huaWenScore{ 0 };
        double huaWenArea{ 0 };
        bool yuan{ false };
        double yuanScore{ 0 };
        double yuanArea{ 0 };
        bool huaPo{ false };
        double huaPoScore{ 0 };
        double huaPoArea{ 0 };
        bool duanXian{ false };
        double duanXianScore{ 0 };
        double duanXianArea{ 0 };
        bool extra5{ false };
        double extra5Score{ 0 };
        double extra5Area{ 0 };
        bool extra6{ false };
        double extra6Score{ 0 };
        double extra6Area{ 0 };
        bool extra7{ false };
        double extra7Score{ 0 };
        double extra7Area{ 0 };
        bool extra8{ false };
        double extra8Score{ 0 };
        double extra8Area{ 0 };
    };

    inline ScoreConfig::ScoreConfig(const rw::oso::ObjectStoreAssembly& assembly)
    {
        auto isAccountAssembly = assembly.getName();
        if (isAccountAssembly != "$class$ScoreConfig$")
        {
            throw std::runtime_error("Assembly is not $class$ScoreConfig$");
        }
        auto queYaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$queYa$"));
        if (!queYaItem) {
            throw std::runtime_error("$variable$queYa is not found");
        }
        queYa = queYaItem->getValueAsBool();
        auto queYaScoreItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$queYaScore$"));
        if (!queYaScoreItem) {
            throw std::runtime_error("$variable$queYaScore is not found");
        }
        queYaScore = queYaScoreItem->getValueAsDouble();
        auto queYaAreaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$queYaArea$"));
        if (!queYaAreaItem) {
            throw std::runtime_error("$variable$queYaArea is not found");
        }
        queYaArea = queYaAreaItem->getValueAsDouble();
        auto tangShangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$tangShang$"));
        if (!tangShangItem) {
            throw std::runtime_error("$variable$tangShang is not found");
        }
        tangShang = tangShangItem->getValueAsBool();
        auto tangShangScoreItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$tangShangScore$"));
        if (!tangShangScoreItem) {
            throw std::runtime_error("$variable$tangShangScore is not found");
        }
        tangShangScore = tangShangScoreItem->getValueAsDouble();
        auto tangShangAreaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$tangShangArea$"));
        if (!tangShangAreaItem) {
            throw std::runtime_error("$variable$tangShangArea is not found");
        }
        tangShangArea = tangShangAreaItem->getValueAsDouble();
        auto zangWuItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zangWu$"));
        if (!zangWuItem) {
            throw std::runtime_error("$variable$zangWu is not found");
        }
        zangWu = zangWuItem->getValueAsBool();
        auto zangWuScoreItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zangWuScore$"));
        if (!zangWuScoreItem) {
            throw std::runtime_error("$variable$zangWuScore is not found");
        }
        zangWuScore = zangWuScoreItem->getValueAsDouble();
        auto zangWuAreaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zangWuArea$"));
        if (!zangWuAreaItem) {
            throw std::runtime_error("$variable$zangWuArea is not found");
        }
        zangWuArea = zangWuAreaItem->getValueAsDouble();
        auto suoXiaoItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$suoXiao$"));
        if (!suoXiaoItem) {
            throw std::runtime_error("$variable$suoXiao is not found");
        }
        suoXiao = suoXiaoItem->getValueAsBool();
        auto suoXiaoScoreItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$suoXiaoScore$"));
        if (!suoXiaoScoreItem) {
            throw std::runtime_error("$variable$suoXiaoScore is not found");
        }
        suoXiaoScore = suoXiaoScoreItem->getValueAsDouble();
        auto suoXiaoAreaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$suoXiaoArea$"));
        if (!suoXiaoAreaItem) {
            throw std::runtime_error("$variable$suoXiaoArea is not found");
        }
        suoXiaoArea = suoXiaoAreaItem->getValueAsDouble();
        auto huaWenItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$huaWen$"));
        if (!huaWenItem) {
            throw std::runtime_error("$variable$huaWen is not found");
        }
        huaWen = huaWenItem->getValueAsBool();
        auto huaWenScoreItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$huaWenScore$"));
        if (!huaWenScoreItem) {
            throw std::runtime_error("$variable$huaWenScore is not found");
        }
        huaWenScore = huaWenScoreItem->getValueAsDouble();
        auto huaWenAreaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$huaWenArea$"));
        if (!huaWenAreaItem) {
            throw std::runtime_error("$variable$huaWenArea is not found");
        }
        huaWenArea = huaWenAreaItem->getValueAsDouble();
        auto yuanItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$yuan$"));
        if (!yuanItem) {
            throw std::runtime_error("$variable$yuan is not found");
        }
        yuan = yuanItem->getValueAsBool();
        auto yuanScoreItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$yuanScore$"));
        if (!yuanScoreItem) {
            throw std::runtime_error("$variable$yuanScore is not found");
        }
        yuanScore = yuanScoreItem->getValueAsDouble();
        auto yuanAreaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$yuanArea$"));
        if (!yuanAreaItem) {
            throw std::runtime_error("$variable$yuanArea is not found");
        }
        yuanArea = yuanAreaItem->getValueAsDouble();
        auto huaPoItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$huaPo$"));
        if (!huaPoItem) {
            throw std::runtime_error("$variable$huaPo is not found");
        }
        huaPo = huaPoItem->getValueAsBool();
        auto huaPoScoreItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$huaPoScore$"));
        if (!huaPoScoreItem) {
            throw std::runtime_error("$variable$huaPoScore is not found");
        }
        huaPoScore = huaPoScoreItem->getValueAsDouble();
        auto huaPoAreaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$huaPoArea$"));
        if (!huaPoAreaItem) {
            throw std::runtime_error("$variable$huaPoArea is not found");
        }
        huaPoArea = huaPoAreaItem->getValueAsDouble();
        auto duanXianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$duanXian$"));
        if (!duanXianItem) {
            throw std::runtime_error("$variable$duanXian is not found");
        }
        duanXian = duanXianItem->getValueAsBool();
        auto duanXianScoreItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$duanXianScore$"));
        if (!duanXianScoreItem) {
            throw std::runtime_error("$variable$duanXianScore is not found");
        }
        duanXianScore = duanXianScoreItem->getValueAsDouble();
        auto duanXianAreaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$duanXianArea$"));
        if (!duanXianAreaItem) {
            throw std::runtime_error("$variable$duanXianArea is not found");
        }
        duanXianArea = duanXianAreaItem->getValueAsDouble();
        auto extra5Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra5$"));
        if (!extra5Item) {
            throw std::runtime_error("$variable$extra5 is not found");
        }
        extra5 = extra5Item->getValueAsBool();
        auto extra5ScoreItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra5Score$"));
        if (!extra5ScoreItem) {
            throw std::runtime_error("$variable$extra5Score is not found");
        }
        extra5Score = extra5ScoreItem->getValueAsDouble();
        auto extra5AreaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra5Area$"));
        if (!extra5AreaItem) {
            throw std::runtime_error("$variable$extra5Area is not found");
        }
        extra5Area = extra5AreaItem->getValueAsDouble();
        auto extra6Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra6$"));
        if (!extra6Item) {
            throw std::runtime_error("$variable$extra6 is not found");
        }
        extra6 = extra6Item->getValueAsBool();
        auto extra6ScoreItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra6Score$"));
        if (!extra6ScoreItem) {
            throw std::runtime_error("$variable$extra6Score is not found");
        }
        extra6Score = extra6ScoreItem->getValueAsDouble();
        auto extra6AreaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra6Area$"));
        if (!extra6AreaItem) {
            throw std::runtime_error("$variable$extra6Area is not found");
        }
        extra6Area = extra6AreaItem->getValueAsDouble();
        auto extra7Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra7$"));
        if (!extra7Item) {
            throw std::runtime_error("$variable$extra7 is not found");
        }
        extra7 = extra7Item->getValueAsBool();
        auto extra7ScoreItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra7Score$"));
        if (!extra7ScoreItem) {
            throw std::runtime_error("$variable$extra7Score is not found");
        }
        extra7Score = extra7ScoreItem->getValueAsDouble();
        auto extra7AreaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra7Area$"));
        if (!extra7AreaItem) {
            throw std::runtime_error("$variable$extra7Area is not found");
        }
        extra7Area = extra7AreaItem->getValueAsDouble();
        auto extra8Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra8$"));
        if (!extra8Item) {
            throw std::runtime_error("$variable$extra8 is not found");
        }
        extra8 = extra8Item->getValueAsBool();
        auto extra8ScoreItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra8Score$"));
        if (!extra8ScoreItem) {
            throw std::runtime_error("$variable$extra8Score is not found");
        }
        extra8Score = extra8ScoreItem->getValueAsDouble();
        auto extra8AreaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra8Area$"));
        if (!extra8AreaItem) {
            throw std::runtime_error("$variable$extra8Area is not found");
        }
        extra8Area = extra8AreaItem->getValueAsDouble();
    }

    inline ScoreConfig::ScoreConfig(const ScoreConfig& obj)
    {
        queYa = obj.queYa;
        queYaScore = obj.queYaScore;
        queYaArea = obj.queYaArea;
        tangShang = obj.tangShang;
        tangShangScore = obj.tangShangScore;
        tangShangArea = obj.tangShangArea;
        zangWu = obj.zangWu;
        zangWuScore = obj.zangWuScore;
        zangWuArea = obj.zangWuArea;
        suoXiao = obj.suoXiao;
        suoXiaoScore = obj.suoXiaoScore;
        suoXiaoArea = obj.suoXiaoArea;
        huaWen = obj.huaWen;
        huaWenScore = obj.huaWenScore;
        huaWenArea = obj.huaWenArea;
        yuan = obj.yuan;
        yuanScore = obj.yuanScore;
        yuanArea = obj.yuanArea;
        huaPo = obj.huaPo;
        huaPoScore = obj.huaPoScore;
        huaPoArea = obj.huaPoArea;
        duanXian = obj.duanXian;
        duanXianScore = obj.duanXianScore;
        duanXianArea = obj.duanXianArea;
        extra5 = obj.extra5;
        extra5Score = obj.extra5Score;
        extra5Area = obj.extra5Area;
        extra6 = obj.extra6;
        extra6Score = obj.extra6Score;
        extra6Area = obj.extra6Area;
        extra7 = obj.extra7;
        extra7Score = obj.extra7Score;
        extra7Area = obj.extra7Area;
        extra8 = obj.extra8;
        extra8Score = obj.extra8Score;
        extra8Area = obj.extra8Area;
    }

    inline ScoreConfig& ScoreConfig::operator=(const ScoreConfig& obj)
    {
        if (this != &obj) {
            queYa = obj.queYa;
            queYaScore = obj.queYaScore;
            queYaArea = obj.queYaArea;
            tangShang = obj.tangShang;
            tangShangScore = obj.tangShangScore;
            tangShangArea = obj.tangShangArea;
            zangWu = obj.zangWu;
            zangWuScore = obj.zangWuScore;
            zangWuArea = obj.zangWuArea;
            suoXiao = obj.suoXiao;
            suoXiaoScore = obj.suoXiaoScore;
            suoXiaoArea = obj.suoXiaoArea;
            huaWen = obj.huaWen;
            huaWenScore = obj.huaWenScore;
            huaWenArea = obj.huaWenArea;
            yuan = obj.yuan;
            yuanScore = obj.yuanScore;
            yuanArea = obj.yuanArea;
            huaPo = obj.huaPo;
            huaPoScore = obj.huaPoScore;
            huaPoArea = obj.huaPoArea;
            duanXian = obj.duanXian;
            duanXianScore = obj.duanXianScore;
            duanXianArea = obj.duanXianArea;
            extra5 = obj.extra5;
            extra5Score = obj.extra5Score;
            extra5Area = obj.extra5Area;
            extra6 = obj.extra6;
            extra6Score = obj.extra6Score;
            extra6Area = obj.extra6Area;
            extra7 = obj.extra7;
            extra7Score = obj.extra7Score;
            extra7Area = obj.extra7Area;
            extra8 = obj.extra8;
            extra8Score = obj.extra8Score;
            extra8Area = obj.extra8Area;
        }
        return *this;
    }

    inline ScoreConfig::operator rw::oso::ObjectStoreAssembly() const
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$class$ScoreConfig$");
        auto queYaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        queYaItem->setName("$variable$queYa$");
        queYaItem->setValueFromBool(queYa);
        assembly.addItem(queYaItem);
        auto queYaScoreItem = std::make_shared<rw::oso::ObjectStoreItem>();
        queYaScoreItem->setName("$variable$queYaScore$");
        queYaScoreItem->setValueFromDouble(queYaScore);
        assembly.addItem(queYaScoreItem);
        auto queYaAreaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        queYaAreaItem->setName("$variable$queYaArea$");
        queYaAreaItem->setValueFromDouble(queYaArea);
        assembly.addItem(queYaAreaItem);
        auto tangShangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        tangShangItem->setName("$variable$tangShang$");
        tangShangItem->setValueFromBool(tangShang);
        assembly.addItem(tangShangItem);
        auto tangShangScoreItem = std::make_shared<rw::oso::ObjectStoreItem>();
        tangShangScoreItem->setName("$variable$tangShangScore$");
        tangShangScoreItem->setValueFromDouble(tangShangScore);
        assembly.addItem(tangShangScoreItem);
        auto tangShangAreaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        tangShangAreaItem->setName("$variable$tangShangArea$");
        tangShangAreaItem->setValueFromDouble(tangShangArea);
        assembly.addItem(tangShangAreaItem);
        auto zangWuItem = std::make_shared<rw::oso::ObjectStoreItem>();
        zangWuItem->setName("$variable$zangWu$");
        zangWuItem->setValueFromBool(zangWu);
        assembly.addItem(zangWuItem);
        auto zangWuScoreItem = std::make_shared<rw::oso::ObjectStoreItem>();
        zangWuScoreItem->setName("$variable$zangWuScore$");
        zangWuScoreItem->setValueFromDouble(zangWuScore);
        assembly.addItem(zangWuScoreItem);
        auto zangWuAreaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        zangWuAreaItem->setName("$variable$zangWuArea$");
        zangWuAreaItem->setValueFromDouble(zangWuArea);
        assembly.addItem(zangWuAreaItem);
        auto suoXiaoItem = std::make_shared<rw::oso::ObjectStoreItem>();
        suoXiaoItem->setName("$variable$suoXiao$");
        suoXiaoItem->setValueFromBool(suoXiao);
        assembly.addItem(suoXiaoItem);
        auto suoXiaoScoreItem = std::make_shared<rw::oso::ObjectStoreItem>();
        suoXiaoScoreItem->setName("$variable$suoXiaoScore$");
        suoXiaoScoreItem->setValueFromDouble(suoXiaoScore);
        assembly.addItem(suoXiaoScoreItem);
        auto suoXiaoAreaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        suoXiaoAreaItem->setName("$variable$suoXiaoArea$");
        suoXiaoAreaItem->setValueFromDouble(suoXiaoArea);
        assembly.addItem(suoXiaoAreaItem);
        auto huaWenItem = std::make_shared<rw::oso::ObjectStoreItem>();
        huaWenItem->setName("$variable$huaWen$");
        huaWenItem->setValueFromBool(huaWen);
        assembly.addItem(huaWenItem);
        auto huaWenScoreItem = std::make_shared<rw::oso::ObjectStoreItem>();
        huaWenScoreItem->setName("$variable$huaWenScore$");
        huaWenScoreItem->setValueFromDouble(huaWenScore);
        assembly.addItem(huaWenScoreItem);
        auto huaWenAreaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        huaWenAreaItem->setName("$variable$huaWenArea$");
        huaWenAreaItem->setValueFromDouble(huaWenArea);
        assembly.addItem(huaWenAreaItem);
        auto yuanItem = std::make_shared<rw::oso::ObjectStoreItem>();
        yuanItem->setName("$variable$yuan$");
        yuanItem->setValueFromBool(yuan);
        assembly.addItem(yuanItem);
        auto yuanScoreItem = std::make_shared<rw::oso::ObjectStoreItem>();
        yuanScoreItem->setName("$variable$yuanScore$");
        yuanScoreItem->setValueFromDouble(yuanScore);
        assembly.addItem(yuanScoreItem);
        auto yuanAreaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        yuanAreaItem->setName("$variable$yuanArea$");
        yuanAreaItem->setValueFromDouble(yuanArea);
        assembly.addItem(yuanAreaItem);
        auto huaPoItem = std::make_shared<rw::oso::ObjectStoreItem>();
        huaPoItem->setName("$variable$huaPo$");
        huaPoItem->setValueFromBool(huaPo);
        assembly.addItem(huaPoItem);
        auto huaPoScoreItem = std::make_shared<rw::oso::ObjectStoreItem>();
        huaPoScoreItem->setName("$variable$huaPoScore$");
        huaPoScoreItem->setValueFromDouble(huaPoScore);
        assembly.addItem(huaPoScoreItem);
        auto huaPoAreaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        huaPoAreaItem->setName("$variable$huaPoArea$");
        huaPoAreaItem->setValueFromDouble(huaPoArea);
        assembly.addItem(huaPoAreaItem);
        auto duanXianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        duanXianItem->setName("$variable$duanXian$");
        duanXianItem->setValueFromBool(duanXian);
        assembly.addItem(duanXianItem);
        auto duanXianScoreItem = std::make_shared<rw::oso::ObjectStoreItem>();
        duanXianScoreItem->setName("$variable$duanXianScore$");
        duanXianScoreItem->setValueFromDouble(duanXianScore);
        assembly.addItem(duanXianScoreItem);
        auto duanXianAreaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        duanXianAreaItem->setName("$variable$duanXianArea$");
        duanXianAreaItem->setValueFromDouble(duanXianArea);
        assembly.addItem(duanXianAreaItem);
        auto extra5Item = std::make_shared<rw::oso::ObjectStoreItem>();
        extra5Item->setName("$variable$extra5$");
        extra5Item->setValueFromBool(extra5);
        assembly.addItem(extra5Item);
        auto extra5ScoreItem = std::make_shared<rw::oso::ObjectStoreItem>();
        extra5ScoreItem->setName("$variable$extra5Score$");
        extra5ScoreItem->setValueFromDouble(extra5Score);
        assembly.addItem(extra5ScoreItem);
        auto extra5AreaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        extra5AreaItem->setName("$variable$extra5Area$");
        extra5AreaItem->setValueFromDouble(extra5Area);
        assembly.addItem(extra5AreaItem);
        auto extra6Item = std::make_shared<rw::oso::ObjectStoreItem>();
        extra6Item->setName("$variable$extra6$");
        extra6Item->setValueFromBool(extra6);
        assembly.addItem(extra6Item);
        auto extra6ScoreItem = std::make_shared<rw::oso::ObjectStoreItem>();
        extra6ScoreItem->setName("$variable$extra6Score$");
        extra6ScoreItem->setValueFromDouble(extra6Score);
        assembly.addItem(extra6ScoreItem);
        auto extra6AreaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        extra6AreaItem->setName("$variable$extra6Area$");
        extra6AreaItem->setValueFromDouble(extra6Area);
        assembly.addItem(extra6AreaItem);
        auto extra7Item = std::make_shared<rw::oso::ObjectStoreItem>();
        extra7Item->setName("$variable$extra7$");
        extra7Item->setValueFromBool(extra7);
        assembly.addItem(extra7Item);
        auto extra7ScoreItem = std::make_shared<rw::oso::ObjectStoreItem>();
        extra7ScoreItem->setName("$variable$extra7Score$");
        extra7ScoreItem->setValueFromDouble(extra7Score);
        assembly.addItem(extra7ScoreItem);
        auto extra7AreaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        extra7AreaItem->setName("$variable$extra7Area$");
        extra7AreaItem->setValueFromDouble(extra7Area);
        assembly.addItem(extra7AreaItem);
        auto extra8Item = std::make_shared<rw::oso::ObjectStoreItem>();
        extra8Item->setName("$variable$extra8$");
        extra8Item->setValueFromBool(extra8);
        assembly.addItem(extra8Item);
        auto extra8ScoreItem = std::make_shared<rw::oso::ObjectStoreItem>();
        extra8ScoreItem->setName("$variable$extra8Score$");
        extra8ScoreItem->setValueFromDouble(extra8Score);
        assembly.addItem(extra8ScoreItem);
        auto extra8AreaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        extra8AreaItem->setName("$variable$extra8Area$");
        extra8AreaItem->setValueFromDouble(extra8Area);
        assembly.addItem(extra8AreaItem);
        return assembly;
    }

    inline bool ScoreConfig::operator==(const ScoreConfig& obj) const
    {
        return queYa == obj.queYa && queYaScore == obj.queYaScore && queYaArea == obj.queYaArea && tangShang == obj.tangShang && tangShangScore == obj.tangShangScore && tangShangArea == obj.tangShangArea && zangWu == obj.zangWu && zangWuScore == obj.zangWuScore && zangWuArea == obj.zangWuArea && suoXiao == obj.suoXiao && suoXiaoScore == obj.suoXiaoScore && suoXiaoArea == obj.suoXiaoArea && huaWen == obj.huaWen && huaWenScore == obj.huaWenScore && huaWenArea == obj.huaWenArea && yuan == obj.yuan && yuanScore == obj.yuanScore && yuanArea == obj.yuanArea && huaPo == obj.huaPo && huaPoScore == obj.huaPoScore && huaPoArea == obj.huaPoArea && duanXian == obj.duanXian && duanXianScore == obj.duanXianScore && duanXianArea == obj.duanXianArea && extra5 == obj.extra5 && extra5Score == obj.extra5Score && extra5Area == obj.extra5Area && extra6 == obj.extra6 && extra6Score == obj.extra6Score && extra6Area == obj.extra6Area && extra7 == obj.extra7 && extra7Score == obj.extra7Score && extra7Area == obj.extra7Area && extra8 == obj.extra8 && extra8Score == obj.extra8Score && extra8Area == obj.extra8Area;
    }

    inline bool ScoreConfig::operator!=(const ScoreConfig& obj) const
    {
        return !(*this == obj);
    }

}

