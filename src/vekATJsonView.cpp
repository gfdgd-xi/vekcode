#include "vekATJsonView.h"
#include <QTableView>
vekATJsonView::vekATJsonView(QWidget *parent) :
    QComboBox(parent)
{

}
void vekATJsonView::resizeEvent(QResizeEvent *e)
{
    int row = model->rowCount();
    int column = model->columnCount();
    int width = geometry().width();
    int cell = width / column;
    QTableView *view = static_cast<QTableView *>(this->view);
    for(int i = 0; i < column; i++)
    {
        view->setColumnWidth(i, cell);
    }
    emit resize_signal(geometry());

}
