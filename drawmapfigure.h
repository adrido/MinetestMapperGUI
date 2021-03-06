#ifndef DRAWMAPFIGURE_H
#define DRAWMAPFIGURE_H

#include <QObject>
#include <QPoint>
#include <QColor>
#include <QMetaEnum>
#include <QIcon>

#include "geometry.h"

class DrawMapFigure : public QObject
{

public:
    enum Figure{
        Unknown,
        Arrow,
        Circle,
        Ellipse,
        Line,
        Point,
        Rectangle,
        Text

    };
    Q_ENUM(Figure)

    explicit DrawMapFigure(QObject *parent = nullptr);
    /**
     * @brief DrawMapFigure
     * @param str QString to convert to DrawMapFigure
     * @param parent
     */
    explicit DrawMapFigure(const QString &str, QObject *parent = nullptr);

    explicit DrawMapFigure(QColor color, QObject *parent = nullptr) :
        QObject(parent), color(color) { }

    explicit DrawMapFigure(QPoint point, QColor color, QObject *parent = nullptr) :
        QObject(parent), point(point), color(color) {}

    explicit DrawMapFigure(Geometry *geometry, QColor color, QObject *parent = nullptr) :
        QObject(parent), geometry(geometry), color(color) { }

	~DrawMapFigure()
	{
		delete geometry;
	}

    //DrawMapFigure(const DrawMapFigure &f) {}
    bool requiresPoint() const;
    bool requiresGeometry() const;
    bool requiresText() const;

    QString getString() const;
    QStringList getSplittedString() const;
    bool getUseImageCoordinates() const;

    int getFigureIndex() const;

    QPoint getPoint() const;

    QString getText() const;
    /**
     * @brief getColor
     * @return
     */
    QColor getColor() const;

    static QStringList getFigureList();

    void setFigure(const Figure &value);
    void setFigure(int value);

    void setText(const QString &value);

    void setColor(const QColor &value);

    Geometry* getGeometry();
    void setGeometry(Geometry *value);

    void setUseImageCoordinates(bool value);
    void setPoint(const QString &value);
    void setPoint(const QPoint &value);

    QIcon getIcon() const;
    static QIcon getIcon(Figure figure);

    void setPoint(const QVariant &value);

    Figure getFigure() const;
    Figure getFigure(const QString &str) const;

signals:

public slots:

protected:
    bool useImageCoordinates;
    Figure figure = Unknown;
    QPoint point;
    Geometry *geometry;
    QString text;
    QColor color;
    QMetaEnum metaFigure = QMetaEnum::fromType<Figure>();
private:
    Q_OBJECT
    static QStringList figuresList;
};

#endif // DRAWMAPFIGURE_H
