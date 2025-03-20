#include "filethread.h"
#include <QDebug>
#include <QTimer>
#include <QFile>

fileThread::fileThread(QObject *parent)
{
    connect(this,&fileThread::finished,this,&fileThread::deleteLater);
}

fileThread::~fileThread()
{
    // 断开所有监听链接
    disconnect();
    // 结束线程
    requestInterruption();
    quit();
    wait();
    qDebug()<<this<<"析构成功！";
}

void fileThread::setFileName(const QString file)
{
    _filePath = file;
}

void fileThread::run()
{
    qDebug()<<"进入线程";

    QTimer *tim = new QTimer();
    QFile file(_filePath);
    int count = 0;

    // 打开文件
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"文件打开失败"<<_filePath;
        return ;
    }

    QString words = "你好，“文件”\n";



    connect(tim, &QTimer::timeout, [&]()
    {
        if (count < 100)
        {
            file.write(words.toUtf8(), words.toUtf8().size());
            file.flush();
            count++;
            qDebug() << "写入完成，共写入" << count << "次";
        } else
        {
            tim->stop();
            file.close();
            delete tim;
            this->quit();
        }
    });
    tim->start(500);
    // 启动事件循环
    exec();

}
