﻿/*
				GNU GENERAL PUBLIC LICENSE
				   Version 2, June 1991
COPYRIGHT (C) Bestkakkoii 2023 All Rights Reserved.
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

*/

#pragma once

#include <QWidget>
#include "ui_battleinfoform.h"
#include <indexer.h>

class BattleInfoForm : public QWidget, public Indexer
{
	Q_OBJECT

public:
	explicit BattleInfoForm(long long index, QWidget* parent);

	virtual ~BattleInfoForm();

private slots:
	void onUpdateTopInfoContents(const QVariant& data);

	void onUpdateBottomInfoContents(const QVariant& data);

	void onUpdateTimeLabelContents(const QString& text);

	void onUpdateLabelCharAction(const QString& text);

	void onUpdateLabelPetAction(const QString& text);

	void onNotifyBattleActionState(long long index, bool left);

	void onBattleTableItemForegroundColorChanged(long long index, const QColor& color);

	void onBattleTableAllItemResetColor();

protected:
	virtual void showEvent(QShowEvent* e) override
	{
		setAttribute(Qt::WA_Mapped);
		QWidget::showEvent(e);
	}

private:
	void updateItemInfoRowContents(TableWidget* tableWidget, const QVariant& data);


private:
	Ui::BattleInfoFormClass ui;
};
