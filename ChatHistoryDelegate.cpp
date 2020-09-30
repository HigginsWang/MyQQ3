#include "ChatHistoryDelegate.h"
#include "ChatRecordOverview.h"
#include <QSize>
#include <QApplication>
#include <QPainter>
ChatHistoryDelegate::ChatHistoryDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{
}

ChatHistoryDelegate::~ChatHistoryDelegate()
{
}

QWidget* ChatHistoryDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	//ChatRecordOverview* editor = new ChatRecordOverview(parent);
	//const QAbstractItemModel* model = index.model();
	//QString username = model->data(model->index(index.row(), 2)).toString();
	//editor->setUsername(username);
	return nullptr;
}

void ChatHistoryDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
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

void ChatHistoryDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	return;
	/*ChatRecordOverview* chatRecordOverview = static_cast<ChatRecordOverview*>(editor);
	const QAbstractItemModel* model = index.model();
	QString username = model->data(model->index(index.row(), 2)).toString();
	chatRecordOverview->setUsername(username);*/
}

QSize ChatHistoryDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	
	QSize size;
	size.setHeight(100);
	size.setWidth(100);
	return size;
}

void ChatHistoryDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	//QStyledItemDelegate::setModelData(editor, model, index);
}

void ChatHistoryDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	editor->setGeometry(option.rect);
}
