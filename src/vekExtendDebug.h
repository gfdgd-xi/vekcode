#ifndef VEKEXTENDDEBUG_H
#define VEKEXTENDDEBUG_H

#include "common.h"
#include <QMutex>
namespace Ui {
class vekExtendDebug;
}

class vekExtendDebug : public QDialog
{
    Q_OBJECT

public:
    explicit vekExtendDebug(QWidget *parent = nullptr);
    ~vekExtendDebug();
public slots:
    void ExtendGame(BaseGameData _dataGame);
private:
    Ui::vekExtendDebug *ui;
    QProcess *m_cmd=nullptr;
    QProcess *d_cmd=nullptr;
    BaseGameData _data;
    QMutex mutex;
    void executeArgsEnv(BaseGameData data);
    void exitProc(QString);
private slots:
    void onReadyRead();
signals:
     void _unVekDebug();
};

#endif // VEKDEBUG_H
