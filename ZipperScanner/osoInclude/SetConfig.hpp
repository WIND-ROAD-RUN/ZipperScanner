#pragma once

#include"oso_core.h"
#include <string>

namespace cdm {
    class SetConfig
    {
    public:
        SetConfig() = default;
        ~SetConfig() = default;

        SetConfig(const rw::oso::ObjectStoreAssembly& assembly);
        SetConfig(const SetConfig& obj);

        SetConfig& operator=(const SetConfig& obj);
        operator rw::oso::ObjectStoreAssembly() const;
        bool operator==(const SetConfig& obj) const;
        bool operator!=(const SetConfig& obj) const;

    public:
        double tifeijuli1{ 0 };
        double tifeijuli2{ 0 };
        double shangXianWei1{ 0 };
        double xiaXianWei1{ 0 };
        double zuoXianWei1{ 0 };
        double youXianWei1{ 0 };
        double xiangSuDangLiang1{ 0 };
        double shangXianWei2{ 0 };
        double xiaXianWei2{ 0 };
        double zuoXianWei2{ 0 };
        double youXianWei2{ 0 };
        double xiangSuDangLiang2{ 0 };
        double qiangBaoGuang{ 0 };
        double qiangZengYi{ 0 };
        double zhongBaoGuang{ 0 };
        double zhongZengYi{ 0 };
        double ruoBaoGuang{ 0 };
        double ruoZengYi{ 0 };
        bool saveNGImg{ false };
        bool saveMaskImg{ false };
        bool saveOKImg{ false };
        bool debugMode{ false };
        bool takeWork1Pictures{ false };
        bool takeWork2Pictures{ false };
        bool qiyongerxiangji{ false };
        bool qiyongyundongkongzhiqi{ false };
        bool yundongkongzhiqichonglian{ false };
        double shedingladaichangdu{ 0 };
        double chongkongjishu{ 0 };
        double dangqianchangdu{ 0 };
        double xiangjichufachangdu{ 0 };
        double shoudongsudu{ 0 };
        double meizhuanmaichongshu{ 0 };
        double zidongladaisudu{ 0 };
        double shedingzhouchang{ 0 };
        double yanshichongkong{ 0 };
        double chongkongshijian{ 0 };
        double yanshiziqi{ 0 };
        double jiajiansushijian{ 0 };
        int qidonganniuIN{ 0 };
        int lalianlawanIN{ 0 };
        int jitingIN{ 0 };
        int bujindianjimaichongOUT{ 0 };
        int chongkongOUT{ 0 };
        int tuojiOUT{ 0 };
        bool isQueya{ false };
        bool isTangshang{ false };
        bool isZangwu{ false };
        bool isSuoxiao{ false };
        bool isExtra1{ false };
        bool isExtra2{ false };
        bool isExtra3{ false };
        bool isExtra4{ false };
        bool isExtra5{ false };
        bool isExtra6{ false };
        bool isExtra7{ false };
        bool isExtra8{ false };
    };

    inline SetConfig::SetConfig(const rw::oso::ObjectStoreAssembly& assembly)
    {
        auto isAccountAssembly = assembly.getName();
        if (isAccountAssembly != "$class$SetConfig$")
        {
            throw std::runtime_error("Assembly is not $class$SetConfig$");
        }
        auto tifeijuli1Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$tifeijuli1$"));
        if (!tifeijuli1Item) {
            throw std::runtime_error("$variable$tifeijuli1 is not found");
        }
        tifeijuli1 = tifeijuli1Item->getValueAsDouble();
        auto tifeijuli2Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$tifeijuli2$"));
        if (!tifeijuli2Item) {
            throw std::runtime_error("$variable$tifeijuli2 is not found");
        }
        tifeijuli2 = tifeijuli2Item->getValueAsDouble();
        auto shangXianWei1Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$shangXianWei1$"));
        if (!shangXianWei1Item) {
            throw std::runtime_error("$variable$shangXianWei1 is not found");
        }
        shangXianWei1 = shangXianWei1Item->getValueAsDouble();
        auto xiaXianWei1Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$xiaXianWei1$"));
        if (!xiaXianWei1Item) {
            throw std::runtime_error("$variable$xiaXianWei1 is not found");
        }
        xiaXianWei1 = xiaXianWei1Item->getValueAsDouble();
        auto zuoXianWei1Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zuoXianWei1$"));
        if (!zuoXianWei1Item) {
            throw std::runtime_error("$variable$zuoXianWei1 is not found");
        }
        zuoXianWei1 = zuoXianWei1Item->getValueAsDouble();
        auto youXianWei1Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$youXianWei1$"));
        if (!youXianWei1Item) {
            throw std::runtime_error("$variable$youXianWei1 is not found");
        }
        youXianWei1 = youXianWei1Item->getValueAsDouble();
        auto xiangSuDangLiang1Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$xiangSuDangLiang1$"));
        if (!xiangSuDangLiang1Item) {
            throw std::runtime_error("$variable$xiangSuDangLiang1 is not found");
        }
        xiangSuDangLiang1 = xiangSuDangLiang1Item->getValueAsDouble();
        auto shangXianWei2Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$shangXianWei2$"));
        if (!shangXianWei2Item) {
            throw std::runtime_error("$variable$shangXianWei2 is not found");
        }
        shangXianWei2 = shangXianWei2Item->getValueAsDouble();
        auto xiaXianWei2Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$xiaXianWei2$"));
        if (!xiaXianWei2Item) {
            throw std::runtime_error("$variable$xiaXianWei2 is not found");
        }
        xiaXianWei2 = xiaXianWei2Item->getValueAsDouble();
        auto zuoXianWei2Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zuoXianWei2$"));
        if (!zuoXianWei2Item) {
            throw std::runtime_error("$variable$zuoXianWei2 is not found");
        }
        zuoXianWei2 = zuoXianWei2Item->getValueAsDouble();
        auto youXianWei2Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$youXianWei2$"));
        if (!youXianWei2Item) {
            throw std::runtime_error("$variable$youXianWei2 is not found");
        }
        youXianWei2 = youXianWei2Item->getValueAsDouble();
        auto xiangSuDangLiang2Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$xiangSuDangLiang2$"));
        if (!xiangSuDangLiang2Item) {
            throw std::runtime_error("$variable$xiangSuDangLiang2 is not found");
        }
        xiangSuDangLiang2 = xiangSuDangLiang2Item->getValueAsDouble();
        auto qiangBaoGuangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$qiangBaoGuang$"));
        if (!qiangBaoGuangItem) {
            throw std::runtime_error("$variable$qiangBaoGuang is not found");
        }
        qiangBaoGuang = qiangBaoGuangItem->getValueAsDouble();
        auto qiangZengYiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$qiangZengYi$"));
        if (!qiangZengYiItem) {
            throw std::runtime_error("$variable$qiangZengYi is not found");
        }
        qiangZengYi = qiangZengYiItem->getValueAsDouble();
        auto zhongBaoGuangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zhongBaoGuang$"));
        if (!zhongBaoGuangItem) {
            throw std::runtime_error("$variable$zhongBaoGuang is not found");
        }
        zhongBaoGuang = zhongBaoGuangItem->getValueAsDouble();
        auto zhongZengYiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zhongZengYi$"));
        if (!zhongZengYiItem) {
            throw std::runtime_error("$variable$zhongZengYi is not found");
        }
        zhongZengYi = zhongZengYiItem->getValueAsDouble();
        auto ruoBaoGuangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$ruoBaoGuang$"));
        if (!ruoBaoGuangItem) {
            throw std::runtime_error("$variable$ruoBaoGuang is not found");
        }
        ruoBaoGuang = ruoBaoGuangItem->getValueAsDouble();
        auto ruoZengYiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$ruoZengYi$"));
        if (!ruoZengYiItem) {
            throw std::runtime_error("$variable$ruoZengYi is not found");
        }
        ruoZengYi = ruoZengYiItem->getValueAsDouble();
        auto saveNGImgItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$saveNGImg$"));
        if (!saveNGImgItem) {
            throw std::runtime_error("$variable$saveNGImg is not found");
        }
        saveNGImg = saveNGImgItem->getValueAsBool();
        auto saveMaskImgItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$saveMaskImg$"));
        if (!saveMaskImgItem) {
            throw std::runtime_error("$variable$saveMaskImg is not found");
        }
        saveMaskImg = saveMaskImgItem->getValueAsBool();
        auto saveOKImgItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$saveOKImg$"));
        if (!saveOKImgItem) {
            throw std::runtime_error("$variable$saveOKImg is not found");
        }
        saveOKImg = saveOKImgItem->getValueAsBool();
        auto debugModeItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$debugMode$"));
        if (!debugModeItem) {
            throw std::runtime_error("$variable$debugMode is not found");
        }
        debugMode = debugModeItem->getValueAsBool();
        auto takeWork1PicturesItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$takeWork1Pictures$"));
        if (!takeWork1PicturesItem) {
            throw std::runtime_error("$variable$takeWork1Pictures is not found");
        }
        takeWork1Pictures = takeWork1PicturesItem->getValueAsBool();
        auto takeWork2PicturesItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$takeWork2Pictures$"));
        if (!takeWork2PicturesItem) {
            throw std::runtime_error("$variable$takeWork2Pictures is not found");
        }
        takeWork2Pictures = takeWork2PicturesItem->getValueAsBool();
        auto qiyongerxiangjiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$qiyongerxiangji$"));
        if (!qiyongerxiangjiItem) {
            throw std::runtime_error("$variable$qiyongerxiangji is not found");
        }
        qiyongerxiangji = qiyongerxiangjiItem->getValueAsBool();
        auto qiyongyundongkongzhiqiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$qiyongyundongkongzhiqi$"));
        if (!qiyongyundongkongzhiqiItem) {
            throw std::runtime_error("$variable$qiyongyundongkongzhiqi is not found");
        }
        qiyongyundongkongzhiqi = qiyongyundongkongzhiqiItem->getValueAsBool();
        auto yundongkongzhiqichonglianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$yundongkongzhiqichonglian$"));
        if (!yundongkongzhiqichonglianItem) {
            throw std::runtime_error("$variable$yundongkongzhiqichonglian is not found");
        }
        yundongkongzhiqichonglian = yundongkongzhiqichonglianItem->getValueAsBool();
        auto shedingladaichangduItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$shedingladaichangdu$"));
        if (!shedingladaichangduItem) {
            throw std::runtime_error("$variable$shedingladaichangdu is not found");
        }
        shedingladaichangdu = shedingladaichangduItem->getValueAsDouble();
        auto chongkongjishuItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$chongkongjishu$"));
        if (!chongkongjishuItem) {
            throw std::runtime_error("$variable$chongkongjishu is not found");
        }
        chongkongjishu = chongkongjishuItem->getValueAsDouble();
        auto dangqianchangduItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$dangqianchangdu$"));
        if (!dangqianchangduItem) {
            throw std::runtime_error("$variable$dangqianchangdu is not found");
        }
        dangqianchangdu = dangqianchangduItem->getValueAsDouble();
        auto xiangjichufachangduItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$xiangjichufachangdu$"));
        if (!xiangjichufachangduItem) {
            throw std::runtime_error("$variable$xiangjichufachangdu is not found");
        }
        xiangjichufachangdu = xiangjichufachangduItem->getValueAsDouble();
        auto shoudongsuduItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$shoudongsudu$"));
        if (!shoudongsuduItem) {
            throw std::runtime_error("$variable$shoudongsudu is not found");
        }
        shoudongsudu = shoudongsuduItem->getValueAsDouble();
        auto meizhuanmaichongshuItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$meizhuanmaichongshu$"));
        if (!meizhuanmaichongshuItem) {
            throw std::runtime_error("$variable$meizhuanmaichongshu is not found");
        }
        meizhuanmaichongshu = meizhuanmaichongshuItem->getValueAsDouble();
        auto zidongladaisuduItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$zidongladaisudu$"));
        if (!zidongladaisuduItem) {
            throw std::runtime_error("$variable$zidongladaisudu is not found");
        }
        zidongladaisudu = zidongladaisuduItem->getValueAsDouble();
        auto shedingzhouchangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$shedingzhouchang$"));
        if (!shedingzhouchangItem) {
            throw std::runtime_error("$variable$shedingzhouchang is not found");
        }
        shedingzhouchang = shedingzhouchangItem->getValueAsDouble();
        auto yanshichongkongItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$yanshichongkong$"));
        if (!yanshichongkongItem) {
            throw std::runtime_error("$variable$yanshichongkong is not found");
        }
        yanshichongkong = yanshichongkongItem->getValueAsDouble();
        auto chongkongshijianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$chongkongshijian$"));
        if (!chongkongshijianItem) {
            throw std::runtime_error("$variable$chongkongshijian is not found");
        }
        chongkongshijian = chongkongshijianItem->getValueAsDouble();
        auto yanshiziqiItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$yanshiziqi$"));
        if (!yanshiziqiItem) {
            throw std::runtime_error("$variable$yanshiziqi is not found");
        }
        yanshiziqi = yanshiziqiItem->getValueAsDouble();
        auto jiajiansushijianItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$jiajiansushijian$"));
        if (!jiajiansushijianItem) {
            throw std::runtime_error("$variable$jiajiansushijian is not found");
        }
        jiajiansushijian = jiajiansushijianItem->getValueAsDouble();
        auto qidonganniuINItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$qidonganniuIN$"));
        if (!qidonganniuINItem) {
            throw std::runtime_error("$variable$qidonganniuIN is not found");
        }
        qidonganniuIN = qidonganniuINItem->getValueAsInt();
        auto lalianlawanINItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$lalianlawanIN$"));
        if (!lalianlawanINItem) {
            throw std::runtime_error("$variable$lalianlawanIN is not found");
        }
        lalianlawanIN = lalianlawanINItem->getValueAsInt();
        auto jitingINItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$jitingIN$"));
        if (!jitingINItem) {
            throw std::runtime_error("$variable$jitingIN is not found");
        }
        jitingIN = jitingINItem->getValueAsInt();
        auto bujindianjimaichongOUTItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$bujindianjimaichongOUT$"));
        if (!bujindianjimaichongOUTItem) {
            throw std::runtime_error("$variable$bujindianjimaichongOUT is not found");
        }
        bujindianjimaichongOUT = bujindianjimaichongOUTItem->getValueAsInt();
        auto chongkongOUTItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$chongkongOUT$"));
        if (!chongkongOUTItem) {
            throw std::runtime_error("$variable$chongkongOUT is not found");
        }
        chongkongOUT = chongkongOUTItem->getValueAsInt();
        auto tuojiOUTItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$tuojiOUT$"));
        if (!tuojiOUTItem) {
            throw std::runtime_error("$variable$tuojiOUT is not found");
        }
        tuojiOUT = tuojiOUTItem->getValueAsInt();
        auto isQueyaItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$isQueya$"));
        if (!isQueyaItem) {
            throw std::runtime_error("$variable$isQueya is not found");
        }
        isQueya = isQueyaItem->getValueAsBool();
        auto isTangshangItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$isTangshang$"));
        if (!isTangshangItem) {
            throw std::runtime_error("$variable$isTangshang is not found");
        }
        isTangshang = isTangshangItem->getValueAsBool();
        auto isZangwuItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$isZangwu$"));
        if (!isZangwuItem) {
            throw std::runtime_error("$variable$isZangwu is not found");
        }
        isZangwu = isZangwuItem->getValueAsBool();
        auto isSuoxiaoItem = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$isSuoxiao$"));
        if (!isSuoxiaoItem) {
            throw std::runtime_error("$variable$isSuoxiao is not found");
        }
        isSuoxiao = isSuoxiaoItem->getValueAsBool();
        auto isExtra1Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$isExtra1$"));
        if (!isExtra1Item) {
            throw std::runtime_error("$variable$isExtra1 is not found");
        }
        isExtra1 = isExtra1Item->getValueAsBool();
        auto isExtra2Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$isExtra2$"));
        if (!isExtra2Item) {
            throw std::runtime_error("$variable$isExtra2 is not found");
        }
        isExtra2 = isExtra2Item->getValueAsBool();
        auto isExtra3Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$isExtra3$"));
        if (!isExtra3Item) {
            throw std::runtime_error("$variable$isExtra3 is not found");
        }
        isExtra3 = isExtra3Item->getValueAsBool();
        auto isExtra4Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$isExtra4$"));
        if (!isExtra4Item) {
            throw std::runtime_error("$variable$isExtra4 is not found");
        }
        isExtra4 = isExtra4Item->getValueAsBool();
        auto isExtra5Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$isExtra5$"));
        if (!isExtra5Item) {
            throw std::runtime_error("$variable$isExtra5 is not found");
        }
        isExtra5 = isExtra5Item->getValueAsBool();
        auto isExtra6Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$isExtra6$"));
        if (!isExtra6Item) {
            throw std::runtime_error("$variable$isExtra6 is not found");
        }
        isExtra6 = isExtra6Item->getValueAsBool();
        auto isExtra7Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$isExtra7$"));
        if (!isExtra7Item) {
            throw std::runtime_error("$variable$isExtra7 is not found");
        }
        isExtra7 = isExtra7Item->getValueAsBool();
        auto isExtra8Item = rw::oso::ObjectStoreCoreToItem(assembly.getItem("$variable$isExtra8$"));
        if (!isExtra8Item) {
            throw std::runtime_error("$variable$isExtra8 is not found");
        }
        isExtra8 = isExtra8Item->getValueAsBool();
    }

    inline SetConfig::SetConfig(const SetConfig& obj)
    {
        tifeijuli1 = obj.tifeijuli1;
        tifeijuli2 = obj.tifeijuli2;
        shangXianWei1 = obj.shangXianWei1;
        xiaXianWei1 = obj.xiaXianWei1;
        zuoXianWei1 = obj.zuoXianWei1;
        youXianWei1 = obj.youXianWei1;
        xiangSuDangLiang1 = obj.xiangSuDangLiang1;
        shangXianWei2 = obj.shangXianWei2;
        xiaXianWei2 = obj.xiaXianWei2;
        zuoXianWei2 = obj.zuoXianWei2;
        youXianWei2 = obj.youXianWei2;
        xiangSuDangLiang2 = obj.xiangSuDangLiang2;
        qiangBaoGuang = obj.qiangBaoGuang;
        qiangZengYi = obj.qiangZengYi;
        zhongBaoGuang = obj.zhongBaoGuang;
        zhongZengYi = obj.zhongZengYi;
        ruoBaoGuang = obj.ruoBaoGuang;
        ruoZengYi = obj.ruoZengYi;
        saveNGImg = obj.saveNGImg;
        saveMaskImg = obj.saveMaskImg;
        saveOKImg = obj.saveOKImg;
        debugMode = obj.debugMode;
        takeWork1Pictures = obj.takeWork1Pictures;
        takeWork2Pictures = obj.takeWork2Pictures;
        qiyongerxiangji = obj.qiyongerxiangji;
        qiyongyundongkongzhiqi = obj.qiyongyundongkongzhiqi;
        yundongkongzhiqichonglian = obj.yundongkongzhiqichonglian;
        shedingladaichangdu = obj.shedingladaichangdu;
        chongkongjishu = obj.chongkongjishu;
        dangqianchangdu = obj.dangqianchangdu;
        xiangjichufachangdu = obj.xiangjichufachangdu;
        shoudongsudu = obj.shoudongsudu;
        meizhuanmaichongshu = obj.meizhuanmaichongshu;
        zidongladaisudu = obj.zidongladaisudu;
        shedingzhouchang = obj.shedingzhouchang;
        yanshichongkong = obj.yanshichongkong;
        chongkongshijian = obj.chongkongshijian;
        yanshiziqi = obj.yanshiziqi;
        jiajiansushijian = obj.jiajiansushijian;
        qidonganniuIN = obj.qidonganniuIN;
        lalianlawanIN = obj.lalianlawanIN;
        jitingIN = obj.jitingIN;
        bujindianjimaichongOUT = obj.bujindianjimaichongOUT;
        chongkongOUT = obj.chongkongOUT;
        tuojiOUT = obj.tuojiOUT;
        isQueya = obj.isQueya;
        isTangshang = obj.isTangshang;
        isZangwu = obj.isZangwu;
        isSuoxiao = obj.isSuoxiao;
        isExtra1 = obj.isExtra1;
        isExtra2 = obj.isExtra2;
        isExtra3 = obj.isExtra3;
        isExtra4 = obj.isExtra4;
        isExtra5 = obj.isExtra5;
        isExtra6 = obj.isExtra6;
        isExtra7 = obj.isExtra7;
        isExtra8 = obj.isExtra8;
    }

    inline SetConfig& SetConfig::operator=(const SetConfig& obj)
    {
        if (this != &obj) {
            tifeijuli1 = obj.tifeijuli1;
            tifeijuli2 = obj.tifeijuli2;
            shangXianWei1 = obj.shangXianWei1;
            xiaXianWei1 = obj.xiaXianWei1;
            zuoXianWei1 = obj.zuoXianWei1;
            youXianWei1 = obj.youXianWei1;
            xiangSuDangLiang1 = obj.xiangSuDangLiang1;
            shangXianWei2 = obj.shangXianWei2;
            xiaXianWei2 = obj.xiaXianWei2;
            zuoXianWei2 = obj.zuoXianWei2;
            youXianWei2 = obj.youXianWei2;
            xiangSuDangLiang2 = obj.xiangSuDangLiang2;
            qiangBaoGuang = obj.qiangBaoGuang;
            qiangZengYi = obj.qiangZengYi;
            zhongBaoGuang = obj.zhongBaoGuang;
            zhongZengYi = obj.zhongZengYi;
            ruoBaoGuang = obj.ruoBaoGuang;
            ruoZengYi = obj.ruoZengYi;
            saveNGImg = obj.saveNGImg;
            saveMaskImg = obj.saveMaskImg;
            saveOKImg = obj.saveOKImg;
            debugMode = obj.debugMode;
            takeWork1Pictures = obj.takeWork1Pictures;
            takeWork2Pictures = obj.takeWork2Pictures;
            qiyongerxiangji = obj.qiyongerxiangji;
            qiyongyundongkongzhiqi = obj.qiyongyundongkongzhiqi;
            yundongkongzhiqichonglian = obj.yundongkongzhiqichonglian;
            shedingladaichangdu = obj.shedingladaichangdu;
            chongkongjishu = obj.chongkongjishu;
            dangqianchangdu = obj.dangqianchangdu;
            xiangjichufachangdu = obj.xiangjichufachangdu;
            shoudongsudu = obj.shoudongsudu;
            meizhuanmaichongshu = obj.meizhuanmaichongshu;
            zidongladaisudu = obj.zidongladaisudu;
            shedingzhouchang = obj.shedingzhouchang;
            yanshichongkong = obj.yanshichongkong;
            chongkongshijian = obj.chongkongshijian;
            yanshiziqi = obj.yanshiziqi;
            jiajiansushijian = obj.jiajiansushijian;
            qidonganniuIN = obj.qidonganniuIN;
            lalianlawanIN = obj.lalianlawanIN;
            jitingIN = obj.jitingIN;
            bujindianjimaichongOUT = obj.bujindianjimaichongOUT;
            chongkongOUT = obj.chongkongOUT;
            tuojiOUT = obj.tuojiOUT;
            isQueya = obj.isQueya;
            isTangshang = obj.isTangshang;
            isZangwu = obj.isZangwu;
            isSuoxiao = obj.isSuoxiao;
            isExtra1 = obj.isExtra1;
            isExtra2 = obj.isExtra2;
            isExtra3 = obj.isExtra3;
            isExtra4 = obj.isExtra4;
            isExtra5 = obj.isExtra5;
            isExtra6 = obj.isExtra6;
            isExtra7 = obj.isExtra7;
            isExtra8 = obj.isExtra8;
        }
        return *this;
    }

    inline SetConfig::operator rw::oso::ObjectStoreAssembly() const
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$class$SetConfig$");
        auto tifeijuli1Item = std::make_shared<rw::oso::ObjectStoreItem>();
        tifeijuli1Item->setName("$variable$tifeijuli1$");
        tifeijuli1Item->setValueFromDouble(tifeijuli1);
        assembly.addItem(tifeijuli1Item);
        auto tifeijuli2Item = std::make_shared<rw::oso::ObjectStoreItem>();
        tifeijuli2Item->setName("$variable$tifeijuli2$");
        tifeijuli2Item->setValueFromDouble(tifeijuli2);
        assembly.addItem(tifeijuli2Item);
        auto shangXianWei1Item = std::make_shared<rw::oso::ObjectStoreItem>();
        shangXianWei1Item->setName("$variable$shangXianWei1$");
        shangXianWei1Item->setValueFromDouble(shangXianWei1);
        assembly.addItem(shangXianWei1Item);
        auto xiaXianWei1Item = std::make_shared<rw::oso::ObjectStoreItem>();
        xiaXianWei1Item->setName("$variable$xiaXianWei1$");
        xiaXianWei1Item->setValueFromDouble(xiaXianWei1);
        assembly.addItem(xiaXianWei1Item);
        auto zuoXianWei1Item = std::make_shared<rw::oso::ObjectStoreItem>();
        zuoXianWei1Item->setName("$variable$zuoXianWei1$");
        zuoXianWei1Item->setValueFromDouble(zuoXianWei1);
        assembly.addItem(zuoXianWei1Item);
        auto youXianWei1Item = std::make_shared<rw::oso::ObjectStoreItem>();
        youXianWei1Item->setName("$variable$youXianWei1$");
        youXianWei1Item->setValueFromDouble(youXianWei1);
        assembly.addItem(youXianWei1Item);
        auto xiangSuDangLiang1Item = std::make_shared<rw::oso::ObjectStoreItem>();
        xiangSuDangLiang1Item->setName("$variable$xiangSuDangLiang1$");
        xiangSuDangLiang1Item->setValueFromDouble(xiangSuDangLiang1);
        assembly.addItem(xiangSuDangLiang1Item);
        auto shangXianWei2Item = std::make_shared<rw::oso::ObjectStoreItem>();
        shangXianWei2Item->setName("$variable$shangXianWei2$");
        shangXianWei2Item->setValueFromDouble(shangXianWei2);
        assembly.addItem(shangXianWei2Item);
        auto xiaXianWei2Item = std::make_shared<rw::oso::ObjectStoreItem>();
        xiaXianWei2Item->setName("$variable$xiaXianWei2$");
        xiaXianWei2Item->setValueFromDouble(xiaXianWei2);
        assembly.addItem(xiaXianWei2Item);
        auto zuoXianWei2Item = std::make_shared<rw::oso::ObjectStoreItem>();
        zuoXianWei2Item->setName("$variable$zuoXianWei2$");
        zuoXianWei2Item->setValueFromDouble(zuoXianWei2);
        assembly.addItem(zuoXianWei2Item);
        auto youXianWei2Item = std::make_shared<rw::oso::ObjectStoreItem>();
        youXianWei2Item->setName("$variable$youXianWei2$");
        youXianWei2Item->setValueFromDouble(youXianWei2);
        assembly.addItem(youXianWei2Item);
        auto xiangSuDangLiang2Item = std::make_shared<rw::oso::ObjectStoreItem>();
        xiangSuDangLiang2Item->setName("$variable$xiangSuDangLiang2$");
        xiangSuDangLiang2Item->setValueFromDouble(xiangSuDangLiang2);
        assembly.addItem(xiangSuDangLiang2Item);
        auto qiangBaoGuangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        qiangBaoGuangItem->setName("$variable$qiangBaoGuang$");
        qiangBaoGuangItem->setValueFromDouble(qiangBaoGuang);
        assembly.addItem(qiangBaoGuangItem);
        auto qiangZengYiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        qiangZengYiItem->setName("$variable$qiangZengYi$");
        qiangZengYiItem->setValueFromDouble(qiangZengYi);
        assembly.addItem(qiangZengYiItem);
        auto zhongBaoGuangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        zhongBaoGuangItem->setName("$variable$zhongBaoGuang$");
        zhongBaoGuangItem->setValueFromDouble(zhongBaoGuang);
        assembly.addItem(zhongBaoGuangItem);
        auto zhongZengYiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        zhongZengYiItem->setName("$variable$zhongZengYi$");
        zhongZengYiItem->setValueFromDouble(zhongZengYi);
        assembly.addItem(zhongZengYiItem);
        auto ruoBaoGuangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        ruoBaoGuangItem->setName("$variable$ruoBaoGuang$");
        ruoBaoGuangItem->setValueFromDouble(ruoBaoGuang);
        assembly.addItem(ruoBaoGuangItem);
        auto ruoZengYiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        ruoZengYiItem->setName("$variable$ruoZengYi$");
        ruoZengYiItem->setValueFromDouble(ruoZengYi);
        assembly.addItem(ruoZengYiItem);
        auto saveNGImgItem = std::make_shared<rw::oso::ObjectStoreItem>();
        saveNGImgItem->setName("$variable$saveNGImg$");
        saveNGImgItem->setValueFromBool(saveNGImg);
        assembly.addItem(saveNGImgItem);
        auto saveMaskImgItem = std::make_shared<rw::oso::ObjectStoreItem>();
        saveMaskImgItem->setName("$variable$saveMaskImg$");
        saveMaskImgItem->setValueFromBool(saveMaskImg);
        assembly.addItem(saveMaskImgItem);
        auto saveOKImgItem = std::make_shared<rw::oso::ObjectStoreItem>();
        saveOKImgItem->setName("$variable$saveOKImg$");
        saveOKImgItem->setValueFromBool(saveOKImg);
        assembly.addItem(saveOKImgItem);
        auto debugModeItem = std::make_shared<rw::oso::ObjectStoreItem>();
        debugModeItem->setName("$variable$debugMode$");
        debugModeItem->setValueFromBool(debugMode);
        assembly.addItem(debugModeItem);
        auto takeWork1PicturesItem = std::make_shared<rw::oso::ObjectStoreItem>();
        takeWork1PicturesItem->setName("$variable$takeWork1Pictures$");
        takeWork1PicturesItem->setValueFromBool(takeWork1Pictures);
        assembly.addItem(takeWork1PicturesItem);
        auto takeWork2PicturesItem = std::make_shared<rw::oso::ObjectStoreItem>();
        takeWork2PicturesItem->setName("$variable$takeWork2Pictures$");
        takeWork2PicturesItem->setValueFromBool(takeWork2Pictures);
        assembly.addItem(takeWork2PicturesItem);
        auto qiyongerxiangjiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        qiyongerxiangjiItem->setName("$variable$qiyongerxiangji$");
        qiyongerxiangjiItem->setValueFromBool(qiyongerxiangji);
        assembly.addItem(qiyongerxiangjiItem);
        auto qiyongyundongkongzhiqiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        qiyongyundongkongzhiqiItem->setName("$variable$qiyongyundongkongzhiqi$");
        qiyongyundongkongzhiqiItem->setValueFromBool(qiyongyundongkongzhiqi);
        assembly.addItem(qiyongyundongkongzhiqiItem);
        auto yundongkongzhiqichonglianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        yundongkongzhiqichonglianItem->setName("$variable$yundongkongzhiqichonglian$");
        yundongkongzhiqichonglianItem->setValueFromBool(yundongkongzhiqichonglian);
        assembly.addItem(yundongkongzhiqichonglianItem);
        auto shedingladaichangduItem = std::make_shared<rw::oso::ObjectStoreItem>();
        shedingladaichangduItem->setName("$variable$shedingladaichangdu$");
        shedingladaichangduItem->setValueFromDouble(shedingladaichangdu);
        assembly.addItem(shedingladaichangduItem);
        auto chongkongjishuItem = std::make_shared<rw::oso::ObjectStoreItem>();
        chongkongjishuItem->setName("$variable$chongkongjishu$");
        chongkongjishuItem->setValueFromDouble(chongkongjishu);
        assembly.addItem(chongkongjishuItem);
        auto dangqianchangduItem = std::make_shared<rw::oso::ObjectStoreItem>();
        dangqianchangduItem->setName("$variable$dangqianchangdu$");
        dangqianchangduItem->setValueFromDouble(dangqianchangdu);
        assembly.addItem(dangqianchangduItem);
        auto xiangjichufachangduItem = std::make_shared<rw::oso::ObjectStoreItem>();
        xiangjichufachangduItem->setName("$variable$xiangjichufachangdu$");
        xiangjichufachangduItem->setValueFromDouble(xiangjichufachangdu);
        assembly.addItem(xiangjichufachangduItem);
        auto shoudongsuduItem = std::make_shared<rw::oso::ObjectStoreItem>();
        shoudongsuduItem->setName("$variable$shoudongsudu$");
        shoudongsuduItem->setValueFromDouble(shoudongsudu);
        assembly.addItem(shoudongsuduItem);
        auto meizhuanmaichongshuItem = std::make_shared<rw::oso::ObjectStoreItem>();
        meizhuanmaichongshuItem->setName("$variable$meizhuanmaichongshu$");
        meizhuanmaichongshuItem->setValueFromDouble(meizhuanmaichongshu);
        assembly.addItem(meizhuanmaichongshuItem);
        auto zidongladaisuduItem = std::make_shared<rw::oso::ObjectStoreItem>();
        zidongladaisuduItem->setName("$variable$zidongladaisudu$");
        zidongladaisuduItem->setValueFromDouble(zidongladaisudu);
        assembly.addItem(zidongladaisuduItem);
        auto shedingzhouchangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        shedingzhouchangItem->setName("$variable$shedingzhouchang$");
        shedingzhouchangItem->setValueFromDouble(shedingzhouchang);
        assembly.addItem(shedingzhouchangItem);
        auto yanshichongkongItem = std::make_shared<rw::oso::ObjectStoreItem>();
        yanshichongkongItem->setName("$variable$yanshichongkong$");
        yanshichongkongItem->setValueFromDouble(yanshichongkong);
        assembly.addItem(yanshichongkongItem);
        auto chongkongshijianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        chongkongshijianItem->setName("$variable$chongkongshijian$");
        chongkongshijianItem->setValueFromDouble(chongkongshijian);
        assembly.addItem(chongkongshijianItem);
        auto yanshiziqiItem = std::make_shared<rw::oso::ObjectStoreItem>();
        yanshiziqiItem->setName("$variable$yanshiziqi$");
        yanshiziqiItem->setValueFromDouble(yanshiziqi);
        assembly.addItem(yanshiziqiItem);
        auto jiajiansushijianItem = std::make_shared<rw::oso::ObjectStoreItem>();
        jiajiansushijianItem->setName("$variable$jiajiansushijian$");
        jiajiansushijianItem->setValueFromDouble(jiajiansushijian);
        assembly.addItem(jiajiansushijianItem);
        auto qidonganniuINItem = std::make_shared<rw::oso::ObjectStoreItem>();
        qidonganniuINItem->setName("$variable$qidonganniuIN$");
        qidonganniuINItem->setValueFromInt(qidonganniuIN);
        assembly.addItem(qidonganniuINItem);
        auto lalianlawanINItem = std::make_shared<rw::oso::ObjectStoreItem>();
        lalianlawanINItem->setName("$variable$lalianlawanIN$");
        lalianlawanINItem->setValueFromInt(lalianlawanIN);
        assembly.addItem(lalianlawanINItem);
        auto jitingINItem = std::make_shared<rw::oso::ObjectStoreItem>();
        jitingINItem->setName("$variable$jitingIN$");
        jitingINItem->setValueFromInt(jitingIN);
        assembly.addItem(jitingINItem);
        auto bujindianjimaichongOUTItem = std::make_shared<rw::oso::ObjectStoreItem>();
        bujindianjimaichongOUTItem->setName("$variable$bujindianjimaichongOUT$");
        bujindianjimaichongOUTItem->setValueFromInt(bujindianjimaichongOUT);
        assembly.addItem(bujindianjimaichongOUTItem);
        auto chongkongOUTItem = std::make_shared<rw::oso::ObjectStoreItem>();
        chongkongOUTItem->setName("$variable$chongkongOUT$");
        chongkongOUTItem->setValueFromInt(chongkongOUT);
        assembly.addItem(chongkongOUTItem);
        auto tuojiOUTItem = std::make_shared<rw::oso::ObjectStoreItem>();
        tuojiOUTItem->setName("$variable$tuojiOUT$");
        tuojiOUTItem->setValueFromInt(tuojiOUT);
        assembly.addItem(tuojiOUTItem);
        auto isQueyaItem = std::make_shared<rw::oso::ObjectStoreItem>();
        isQueyaItem->setName("$variable$isQueya$");
        isQueyaItem->setValueFromBool(isQueya);
        assembly.addItem(isQueyaItem);
        auto isTangshangItem = std::make_shared<rw::oso::ObjectStoreItem>();
        isTangshangItem->setName("$variable$isTangshang$");
        isTangshangItem->setValueFromBool(isTangshang);
        assembly.addItem(isTangshangItem);
        auto isZangwuItem = std::make_shared<rw::oso::ObjectStoreItem>();
        isZangwuItem->setName("$variable$isZangwu$");
        isZangwuItem->setValueFromBool(isZangwu);
        assembly.addItem(isZangwuItem);
        auto isSuoxiaoItem = std::make_shared<rw::oso::ObjectStoreItem>();
        isSuoxiaoItem->setName("$variable$isSuoxiao$");
        isSuoxiaoItem->setValueFromBool(isSuoxiao);
        assembly.addItem(isSuoxiaoItem);
        auto isExtra1Item = std::make_shared<rw::oso::ObjectStoreItem>();
        isExtra1Item->setName("$variable$isExtra1$");
        isExtra1Item->setValueFromBool(isExtra1);
        assembly.addItem(isExtra1Item);
        auto isExtra2Item = std::make_shared<rw::oso::ObjectStoreItem>();
        isExtra2Item->setName("$variable$isExtra2$");
        isExtra2Item->setValueFromBool(isExtra2);
        assembly.addItem(isExtra2Item);
        auto isExtra3Item = std::make_shared<rw::oso::ObjectStoreItem>();
        isExtra3Item->setName("$variable$isExtra3$");
        isExtra3Item->setValueFromBool(isExtra3);
        assembly.addItem(isExtra3Item);
        auto isExtra4Item = std::make_shared<rw::oso::ObjectStoreItem>();
        isExtra4Item->setName("$variable$isExtra4$");
        isExtra4Item->setValueFromBool(isExtra4);
        assembly.addItem(isExtra4Item);
        auto isExtra5Item = std::make_shared<rw::oso::ObjectStoreItem>();
        isExtra5Item->setName("$variable$isExtra5$");
        isExtra5Item->setValueFromBool(isExtra5);
        assembly.addItem(isExtra5Item);
        auto isExtra6Item = std::make_shared<rw::oso::ObjectStoreItem>();
        isExtra6Item->setName("$variable$isExtra6$");
        isExtra6Item->setValueFromBool(isExtra6);
        assembly.addItem(isExtra6Item);
        auto isExtra7Item = std::make_shared<rw::oso::ObjectStoreItem>();
        isExtra7Item->setName("$variable$isExtra7$");
        isExtra7Item->setValueFromBool(isExtra7);
        assembly.addItem(isExtra7Item);
        auto isExtra8Item = std::make_shared<rw::oso::ObjectStoreItem>();
        isExtra8Item->setName("$variable$isExtra8$");
        isExtra8Item->setValueFromBool(isExtra8);
        assembly.addItem(isExtra8Item);
        return assembly;
    }

    inline bool SetConfig::operator==(const SetConfig& obj) const
    {
        return tifeijuli1 == obj.tifeijuli1 && tifeijuli2 == obj.tifeijuli2 && shangXianWei1 == obj.shangXianWei1 && xiaXianWei1 == obj.xiaXianWei1 && zuoXianWei1 == obj.zuoXianWei1 && youXianWei1 == obj.youXianWei1 && xiangSuDangLiang1 == obj.xiangSuDangLiang1 && shangXianWei2 == obj.shangXianWei2 && xiaXianWei2 == obj.xiaXianWei2 && zuoXianWei2 == obj.zuoXianWei2 && youXianWei2 == obj.youXianWei2 && xiangSuDangLiang2 == obj.xiangSuDangLiang2 && qiangBaoGuang == obj.qiangBaoGuang && qiangZengYi == obj.qiangZengYi && zhongBaoGuang == obj.zhongBaoGuang && zhongZengYi == obj.zhongZengYi && ruoBaoGuang == obj.ruoBaoGuang && ruoZengYi == obj.ruoZengYi && saveNGImg == obj.saveNGImg && saveMaskImg == obj.saveMaskImg && saveOKImg == obj.saveOKImg && debugMode == obj.debugMode && takeWork1Pictures == obj.takeWork1Pictures && takeWork2Pictures == obj.takeWork2Pictures && qiyongerxiangji == obj.qiyongerxiangji && qiyongyundongkongzhiqi == obj.qiyongyundongkongzhiqi && yundongkongzhiqichonglian == obj.yundongkongzhiqichonglian && shedingladaichangdu == obj.shedingladaichangdu && chongkongjishu == obj.chongkongjishu && dangqianchangdu == obj.dangqianchangdu && xiangjichufachangdu == obj.xiangjichufachangdu && shoudongsudu == obj.shoudongsudu && meizhuanmaichongshu == obj.meizhuanmaichongshu && zidongladaisudu == obj.zidongladaisudu && shedingzhouchang == obj.shedingzhouchang && yanshichongkong == obj.yanshichongkong && chongkongshijian == obj.chongkongshijian && yanshiziqi == obj.yanshiziqi && jiajiansushijian == obj.jiajiansushijian && qidonganniuIN == obj.qidonganniuIN && lalianlawanIN == obj.lalianlawanIN && jitingIN == obj.jitingIN && bujindianjimaichongOUT == obj.bujindianjimaichongOUT && chongkongOUT == obj.chongkongOUT && tuojiOUT == obj.tuojiOUT && isQueya == obj.isQueya && isTangshang == obj.isTangshang && isZangwu == obj.isZangwu && isSuoxiao == obj.isSuoxiao && isExtra1 == obj.isExtra1 && isExtra2 == obj.isExtra2 && isExtra3 == obj.isExtra3 && isExtra4 == obj.isExtra4 && isExtra5 == obj.isExtra5 && isExtra6 == obj.isExtra6 && isExtra7 == obj.isExtra7 && isExtra8 == obj.isExtra8;
    }

    inline bool SetConfig::operator!=(const SetConfig& obj) const
    {
        return !(*this == obj);
    }

}

