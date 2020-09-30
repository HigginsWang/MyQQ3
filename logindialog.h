#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMovie>
QT_BEGIN_NAMESPACE
namespace Ui { class LoginDialog; }
QT_END_NAMESPACE


class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog::LoginDialog(QWidget* parent = nullptr);
    ~LoginDialog();

    
private:
    Ui::LoginDialog *ui;
    QMovie* movie = nullptr;
private slots:
    void on_loginPushButton_clieked();
    void on_loginSuccessfully();
signals:
    void signal_getLoginRetSuccessfully();
    
};

#endif // LOGINDIALOG_H
