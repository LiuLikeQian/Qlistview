#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H
#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QStandardItemModel>

//ItemDta
typedef struct
{
    int ID;
    QString BGKImage;

}ItemData;


class ItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
signals:
    void deleteItem(const QModelIndex &index);   //删除信号

public:

    explicit ItemDelegate(QObject *parent = 0);
    ~ItemDelegate();
/*
    enum ItemType{
        ItemNormal = 0,
        ItemCheck
    };

    enum ButtonStates{
        ButtonNormal = 0,
        ButtonHover,
        ButtonPress
    };

    ItemType PItemType; //图标种类
    ButtonStates PButtonStates; //按钮状态
  */


    //重写重画函数
    void paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const;
    //重写编辑事件
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);


private slots:

    void receiveUrl(ItemData &);

private:
    QPoint mousePonit;  //鼠标位置

    ItemData *PItemData;

};

#endif // ITEMDELEGATE_H
