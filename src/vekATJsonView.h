#ifndef VEKATJSONVIEW_H
#define VEKATJSONVIEW_H

#include <QComboBox>

class vekATJsonView: public QComboBox
{
    Q_OBJECT
public:
   explicit vekATJsonView(QWidget *parent = 0);
signals:
    void resize_signal(QRect );

public slots:

public:

    void resizeEvent(QResizeEvent *);
    class ComboBoxBuild
    {
    public:
        ComboBoxBuild(QWidget *parent) :
            parent(parent),
            comboBox(NULL),
            view(NULL),
            model(NULL)
        {
        }

        void setView(QAbstractItemView *itemView)
        {
            this->view = itemView;
        }

        void setModel(QAbstractItemModel *model)
        {
            this->model = model;
        }

        vekATJsonView *build()
        {
            if( !model || !view)
            comboBox = new vekATJsonView(parent);
            comboBox->setModel(model);
            comboBox->setView(view);
            comboBox->view = view;
            comboBox->model = model;
            return comboBox;
        }
    private:
        QWidget *parent;
        vekATJsonView *comboBox;
        QAbstractItemView *view;
        QAbstractItemModel *model;
    };

private:
    QAbstractItemView *view;
    QAbstractItemModel *model;
};

#endif // VEKATJSONVIEW_H
