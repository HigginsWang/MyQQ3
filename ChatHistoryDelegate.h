#pragma once

#include <QStyledItemDelegate>
class ChatHistoryDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	ChatHistoryDelegate(QObject *parent = 0);

	~ChatHistoryDelegate();

	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;

	void setEditorData(QWidget* editor, const QModelIndex& index) const Q_DECL_OVERRIDE;

	void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const Q_DECL_OVERRIDE;

	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;

	void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;


};
