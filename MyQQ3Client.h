#pragma once

#include <QtWidgets/QMainWindow>
#include <ui_MyQQ3Client.h>
#include <QtSql/QSql>
#include <Qtsql/QSqlDatabase>
#include <Qtsql/QSqlTableModel>
#include <QDataWidgetMapper>
#include <QTableView>

#include "ContactsDelegate.h"
#include "net.h"
#include <warning.h>
#include <QMessageBox>
#include <QtSql/QSqlRecord>
#include "proto.pb.h"
#include "ChatHistoryQSqlTableModel.h"
#include "ChatHistoryDelegate.h"
#include "ChatHistoryContactsDelegate.h"
#include "ChatHistoryContactsModel.h"
/*
QT_BEGIN_NAMESPACE
namespace Ui { class MyQQ3Client; }
QT_END_NAMESPACE
*/

class MyQQ3Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyQQ3Client(QWidget* parent = Q_NULLPTR);

    ~MyQQ3Client();
private:

    std::string m_userid;

    std::string m_username;

    Ui::MyQQ3ClientClass *ui;

    QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE");

    QSqlTableModel* tableModel = Q_NULLPTR;

    //QTableView *tableView = Q_NULLPTR;

    //ContactsDelegate* contactsDelegatePtr = Q_NULLPTR;


    QDataWidgetMapper* contactsDataMapper = Q_NULLPTR;

    ChatHistoryQSqlTableModel* chatHistoryQSqlTableModel = Q_NULLPTR;

    ChatHistoryDelegate* chatHistoryDelegate = Q_NULLPTR;

    ChatHistoryContactsModel* chatHistoryContactsModel = Q_NULLPTR;

    ChatHistoryContactsDelegate* chatHistoyrContactsDelegate = Q_NULLPTR;

    bool insertContactsRecord();

signals:

private slots:
    void on_loginSuccessfully(QString, QString);

    void on_receive_S2C_GETALLFRIENDSRET(MyQQ3Proto::S2C_GETALLFRIENDSRET);

    void commit();

    void addContact(QVariant user1id, QVariant user1name, QVariant user2id, QVariant user2name, 
        QVariant user2inuser1markname, QVariant user1inuser2markname, QVariant becomefriendtime);
    
    void add();

    void on_setChatTarget_finished_SIGNAL();
};