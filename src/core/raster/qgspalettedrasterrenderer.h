/***************************************************************************
                         qgspalettedrasterrenderer.h
                         ---------------------------
    begin                : December 2011
    copyright            : (C) 2011 by Marco Hugentobler
    email                : marco at sourcepole dot ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSPALETTEDRASTERRENDERER_H
#define QGSPALETTEDRASTERRENDERER_H

#include "qgis_core.h"
#include "qgis.h"
#include <QVector>

#include "qgsrasterrenderer.h"
#include "qgscolorrampshader.h"

class QColor;
class QDomElement;

/** \ingroup core
  * Renderer for paletted raster images.
*/
class CORE_EXPORT QgsPalettedRasterRenderer: public QgsRasterRenderer
{
  public:

    //! Properties of a single value class
    struct Class
    {
      //! Constructor for Class
      Class( int value, const QColor &color = QColor(), const QString &label = QString() )
        : value( value )
        , color( color )
        , label( label )
      {}

      //! Value
      int value;

      //! Color to render value
      QColor color;
      //! Label for value
      QString label;
    };

    //! Map of value to class properties
    typedef QList< Class > ClassData;

    /**
     * Constructor for QgsPalettedRasterRenderer.
     */
    QgsPalettedRasterRenderer( QgsRasterInterface *input, int bandNumber, const ClassData &classes );

    //! QgsPalettedRasterRenderer cannot be copied. Use clone() instead.
    QgsPalettedRasterRenderer( const QgsPalettedRasterRenderer & ) = delete;
    //! QgsPalettedRasterRenderer cannot be copied. Use clone() instead.
    const QgsPalettedRasterRenderer &operator=( const QgsPalettedRasterRenderer & ) = delete;

    QgsPalettedRasterRenderer *clone() const override SIP_FACTORY;
    static QgsRasterRenderer *create( const QDomElement &elem, QgsRasterInterface *input ) SIP_FACTORY;

    QgsRasterBlock *block( int bandNo, const QgsRectangle &extent, int width, int height, QgsRasterBlockFeedback *feedback = nullptr ) override SIP_FACTORY;

    //! Returns number of colors
    int nColors() const { return mClassData.size(); }

    /**
     * Returns a map of value to classes (colors) used by the renderer.
     */
    ClassData classes() const;

    /** Return optional category label
     * \since QGIS 2.1 */
    QString label( int idx ) const;

    /** Set category label
     *  \since QGIS 2.1 */
    void setLabel( int idx, const QString &label );

    void writeXml( QDomDocument &doc, QDomElement &parentElem ) const override;

    void legendSymbologyItems( QList< QPair< QString, QColor > > &symbolItems SIP_OUT ) const override;

    QList<int> usesBands() const override;

    /**
     * Set the source color \a ramp. Ownership is transferred to the renderer.
     * \since QGIS 3.0
     * \see sourceColorRamp()
     */
    void setSourceColorRamp( QgsColorRamp *ramp SIP_TRANSFER );

    /** Get the source color ramp
     * \since QGIS 3.0
     * \see setSourceColorRamp()
     */
    QgsColorRamp *sourceColorRamp() const;

    /**
     * Converts a raster color \a table to paletted renderer class data.
     * \since QGIS 3.0
     */
    static QgsPalettedRasterRenderer::ClassData colorTableToClassData( const QList<QgsColorRampShader::ColorRampItem> &table );

    /**
     * Converts a \a string containing a color table or class data to to paletted renderer class data.
     * \since QGIS 3.0
     * \see classDataFromFile()
     * \see classDataToString()
     */
    static QgsPalettedRasterRenderer::ClassData classDataFromString( const QString &string );

    /**
     * Opens a color table file and returns corresponding paletted renderer class data.
     * \since QGIS 3.0
     * \see classDataFromString()
     */
    static QgsPalettedRasterRenderer::ClassData classDataFromFile( const QString &path );

    /**
     * Converts classes to a string representation, using the .clr/gdal color table file format.
     * \since QGIS 3.0
     * \see classDataFromString()
     */
    static QString classDataToString( const QgsPalettedRasterRenderer::ClassData &classes );

    /**
     * Generates class data from a \a raster, for the specified \a bandNumber. An optional
     * color \a ramp can be specified to automatically assign colors from the ramp.
     * \since QGIS 3.0
     */
    static QgsPalettedRasterRenderer::ClassData classDataFromRaster( QgsRasterInterface *raster, int bandNumber, QgsColorRamp *ramp = nullptr,
        QgsRasterBlockFeedback *feedback = nullptr );

  private:

    int mBand;
    ClassData mClassData;

    //! Source color ramp
    std::unique_ptr<QgsColorRamp> mSourceColorRamp;

    //! Premultiplied color map
    QMap< int, QRgb > mColors;
    void updateArrays();
};

#endif // QGSPALETTEDRASTERRENDERER_H
