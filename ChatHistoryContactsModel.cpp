#include "ChatHistoryContactsModel.h"
#include "ChatHistoryContactOverview.h"
#include <QImage>
#include "ChatRecordOverview.h"
ChatHistoryContactsModel::ChatHistoryContactsModel(QObject *parent)
	: QSqlQueryModel(parent)
{
}

ChatHistoryContactsModel::~ChatHistoryContactsModel()
{
}

QVariant ChatHistoryContactsModel::data(const QModelIndex& index, int role) const
{
	QModelIndex userSendNameIndex = index.model()->index(index.row(), 0);
	QString userName = QSqlQueryModel::data(userSendNameIndex, role).toString();

	QModelIndex contentIndex = index.model()->index(index.row(), 1);
	QString content = QSqlQueryModel::data(contentIndex, role).toString();

	QImage image(":/myqq3_2profile.jpg");
	image = image.scaled(45, 45);

	ChatRecordOverview chatRecordOverview(userName, content, image);

	return QVariant::fromValue(chatRecordOverview);
	return QVariant();
}

bool ChatHistoryContactsModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	ChatRecordOverview chatRecordOverview = qvariant_cast<ChatRecordOverview>(value);
	QString userSendName = chatRecordOverview.getUserSendName();
	QString content = chatRecordOverview.getContent();
	QImage image = chatRecordOverview.getImage();
	return QSqlQueryModel::setData(index, value, role);
}
