#pragma once

#include <QCheckBox>
#include <QObject>

#include "IModule.hpp"

namespace rw::rqw
{
	class LabelWarning;
}

class HandleScanner;
class DlgProductScore;
class DlgProductSet;

class UIModule
	: public QObject, public IModule<void>
{
	Q_OBJECT
public:
	void build() override;
	void destroy() override;
	void start() override;
	void stop() override;
public:
	void ini_dlgProductScoreGroupList();
	void ini_dlgProductSetCheckList();
	void connectSetAndScore();
public:
	DlgProductSet* _dlgProductSet = nullptr;
	DlgProductScore* _dlgProductScore = nullptr;
	HandleScanner* _handleScanner = nullptr;
	rw::rqw::LabelWarning* labelWarning = nullptr;

	QVector<QCheckBox*> _dlgProductSetCheckList{};
	QVector<QWidget*> _dlgProductScoreGroupList{};
};
