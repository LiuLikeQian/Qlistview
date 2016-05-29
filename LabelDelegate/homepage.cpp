#include "homepage.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
{
    //控件定义
    PhotoListView = new QListView;
    AddBtn = new QPushButton("add");
    mainLayout = new QVBoxLayout(this);
    StandardItemModel = new QStandardItemModel(this);
    PDelegate = new ItemDelegate(this);
    PItemData = new ItemData;


    PhotoListView->setItemDelegate(PDelegate);       //为视图设置委托
    PhotoListView->setSpacing(10);                   //为视图设置控件间距
    PhotoListView->setModel(StandardItemModel);      //为委托设置模型
    PhotoListView->setViewMode(QListView::IconMode); //设置Item图标显示
    PhotoListView->setDragEnabled(false);            //控件不允许拖动


    //PhotoListView->setStyleSheet("border-image:url(:/image/LabelBack.png);");
    PhotoListView->setStyleSheet("QListView::item:selected{border:1px solid #555555}");

    PhotoListView->setEditTriggers(QAbstractItemView::NoEditTriggers); //双击Item不可编辑

    /*控件布局*/
    mainLayout->addWidget(PhotoListView);
    mainLayout->addWidget(AddBtn);
    resize(400,400);

    /*连接信号与槽*/
    connect(AddBtn,&QPushButton::clicked,this,&HomePage::addSlot);
    connect(PDelegate,&ItemDelegate::deleteItem,this,&HomePage::deleteSlot);
    connect(PhotoListView,&QListView::clicked,this,&HomePage::clickIndex);

    connect(this,SIGNAL(sendUrl(ItemData&)),PDelegate,SLOT(receiveUrl(ItemData&)));

}

HomePage::~HomePage()
{

}

//添加槽
void HomePage::addSlot()
{
    //获取图片
/*
    QStringList Stringlist = QFileDialog::getOpenFileNames(this,"Open file",QDir::currentPath(),tr("(*.png)"));

    if (Stringlist.size() == 0)
    {
        return;
    }
*/



    //PItemData->BGKImage = Stringlist.at(i);

    PItemData->BGKImage = ":/image/2.png";
    PItemData->ID = 0;

    emit sendUrl(*PItemData);



    QStandardItem *Item = new QStandardItem;

    Item->setSizeHint(QSize(60,60));         //设置Item大小为了美观

    QVariant photoUrl(PItemData->BGKImage);

    Item->setData(photoUrl.toString(),Qt::UserRole);

    StandardItemModel->appendRow(Item);      //追加Item


}


/*删除Item*/
void HomePage::deleteSlot(const QModelIndex & index)
{

    PhotoListView->model()->removeRow(index.row());//删除Item
    qDebug()<<"delete sucessfully!!";              //测试

}

void HomePage::clickIndex(const QModelIndex &index)
{
    qDebug()<<index.data(Qt::DecorationRole);

}

void HomePage::releaseData(QStandardItemModel *index)
{
    QStandardItemModel *model = index;
    if(model)
    {
        delete model;
    }
}
