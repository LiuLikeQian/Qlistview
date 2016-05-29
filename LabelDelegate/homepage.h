#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QLabel>
#include "itemdelegate.h"
#include <QListView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
#include <QSize>
#include <QDebug>
#include <QVariant>
#include <QStringList>
#include <QFileDialog>




class HomePage : public QWidget
{
    Q_OBJECT

signals:
    void sendUrl(ItemData&);

public:
    HomePage(QWidget *parent = 0);
    ~HomePage();
    void releaseData(QStandardItemModel *);

private:
    QStandardItemModel *StandardItemModel;   //模型
    QListView *PhotoListView;                //listview
    QPushButton *AddBtn;                     //添加Btn
    QVBoxLayout *mainLayout;                 //主布局(垂直布局)
    ItemDelegate *PDelegate;                 //委托
    ItemData *PItemData;


private slots:
    void addSlot();                          //添加槽
    void deleteSlot(const QModelIndex &);    //删除槽
    void clickIndex(const QModelIndex &);


};

#endif // HOMEPAGE_H
