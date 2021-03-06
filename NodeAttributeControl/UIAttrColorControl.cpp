#include "UIAttrColorControl.h"

UIAttrColorControl::UIAttrColorControl(NDAttributeBase* attribute, QWidget* parent)
    :UICustomColorControl(parent)
{
    setAttribute(attribute);
}

UIAttrColorControl::~UIAttrColorControl()
{

}

void UIAttrColorControl::setAttribute(NDAttributeBase* attribute)
{
    if (attribute == nullptr || attribute->Type() != NDAttributeBase::t_color)
        return;

    m_attribute = qobject_cast<NDColorAttribute*>(attribute);
    this->setCurrentColor(m_attribute->getCurrentValue());
    this->setTagText(m_attribute->getDisplayName());

    // 连接信号和槽
    QObject::connect(this, &UIAttrColorControl::colorChanged, this, &UIAttrColorControl::onControlValuedChanged);
    QObject::connect(this, &UIAttrColorControl::colorDragChanged, this, &UIAttrColorControl::onControlValuedChanged);
    QObject::connect(m_attribute, &NDColorAttribute::valueChanged, this, &UIAttrColorControl::onColorValueChanged);
}

void UIAttrColorControl::onColorValueChanged(const QColor& value)
{
    this->setCurrentColor(value);
}

void UIAttrColorControl::onControlValuedChanged(const QColor& color)
{
    if (m_attribute == nullptr)
        return;

    this->blockSignals(true);
    m_attribute->setCurrentValue(color);
    this->blockSignals(false);
}
