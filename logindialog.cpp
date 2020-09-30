#include "logindialog.h"
#include "ui_logindialog.h"
#include <QLabel>
#include <QMovie>
#include <functional>
#include "proto.pb.h"
#include "net.h"

LoginDialog::LoginDialog( QWidget* parent) : QDialog(parent), ui(new Ui::LoginDialog){
    ui->setupUi(this);
    connect(ui->loginPushButton, &QPushButton::clicked, this, &LoginDialog::on_loginPushButton_clieked);
    setAttribute(Qt::WA_DeleteOnClose);
    movie = new QMovie(":/5-121204193R0-50.gif");
    ui->loadingLabel->setMovie(movie);
    
    if (this->exec() == QDialog::Accepted)
    {
        std::cout << "accepted" << std::endl;
    }

    
}

LoginDialog::~LoginDialog()
{
   delete ui;
}

void LoginDialog::on_loginSuccessfully()
{
    this->accept();
}

void LoginDialog::on_loginPushButton_clieked()
{
    if (ui->userNameLineEdit->text() == nullptr || ui->passwordLineEdit->text() ==  nullptr)return;
    if (ui->userNameLineEdit->text().trimmed() == "" || ui->passwordLineEdit->text().trimmed() == "")return;

    MyQQ3Proto::C2S_LOGIN c2s_login;
    c2s_login.set_name(ui->userNameLineEdit->text().toStdString());
    c2s_login.set_password(ui->passwordLineEdit->text().toStdString());
    std::string c2s_login_serialized = c2s_login.SerializeAsString();
    std::cout << ui->userNameLineEdit->text().toStdString() << endl;
    websocket_endpoint::instance().send(c2s_login_serialized, message_type::C2S_LOGIN);
    movie->start();
    ui->loginPushButton->setEnabled(false);
    connect(&websocket_endpoint::instance(), &websocket_endpoint::loginDone2, this, &LoginDialog::on_loginSuccessfully);

}