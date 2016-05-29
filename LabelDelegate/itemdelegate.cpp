#include "itemdelegate.h"

#include <QPainter>
#include <QMouseEvent>
#include <QStyledItemDelegate>
#include <QToolTip>
#include <QApplication>
#include <QStyle>
#include <QEvent>
#include <QMessageBox>
#include <QDebug>
#include "homepage.h"

ItemDelegate::ItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
  PItemData = new ItemData;

}

ItemDelegate::~ItemDelegate()
{
    qDebug()<<"delegate is not existed";
}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{


    QStyleOptionViewItem viewOption(option);//用来在视图中画一个item
    //还有个viewOption初始化

    //viewOption.state这个变量保存在绘制控件时使用的样式标志
    if(viewOption.state & QStyle::State_HasFocus)//后者用于指示该控件是否有焦点
    {
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
    }

    QRectF rect;
    rect.setX(option.rect.x());
    rect.setY(option.rect.y());
    rect.setWidth( option.rect.width()-1);
    rect.setHeight(option.rect.height()-1);

    QColor ColorFrame(213,213,213,255);
    painter->setPen(ColorFrame);

    if ( (option.state & QStyle::State_Selected) )//鼠标选中
    {
        painter->drawRect(rect);
    }
    else if ( option.state & QStyle::State_MouseOver)//鼠标滑过的颜色
    {
        painter->drawRect(rect);
    }else//默认
    {

    }



    int height = (viewOption.rect.width());//获取左边矩形的宽度

    QPixmap pixmap = QPixmap(":/image/close_hover.png");
    QPixmap photoBack = QPixmap(":/image/2.png");

    //绘制控件区域以及大小长度宽度
    QRect DeleteRect = QRect(viewOption.rect.left() + viewOption.rect.width()-12, viewOption.rect.top(),12,12);
    QRect BackRect = QRect(viewOption.rect.left() + viewOption.rect.width()-height+4, viewOption.rect.top()+6,50,50);
    //在上述区域画出对应的图片

    painter->drawPixmap(DeleteRect,pixmap);     //画出删除按钮
    //painter->drawPixmap(BackRect,photoBack);  //画出背景图片
    qDebug()<<PItemData->BGKImage<<"paint";
    painter->drawPixmap(BackRect,PItemData->BGKImage);  //画出背景图片

   // painter->drawPixmap(option.rect,QPixmap(Data->BGKImage));//我这获取的路径是绝对的路径


}

bool ItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    //构造一个矩形区域 用于相应删除按钮的操作区域
    QRect decorationRect = QRect(option.rect.left() + option.rect.width()-12, option.rect.top(), 12, 12);

    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);//将事件转换为鼠标事件

    //判断当前事件是鼠标按钮事件，并且鼠标位置是属于当前矩形范围内，就发送deleteItem信号
    if (event->type() == QEvent::MouseButtonPress && decorationRect.contains(mouseEvent->pos()))
    {
        emit deleteItem(index);
        //qDebug()<<"delete";
    }
    //返回编辑事件
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

void ItemDelegate::receiveUrl(ItemData &index)
{
    PItemData = &index;
    qDebug()<<PItemData->BGKImage<<"receiverUrl";
}

