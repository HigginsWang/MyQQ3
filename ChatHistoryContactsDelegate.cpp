#include "ChatHistoryContactsDelegate.h"
#include <iostream>
#include <QPainter>
#include "ChatRecordOverview.h"
ChatHistoryContactsDelegate::~ChatHistoryContactsDelegate()
{
}

ChatHistoryContactsDelegate::ChatHistoryContactsDelegate(QObject* parent) : QStyledItemDelegate(parent)
{

}

QWidget* ChatHistoryContactsDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	return nullptr;
}

void ChatHistoryContactsDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.data().canConvert<ChatRecordOverview>()) {
		ChatRecordOverview chatRecordOverview = qvariant_cast<ChatRecordOverview>(index.data());

		//if (option.state & QStyle::State_Selected) painter->fillRect(option.rect, option.palette.highlight());

		chatRecordOverview.paint(painter, option.rect, option.palette);//StarRating::EditMode::ReadOnly);
	}
	else {
		QStyledItemDelegate::paint(painter, option, index);
	}
}

void ChatHistoryContactsDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
}

void ChatHistoryContactsDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
}

QSize ChatHistoryContactsDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	return QSize(314, 80);
}

void ChatHistoryContactsDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
}
