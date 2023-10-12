﻿import Utility;
import Config;

#include "stdafx.h"
#include "form/afkform.h"
#include "generalform.h"
#include "selectobjectform.h"

#include "mainthread.h"
#include <injector.h>
#include "signaldispatcher.h"

//#ifndef _DEBUG
//#include "net/webauthenticator.h"
//#endif

GeneralForm::GeneralForm(__int64 index, QWidget* parent)
	: QWidget(parent)
	, Indexer(index)
{
	ui.setupUi(this);

	connect(this, &GeneralForm::resetControlTextLanguage, this, &GeneralForm::onResetControlTextLanguage, Qt::QueuedConnection);

	SignalDispatcher& signalDispatcher = SignalDispatcher::getInstance(index);
	connect(&signalDispatcher, &SignalDispatcher::setStartButtonEnabled, ui.pushButton_start, &PushButton::setEnabled, Qt::QueuedConnection);
	connect(&signalDispatcher, &SignalDispatcher::applyHashSettingsToUI, this, &GeneralForm::onApplyHashSettingsToUI, Qt::QueuedConnection);
	connect(&signalDispatcher, &SignalDispatcher::gameStarted, this, &GeneralForm::onGameStart, Qt::QueuedConnection);


	QList<PushButton*> buttonList = util::findWidgets<PushButton>(this);
	for (auto& button : buttonList)
	{
		if (button)
			connect(button, &PushButton::clicked, this, &GeneralForm::onButtonClicked, Qt::QueuedConnection);
	}

	QList <QCheckBox*> checkBoxList = util::findWidgets<QCheckBox>(this);
	for (auto& checkBox : checkBoxList)
	{
		if (checkBox)
			connect(checkBox, &QCheckBox::stateChanged, this, &GeneralForm::onCheckBoxStateChanged, Qt::QueuedConnection);
	}

	QList <QSpinBox*> spinBoxList = util::findWidgets<QSpinBox>(this);
	for (auto& spinBox : spinBoxList)
	{
		if (spinBox)
			connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxValueChanged(int)), Qt::QueuedConnection);
	}

	QList <ComboBox*> comboBoxList = util::findWidgets<ComboBox>(this);
	for (auto& comboBox : comboBoxList)
	{
		if (comboBox)
		{
			connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxCurrentIndexChanged(int)), Qt::QueuedConnection);
			connect(comboBox, &ComboBox::clicked, this, &GeneralForm::onComboBoxClicked, Qt::QueuedConnection);
		}
	}

	std::unique_ptr<AfkForm> _pAfkForm(new AfkForm(index, nullptr));
	if (_pAfkForm == nullptr)
		return;

	pAfkForm_ = _pAfkForm.release();
	pAfkForm_->hide();

	emit ui.comboBox_paths->clicked();
	emit signalDispatcher.applyHashSettingsToUI();

	QVector<QPair<QString, QString>> fileList;
	if (!util::enumAllFiles(util::applicationDirPath() + "/settings", ".json", &fileList))
	{
		return;
	}

	__int64 idx = 0;
	__int64 defaultIndex = -1;
	ui.comboBox_setting->blockSignals(true);
	ui.comboBox_setting->clear();
	for (const QPair<QString, QString>& pair : fileList)
	{
		ui.comboBox_setting->addItem(pair.first, pair.second);
		if (pair.first.contains("default.json"))
			defaultIndex = idx;
		++idx;
	}

	if (defaultIndex >= 0)
		ui.comboBox_setting->setCurrentIndex(defaultIndex);

	ui.comboBox_setting->blockSignals(false);

	//驗證
#ifdef WEBAUTHENTICATOR_H
#ifndef _DEBUG
	static bool isFirstInstance = false;
	if (!isFirstInstance)
	{

		QtConcurrent::run([this]()
			{
				Net::Authenticator* g_Authenticator = Net::Authenticator::getInstance(getIndex());
				std::unique_ptr<QString> username(new QString("satester"));
				std::unique_ptr<QString> encode_password(new QString("AwJk8DlkCUVxRMgaHDEMEHQR"));
				if (g_Authenticator->Login(*username, *encode_password))
					isFirstInstance = true;
				else
					MINT::NtTerminateProcess(GetCurrentProcess(), 0);
			});
	}
#endif
#endif
}

GeneralForm::~GeneralForm()
{
	__int64 currentIndex = getIndex();

	if (pAfkForm_ != nullptr)
	{
		pAfkForm_->close();
		pAfkForm_->deleteLater();
		pAfkForm_ = nullptr;
	}

	ThreadManager& thread_manager = ThreadManager::getInstance();
	thread_manager.close(currentIndex);
	qDebug() << "~GeneralForm()";
}

void GeneralForm::onResetControlTextLanguage()
{
	const QStringList positionList = { tr("Left"), tr("Right"), tr("None") };

	//下午 黃昏 午夜 早晨 中午
	const QStringList timeList = { tr("Afternoon"), tr("Dusk"), tr("Midnight"), tr("Morning"), tr("Noon") };

	ui.comboBox_position->clear();
	ui.comboBox_locktime->clear();

	ui.comboBox_position->addItems(positionList);
	ui.comboBox_locktime->addItems(timeList);

	emit ui.comboBox_server->clicked();
}

void GeneralForm::onComboBoxClicked()
{
	ComboBox* pComboBox = qobject_cast<ComboBox*>(sender());
	if (!pComboBox)
	{
		return;
	}

	QString name = pComboBox->objectName();
	if (name.isEmpty())
	{
		return;
	}

	if (name == "comboBox_setting")
	{
		QVector<QPair<QString, QString>> fileList;
		if (!util::enumAllFiles(util::applicationDirPath() + "/settings", ".json", &fileList))
		{
			return;
		}

		int currentIndex = ui.comboBox_setting->currentIndex();
		ui.comboBox_setting->blockSignals(true);
		ui.comboBox_setting->clear();
		for (const QPair<QString, QString>& pair : fileList)
		{
			ui.comboBox_setting->addItem(pair.first, pair.second);
		}

		ui.comboBox_setting->setCurrentIndex(currentIndex);

		ui.comboBox_setting->blockSignals(false);

		return;
	}

	if (name == "comboBox_server")
	{
		createServerList();

		return;
	}

	if (name == "comboBox_paths")
	{
		QListView* pListView = qobject_cast<QListView*>(ui.comboBox_paths->view());
		if (pListView)
		{
			pListView->setMinimumWidth(260);
			pListView->setMaximumWidth(260);
		}

		Config config;
		QStringList paths = config.readArray<QString>("System", "Command", "DirPath");
		QStringList newPaths;

		if (paths.isEmpty())
		{
			QString path;
			SignalDispatcher& signalDispatcher = SignalDispatcher::getInstance(getIndex());
			QEventLoop loop;
			emit signalDispatcher.fileDialogShow(SASH_SUPPORT_GAMENAME, QFileDialog::AcceptOpen, &path, &loop);
			loop.exec();

			if (path.isEmpty())
			{
				return;
			}

			paths.append(path);
		}

		for (const QString& path : paths)
		{
			if (path.contains(SASH_SUPPORT_GAMENAME) && QFile::exists(path) && !newPaths.contains(path))
			{
				newPaths.append(path);
			}
		}

		if (newPaths.isEmpty())
		{
			return;
		}

		int currentIndex = ui.comboBox_paths->currentIndex();
		ui.comboBox_paths->blockSignals(true);
		ui.comboBox_paths->clear();
		for (const QString& it : newPaths)
		{
			//只顯示 上一級文件夾名稱/fileName
			QFileInfo fileInfo(it);
			QString fName = fileInfo.fileName();
			QString path = fileInfo.path();
			QFileInfo pathInfo(path);
			QString pathName = pathInfo.fileName();
			ui.comboBox_paths->addItem(pathName + "/" + fName, it);
		}

		config.writeArray<QString>("System", "Command", "DirPath", newPaths);
		ui.comboBox_paths->setCurrentIndex(currentIndex);
		ui.comboBox_paths->blockSignals(false);

		return;
	}
}

void GeneralForm::onButtonClicked()
{
	PushButton* pPushButton = qobject_cast<PushButton*>(sender());
	if (!pPushButton)
		return;

	QString name = pPushButton->objectName();
	if (name.isEmpty())
		return;

	__int64 currentIndex = getIndex();

	Injector& injector = Injector::getInstance(currentIndex);

	if (name == "pushButton_addpath")
	{

		SignalDispatcher& signalDispatcher = SignalDispatcher::getInstance(currentIndex);
		QString newPath;
		QEventLoop loop;
		emit signalDispatcher.fileDialogShow(SASH_SUPPORT_GAMENAME, QFileDialog::AcceptOpen, &newPath, &loop);
		loop.exec();

		if (newPath.isEmpty())
			return;

		if (!newPath.contains(SASH_SUPPORT_GAMENAME) || !QFile::exists(newPath))
			return;

		Config config;
		QStringList paths = config.readArray<QString>("System", "Command", "DirPath");
		QStringList newPaths;

		for (const QString& path : paths)
		{
			if (path.contains(SASH_SUPPORT_GAMENAME) && QFile::exists(path) && !newPaths.contains(path))
			{
				newPaths.append(path);
			}
		}

		if (!newPaths.contains(newPath))
			newPaths.append(newPath);

		ui.comboBox_paths->blockSignals(true);
		ui.comboBox_paths->clear();
		for (const QString& it : newPaths)
		{
			//只顯示 上一級文件夾名稱/fileName
			QFileInfo fileInfo(it);
			QString path = fileInfo.path();
			QFileInfo pathInfo(path);
			QString pathName = pathInfo.fileName();
			ui.comboBox_paths->addItem(pathName + "/" + fileInfo.fileName(), it);
		}

		ui.comboBox_paths->setCurrentIndex(ui.comboBox_paths->count() - 1);
		ui.comboBox_paths->blockSignals(false);
		config.writeArray<QString>("System", "Command", "DirPath", newPaths);
		return;
	}

	if (name == "pushButton_setting")
	{
		if (ui.comboBox_setting->currentText().isEmpty())
			return;

		QString fileName = ui.comboBox_setting->currentData().toString();
		if (fileName.isEmpty())
			return;

		SignalDispatcher& signalDispatcher = SignalDispatcher::getInstance(currentIndex);
		emit signalDispatcher.loadHashSettings(fileName, true);
		return;
	}

	if (name == "pushButton_logout")
	{
		//bool flag = injector.getEnableHash(kLogOutEnable);
		if (injector.isValid())
		{
			//QMessageBox::StandardButton button = QMessageBox::warning(this, tr("logout"), tr("Are you sure you want to logout now?"),
			//	QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
			//if (button == QMessageBox::Yes)
			//{
			injector.setEnableHash(kLogOutEnable, true);
			//}
		}
		return;
	}

	if (name == "pushButton_logback")
	{
		if (injector.isValid())
		{
			//QMessageBox::StandardButton button = QMessageBox::warning(this, tr("logback"), tr("Are you sure you want to logback now?"),
			//	QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
			//if (button == QMessageBox::Yes)
			//{
			injector.setEnableHash(kLogBackEnable, true);
			//}
		}

		return;
	}

	if (name == "pushButton_clear")
	{
		if (injector.isValid() && !injector.server.isNull())
		{
			injector.server->cleanChatHistory();
		}

		return;
	}

	if (name == "pushButton_start")
	{
		onGameStart();
		return;
	}

	if (name == "pushButton_joingroup")
	{
		if (!injector.server.isNull())
			injector.server->setTeamState(true);
		return;
	}

	if (name == "pushButton_leavegroup")
	{
		if (!injector.server.isNull())
			injector.server->setTeamState(false);
		return;
	}

	if (name == "pushButton_dock")
	{
		bool flag = injector.getEnableHash(kWindowDockEnable);
		injector.setEnableHash(kWindowDockEnable, !flag);
		if (flag)
		{
			ui.pushButton_dock->setText(tr("dock"));
		}
		else
		{
			ui.pushButton_dock->setText(tr("undock"));
		}

		return;
	}

	if (name == "pushButton_afksetting")
	{
		if (pAfkForm_ == nullptr)
		{
			std::unique_ptr<AfkForm> _pAfkForm(new AfkForm(currentIndex, nullptr));
			if (_pAfkForm == nullptr)
				return;

			emit _pAfkForm->resetControlTextLanguage();
			_pAfkForm->show();
			pAfkForm_ = _pAfkForm.release();
		}
		else
		{
			if (pAfkForm_->isHidden())
				pAfkForm_->show();
			else
				pAfkForm_->hide();
		}
		return;
	}

	if (name == "pushButton_watch")
	{

		return;
	}

	if (name == "pushButton_eo")
	{
		injector.setEnableHash(kEchoEnable, true);
		return;
	}

	if (name == "pushButton_savesettings")
	{
		QString fileName;
		if (!injector.server.isNull())
			fileName = injector.server->getPC().name;
		SignalDispatcher& signalDispatcher = SignalDispatcher::getInstance(currentIndex);
		emit signalDispatcher.saveHashSettings(fileName);
		return;
	}

	if (name == "pushButton_loadsettings")
	{
		QString fileName;
		if (!injector.server.isNull())
			fileName = injector.server->getPC().name;
		SignalDispatcher& signalDispatcher = SignalDispatcher::getInstance(currentIndex);
		emit signalDispatcher.loadHashSettings(fileName);
		return;
	}

	if (name == "pushButton_set")
	{

	}
}

void GeneralForm::onCheckBoxStateChanged(int state)
{
	QCheckBox* pCheckBox = qobject_cast<QCheckBox*>(sender());
	if (!pCheckBox)
		return;

	bool isChecked = (state == Qt::Checked);

	QString name = pCheckBox->objectName();
	if (name.isEmpty())
		return;

	__int64 currentIndex = getIndex();
	Injector& injector = Injector::getInstance(currentIndex);

	//login
	if (name == "checkBox_autologin")
	{
		injector.setEnableHash(kAutoLoginEnable, isChecked);
		return;
	}

	if (name == "checkBox_autoreconnect")
	{
		injector.setEnableHash(kAutoReconnectEnable, isChecked);
		return;
	}

	//support
	if (name == "checkBox_hidechar")
	{
		injector.setEnableHash(kHideCharacterEnable, isChecked);
		return;
	}

	if (name == "checkBox_closeeffect")
	{
		injector.setEnableHash(kCloseEffectEnable, isChecked);
		return;
	}

	if (name == "checkBox_optimize")
	{
		injector.setEnableHash(kOptimizeEnable, isChecked);
		return;
	}

	if (name == "checkBox_hidewindow")
	{
		injector.setEnableHash(kHideWindowEnable, isChecked);
		if (isChecked)
			injector.hide();
		else
			injector.show();

		return;
	}

	if (name == "checkBox_mute")
	{
		injector.setEnableHash(kMuteEnable, isChecked);
		return;
	}

	if (name == "checkBox_autojoin")
	{
		injector.setEnableHash(kAutoJoinEnable, isChecked);
		__int64 type = injector.getValueHash(kAutoFunTypeValue);
		if (isChecked && type != 0)
		{
			injector.setValueHash(kAutoFunTypeValue, 0);
		}

		SignalDispatcher& signalDispatcher = SignalDispatcher::getInstance(currentIndex);
		emit signalDispatcher.applyHashSettingsToUI();
		return;
	}

	if (name == "checkBox_locktime")
	{
		injector.setEnableHash(kLockTimeEnable, isChecked);
		return;
	}

	if (name == "checkBox_autofreememory")
	{
		injector.setEnableHash(kAutoFreeMemoryEnable, isChecked);
		return;
	}

	//support2
	if (name == "checkBox_fastwalk")
	{
		injector.setEnableHash(kFastWalkEnable, isChecked);
		return;
	}

	if (name == "checkBox_passwall")
	{
		injector.setEnableHash(kPassWallEnable, isChecked);
		return;
	}

	if (name == "checkBox_lockmove")
	{
		injector.setEnableHash(kLockMoveEnable, isChecked);
		injector.sendMessage(kEnableMoveLock, isChecked, NULL);
		return;
	}

	if (name == "checkBox_lockimage")
	{
		injector.setEnableHash(kLockImageEnable, isChecked);
		return;
	}

	if (name == "checkBox_autodropmeat")
	{
		injector.setEnableHash(kAutoDropMeatEnable, isChecked);

		return;
	}

	if (name == "checkBox_autodrop")
	{
		bool bOriginal = injector.getEnableHash(kAutoDropEnable);
		if (bOriginal == isChecked)
			return;

		injector.setEnableHash(kAutoDropEnable, isChecked);

		if (!isChecked)
			return;

		QStringList srcList;
		QStringList dstList;
		QStringList srcSelectList;

		QVariant d = injector.getUserData(kUserItemNames);
		if (d.isValid())
		{
			srcSelectList = d.toStringList();
		}

		QString src = injector.getStringHash(kAutoDropItemString);
		if (!src.isEmpty())
		{
			srcList = src.split(rexOR, Qt::SkipEmptyParts);
		}

		if (!createSelectObjectForm(SelectObjectForm::kAutoDropItem, srcSelectList, srcList, &dstList, this))
			return;

		QString dst = dstList.join("|");
		injector.setStringHash(kAutoDropItemString, dst);

		return;
	}

	if (name == "checkBox_autostack")
	{
		injector.setEnableHash(kAutoStackEnable, isChecked);
		return;
	}

	if (name == "checkBox_knpc")
	{
		injector.setEnableHash(kKNPCEnable, isChecked);
		return;
	}

	if (name == "checkBox_autoanswer")
	{
		injector.setEnableHash(kAutoAnswerEnable, isChecked);
		return;
	}

	if (name == "checkBox_autoeatbean")
	{
		injector.setEnableHash(kAutoEatBeanEnable, isChecked);
		return;
	}

	//battle
	if (name == "checkBox_autowalk")
	{
		if (isChecked)
		{
			ui.checkBox_fastautowalk->setChecked(!isChecked);
		}
		injector.setEnableHash(kAutoWalkEnable, isChecked);
		return;
	}

	if (name == "checkBox_fastautowalk")
	{
		if (isChecked)
		{
			ui.checkBox_autowalk->setChecked(!isChecked);
		}
		injector.setEnableHash(kFastAutoWalkEnable, isChecked);
		return;
	}

	if (name == "checkBox_fastbattle")
	{
		if (isChecked)
		{
			ui.checkBox_autobattle->setChecked(!isChecked);
		}

		bool bOriginal = injector.getEnableHash(kFastBattleEnable);
		injector.setEnableHash(kFastBattleEnable, isChecked);
		if (!bOriginal && isChecked && !injector.server.isNull())
		{
			injector.server->doBattleWork(false);
		}
		return;
	}

	if (name == "checkBox_autobattle")
	{
		if (isChecked)
		{
			ui.checkBox_fastbattle->setChecked(!isChecked);
		}

		bool bOriginal = injector.getEnableHash(kAutoBattleEnable);
		injector.setEnableHash(kAutoBattleEnable, isChecked);
		if (!bOriginal && isChecked && !injector.server.isNull())
		{
			injector.server->doBattleWork(false);
		}

		return;
	}

	if (name == "checkBox_autocatch")
	{
		injector.setEnableHash(kAutoCatchEnable, isChecked);
		return;
	}

	if (name == "checkBox_autoescape")
	{
		injector.setEnableHash(kAutoEscapeEnable, isChecked);
		return;
	}

	if (name == "checkBox_lockattck")
	{
		bool bOriginal = injector.getEnableHash(kLockAttackEnable);
		if (bOriginal == isChecked)
			return;

		injector.setEnableHash(kLockAttackEnable, isChecked);

		if (!isChecked)
			return;

		QStringList srcList;
		QStringList dstList;
		QStringList srcSelectList;

		QVariant d = injector.getUserData(kUserEnemyNames);
		if (d.isValid())
			srcSelectList = d.toStringList();

		for (QString& it : srcSelectList)
		{
			it.prepend("%(ename) == ");
		}

		QString src = injector.getStringHash(kLockAttackString);
		if (!src.isEmpty())
			srcList = src.split(rexOR, Qt::SkipEmptyParts);

		if (!createSelectObjectForm(SelectObjectForm::kLockAttack, srcSelectList, srcList, &dstList, this))
			return;

		QString dst = dstList.join("|");
		injector.setStringHash(kLockAttackString, dst);
		return;
	}

	if (name == "checkBox_lockescape")
	{
		bool bOriginal = injector.getEnableHash(kLockEscapeEnable);
		if (bOriginal == isChecked)
			return;

		injector.setEnableHash(kLockEscapeEnable, isChecked);

		if (!isChecked)
			return;

		QStringList srcList;
		QStringList dstList;
		QStringList srcSelectList;

		QVariant d = injector.getUserData(kUserEnemyNames);
		if (d.isValid())
			srcSelectList = d.toStringList();

		QString src = injector.getStringHash(kLockEscapeString);
		if (!src.isEmpty())
			srcList = src.split(rexOR, Qt::SkipEmptyParts);

		if (!createSelectObjectForm(SelectObjectForm::kLockEscape, srcSelectList, srcList, &dstList, this))
			return;

		QString dst = dstList.join("|");
		injector.setStringHash(kLockEscapeString, dst);
		return;
	}

	if (name == "checkBox_battletimeextend")
	{
		injector.setEnableHash(kBattleTimeExtendEnable, isChecked);
		return;
	}

	if (name == "checkBox_falldownescape")
	{
		injector.setEnableHash(kFallDownEscapeEnable, isChecked);
		return;
	}

	if (name == "checkBox_showexp")
	{
		injector.setEnableHash(kShowExpEnable, isChecked);
		return;
	}

	if (name == "checkBox_autoswitch")
	{
		injector.setEnableHash(kBattleAutoSwitchEnable, isChecked);
		return;
	}

	if (name == "checkBox_battleautoeo")
	{
		injector.setEnableHash(kBattleAutoEOEnable, isChecked);
		return;
	}

	//shortcut switcher
	if (name == "checkBox_switcher_team")
	{
		injector.setEnableHash(kSwitcherTeamEnable, isChecked);
		return;
	}

	if (name == "checkBox_switcher_pk")
	{
		injector.setEnableHash(kSwitcherPKEnable, isChecked);
		return;
	}

	if (name == "checkBox_switcher_card")
	{
		injector.setEnableHash(kSwitcherCardEnable, isChecked);
		return;
	}

	if (name == "checkBox_switcher_trade")
	{
		injector.setEnableHash(kSwitcherTradeEnable, isChecked);
		return;
	}

	if (name == "checkBox_switcher_group")
	{
		injector.setEnableHash(kSwitcherGroupEnable, isChecked);
		return;
	}

	if (name == "checkBox_switcher_family")
	{
		injector.setEnableHash(kSwitcherFamilyEnable, isChecked);
		return;
	}

	if (name == "checkBox_switcher_job")
	{
		injector.setEnableHash(kSwitcherJobEnable, isChecked);
		return;
	}

	else if (name == "checkBox_switcher_world")
	{
		injector.setEnableHash(kSwitcherWorldEnable, isChecked);
		return;
	}
}

void GeneralForm::onSpinBoxValueChanged(int value)
{
	QSpinBox* pSpinBox = qobject_cast<QSpinBox*>(sender());
	if (!pSpinBox)
		return;

	QString name = pSpinBox->objectName();
	if (name.isEmpty())
		return;

	__int64 currentIndex = getIndex();
	Injector& injector = Injector::getInstance(currentIndex);

	if (name == "spinBox_speedboost")
	{
		injector.setValueHash(kSpeedBoostValue, value);
		return;
	}
}

void GeneralForm::onComboBoxCurrentIndexChanged(int value)
{
	ComboBox* pComboBox = qobject_cast<ComboBox*>(sender());
	if (!pComboBox)
		return;

	QString name = pComboBox->objectName();
	if (name.isEmpty())
		return;

	__int64 currentIndex = getIndex();
	Injector& injector = Injector::getInstance(currentIndex);
	if (name == "comboBox_serverlist")
	{
		{
			Config config;
			config.write("System", "Server", "LastServerListSelection", ui.comboBox_serverlist->currentIndex());
		}

		emit ui.comboBox_server->clicked();
		return;
	}

	if (name == "comboBox_server")
	{
		injector.setValueHash(kServerValue, value);
		serverListReLoad();
		return;
	}

	if (name == "comboBox_subserver")
	{
		injector.setValueHash(kSubServerValue, value);
		return;
	}

	if (name == "comboBox_position")
	{
		injector.setValueHash(kPositionValue, value);
		return;
	}

	if (name == "comboBox_locktime")
	{
		injector.setValueHash(kLockTimeValue, value);
		if (ui.checkBox_locktime->isChecked())
			injector.sendMessage(kSetTimeLock, true, value);
		return;
	}

	if (name == "comboBox_paths")
	{
		Config config;
		__int64 current = ui.comboBox_paths->currentIndex();
		if (current >= 0)
			config.write("System", "Command", "LastSelection", ui.comboBox_paths->currentIndex());
		return;
	}
}

void GeneralForm::onApplyHashSettingsToUI()
{
	__int64 currentIndex = getIndex();
	Injector& injector = Injector::getInstance(currentIndex);
	QHash<UserSetting, bool> enableHash = injector.getEnablesHash();
	QHash<UserSetting, __int64> valueHash = injector.getValuesHash();
	QHash<UserSetting, QString> stringHash = injector.getStringsHash();

	{
		Config config;
		__int64 index = config.read<__int64>("System", "Command", "LastSelection");

		if (index >= 0 && index < ui.comboBox_paths->count())
		{
			ui.comboBox_paths->blockSignals(true);
			ui.comboBox_paths->setCurrentIndex(index);
			ui.comboBox_paths->blockSignals(false);
		}
		else if (ui.comboBox_paths->count() > 0)
			ui.comboBox_paths->setCurrentIndex(0);

		__int64 count = config.read<__int64>("System", "Server", "ListCount");
		if (count <= 0)
		{
			count = 3;
			config.write("System", "Server", "ListCount", count);
		}

		ui.comboBox_serverlist->blockSignals(true);

		ui.comboBox_serverlist->clear();
		for (__int64 i = 0; i < count; ++i)
		{
			ui.comboBox_serverlist->addItem(tr("ServerList%1").arg(i + 1), i);
		}

		__int64 lastServerListSelection = config.read<__int64>("System", "Server", "LastServerListSelection");
		if (lastServerListSelection >= 0 && lastServerListSelection < count)
			ui.comboBox_serverlist->setCurrentIndex(lastServerListSelection);
		else if (ui.comboBox_serverlist->count() > 0)
			ui.comboBox_serverlist->setCurrentIndex(0);

		ui.comboBox_serverlist->blockSignals(false);
	}

	__int64 value = 0;

	//login
	value = valueHash.value(kServerValue);
	if (value >= 0 && value < ui.comboBox_server->count())
		ui.comboBox_server->setCurrentIndex(value);
	else
		ui.comboBox_server->setCurrentIndex(0);

	serverListReLoad();

	value = valueHash.value(kSubServerValue);
	if (value >= 0 && value < ui.comboBox_subserver->count())
		ui.comboBox_subserver->setCurrentIndex(value);
	else
		ui.comboBox_subserver->setCurrentIndex(0);

	value = valueHash.value(kPositionValue);
	if (value >= 0 && value < ui.comboBox_position->count())
		ui.comboBox_position->setCurrentIndex(value);
	else
		ui.comboBox_position->setCurrentIndex(0);

	if (enableHash.value(kWindowDockEnable))
		ui.pushButton_dock->setText(tr("undock"));
	else
		ui.pushButton_dock->setText(tr("dock"));

	ui.comboBox_locktime->setCurrentIndex(valueHash.value(kLockTimeValue));
	ui.checkBox_autologin->setChecked(enableHash.value(kAutoLoginEnable));
	ui.checkBox_autoreconnect->setChecked(enableHash.value(kAutoReconnectEnable));

	//support
	ui.checkBox_hidechar->setChecked(enableHash.value(kHideCharacterEnable));
	ui.checkBox_closeeffect->setChecked(enableHash.value(kCloseEffectEnable));
	ui.checkBox_optimize->setChecked(enableHash.value(kOptimizeEnable));
	ui.checkBox_hidewindow->setChecked(enableHash.value(kHideWindowEnable));
	ui.checkBox_mute->setChecked(enableHash.value(kMuteEnable));
	ui.checkBox_autojoin->setChecked(enableHash.value(kAutoJoinEnable));
	ui.checkBox_locktime->setChecked(enableHash.value(kLockTimeEnable));
	ui.checkBox_autofreememory->setChecked(enableHash.value(kAutoFreeMemoryEnable));
	ui.checkBox_showexp->setChecked(enableHash.value(kShowExpEnable));

	//sp
	ui.spinBox_speedboost->setValue(valueHash.value(kSpeedBoostValue));


	//support2
	ui.checkBox_fastwalk->setChecked(enableHash.value(kFastWalkEnable));
	ui.checkBox_passwall->setChecked(enableHash.value(kPassWallEnable));
	ui.checkBox_lockmove->setChecked(enableHash.value(kLockMoveEnable));
	ui.checkBox_lockimage->setChecked(enableHash.value(kLockImageEnable));
	ui.checkBox_autodropmeat->setChecked(enableHash.value(kAutoDropMeatEnable));
	ui.checkBox_autodrop->setChecked(enableHash.value(kAutoDropEnable));
	ui.checkBox_autostack->setChecked(enableHash.value(kAutoStackEnable));
	ui.checkBox_knpc->setChecked(enableHash.value(kKNPCEnable));
	ui.checkBox_autoanswer->setChecked(enableHash.value(kAutoAnswerEnable));
	ui.checkBox_autoeatbean->setChecked(enableHash.value(kAutoEatBeanEnable));

	//battle
	ui.checkBox_autowalk->setChecked(enableHash.value(kAutoWalkEnable));
	ui.checkBox_fastautowalk->setChecked(enableHash.value(kFastAutoWalkEnable));
	ui.checkBox_fastbattle->setChecked(enableHash.value(kFastBattleEnable));
	ui.checkBox_autobattle->setChecked(enableHash.value(kAutoBattleEnable));
	ui.checkBox_autocatch->setChecked(enableHash.value(kAutoCatchEnable));
	ui.checkBox_lockattck->setChecked(enableHash.value(kLockAttackEnable));
	ui.checkBox_autoescape->setChecked(enableHash.value(kAutoEscapeEnable));
	ui.checkBox_lockescape->setChecked(enableHash.value(kLockEscapeEnable));
	ui.checkBox_battletimeextend->setChecked(enableHash.value(kBattleTimeExtendEnable));
	ui.checkBox_falldownescape->setChecked(enableHash.value(kFallDownEscapeEnable));
	ui.checkBox_autoswitch->setChecked(enableHash.value(kBattleAutoSwitchEnable));
	ui.checkBox_battleautoeo->setChecked(enableHash.value(kBattleAutoEOEnable));

	//switcher
	ui.checkBox_switcher_team->setChecked(enableHash.value(kSwitcherTeamEnable));
	ui.checkBox_switcher_pk->setChecked(enableHash.value(kSwitcherPKEnable));
	ui.checkBox_switcher_card->setChecked(enableHash.value(kSwitcherCardEnable));
	ui.checkBox_switcher_trade->setChecked(enableHash.value(kSwitcherTradeEnable));
	ui.checkBox_switcher_group->setChecked(enableHash.value(kSwitcherGroupEnable));
	ui.checkBox_switcher_family->setChecked(enableHash.value(kSwitcherFamilyEnable));
	ui.checkBox_switcher_job->setChecked(enableHash.value(kSwitcherJobEnable));
	ui.checkBox_switcher_world->setChecked(enableHash.value(kSwitcherWorldEnable));
}

void GeneralForm::onGameStart()
{
	ui.pushButton_start->setEnabled(false);
	QMetaObject::invokeMethod(this, "startGameAsync", Qt::QueuedConnection);
}

void GeneralForm::startGameAsync()
{
	do
	{
		QString path = ui.comboBox_paths->currentData().toString();
		if (path.isEmpty())
			break;

		QFileInfo fileInfo(path);
		if (!fileInfo.exists() || fileInfo.isDir() || fileInfo.suffix() != "exe")
			break;

		QString dirPath = fileInfo.absolutePath();
		QByteArray dirPathUtf8 = dirPath.toUtf8();
		qputenv("GAME_DIR_PATH", dirPathUtf8);

		ThreadManager& thread_manager = ThreadManager::getInstance();

		__int64 currentIndex = getIndex();

		Injector& injector = Injector::getInstance(currentIndex);
		injector.currentGameExePath = path;

		std::unique_ptr<Server> _pServer(new Server(currentIndex, this));
		if (_pServer == nullptr)
			break;

		if (!_pServer->start(this))
			break;

		injector.server.reset(_pServer.release());

		MainObject* pMainObject = nullptr;
		if (!thread_manager.createThread(currentIndex, &pMainObject, nullptr) || (nullptr == pMainObject))
			break;

		connect(pMainObject, &MainObject::finished, this, [this]()
			{
				ui.pushButton_start->setEnabled(true);
			}, Qt::QueuedConnection);

		return;
	} while (false);

	ui.pushButton_start->setEnabled(true);
}

void GeneralForm::createServerList()
{
	__int64 currentIndex = getIndex();
	__int64 currentListIndex = ui.comboBox_serverlist->currentIndex();
	if (currentListIndex < 0)
		currentListIndex = 0;
	QStringList list;
	Injector& injector = Injector::getInstance(currentIndex);

	{
		Config config;

		injector.currentServerListIndex = currentListIndex;
		list = config.readArray<QString>("System", "Server", QString("List_%1").arg(currentListIndex));
		if (list.isEmpty())
		{
			static const QStringList defaultListSO = {
				"1|「活动互动」1线|活动电信1线, 活动联通1线, 活动移动1线, 活动海外1线",
				"2|「摆摊交易」4线|摆摊电信4线, 摆摊联通4线, 摆摊移动4线, 摆摊海外4线",
				"3|练级挂机5线|族战电信5线, 族战联通5线, 石器移动5线, 石器海外5线",
				"4|练级挂机6线|石器电信6线, 石器联通6线, 石器移动6线, 石器海外6线",
				"5|「庄园族战」2线|族战电信2线, 族战联通2线, 族战移动2线, 族战海外2线",
				"6|练级挂机7线|石器挂机7线",
				"7|练级挂机8线|石器电信8线, 石器联通8线",
				"8|练级挂机13|电信 13专线, 联通 13专线, 移动 13专线, 海外 13专线",
				"9|「双号副本」3线|石器电信3线, 石器联通3线, 石器移动3线, 石器海外3线",
				"10|「练级副本」9线|石器电信9线, 石器联通9线",
				"11|10 19 20线|挂机 10专线, 备用 10专线, 电信 19专线, 其他 19专线, 电信 20专线, 其他 20专线",
				"12|11 21 22线|挂机 11专线, 备用 11专线, 电信 21专线, 其他 21专线, 电信 22专线, 其他 22专线, 电信 23专线, 其他 23专线",
				"13|全球加速12|电信 12专线, 联通 12专线, 移动 12专线, 港澳台 12线, 美国 12专线",
				"14|14 16 17 18|电信 14专线, 联通移动14线, 移动 14专线, 海外 14专线,电信 16专线, 联通 16专线, 移动 16专线, 海外 16专线, 电信 17专线, 联通 17专线, 移动 17专线, 海外 17专线, 电信 18专线, 联通 18专线, 移动 18专线",
				"15|公司专线15|公司电信15, 公司联通15, 「活动互动」1线, 「摆摊交易」4线",
			};

			static const QStringList defaultListSE = {
				"1|1线∥活动互动|电信活动1线, 联通活动1线, 移动活动1线, 海外活动1线",
				"2|2线∥摆摊交易|电信摆摊2线, 联通摆摊2线, 移动摆摊2线, 海外摆摊2线",
				"3|3线∥庄园族战|电信族战3线, 联通族战3线, 移动族战3线, 海外族战3线",
				"4|4线∥练级挂机|电信练级4线, 联通练级4线, 移动练级4线, 海外练级4线",
				"5|5线∥练级挂机|电信练级5线, 联通练级5线, 移动练级5线, 海外练级5线",
				"6|6线∥练级挂机|电信练级6线, 联通练级6线, 移动练级6线, 海外练级6线",
				"7|7线∥练级挂机|电信练级7线, 联通练级7线, 移动练级7线, 海外练级7线",
				"8|8线∥练级挂机|电信练级8线, 联通练级8线, 移动练级8线, 海外练级8线, 备用练级8线",
				"9|9线∥练级挂机|电信练级9线, 联通练级9线, 移动练级9线, 海外练级9线, 备用练级9线",
				"10|15线∥公司专线|电信公司15线, 联通公司15线, 移动公司15线, 海外公司15线",
				"11|21线∥会员专线|电信会员21线, 联通会员21线, 移动会员21线, 海外会员21线",
				"12|22线∥会员专线|电信会员22线, 联通会员22线, 移动会员22线, 海外会员22线",
			};

			static const QStringList defaultListXGSA = {
				"1|满天星|电信线路, 网通线路",
				"2|薰衣草|电信线路, 网通线路",
				"3|紫罗兰|电信线路, 网通线路",
				"4|风信子|电信线路, 网通线路",
				"5|待宵草|电信线路, 网通线路",
				"6|欧薄菏|电信线路, 网通线路",
				"7|车前草|电信线路, 网通线路",
				"8|石竹花|电信线路, 网通线路",
				"9|勿忘我|电信线路, 网通线路",
			};

			const QList<QStringList> defaultList = {
				defaultListSO,
				defaultListSE,
				defaultListXGSA,
			};

			for (__int64 i = 0; i < defaultList.size(); ++i)
				config.writeArray<QString>("System", "Server", QString("List_%1").arg(i), defaultList.value(i));

			if (currentListIndex >= 0 && currentListIndex < defaultList.size())
				list = defaultList.value(currentListIndex);
		}
	}

	QString currentText = ui.comboBox_server->currentText();
	__int64 current = ui.comboBox_server->currentIndex();

	ui.comboBox_server->setUpdatesEnabled(false);
	ui.comboBox_subserver->setUpdatesEnabled(false);
	ui.comboBox_server->clear();
	ui.comboBox_subserver->clear();

	QStringList serverNameList;
	QStringList subServerNameList;
	for (const QString& it : list)
	{
		QStringList subList = it.split(rexOR, Qt::SkipEmptyParts);
		if (subList.isEmpty())
			continue;

		if (subList.size() != 3)
			continue;

		QString indexStr = subList.takeFirst();
		//檢查是否為數字
		if (indexStr.toLongLong() <= 0)
			continue;

		QString server = subList.takeFirst();

		subList = subList.first().split(rexComma, Qt::SkipEmptyParts);
		if (subList.isEmpty())
			continue;

		serverNameList.append(server);
		subServerNameList.append(subList);

		serverList[currentListIndex].insert(server, subList);
		ui.comboBox_server->addItem(server);
		ui.comboBox_subserver->addItems(subList);
	}

	injector.serverNameList = serverNameList;
	injector.subServerNameList = subServerNameList;

	if (current >= 0)
		ui.comboBox_server->setCurrentIndex(current);
	else
		ui.comboBox_server->setCurrentIndex(0);
	ui.comboBox_subserver->setCurrentIndex(0);
	ui.comboBox_server->setUpdatesEnabled(true);
	ui.comboBox_subserver->setUpdatesEnabled(true);
}

void GeneralForm::serverListReLoad()
{
	__int64 current = ui.comboBox_subserver->currentIndex();
	__int64 currentServerList = ui.comboBox_serverlist->currentIndex();
	if (currentServerList < 0)
		currentServerList = 0;

	ui.comboBox_subserver->setUpdatesEnabled(false);
	ui.comboBox_subserver->clear();
	ui.comboBox_subserver->addItems(serverList.value(currentServerList).value(ui.comboBox_server->currentText()));
	if (current >= 0)
		ui.comboBox_subserver->setCurrentIndex(current);
	else
		ui.comboBox_subserver->setCurrentIndex(0);
	ui.comboBox_subserver->setUpdatesEnabled(true);
}