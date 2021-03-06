#pragma once

#include <QSqlTableModel>
#include "ChatRecordOverview.h"
class ChatHistoryQSqlTableModel : public QSqlTableModel
{
	Q_OBJECT

public:
	ChatHistoryQSqlTableModel(QObject* parent = nullptr, QSqlDatabase db = QSqlDatabase());


	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;


	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

	~ChatHistoryQSqlTableModel();

private:


signals:
	void setChatTarget_finished_SIGNAL();
	//void setChatTarget_SINGAL(QString targetStr);


	


private slots:

	void setChatTarget(QString targetStr);
};
