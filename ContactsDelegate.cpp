#include "ContactsDelegate.h"
#include "FriendOverview.h"
#include <QPainter>

ContactsDelegate::ContactsDelegate(QObject* parent) : QStyledItemDelegate(parent){

}

void ContactsDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QRect rect;
	rect.setWidth(option.rect.width() + 20);
	rect.setHeight(option.rect.height() + 20);
	editor->setGeometry(option.rect);
}

QWidget* ContactsDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	FriendOverview* editor = new FriendOverview(parent);
	setEditorData(editor,index);
	cout << "createEditor" << endl;
	return editor;
}

void ContactsDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	//QVariant value = index.model()->data(index, Qt::DisplayRole);
	int row = index.row();
	QModelIndex qmodeindex = index.model()->index(row, 0);
	QModelIndex qmodeindex2 = index.model()->index(row, 1);
	QString profile = index.model()->data(qmodeindex, Qt::DisplayRole).toString();
	QString markname = index.model()->data(qmodeindex2, Qt::DisplayRole).toString();
	FriendOverview* friendOverview = static_cast<FriendOverview*>(editor);
	friendOverview->setProfile(profile);
	friendOverview->setMarkname(markname);
	cout << "setEditorData" << endl;
}

void ContactsDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	FriendOverview* friendOverview = static_cast<FriendOverview*>(editor);
	
	QString profile = friendOverview->getProfile();
	QString markname = friendOverview->getMarkname();
	int row = index.row();
	QModelIndex qmodeindex = index.model()->index(row, 0);
	QModelIndex qmodeindex2 = index.model()->index(row, 1);
	model->setData(qmodeindex, friendOverview->getProfile(), Qt::FontRole);
	model->setData(qmodeindex2, friendOverview->getMarkname(), Qt::FontRole);
}

void ContactsDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	//FriendOverview* d = new FriendOverview;

	//int row = index.row();
	//QModelIndex qmodeindex = index.model()->index(row, 0);
	//QModelIndex qmodeindex2 = index.model()->index(row, 1);
	//QString profile = index.model()->data(qmodeindex, Qt::EditRole).toString();
	//QString markname = index.model()->data(qmodeindex2, Qt::EditRole).toString();
	//painter->drawText(2, 10, 10, 10, 0, profile );
	//painter->drawText(20, 10, 10, 10, 0, markname);

	QStyledItemDelegate::paint(painter, option, index);
}
