#pragma once

#include <QWidget>
#include <QVariant>
#include <QMetaType>
#include <QImage>
//namespace Ui { class ChatRecordOverview; };

class ChatRecordOverview //: public QWidget
{
	//Q_OBJECT

public:
	//explicit ChatRecordOverview(QWidget *parent = Q_NULLPTR);
	explicit ChatRecordOverview(){}
	explicit ChatRecordOverview(QString userSendName_, QString content_, QImage image_);
	~ChatRecordOverview();
	void setUserSendName(QString userSendName_);
	void setContent(QString content_);
	void setQImage(QImage image_);

	void paint(QPainter* painter, const QRect& rect, const QPalette& palette) const;
    
	QString getUserSendName() { return userSendName; }
	QString getContent() { return content; }
	QImage getImage() { return image; }
private:
	//Ui::ChatRecordOverview *ui;
	QString userSendName;
	QString content;
	QImage image;
	
};
Q_DECLARE_METATYPE(ChatRecordOverview)