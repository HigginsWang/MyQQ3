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

#include "dataStructure.h"
#include "net.h"
#include "Main.h"
int main(int argc, char *argv[]) 
{
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    

    //cout << uid_str << endl;
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
