#ifndef VGIT_H
#define VGIT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class vGit; }
QT_END_NAMESPACE

class vGit : public QWidget
{
    Q_OBJECT

public:
    vGit(QWidget *parent = nullptr);
    ~vGit();

private:
    Ui::vGit *ui;
};
#endif // VGIT_H
