#include "osoFIleUtiltyFunc.hpp"

#include "Utilty.hpp"

rw::imgPro::EliminationInfoFunc::ClassIdWithConfigMap cdm::ScoreConfigConvert::toClassIdWithEliConfigMap(
	const cdm::ScoreConfig& config, double areaFactor, double scoreFactor)
{
	rw::imgPro::EliminationInfoFunc::ClassIdWithConfigMap result{};

	rw::imgPro::EliminationInfoGetConfig configBase;
	configBase.isUsingArea = true;
	configBase.isUsingScore = true;
	configBase.areaFactor = areaFactor;
	configBase.scoreFactor = scoreFactor;
	configBase.areaIsUsingComplementarySet = false;
	configBase.scoreIsUsingComplementarySet = false;

	for (int i = ClassId::minNum; i <= ClassId::maxNum; i++)
	{
		result[i] = configBase;
	}

	result[ClassId::Queya].areaRange = { 0,config.queYaArea };
	result[ClassId::Queya].scoreRange = { 0,config.queYaScore };

	result[ClassId::Tangshang].areaRange = { 0,config.tangShangArea };
	result[ClassId::Tangshang].scoreRange = { 0,config.tangShangScore };

	result[ClassId::Zangwu].areaRange = { 0,config.zangWuArea };
	result[ClassId::Zangwu].scoreRange = { 0,config.zangWuScore };

	result[ClassId::Suoxiao].areaRange = { 0,config.suoXiaoArea };
	result[ClassId::Suoxiao].scoreRange = { 0,config.suoXiaoScore };

	result[ClassId::Huawen].areaRange = { 0,config.huaWenArea };
	result[ClassId::Huawen].scoreRange = { 0,config.huaWenScore };

	result[ClassId::Yuan].areaRange = { 0,config.yuanArea };
	result[ClassId::Yuan].scoreRange = { 0,config.yuanScore };

	result[ClassId::Huapo].areaRange = { 0,config.huaPoArea };
	result[ClassId::Huapo].scoreRange = { 0,config.huaPoScore };

	result[ClassId::Duanxian].areaRange = { 0,config.duanXianArea };
	result[ClassId::Duanxian].scoreRange = { 0,config.duanXianScore };

	return result;
}

rw::imgPro::DefectResultInfoFunc::ClassIdWithConfigMap cdm::ScoreConfigConvert::toClassIdWithDefConfigMap(
	const cdm::ScoreConfig& config)
{
	rw::imgPro::DefectResultInfoFunc::ClassIdWithConfigMap result;
	rw::imgPro::DefectResultInfoFunc::Config configBase;
	configBase.isEnable = false;
	for (int i = ClassId::minNum; i <= ClassId::maxNum; i++)
	{
		result[i] = configBase;
	}

	result[ClassId::Queya].isEnable = config.queYa;
	result[ClassId::Tangshang].isEnable = config.tangShang;
	result[ClassId::Zangwu].isEnable = config.zangWu;
	result[ClassId::Suoxiao].isEnable = config.suoXiao;
	result[ClassId::Huawen].isEnable = config.huaWen;
	result[ClassId::Yuan].isEnable = config.yuan;
	result[ClassId::Huapo].isEnable = config.huaPo;
	result[ClassId::Duanxian].isEnable = config.duanXian;

	return result;
}
