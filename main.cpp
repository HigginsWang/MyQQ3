#include "MyQQ3Client.h"
#include "logindialog.h"
#include <QtWidgets/QApplication>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>
#include <QDialog>
#include <QEvent>
#include <QException>
#include <QTextCodec>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "dataStructure.h"
#include "net.h"
#include "Main.h"
int main(int argc, char *argv[]) 
{
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    boost::uuids::uuid uid = boost::uuids::random_generator()();
    const string uid_str = boost::uuids::to_string(uid);

    cout << uid_str << endl;
    try {
        websocket_endpoint::instance().connect("ws://localhost:9002");

        QApplication a(argc, argv);
        MyQQ3Client* w = new MyQQ3Client;

        LoginDialog* l = new LoginDialog;
        return a.exec();

    }
    catch (std::exception e)
    {
        cout << e.what() << endl;
    }
    
    
}
