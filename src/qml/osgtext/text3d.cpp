#include "text3d.hpp"
#include "text3dindex.hpp"

#include <osgText/Text3D>

#include <osgQt/QFontImplementation>

#include <QDebug>

/*!
   \qmltype Text3D
   \inherits TextBase
   \inqmlmodule osgText
   \brief 3-dimensional text
 */

namespace osgText {

Text3DQtQml::Index::Index(Text3D *text3D) :
    TextBaseQtQml::Index(text3D),
    qthis(0)
{
    othis = text3D;
}

void Text3DQtQml::Index::classBegin()
{
    if(!othis) othis = new Text3D();

    othis->setFont("fonts/arial.ttf");

    //osg::Vec3 pos(0.0f,0.0f,0.0f);
    //othis->setPosition(pos);

    TextBaseQtQml::Index::othis = othis;
    TextBaseQtQml::Index::qthis = qthis;

    TextBaseQtQml::Index::classBegin();
}

void Text3DQtQml::Index::componentComplete()
{
    TextBaseQtQml::Index::othis = othis;
    TextBaseQtQml::Index::qthis = qthis;

    TextBaseQtQml::Index::componentComplete();
}

Text3DQtQml::Text3DQtQml(QObject *parent) :
  TextBaseQtQml(parent)
{
}

Text3DQtQml::Text3DQtQml(Text3DQtQml::Index *index, QObject *parent) :
  TextBaseQtQml(index, parent)
{
}

void Text3DQtQml::classBegin()
{
    if(!i) i = new Index();
    static_cast<Index*>(i)->qthis = this;
    TextBaseQtQml::classBegin();
}

/*!
   \qmlproperty real osgText::Text3D::characterDepth

   The Charactere Depth of text
 */

qreal Text3DQtQml::getCharacterDepth() const
{
    return static_cast<qreal>(static_cast<Index*>(i)->othis->getCharacterDepth());
}

void Text3DQtQml::setCharacterDepth(qreal depth)
{
    if(getCharacterDepth() == depth) return;

    static_cast<Index*>(i)->othis->setCharacterDepth(static_cast<float>(depth));

    emit characterDepthChanged(depth);
}

Text3D *Text3DQtQml::text3D()
{
    return static_cast<Index*>(i)->othis;
}

Text3DQtQml *Text3DQtQml::fromText3D(Text3D *text3D, QObject *parent)
{
    if(!text3D) return 0;

    if(osgQtQml::Index *index = osgQtQml::Index::checkIndex(text3D))
    {
        return static_cast<Index*>(index)->qthis;
    }

    Text3DQtQml *result = new Text3DQtQml(new Index(text3D), parent);
    result->classBegin();
    return result;
}

}
