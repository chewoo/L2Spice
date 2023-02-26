#include "imageItem.h"

ImageItem::ImageItem()
{
    QGraphicsItem::setAcceptHoverEvents(true);
    deleted = false;
    inputed = false;
}

ImageItem::ImageItem(const QString& s)
{
    pixmap = new QPixmap(s);
    rect = pixmap->rect();
    QGraphicsItem::setAcceptHoverEvents(true);
    deleted = false;
    inputed = false;
    imagePath = s;
}
ImageItem::ImageItem(const QString& s,const QRect &r)
{
    pixmap = new QPixmap(s);
    rect = r;
    QGraphicsItem::setAcceptHoverEvents(true);
    deleted = false;
    inputed = false;
    imagePath = s;
}
void ImageItem::setPixmap(const QString &s)
{
    if(pixmap == nullptr)
    {
        pixmap = new QPixmap(s);
        imagePath = s;
    }
}
void ImageItem::setRect(const QRect &r)
{
    rect = r;
}
void ImageItem::setName(const QString &s)
{
    name = s;
}
void ImageItem::setCharacteristic(const QString &c)
{
    characteristic = c;
}
QString ImageItem::getimagePath()
{
    return imagePath;
}
const QRect& ImageItem::getRect()
{
    return rect;
}
void ImageItem::rotate90(int rotateA)
{
    QTransform trans;
    trans.translate(rect.width()/2,rect.height()/2);
    trans.rotate(rotateA + 90);
    trans.translate(-rect.width()/2,-rect.height()/2);
    this->setTransform(trans);
}
void ImageItem::Delete()
{
    deleted = true;
}
void ImageItem::setInput(bool tf)
{
    inputed = tf;
}
bool ImageItem::getInput()
{
    return inputed;
}
bool ImageItem::getDelete()
{
    return deleted;
}
void ImageItem::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QFont font = painter->font();
    font.setPixelSize(20);
    painter->setFont(font);
    painter->drawPixmap(rect,*pixmap);
    painter->drawText(rect,name);
    QRect crect= rect;
    font.setPixelSize(10);
    painter->setFont(font);
    crect.setX(rect.x()+rect.width()*0.65);
    crect.setY(rect.y()+rect.height()*0.1);
    painter->drawText(crect,characteristic);
}
QRectF ImageItem::boundingRect()const
{
    return rect;
}

void ImageItem::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    QGraphicsItem::mousePressEvent(e);
}

ImageItem::~ImageItem()
{
    delete pixmap;

}
