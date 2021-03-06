/************************************************************************
 * This file has been generated automatically from                      *
 *                                                                      *
 * src/gui/editorwidgets/qgsdoublespinbox.h                             *
 *                                                                      *
 * Do not edit manually ! Edit header and run scripts/sipify.pl again   *
 ************************************************************************/





%ModuleHeaderCode
// fix to allow compilation with sip that for some reason
// doesn't add this include to the file where the code from
// ConvertToSubClassCode goes.
#include <qgsdoublespinbox.h>
%End


class QgsDoubleSpinBox : QDoubleSpinBox
{
%Docstring
 The QgsSpinBox is a spin box with a clear button that will set the value to the defined clear value.
 The clear value can be either the minimum or the maiximum value of the spin box or a custom value.
 This value can then be handled by a special value text.
%End

%TypeHeaderCode
#include "qgsdoublespinbox.h"
%End

%ConvertToSubClassCode
    if ( qobject_cast<QgsDoubleSpinBox *>( sipCpp ) )
      sipType = sipType_QgsDoubleSpinBox;
    else
      sipType = NULL;
%End
  public:

    enum ClearValueMode
    {
      MinimumValue,
      MaximumValue,
      CustomValue,
    };

    explicit QgsDoubleSpinBox( QWidget *parent /TransferThis/ = 0 );
%Docstring
 Constructor for QgsDoubleSpinBox.
 \param parent parent widget
%End

    void setShowClearButton( const bool showClearButton );
%Docstring
 Sets whether the widget will show a clear button. The clear button
 allows users to reset the widget to a default or empty state.
 \param showClearButton set to true to show the clear button, or false to hide it
.. seealso:: showClearButton()
%End

    bool showClearButton() const;
%Docstring
 Returns whether the widget is showing a clear button.
.. seealso:: setShowClearButton()
 :rtype: bool
%End

    void setExpressionsEnabled( const bool enabled );
%Docstring
 Sets if the widget will allow entry of simple expressions, which are
 evaluated and then discarded.
 \param enabled set to true to allow expression entry
.. versionadded:: 2.7
%End

    bool expressionsEnabled() const;
%Docstring
 Returns whether the widget will allow entry of simple expressions, which are
 evaluated and then discarded.
 :return: true if spin box allows expression entry
.. versionadded:: 2.7
 :rtype: bool
%End

    virtual void clear();
%Docstring
Set the current value to the value defined by the clear value.
%End

    void setClearValue( double customValue, const QString &clearValueText = QString() );
%Docstring
 Defines the clear value as a custom value and will automatically set the clear value mode to CustomValue.
 \param customValue defines the numerical value used as the clear value
 \param clearValueText is the text displayed when the spin box is at the clear value. If not specified, no special value text is used.
.. seealso:: setClearValue()
%End

    void setClearValueMode( ClearValueMode mode, const QString &clearValueText = QString() );
%Docstring
 Defines if the clear value should be the minimum or maximum values of the widget or a custom value.
 \param mode mode to user for clear value
 \param clearValueText is the text displayed when the spin box is at the clear value. If not specified, no special value text is used.
%End

    double clearValue() const;
%Docstring
 Returns the value used when clear() is called.
.. seealso:: setClearValue()
 :rtype: float
%End

    virtual double valueFromText( const QString &text ) const;
    virtual QValidator::State validate( QString &input, int &pos ) const;
    virtual void paintEvent( QPaintEvent *e );


  protected:
    virtual void changeEvent( QEvent *event );

};

/************************************************************************
 * This file has been generated automatically from                      *
 *                                                                      *
 * src/gui/editorwidgets/qgsdoublespinbox.h                             *
 *                                                                      *
 * Do not edit manually ! Edit header and run scripts/sipify.pl again   *
 ************************************************************************/
