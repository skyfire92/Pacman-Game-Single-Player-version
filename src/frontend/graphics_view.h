#pragma once

#include <QGraphicsView>
#include <QTimer>
#include <QElapsedTimer>

class QTimer;

class GraphicsView : public QGraphicsView
{
Q_OBJECT

signals:
    void mousePositionChangedEvent(const QPointF& mousePosition);
    void mouseLeftButtonClicked(const QPointF& mousePosition);

public:
    explicit GraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr);

    void drawForeground(QPainter* painter, const QRectF& rect) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

    void updateViewport();

private slots:
    void updateFPS();

private:
    void initializePainterData();

    QTimer fpsTimer_;
    QElapsedTimer frameTimeTimer_;
    int frameCount_{};
    double currentFPS_{};

    QFont fpsCounterFont_;
    QPen fpsCounterPen_;
};
