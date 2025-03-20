#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QDialog>
#include <QToolBar>
#include <QStatusBar>
#include <QDebug>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QFileDialog>

#include <QSqlDatabase>   // 数据库核心类
#include <QSqlQuery>      // 数据库操作类
#include <QSqlError>      // 错误处理类

#include "mywidget.h"

struct WidgetPrivate
{
    QMenu *fileMenu;
    QToolBar *toolsMenu;
    QStatusBar *statsMenu;
    QPushButton *Btn;
    QPushButton *fileBtn;
    QTableWidget *tableWidget;
    MyWidget *myWidget;
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    p(new WidgetPrivate)
{
    ui->setupUi(this);

    setWindowTitle(" 界面程序 -（江禹锋）- 25/3/17 ");

    // 创建菜单栏
    p->fileMenu = menuBar()->addMenu("菜单栏");
    p->toolsMenu = addToolBar("工具栏");
    p->statsMenu = statusBar();

    setFirstMenu();
    setSecondMenu();
    setThirdMenu();
    setTable();

    p->Btn = new QPushButton("表格倒序",this);
    p->Btn->move(0,450);

    p->fileBtn = new QPushButton("写入",this);
    p->fileBtn->move(0,500);

    connect(p->Btn,&QPushButton::clicked,this,&MainWindow::handleBtn);
    connect(p->fileBtn,&QPushButton::clicked,this,&MainWindow::handleFileBtn);

//    QSqlDatabase db;
//    // 使用SQLite数据库
//    db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("127.0.0.1");
//    db.setUserName("admin");
//    db.setPassword("123456");
//    db.setPort(3306);
//    db.setDatabaseName("数据库表1");

//    if(db.open())
//    {
//        qDebug()<<"success";
//    }
//    else
//    {
//        qDebug()<<"error:"<<db.lastError();
//    }



//    p->myWidget->show();


}

MainWindow::~MainWindow()
{
    delete ui;
    delete p;
}

void MainWindow::setFirstMenu()
{
    //创建二级菜单
    QMenu *menuFile = new QMenu("文件");
    QMenu *menuView = new QMenu("视图");
    QMenu *menuSet = new QMenu("设置");
    QMenu *menuHelp = new QMenu("帮助");

    p->fileMenu->addMenu(menuFile);
    p->fileMenu->addMenu(menuView);
    p->fileMenu->addMenu(menuSet);
    p->fileMenu->addMenu(menuHelp);

    //创建三级菜单
    QMenu *newPage = new QMenu("打开新页面");

    menuView->addMenu(newPage);

    QAction *action = new QAction("打开新页面"); // 菜单动作
    newPage->addAction(action);
    connect(action, &QAction::triggered, this, &MainWindow::newPageFunc);
}

void MainWindow::setSecondMenu()
{
    //创建工具栏的菜单
    QAction *action1 = new QAction("输出1");
    QAction *action2 = new QAction("输出2");
    QAction *action3 = new QAction("输出3");
    QAction *action4 = new QAction("输出4");
    QAction *action5 = new QAction("输出5");

    QList<QAction*> actions = {action1, action2, action3, action4, action5};

    for(int i=1;i<=5;i++)
        p->toolsMenu->addAction(actions[i-1]);

    action1->setIcon(QIcon(":/pic/blueTable.png"));
    action2->setIcon(QIcon(":/pic/pdf.png"));
    action3->setIcon(QIcon(":/pic/picture.png"));
    action4->setIcon(QIcon(":/pic/put.png"));
    action5->setIcon(QIcon(":/pic/table.png"));


    // 连接信号与槽
    connect(action1, &QAction::triggered, this, [=](){
        qDebug() << "输出111" ;
    });
    connect(action2, &QAction::triggered, this, [=](){
        qDebug() << "输出222" ;
    });
    connect(action3, &QAction::triggered, this, [=](){
        qDebug() << "输出333" ;
    });
    connect(action4, &QAction::triggered, this, [=](){
        qDebug() << "输出444" ;
    });
    connect(action5, &QAction::triggered, this, [=](){
        qDebug() << "输出555" ;
    });
}

void MainWindow::setThirdMenu()
{
    QLabel* label1 = new QLabel("状态1");
    label1->setAlignment(Qt::AlignLeft);       //左对齐

    QLabel* label2 = new QLabel("    状态2");
    label2->setAlignment(Qt::AlignRight);       //右对齐
    QLabel* label3 = new QLabel("    状态3");
    label3->setAlignment(Qt::AlignRight);       //右对齐

    p->statsMenu->addWidget(label1);
    p->statsMenu->addWidget(label2);
    p->statsMenu->addWidget(label3);

}

void MainWindow::setTable()
{
    //添加一个 8 行 5 列的表格
    p->tableWidget = new QTableWidget(8,5,this);

    p->tableWidget->resize(520,350);
    p->tableWidget->move(0,78);
    //设置表格中每一行的表头
    p->tableWidget->setHorizontalHeaderLabels(QStringList() << "语文" << "数学" << "英语" << "平均分" << "总分");

    p->tableWidget->setColumnWidth(0, 100);
    p->tableWidget->setColumnWidth(1, 100);
    p->tableWidget->setColumnWidth(2, 100);
    p->tableWidget->setColumnWidth(3, 100);
    p->tableWidget->setColumnWidth(4, 100);


}

void MainWindow::newPageFunc()
{
    QDialog *newWindow = new QDialog(this);
    newWindow->setWindowTitle("新窗口");
    newWindow->resize(300, 200);
    newWindow->show();
}

void MainWindow::handleBtn()
{
    // 倒序
    int rowCount = p->tableWidget->rowCount();
    int colCount = p->tableWidget->columnCount();

    // 创建一个二维列表存储所有行数据
    QList<QList<QTableWidgetItem*>> rowsData;

    for (int i = 0; i < rowCount; i++)
    {
        QList<QTableWidgetItem*> row;
        for (int j = 0; j < colCount; j++)
        {
            row.append(p->tableWidget->takeItem(i, j));
        }

        // 将整行数据添加到总列表
        rowsData.append(row);
    }

    // 倒序插入数据
    p->tableWidget->clearContents();
    for (int i = 0; i < rowCount; i++)
    {
        int newRow = rowCount - 1 - i;
        for (int j = 0; j < colCount; j++)
        {
            p->tableWidget->setItem(newRow, j, rowsData[i][j]);
        }
    }
}

void MainWindow::handleFileBtn()
{
    QFileDialog dig;
    QString fileName = QFileDialog::getOpenFileName(this,"选择文件","./","ALL(*.*)、txt(*.txt)");
    qDebug()<<"文件名:" << fileName;


    // 开启线程
    _fileThread = new fileThread(this);
    _fileThread->setFileName(fileName);
    _fileThread->start();
}
