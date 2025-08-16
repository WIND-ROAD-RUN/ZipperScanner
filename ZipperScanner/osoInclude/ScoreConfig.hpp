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
        bool extra1{ false };
        double extra1Score{ 0 };
        double extra1Area{ 0 };
        bool extra2{ false };
        double extra2Score{ 0 };
        double extra2Area{ 0 };
        bool extra3{ false };
        double extra3Score{ 0 };
        double extra3Area{ 0 };
        bool extra4{ false };
        double extra4Score{ 0 };
        double extra4Area{ 0 };
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
        auto extra1Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra1$"));
        if (!extra1Item) {
            throw std::runtime_error("$variable$extra1 is not found");
        }
        extra1 = extra1Item->getValueAsBool();
        auto extra1ScoreItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra1Score$"));
        if (!extra1ScoreItem) {
            throw std::runtime_error("$variable$extra1Score is not found");
        }
        extra1Score = extra1ScoreItem->getValueAsDouble();
        auto extra1AreaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra1Area$"));
        if (!extra1AreaItem) {
            throw std::runtime_error("$variable$extra1Area is not found");
        }
        extra1Area = extra1AreaItem->getValueAsDouble();
        auto extra2Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra2$"));
        if (!extra2Item) {
            throw std::runtime_error("$variable$extra2 is not found");
        }
        extra2 = extra2Item->getValueAsBool();
        auto extra2ScoreItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra2Score$"));
        if (!extra2ScoreItem) {
            throw std::runtime_error("$variable$extra2Score is not found");
        }
        extra2Score = extra2ScoreItem->getValueAsDouble();
        auto extra2AreaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra2Area$"));
        if (!extra2AreaItem) {
            throw std::runtime_error("$variable$extra2Area is not found");
        }
        extra2Area = extra2AreaItem->getValueAsDouble();
        auto extra3Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra3$"));
        if (!extra3Item) {
            throw std::runtime_error("$variable$extra3 is not found");
        }
        extra3 = extra3Item->getValueAsBool();
        auto extra3ScoreItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra3Score$"));
        if (!extra3ScoreItem) {
            throw std::runtime_error("$variable$extra3Score is not found");
        }
        extra3Score = extra3ScoreItem->getValueAsDouble();
        auto extra3AreaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra3Area$"));
        if (!extra3AreaItem) {
            throw std::runtime_error("$variable$extra3Area is not found");
        }
        extra3Area = extra3AreaItem->getValueAsDouble();
        auto extra4Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra4$"));
        if (!extra4Item) {
            throw std::runtime_error("$variable$extra4 is not found");
        }
        extra4 = extra4Item->getValueAsBool();
        auto extra4ScoreItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra4Score$"));
        if (!extra4ScoreItem) {
            throw std::runtime_error("$variable$extra4Score is not found");
        }
        extra4Score = extra4ScoreItem->getValueAsDouble();
        auto extra4AreaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$extra4Area$"));
        if (!extra4AreaItem) {
            throw std::runtime_error("$variable$extra4Area is not found");
        }
        extra4Area = extra4AreaItem->getValueAsDouble();
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
        extra1 = obj.extra1;
        extra1Score = obj.extra1Score;
        extra1Area = obj.extra1Area;
        extra2 = obj.extra2;
        extra2Score = obj.extra2Score;
        extra2Area = obj.extra2Area;
        extra3 = obj.extra3;
        extra3Score = obj.extra3Score;
        extra3Area = obj.extra3Area;
        extra4 = obj.extra4;
        extra4Score = obj.extra4Score;
        extra4Area = obj.extra4Area;
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
            extra1 = obj.extra1;
            extra1Score = obj.extra1Score;
            extra1Area = obj.extra1Area;
            extra2 = obj.extra2;
            extra2Score = obj.extra2Score;
            extra2Area = obj.extra2Area;
            extra3 = obj.extra3;
            extra3Score = obj.extra3Score;
            extra3Area = obj.extra3Area;
            extra4 = obj.extra4;
            extra4Score = obj.extra4Score;
            extra4Area = obj.extra4Area;
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
        auto extra1Item = std::make_shared<rw::oso::ObjectStoreItem>();
        extra1Item->setName("$variable$extra1$");
        extra1Item->setValueFromBool(extra1);
        assembly.addItem(extra1Item);
        auto extra1ScoreItem = std::make_shared<rw::oso::ObjectStoreItem>();
        extra1ScoreItem->setName("$variable$extra1Score$");
        extra1ScoreItem->setValueFromDouble(extra1Score);
        assembly.addItem(extra1ScoreItem);
        auto extra1AreaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        extra1AreaItem->setName("$variable$extra1Area$");
        extra1AreaItem->setValueFromDouble(extra1Area);
        assembly.addItem(extra1AreaItem);
        auto extra2Item = std::make_shared<rw::oso::ObjectStoreItem>();
        extra2Item->setName("$variable$extra2$");
        extra2Item->setValueFromBool(extra2);
        assembly.addItem(extra2Item);
        auto extra2ScoreItem = std::make_shared<rw::oso::ObjectStoreItem>();
        extra2ScoreItem->setName("$variable$extra2Score$");
        extra2ScoreItem->setValueFromDouble(extra2Score);
        assembly.addItem(extra2ScoreItem);
        auto extra2AreaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        extra2AreaItem->setName("$variable$extra2Area$");
        extra2AreaItem->setValueFromDouble(extra2Area);
        assembly.addItem(extra2AreaItem);
        auto extra3Item = std::make_shared<rw::oso::ObjectStoreItem>();
        extra3Item->setName("$variable$extra3$");
        extra3Item->setValueFromBool(extra3);
        assembly.addItem(extra3Item);
        auto extra3ScoreItem = std::make_shared<rw::oso::ObjectStoreItem>();
        extra3ScoreItem->setName("$variable$extra3Score$");
        extra3ScoreItem->setValueFromDouble(extra3Score);
        assembly.addItem(extra3ScoreItem);
        auto extra3AreaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        extra3AreaItem->setName("$variable$extra3Area$");
        extra3AreaItem->setValueFromDouble(extra3Area);
        assembly.addItem(extra3AreaItem);
        auto extra4Item = std::make_shared<rw::oso::ObjectStoreItem>();
        extra4Item->setName("$variable$extra4$");
        extra4Item->setValueFromBool(extra4);
        assembly.addItem(extra4Item);
        auto extra4ScoreItem = std::make_shared<rw::oso::ObjectStoreItem>();
        extra4ScoreItem->setName("$variable$extra4Score$");
        extra4ScoreItem->setValueFromDouble(extra4Score);
        assembly.addItem(extra4ScoreItem);
        auto extra4AreaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        extra4AreaItem->setName("$variable$extra4Area$");
        extra4AreaItem->setValueFromDouble(extra4Area);
        assembly.addItem(extra4AreaItem);
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
        return queYa == obj.queYa && queYaScore == obj.queYaScore && queYaArea == obj.queYaArea && tangShang == obj.tangShang && tangShangScore == obj.tangShangScore && tangShangArea == obj.tangShangArea && zangWu == obj.zangWu && zangWuScore == obj.zangWuScore && zangWuArea == obj.zangWuArea && suoXiao == obj.suoXiao && suoXiaoScore == obj.suoXiaoScore && suoXiaoArea == obj.suoXiaoArea && extra1 == obj.extra1 && extra1Score == obj.extra1Score && extra1Area == obj.extra1Area && extra2 == obj.extra2 && extra2Score == obj.extra2Score && extra2Area == obj.extra2Area && extra3 == obj.extra3 && extra3Score == obj.extra3Score && extra3Area == obj.extra3Area && extra4 == obj.extra4 && extra4Score == obj.extra4Score && extra4Area == obj.extra4Area && extra5 == obj.extra5 && extra5Score == obj.extra5Score && extra5Area == obj.extra5Area && extra6 == obj.extra6 && extra6Score == obj.extra6Score && extra6Area == obj.extra6Area && extra7 == obj.extra7 && extra7Score == obj.extra7Score && extra7Area == obj.extra7Area && extra8 == obj.extra8 && extra8Score == obj.extra8Score && extra8Area == obj.extra8Area;
    }

    inline bool ScoreConfig::operator!=(const ScoreConfig& obj) const
    {
        return !(*this == obj);
    }

}

