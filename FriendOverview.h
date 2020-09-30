#pragma once

#include <QWidget>
#include <QMetaType>

QT_BEGIN_NAMESPACE
namespace Ui { class FriendOverview; };
QT_END_NAMESPACE
class FriendOverview : public QWidget
{
	Q_OBJECT

public:
	FriendOverview(QWidget *parent = Q_NULLPTR);
	//FriendOverview::FriendOverview(const FriendOverview& fo);
	~FriendOverview();
	void setMarkname(QString markname = "markname");//std::string markname = "markname");
	void setProfile(QString profile = "profile");//std::string profile = "profile");
	QString getMarkname();
	QString getProfile();
private:
	Ui::FriendOverview *ui;

private slots:

};