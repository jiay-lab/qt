#ifndef FILETHREAD_H
#define FILETHREAD_H

#include <QThread>

class fileThread : public  QThread
{
    Q_OBJECT
public:
    explicit fileThread(QObject *parent = nullptr);
    ~fileThread() override;

    void setFileName(const QString file);
private:
    void run() override;

private:
    QString _filePath;
};

#endif // FILETHREAD_H
