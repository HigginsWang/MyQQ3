#pragma once
#include <QStyledItemDelegate>
//#include <QModelIndex>
#include <iostream>

using namespace std;

class ContactsDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    
    explicit ContactsDelegate(QObject* parent = Q_NULLPTR);

    using QStyledItemDelegate::QStyledItemDelegate;

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,const QModelIndex& index) const Q_DECL_OVERRIDE;

    void updateEditorGeometry(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;
    
    void setEditorData(QWidget* editor, const QModelIndex& index) const Q_DECL_OVERRIDE;

    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const Q_DECL_OVERRIDE;
    
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;

};

