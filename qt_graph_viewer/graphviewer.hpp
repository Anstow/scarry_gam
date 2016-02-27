#ifndef GRAPHVIEWER_HPP
#define GRAPHVIEWER_HPP

#include <QMainWindow>

namespace Ui {
class GraphViewer;
}

class GraphViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphViewer(QWidget *parent = 0);
    ~GraphViewer();

private:
    Ui::GraphViewer *ui;
};

#endif // GRAPHVIEWER_HPP
