#include "MyQQ3Client.h"
#include "ui_MyQQ3Client.h"
//#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QTime>
#include <QDateTime>
#include <QDebug>
#include <QException>
#include <QSqlQuery>
#include "ChatRecordOverview.h"
MyQQ3Client::MyQQ3Client(QWidget* parent) : QMainWindow(parent), ui(new Ui::MyQQ3ClientClass)
{
    ui->setupUi(this);
    qRegisterMetaType<MyQQ3Proto::S2C_GETALLFRIENDSRET>("MyQQ3Proto::S2C_GETALLFRIENDSRET");
    
    connect(&websocket_endpoint::instance(), &websocket_endpoint::loginDone1, this, &MyQQ3Client::on_loginSuccessfully,Qt::ConnectionType::QueuedConnection);

    connect(ui->ChatButton, &QPushButton::clicked, [=]() {ui->mainStackedWidget->setCurrentIndex(0);});
    connect(ui->ContactButton, &QPushButton::clicked, [=]() {ui->mainStackedWidget->setCurrentIndex(1);});
    connect(ui->CollectButton, &QPushButton::clicked, [=]() {ui->mainStackedWidget->setCurrentIndex(2);});
    connect(ui->FileButton, &QPushButton::clicked, [=]() {ui->mainStackedWidget->setCurrentIndex(3);});
    connect(&websocket_endpoint::instance(), &websocket_endpoint::receive_S2C_GETALLFRIENDSRET, this, &MyQQ3Client::on_receive_S2C_GETALLFRIENDSRET,Qt::ConnectionType::QueuedConnection);
    ui->mainStackedWidget->setCurrentIndex(0);
}



void MyQQ3Client::on_loginSuccessfully(QString userid, QString username)
{
    this->show();
    m_userid.assign(userid.toStdString());
    m_username.assign(username.toStdString());


    
    /// <summary>
    /// 初始化数据库
    /// </summary>
    QString fileName(userid + ".db");
    DB.setDatabaseName(fileName);
    if (!DB.open()) { QMessageBox::warning(this, "错误", "打开" + userid + "数据库错误", QMessageBox::Ok, QMessageBox::NoButton); }

    /// <summary>
    /// 初始化好友列表
    /// </summary>
    tableModel = new QSqlTableModel(this);//, DB);
    tableModel->setTable("contacts");
    if (!tableModel->select()) { QMessageBox::warning(this, "错误", "打开contacts数据表错误", QMessageBox::Ok, QMessageBox::NoButton); }
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(tableModel);

    connect(ui->add, &QPushButton::clicked, this, &MyQQ3Client::add);
    connect(ui->commit, &QPushButton::clicked, this, &MyQQ3Client::commit);

    contactsDataMapper = new QDataWidgetMapper(this);
    contactsDataMapper->setModel(tableModel);
    contactsDataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    contactsDataMapper->addMapping(ui->markNameLineEdit, tableModel->fieldIndex("user2inuser1markname"));
    contactsDataMapper->addMapping(ui->MyQQ3NameDisplay, tableModel->fieldIndex("user2name"));
    contactsDataMapper->toFirst();
    //ui->listView->setItemDelegate(contactsDelegatePtr);
    
    /// <summary>
    /// 初始化聊天记录
    /// </summary>
    chatHistoryQSqlTableModel = new ChatHistoryQSqlTableModel(this, DB);
    chatHistoryQSqlTableModel->setTable("chathistory");
    //chatHistoryQSqlTableModel->setQuery(QSqlQuery("select distinct from chathistory "));
    if (!chatHistoryQSqlTableModel->select()) { QMessageBox::warning(this, "错误", "打开chathistory数据表错误", QMessageBox::Ok, QMessageBox::NoButton); }
    chatHistoryQSqlTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    chatHistoryDelegate = new ChatHistoryDelegate(this);
    ui->ChatHistoryListView->setModel(chatHistoryQSqlTableModel);
    ui->ChatHistoryListView->setItemDelegate(chatHistoryDelegate);
    ui->ChatHistoryListView->setEditTriggers(QAbstractItemView::EditTrigger::AllEditTriggers);
    ui->ChatHistoryListView->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);

    //ui->listWidget->setModel(chatHistoryQSqlTableModel);

    /// <summary>
    /// 初始化聊天联系人列表
    /// </summary>
    chatHistoryContactsModel = new ChatHistoryContactsModel(this);
    chatHistoryContactsModel->setQuery(QSqlQuery("select userreceivername as dufiang, content from (select * from (select userreceivername , content  from (select *from chathistory order by chatrecordsendtimestamp desc) where sendorreceive = 0  group by userreceivername) union select * from (select usersendername , content from chathistory where sendorreceive = 1  group by usersendername order by chatrecordreceiverreceivetimestamp desc)) group by userreceivername;"));
    ui->chatHistoryContactsListView->setModel(chatHistoryContactsModel);
    ui->chatHistoryContactsListView->setItemDelegate(chatHistoyrContactsDelegate  = new ChatHistoryContactsDelegate);


    connect(
        chatHistoyrContactsDelegate,
        SIGNAL(setChatTarget_SINGAL(QString)),
        chatHistoryQSqlTableModel, 
        SLOT(setChatTarget(QString))
    );
    //connect(chatHistoryQSqlTableModel, SIGNAL(setChatTarget_SINGAL(QString)), chatHistoryQSqlTableModel, ));
    //connect(chatHistoryQSqlTableModel, SIGNAL(setChatTarget_finished_SIGNAL), this, SLOT(on_setChatTarget_finished_SIGNAL));
    /// <summary>
    /// 发送消息请求好友列表
    /// </summary>
    MyQQ3Proto::C2S_GETALLFRIENDS c2s_getallfriends;
    c2s_getallfriends.set_userid(m_userid);
    websocket_endpoint::instance().send(c2s_getallfriends.SerializeAsString(), message_type::C2S_GETALLFRIENDS);

}

    
MyQQ3Client::~MyQQ3Client()
{
    if (ui != nullptr)delete ui;
    DB.close();
}

bool MyQQ3Client::insertContactsRecord()//QString id, QString timestamp)
{

    //cout << tableModel->database().transaction() << endl;
    QSqlRecord rd = tableModel->record(1);
    rd.setValue("id", tableModel->rowCount() + 1);
    rd.setValue("becomefriendtime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    bool result = tableModel->insertRecord(-1, rd);
    cout << tableModel->submitAll() << endl;
    //cout << tableModel->database().commit() << endl;
    return result;
}

void MyQQ3Client::on_receive_S2C_GETALLFRIENDSRET(MyQQ3Proto::S2C_GETALLFRIENDSRET s2c_getallfriendsret)
{
    if (tableModel == Q_NULLPTR)return;
    tableModel->removeRows(0,tableModel->rowCount());
    tableModel->submitAll();
    cout << "void MyQQ3Client::on_receive_S2C_GETALLFRIENDSRET(MyQQ3Proto::S2C_GETALLFRIENDSRET s2c_getallfriendsret)" << endl;
    if (tableModel == Q_NULLPTR) {
        return;
    }
    auto t = s2c_getallfriendsret.mutable_friends(); 
    for (auto it = t->begin(); it != t->end(); ++it)
    {
        QString becomefriendtime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        
        addContact(
            QString::fromStdString(s2c_getallfriendsret.userid()), 
            QString::fromStdString(s2c_getallfriendsret.username()),
            QString::fromStdString(it->userid()), 
            QString::fromStdString(it->username()), 
            QString::fromStdString(""),
            QString::fromStdString(""), 
                becomefriendtime);
    }
   
}

void MyQQ3Client::commit()
{
    cout << tableModel->submitAll() << endl;
    cout << tableModel->lastError().text().toStdString() << endl;
}

void MyQQ3Client::add()
{
    if (tableModel == Q_NULLPTR)return;
    QSqlRecord rdd = tableModel->record();
    rdd.setValue("id", tableModel->rowCount() + 1);
    rdd.setValue("user1id", "myqq3_1");
    rdd.setValue("user1name", "wangxiaojie");
    rdd.setValue("user2id", "liuyifei");
    rdd.setValue("user2name", "liuyifei");
    rdd.setValue("user2inuser1markname", "wangxiaojie");
    rdd.setValue("user1inuser2markname", "liuyifei");
    rdd.setValue("becomefriendtime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    cout << tableModel->insertRecord(-1, rdd) << endl;
    cout << tableModel->lastError().text().toStdString() << endl;
    cout << tableModel->submitAll() << endl;
}

void MyQQ3Client::on_setChatTarget_finished_SIGNAL()
{
    if (chatHistoryQSqlTableModel != nullptr)chatHistoryQSqlTableModel->select();
}

void MyQQ3Client::addContact(QVariant user1id, QVariant user1name, QVariant user2id, QVariant user2name, QVariant user2inuser1markname, QVariant user1inuser2markname, QVariant becomefriendtime)
{
    if (tableModel == Q_NULLPTR)return;
    QSqlRecord rdd = tableModel->record();
    rdd.setValue("id", tableModel->rowCount() + 1);
    rdd.setValue("user1id", user1id);
    rdd.setValue("user1name", user1name);
    rdd.setValue("user2id", user2id);
    rdd.setValue("user2name", user2name);
    rdd.setValue("user2inuser1markname", user2inuser1markname);
    rdd.setValue("user1inuser2markname", user1inuser2markname);
    rdd.setValue("becomefriendtime", becomefriendtime);
    
    cout <<  tableModel->insertRecord(-1, rdd) << endl;
    cout << tableModel->lastError().text().toStdString() << endl;
    cout << tableModel->submitAll() << endl;
}
