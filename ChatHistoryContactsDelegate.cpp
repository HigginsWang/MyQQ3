#include "ChatHistoryContactsDelegate.h"
#include <iostream>
#include <QPainter>
#include "ChatRecordOverview.h"
#include "ChatHistoryContactEditor.h"
#include <QPushButton>
#include <QMouseEvent>
ChatHistoryContactsDelegate::~ChatHistoryContactsDelegate()
{
}

ChatHistoryContactsDelegate::ChatHistoryContactsDelegate(QObject* parent) : QStyledItemDelegate(parent)
{

}

//QWidget* ChatHistoryContactsDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
//{
//	std::cout << "isherevvvvvvvvvvvvvvvvv?" << std::endl;
//	if (index.data().canConvert<ChatRecordOverview>()) {
//		ChatHistoryContactEditor* editor = new ChatHistoryContactEditor(parent);
//		
//		return editor;
//	}
//	return nullptr;
//}

void ChatHistoryContactsDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (option.state & QStyle::State_Sunken)std::cout << "cout" << std::endl;
	if (index.data().canConvert<ChatRecordOverview>()) {
		ChatRecordOverview chatRecordOverview = qvariant_cast<ChatRecordOverview>(index.data());

		//if (option.state & QStyle::State_Selected) painter->fillRect(option.rect, option.palette.highlight());

		chatRecordOverview.paint(painter, option.rect, option.palette);//StarRating::EditMode::ReadOnly);
	}
	else {
		QStyledItemDelegate::paint(painter, option, index);
	}
	//QStyledItemDelegate::paint(painter, option, index);
}

//void ChatHistoryContactsDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
//{
//}
//
//void ChatHistoryContactsDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
//{
//}

QSize ChatHistoryContactsDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	return QSize(314, 80);
}

bool ChatHistoryContactsDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
	QRect rect = QRect(option.rect.left() ,  option.rect.top(), option.rect.width(), option.rect.height());
	QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
	if (event->type() == QEvent::MouseButtonPress && rect.contains(mouseEvent->pos()))
	{
		std::cout << "good" << std::endl;
	}
	return QStyledItemDelegate::editorEvent(event, model, option, index);
}

//void ChatHistoryContactsDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
//{
//}
