/************************************************************************
 * This file has been generated automatically from                      *
 *                                                                      *
 * src/core/geometry/qgscurve.h                                         *
 *                                                                      *
 * Do not edit manually ! Edit header and run scripts/sipify.pl again   *
 ************************************************************************/





class QgsCurve: QgsAbstractGeometry
{
%Docstring
 Abstract base class for curved geometry type
.. versionadded:: 2.10
%End

%TypeHeaderCode
#include "qgscurve.h"
%End
  public:
    QgsCurve();

    virtual bool operator==( const QgsCurve &other ) const = 0;
    virtual bool operator!=( const QgsCurve &other ) const = 0;
%Docstring
 :rtype: bool
%End

    virtual QgsCurve *clone() const = 0 /Factory/;

    virtual QgsPointV2 startPoint() const = 0;
%Docstring
 Returns the starting point of the curve.
.. seealso:: endPoint
 :rtype: QgsPointV2
%End

    virtual QgsPointV2 endPoint() const = 0;
%Docstring
 Returns the end point of the curve.
.. seealso:: startPoint
 :rtype: QgsPointV2
%End

    virtual bool isClosed() const;
%Docstring
 Returns true if the curve is closed.
 :rtype: bool
%End

    virtual bool isRing() const;
%Docstring
 Returns true if the curve is a ring.
 :rtype: bool
%End

    virtual QgsLineString *curveToLine( double tolerance = M_PI_2 / 90, SegmentationToleranceType toleranceType = MaximumAngle ) const = 0 /Factory/;
%Docstring
 Returns a new line string geometry corresponding to a segmentized approximation
 of the curve.
 \param tolerance segmentation tolerance
 \param toleranceType maximum segmentation angle or maximum difference between approximation and curve*
 :rtype: QgsLineString
%End

    virtual void addToPainterPath( QPainterPath &path ) const = 0;
%Docstring
 Adds a curve to a painter path.
%End

    virtual void drawAsPolygon( QPainter &p ) const = 0;
%Docstring
 Draws the curve as a polygon on the specified QPainter.
 \param p destination QPainter
%End

    virtual void points( QgsPointSequence &pt /Out/ ) const = 0;
%Docstring
 Returns a list of points within the curve.
%End

    virtual int numPoints() const = 0;
%Docstring
 Returns the number of points in the curve.
 :rtype: int
%End

    virtual void sumUpArea( double &sum /Out/ ) const = 0;
%Docstring
 Sums up the area of the curve by iterating over the vertices (shoelace formula).
%End

    virtual QgsCoordinateSequence coordinateSequence() const;
    virtual bool nextVertex( QgsVertexId &id, QgsPointV2 &vertex /Out/ ) const;

    virtual bool pointAt( int node, QgsPointV2 &point /Out/, QgsVertexId::VertexType &type /Out/ ) const = 0;
%Docstring
 Returns the point and vertex id of a point within the curve.
 \param node node number, where the first node is 0
 \param point will be set to point at corresponding node in the curve
 \param type will be set to the vertex type of the node
 :return: true if node exists within the curve
 :rtype: bool
%End

    virtual QgsCurve *reversed() const = 0 /Factory/;
%Docstring
 Returns a reversed copy of the curve, where the direction of the curve has been flipped.
.. versionadded:: 2.14
 :rtype: QgsCurve
%End

    virtual QgsAbstractGeometry *boundary() const /Factory/;

    virtual QgsCurve *segmentize( double tolerance = M_PI_2 / 90, SegmentationToleranceType toleranceType = MaximumAngle ) const /Factory/;

%Docstring
 Returns a geometry without curves. Caller takes ownership
 \param tolerance segmentation tolerance
 \param toleranceType maximum segmentation angle or maximum difference between approximation and curve*
 :rtype: QgsCurve
%End

    virtual int vertexCount( int part = 0, int ring = 0 ) const;
    virtual int ringCount( int part = 0 ) const;
    virtual int partCount() const;
    virtual QgsPointV2 vertexAt( QgsVertexId id ) const;

    virtual QgsRectangle boundingBox() const;

    virtual double xAt( int index ) const = 0;
%Docstring
 Returns the x-coordinate of the specified node in the line string.
 \param index index of node, where the first node in the line is 0
 :return: x-coordinate of node, or 0.0 if index is out of bounds
.. seealso:: setXAt()
 :rtype: float
%End

    virtual double yAt( int index ) const = 0;
%Docstring
 Returns the y-coordinate of the specified node in the line string.
 \param index index of node, where the first node in the line is 0
 :return: y-coordinate of node, or 0.0 if index is out of bounds
.. seealso:: setYAt()
 :rtype: float
%End

    QPolygonF asQPolygonF() const;
%Docstring
 Returns a QPolygonF representing the points.
 :rtype: QPolygonF
%End


  protected:

    virtual void clearCache() const;

};

/************************************************************************
 * This file has been generated automatically from                      *
 *                                                                      *
 * src/core/geometry/qgscurve.h                                         *
 *                                                                      *
 * Do not edit manually ! Edit header and run scripts/sipify.pl again   *
 ************************************************************************/
