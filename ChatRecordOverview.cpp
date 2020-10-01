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
    qpointuserSendName.setX(65);
    qpointuserSendName.setY(20);

    qpointContent.setX(65);
    qpointContent.setY(50);

    qpointImage.setX(10);
    qpointImage.setY(10);
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

    painter->translate(rect.x(), rect.y());
    painter->drawText(qpointuserSendName, userSendName);
    painter->drawText(qpointContent, content);
    painter->drawImage(qpointImage, image);
    
    painter->restore();
}
