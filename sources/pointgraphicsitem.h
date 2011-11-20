/*
 * pointgraphicsitem.h
 *
 *  Created on: 24.01.2011
 *      Author: ZooNer
 */

#ifndef POINTGRAPHICSITEM_H_
#define POINTGRAPHICSITEM_H_

#include <QGraphicsItem>
#include "scgpointobject.h"

class PointGraphicsItem:public QGraphicsItem
{
public:
    enum { Type = UserType + 6 };
    /*!
     *
     * @param parent SCgPointObject, controlled by this item.
     * @param pointIndex Index of Point in mPoints vector of SCgPointObject.
     */
    PointGraphicsItem(SCgPointObject* parent, int pointIndex);
    virtual ~PointGraphicsItem();

    //! @see QGraphicsItem::type()
    int type() const
    {
        return Type;
    }

    //! Sets new index for point, that controlled by this item.
    void setPointIndex(int index)
    {
        mPointIndex = index;
    }

    //! @return object which is controlled by this item.
    SCgPointObject* parentSCgPointObject() const
    {
        return mParent;
    }

    //! @return controlled point's index.
    int pointIndex() const
    {
        return mPointIndex;
    }

protected:
    //! @see QGraphicsItem::boundingRect
    QRectF boundingRect() const;
    //! @see QgraphicsItem::shape()
    QPainterPath shape() const;
    //! @see QGraphicsItem::paint()
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //! @see QGraphicsItem::ItemChange()
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);


    //! Size of point. (different values for different types of parent)
    QSizeF mSize;
    //! Pointer to parent object.
    SCgPointObject* mParent;
    //! Point index in mPoints vector, that controlled by this object.
    int mPointIndex;
    //! Point color
    QColor mColor;
};


class IncidencePointGraphicsItem:public PointGraphicsItem
{
public:
    enum { Type = UserType + 7 };
    /*!
     *
     * @param parent SCgPointObject, controlled by this item.
     * @param pointIndex Index of Point in mPoints vector of SCgPointObject.
     */
    IncidencePointGraphicsItem(SCgPointObject* parent, int pointIndex);
    virtual ~IncidencePointGraphicsItem();

    //! Returns object behind this point (except parent)
    SCgObject* objectAtPoint() const;

    SCgPointObject::IncidentRole role() const
    {
        return mPointIndex ? SCgPointObject::IncidentEnd : SCgPointObject::IncidentBegin;
    }

    //! @see SCgPointObject::isAcceptable;
    bool canBeFixed() const
    {
        return mParent->isAcceptable(objectAtPoint(),role());
    }

    //! @see QGraphicsItem::type()
    int type() const
    {
        return Type;
    }

protected:

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
    {
        mParent->updatePosition();
        QGraphicsItem::mouseReleaseEvent(event);
    }
    //! @see QGraphicsItem::ItemChange()
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif /* POINTGRAPHICSITEM_H_ */
