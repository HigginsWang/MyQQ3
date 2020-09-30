#include "FriendOverview.h"
#include "ui_FriendOverview.h"

FriendOverview::FriendOverview(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::FriendOverview();
	ui->setupUi(this);
}

//FriendOverview::FriendOverview(const FriendOverview& fo)
//{
//	ui = new Ui::FriendOverview();
//	ui->setupUi(this);
//	ui->markname->setText("dkl");
//}
FriendOverview::~FriendOverview()
{
	delete ui;
}

void FriendOverview::setMarkname(QString markname)
{
	ui->markname->setText(markname);
}

//void FriendOverview::setMarkname(QString markname);//std::string markname)
//{
//	//QString value;
//	//value.fromStdString(markname);
//	//ui->profile->setText("TEXT::::::::");
//	ui->markname->setText(markname);
//}

void FriendOverview::setProfile(QString profile)//std::string profile)
{
	//QString value;
	//value.fromStdString(profile);
	ui->profile->setText(profile);
}

QString FriendOverview::getMarkname()
{
	return ui->markname->text();
	//return QString();
}

QString FriendOverview::getProfile()
{
	return ui->profile->text();
}
