#include "ChatHistoryContactEditor.h"
#include "ui_ChatHistoryContactEditor.h"
#include <QPainter>
ChatHistoryContactEditor::ChatHistoryContactEditor(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::ChatHistoryContactEditor();
	ui->setupUi(this);
}

ChatHistoryContactEditor::~ChatHistoryContactEditor()
{
	delete ui;
}

void ChatHistoryContactEditor::paintEvent(QPaintEvent* event)
{
	QPainter painter;
	chco.paint(&painter, rect(), palette());
}
