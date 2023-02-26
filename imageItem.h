#ifndef IMAGEITEM_H
#define IMAGEITEM_H
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QRect>
#include <QDebug>

class Workspace;

class ImageItem : public QGraphicsItem
{
    private:
        QPixmap *pixmap;
        QString imagePath;
        QRect rect;
        QString name;
        QString characteristic;
        bool deleted;
        bool inputed;
    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent*)override;
    public:
        ImageItem();
        ImageItem(const QString& s);
        ImageItem(const QString& s,const QRect &r);
        void setPixmap(const QString &s);
        void setRect(const QRect &r);
        void setName(const QString &s);
        void setCharacteristic(const QString &c);
        QString getimagePath();
        const QRect& getRect();
        void rotate90(int rotateA);
        void Delete();
        void setInput(bool);
        bool getDelete();
        bool getInput();
        void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;
        QRectF boundingRect()const override;
        ~ImageItem();
    private slots:


};

#endif // IMAGE_H
