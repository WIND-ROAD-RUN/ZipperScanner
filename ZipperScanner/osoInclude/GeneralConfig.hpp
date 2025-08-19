#pragma once

#include"oso_core.h"
#include <string>

namespace cdm {
    class GeneralConfig
    {
    public:
        GeneralConfig() = default;
        ~GeneralConfig() = default;

        GeneralConfig(const rw::oso::ObjectStoreAssembly& assembly);
        GeneralConfig(const GeneralConfig& obj);

        GeneralConfig& operator=(const GeneralConfig& obj);
        operator rw::oso::ObjectStoreAssembly() const;
        bool operator==(const GeneralConfig& obj) const;
        bool operator!=(const GeneralConfig& obj) const;

    public:
        double produceLength{ 0 };
        int punchCount{ 0 };
        bool qiangGuang{ false };
        bool zhongGuang{ false };
        bool ruoGuang{ false };
        bool isDebug{ false };
        bool isSaveImg{ false };
        bool isshibiekuang{ true };
        bool iswenzi{ true };
        bool isStart{ false };
        bool isStop{ false };
        double shedingladaichangdu{ 0 };
    };

    inline GeneralConfig::GeneralConfig(const rw::oso::ObjectStoreAssembly& assembly)
    {
        auto isAccountAssembly = assembly.getName();
        if (isAccountAssembly != "$class$GeneralConfig$")
        {
            throw std::runtime_error("Assembly is not $class$GeneralConfig$");
        }
        auto produceLengthItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$produceLength$"));
        if (!produceLengthItem) {
            throw std::runtime_error("$variable$produceLength is not found");
        }
        produceLength = produceLengthItem->getValueAsDouble();
        auto punchCountItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$punchCount$"));
        if (!punchCountItem) {
            throw std::runtime_error("$variable$punchCount is not found");
        }
        punchCount = punchCountItem->getValueAsInt();
        auto qiangGuangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$qiangGuang$"));
        if (!qiangGuangItem) {
            throw std::runtime_error("$variable$qiangGuang is not found");
        }
        qiangGuang = qiangGuangItem->getValueAsBool();
        auto zhongGuangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zhongGuang$"));
        if (!zhongGuangItem) {
            throw std::runtime_error("$variable$zhongGuang is not found");
        }
        zhongGuang = zhongGuangItem->getValueAsBool();
        auto ruoGuangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$ruoGuang$"));
        if (!ruoGuangItem) {
            throw std::runtime_error("$variable$ruoGuang is not found");
        }
        ruoGuang = ruoGuangItem->getValueAsBool();
        auto isDebugItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$isDebug$"));
        if (!isDebugItem) {
            throw std::runtime_error("$variable$isDebug is not found");
        }
        isDebug = isDebugItem->getValueAsBool();
        auto isSaveImgItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$isSaveImg$"));
        if (!isSaveImgItem) {
            throw std::runtime_error("$variable$isSaveImg is not found");
        }
        isSaveImg = isSaveImgItem->getValueAsBool();
        auto isshibiekuangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$isshibiekuang$"));
        if (!isshibiekuangItem) {
            throw std::runtime_error("$variable$isshibiekuang is not found");
        }
        isshibiekuang = isshibiekuangItem->getValueAsBool();
        auto iswenziItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$iswenzi$"));
        if (!iswenziItem) {
            throw std::runtime_error("$variable$iswenzi is not found");
        }
        iswenzi = iswenziItem->getValueAsBool();
        auto isStartItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$isStart$"));
        if (!isStartItem) {
            throw std::runtime_error("$variable$isStart is not found");
        }
        isStart = isStartItem->getValueAsBool();
        auto isStopItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$isStop$"));
        if (!isStopItem) {
            throw std::runtime_error("$variable$isStop is not found");
        }
        isStop = isStopItem->getValueAsBool();
        auto shedingladaichangduItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$shedingladaichangdu$"));
        if (!shedingladaichangduItem) {
            throw std::runtime_error("$variable$shedingladaichangdu is not found");
        }
        shedingladaichangdu = shedingladaichangduItem->getValueAsDouble();
    }

    inline GeneralConfig::GeneralConfig(const GeneralConfig& obj)
    {
        produceLength = obj.produceLength;
        punchCount = obj.punchCount;
        qiangGuang = obj.qiangGuang;
        zhongGuang = obj.zhongGuang;
        ruoGuang = obj.ruoGuang;
        isDebug = obj.isDebug;
        isSaveImg = obj.isSaveImg;
        isshibiekuang = obj.isshibiekuang;
        iswenzi = obj.iswenzi;
        isStart = obj.isStart;
        isStop = obj.isStop;
        shedingladaichangdu = obj.shedingladaichangdu;
    }

    inline GeneralConfig& GeneralConfig::operator=(const GeneralConfig& obj)
    {
        if (this != &obj) {
            produceLength = obj.produceLength;
            punchCount = obj.punchCount;
            qiangGuang = obj.qiangGuang;
            zhongGuang = obj.zhongGuang;
            ruoGuang = obj.ruoGuang;
            isDebug = obj.isDebug;
            isSaveImg = obj.isSaveImg;
            isshibiekuang = obj.isshibiekuang;
            iswenzi = obj.iswenzi;
            isStart = obj.isStart;
            isStop = obj.isStop;
            shedingladaichangdu = obj.shedingladaichangdu;
        }
        return *this;
    }

    inline GeneralConfig::operator rw::oso::ObjectStoreAssembly() const
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$class$GeneralConfig$");
        auto produceLengthItem = std::make_shared<rw::oso::ObjectStoreItem>();
        produceLengthItem->setName("$variable$produceLength$");
        produceLengthItem->setValueFromDouble(produceLength);
        assembly.addItem(produceLengthItem);
        auto punchCountItem = std::make_shared<rw::oso::ObjectStoreItem>();
        punchCountItem->setName("$variable$punchCount$");
        punchCountItem->setValueFromInt(punchCount);
        assembly.addItem(punchCountItem);
        auto qiangGuangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        qiangGuangItem->setName("$variable$qiangGuang$");
        qiangGuangItem->setValueFromBool(qiangGuang);
        assembly.addItem(qiangGuangItem);
        auto zhongGuangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        zhongGuangItem->setName("$variable$zhongGuang$");
        zhongGuangItem->setValueFromBool(zhongGuang);
        assembly.addItem(zhongGuangItem);
        auto ruoGuangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        ruoGuangItem->setName("$variable$ruoGuang$");
        ruoGuangItem->setValueFromBool(ruoGuang);
        assembly.addItem(ruoGuangItem);
        auto isDebugItem = std::make_shared<rw::oso::ObjectStoreItem>();
        isDebugItem->setName("$variable$isDebug$");
        isDebugItem->setValueFromBool(isDebug);
        assembly.addItem(isDebugItem);
        auto isSaveImgItem = std::make_shared<rw::oso::ObjectStoreItem>();
        isSaveImgItem->setName("$variable$isSaveImg$");
        isSaveImgItem->setValueFromBool(isSaveImg);
        assembly.addItem(isSaveImgItem);
        auto isshibiekuangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        isshibiekuangItem->setName("$variable$isshibiekuang$");
        isshibiekuangItem->setValueFromBool(isshibiekuang);
        assembly.addItem(isshibiekuangItem);
        auto iswenziItem = std::make_shared<rw::oso::ObjectStoreItem>();
        iswenziItem->setName("$variable$iswenzi$");
        iswenziItem->setValueFromBool(iswenzi);
        assembly.addItem(iswenziItem);
        auto isStartItem = std::make_shared<rw::oso::ObjectStoreItem>();
        isStartItem->setName("$variable$isStart$");
        isStartItem->setValueFromBool(isStart);
        assembly.addItem(isStartItem);
        auto isStopItem = std::make_shared<rw::oso::ObjectStoreItem>();
        isStopItem->setName("$variable$isStop$");
        isStopItem->setValueFromBool(isStop);
        assembly.addItem(isStopItem);
        auto shedingladaichangduItem = std::make_shared<rw::oso::ObjectStoreItem>();
        shedingladaichangduItem->setName("$variable$shedingladaichangdu$");
        shedingladaichangduItem->setValueFromDouble(shedingladaichangdu);
        assembly.addItem(shedingladaichangduItem);
        return assembly;
    }

    inline bool GeneralConfig::operator==(const GeneralConfig& obj) const
    {
        return produceLength == obj.produceLength && punchCount == obj.punchCount && qiangGuang == obj.qiangGuang && zhongGuang == obj.zhongGuang && ruoGuang == obj.ruoGuang && isDebug == obj.isDebug && isSaveImg == obj.isSaveImg && isshibiekuang == obj.isshibiekuang && iswenzi == obj.iswenzi && isStart == obj.isStart && isStop == obj.isStop && shedingladaichangdu == obj.shedingladaichangdu;
    }

    inline bool GeneralConfig::operator!=(const GeneralConfig& obj) const
    {
        return !(*this == obj);
    }

}

