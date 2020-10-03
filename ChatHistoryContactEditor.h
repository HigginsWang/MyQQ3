#pragma once

#include <QWidget>
#include "ChatHistoryContactOverview.h"
#include <iostream>
namespace Ui { class ChatHistoryContactEditor; };

class ChatHistoryContactEditor : public QWidget
{
	Q_OBJECT

public:

	ChatHistoryContactEditor(QWidget *parent = Q_NULLPTR);

	~ChatHistoryContactEditor();

	void paintEvent(QPaintEvent* event) override;

	void mouseReleaseEvent(QMouseEvent* event)
	{
		std::cout << "________________________________________________" << std::endl;
	}
private:
	Ui::ChatHistoryContactEditor *ui;
	ChatHistoryContactOverview chco;
};
