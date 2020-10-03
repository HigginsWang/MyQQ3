#pragma once

#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
class ChatHistoryContactsDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:

	ChatHistoryContactsDelegate(QObject* parent = (QObject*)nullptr);

	~ChatHistoryContactsDelegate();// {}

	//QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

	//void setEditorData(QWidget* editor, const QModelIndex& index) const override;

	//void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

	//void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

	bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);
private:

private slots:
};

