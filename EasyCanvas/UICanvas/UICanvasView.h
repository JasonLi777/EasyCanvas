#ifndef UICANVASVIEW_H
#define UICANVASVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>

class UICanvasOperBase;
class UICanvasPathItem;
class NDNodeBase;
class UICanvasScene;
class UICanvasView : public QGraphicsView
{
    Q_OBJECT

public:
    enum CanvasMode
    {
        t_ArrowMode,            // 选择编辑模式
        t_FreeDrawMode,         // 自由绘制模式
        t_ImageMode,            // 图片模式
    };

public:
    UICanvasView(QWidget* parent = nullptr);
    ~UICanvasView();

    // 设置操作器
    void setCurrentOperator(UICanvasOperBase* canvasOper);

    // Create Items
    void createImageItem(void);
    void createTextItem(void);
    void createRectItem(void);
    void createEllipseItem(void);
    void createAudioItem(void);

    // 设置选中矩形
    void setSelectedRectVisible(bool isVisible);
    // 设置选中矩形范围
    void setSelectedRect(const QRect& rect);

    // 设置/获取当前模式
    void setCurrentMode(CanvasMode mode);
    CanvasMode getCurrentMode(void);

    // 获取当前选中的Item的节点
    NDNodeBase* getCurrentSelectedNode(void);

    // 获取中心点坐标
    QPointF getCenterPos(void);

    // 保存
    void saveToImage(const QString& imagePath);

    // 清除所有选择
    void cleanAllSelected(void);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

    void drawBackground(QPainter * painter, const QRectF & rect) override;
    void drawForeground(QPainter * painter, const QRectF & rect) override;

private:
    UICanvasScene* m_pScene = nullptr;

    UICanvasPathItem* m_pathItem = nullptr;
    UICanvasOperBase* m_pCurrentOper = nullptr;

    // 选中矩形相关
    bool m_isSelectedRectVisible = false;
    QRect m_selectedRect;
    QColor m_cSelectedPenColor;
    QColor m_cSelectedBrushColor;

    CanvasMode m_mode = t_ArrowMode;
    QPixmap m_penPixmap;

signals:
    void itemSelectedChanged(void);
};

#endif
