#include "ChatRecordOverview.h"
//#include "ui_ChatRecordOverview.h"
#include <QPainter>
//ChatRecordOverview::ChatRecordOverview(QWidget *parent)
//	: QWidget(parent)
//{
//	ui = new Ui::ChatRecordOverview();
//	ui->setupUi(this);
//	
//}

ChatRecordOverview::ChatRecordOverview(QString userSendName_, QString content_, QImage image_):
    userSendName(userSendName_),content(content_),image(image_)
{

}

ChatRecordOverview::~ChatRecordOverview()
{
	//delete ui;
}

void ChatRecordOverview::setUserSendName(QString username_)
{
	//ui->username->setText(username);
    userSendName = username_;
}

void ChatRecordOverview::setContent(QString content_)
{
    content = content_;
}

void ChatRecordOverview::setQImage(QImage image_)
{
    image = image_;
}

void ChatRecordOverview::paint(QPainter* painter, const QRect& rect, const QPalette& palette) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    //painter->setPen(Qt::pen);
    //painter->setBrush(mode == EditMode::Editable ?
    //    palette.highlight() :
    //    palette.windowText());
    painter->translate(rect.x(), rect.y());
    painter->drawText(QPoint(65, 20), userSendName);
    painter->drawText(QPoint(65, 50), content);
    painter->drawImage(QPoint(10, 10), image.scaled(QSize(45, 45)));

    painter->restore();
}
