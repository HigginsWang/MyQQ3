#include "ChatRecordOverview.h"
//#include "ui_ChatRecordOverview.h"
#include <QPainter>
#include <QStyle>
#include <QApplication>
#include <QtWidgets\qstyleoption.h>
#include <QRect>
#include <iostream>
#include <QDateTime>
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
    //std::cout << "paintBe:" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz").toStdString() << std::endl;
    painter->save();
    //painter->setRenderHint(QPainter::Antialiasing, true);
    QPixmap pixmap(rect.width(), rect.height());
    pixmap.fill(QColor(0,0,0,0));
  /*  QStyleOptionViewItem item;
    item.rect.setRect(rect.x(), rect.y(), rect.width(), rect.height());
    item.text = content;
    item.textElideMode = Qt::ElideLeft;*/
    painter->translate(rect.x(), rect.y());
    
    painter->drawText(qpointuserSendName, userSendName);
    //std::cout << userSendName.toStdString() + ":" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz").toStdString() << std::endl;
    painter->drawText(qpointContent, content);
    //std::cout << content.toStdString() + ":" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz").toStdString() << std::endl;
    painter->drawImage(qpointImage, image);
    //std::cout << "drawImage:" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz").toStdString() << std::endl;
    //painter->end();
    //QApplication::style()->drawPrimitive(QStyle::PrimitiveElement::PE_Frame, &item, painter, this);
    //QApplication::style()->drawControl()
    painter->drawPixmap(0, 0, pixmap);
    //std::cout << "drawPixmap:" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz").toStdString() << std::endl;
    painter->restore();
}
