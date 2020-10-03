#include "ChatHistoryContactOverview.h"
#include <QRect>

ChatHistoryContactOverview::ChatHistoryContactOverview()
{
}

ChatHistoryContactOverview::~ChatHistoryContactOverview()
{
}

void ChatHistoryContactOverview::paint(QPainter* painter, const QRect& rect, const QPalette& palette) const
{
	painter->save();
    //painter->setRenderHint(QPainter::Antialiasing, true);
    painter->translate(rect.x(), rect.y());
	painter->drawText(QPoint(5, 5), username);
	painter->drawText(QPoint(5, 30), content);

	painter->restore();
}
