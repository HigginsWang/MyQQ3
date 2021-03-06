#include "ChatHistoryQSqlTableModel.h"
#include <QImage>
#include <QDateTime>
#include <iostream>
#include "ChatRecordOverview.h"
ChatHistoryQSqlTableModel::ChatHistoryQSqlTableModel(QObject* parent, QSqlDatabase db )
	: QSqlTableModel(parent,db)
{
	qRegisterMetaType<ChatRecordOverview>("ChatRecordOverview");
	//setHeaderData(2, Qt::Orientation::Horizontal, "", Qt::UserRole + 1);
	//setHeaderData(11, Qt::Orientation::Horizontal, "", Qt::UserRole + 2);

}

QVariant ChatHistoryQSqlTableModel::data(const QModelIndex& index, int role) const
{
	QModelIndex userSendNameIndex = index.model()->index(index.row(), 2);
	QString userSendName = QSqlTableModel::data(userSendNameIndex, role).toString();

	QModelIndex contentIndex = index.model()->index(index.row(), 11);
	QString content = QSqlTableModel::data(contentIndex, role).toString();

	QImage image(":/myqq3_2profile.jpg");
	image = image.scaled(45, 45);
	
	ChatRecordOverview chatRecordOverview(userSendName, content, image);

	return QVariant::fromValue(chatRecordOverview);
}

bool ChatHistoryQSqlTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	ChatRecordOverview chatRecordOverview = qvariant_cast<ChatRecordOverview>(value);
	QString userSendName = chatRecordOverview.getUserSendName();
	QString content = chatRecordOverview.getContent();
	QImage image = chatRecordOverview.getImage();
	return QSqlTableModel::setData(index, value, role);
	//return false;
}

ChatHistoryQSqlTableModel::~ChatHistoryQSqlTableModel()
{

}

void ChatHistoryQSqlTableModel::setChatTarget(QString targetStr)
{
	setFilter("usersendername = '" + targetStr + +"'" + " or userreceivername = " + "'" + targetStr + "'");
	select();
	
	//std::cout << "setChatTarget:" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz").toStdString() << std::endl;
}