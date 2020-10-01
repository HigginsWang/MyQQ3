#pragma once
#include <QPainter>

class ChatHistoryContactOverview {

public:

	ChatHistoryContactOverview();

	~ChatHistoryContactOverview();

	void paint(QPainter* painter, const QRect& rect, const QPalette& palette) const;

	void setUserName(QString username_) { username = username_; }

	void setContent(QString content_) { content = content_; }
	
	QString getUserName() { return username; }
	
	QString getContent() { return content; }

	void setQImage(QImage image_) { image = image_; }

	QImage getImage() { return image; }
private:

	QString username;

	QString content;

	QImage image;
};
