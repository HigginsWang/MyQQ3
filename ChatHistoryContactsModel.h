#pragma once

#include <QSqlQueryModel>

class ChatHistoryContactsModel : public QSqlQueryModel
{
	Q_OBJECT

public:
	
	ChatHistoryContactsModel(QObject *parent);

	~ChatHistoryContactsModel();

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

private slots:


signals:
	
};
