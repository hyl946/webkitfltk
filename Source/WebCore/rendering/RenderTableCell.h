/*
 * Copyright (C) 1997 Martin Jones (mjones@kde.org)
 *           (C) 1997 Torben Weis (weis@kde.org)
 *           (C) 1998 Waldo Bastian (bastian@kde.org)
 *           (C) 1999 Lars Knoll (knoll@kde.org)
 *           (C) 1999 Antti Koivisto (koivisto@kde.org)
 * Copyright (C) 2003, 2004, 2005, 2006, 2007, 2009 Apple Inc. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef RenderTableCell_h
#define RenderTableCell_h

#include "RenderBlockFlow.h"
#include "RenderTableRow.h"
#include "RenderTableSection.h"

namespace WebCore {

// These is limited by the size of RenderTableCell::m_column bitfield.
static const unsigned unsetColumnIndex = 0x1FFFFFF;
static const unsigned maxColumnIndex = 0x1FFFFFE; // 33554430

enum IncludeBorderColorOrNot { DoNotIncludeBorderColor, IncludeBorderColor };

class RenderTableCell final : public RenderBlockFlow {
public:
    RenderTableCell(Element&, Ref<RenderStyle>&&);
    RenderTableCell(Document&, Ref<RenderStyle>&&);
    
    unsigned colSpan() const;
    unsigned rowSpan() const;

    // Called from HTMLTableCellElement.
    void colSpanOrRowSpanChanged();

    void setCol(unsigned column);
    unsigned col() const;

    RenderTableCell* nextCell() const;
    RenderTableCell* previousCell() const;

    RenderTableRow* row() const { return downcast<RenderTableRow>(parent()); }
    RenderTableSection* section() const;
    RenderTable* table() const;
    unsigned rowIndex() const;
    Length styleOrColLogicalWidth() const;
    int logicalHeightForRowSizing() const;

    void setCellLogicalWidth(int constrainedLogicalWidth);

    virtual LayoutUnit borderLeft() const override;
    virtual LayoutUnit borderRight() const override;
    virtual LayoutUnit borderTop() const override;
    virtual LayoutUnit borderBottom() const override;
    virtual LayoutUnit borderStart() const override;
    virtual LayoutUnit borderEnd() const override;
    virtual LayoutUnit borderBefore() const override;
    virtual LayoutUnit borderAfter() const override;

    void collectBorderValues(RenderTable::CollapsedBorderValues&) const;
    static void sortBorderValues(RenderTable::CollapsedBorderValues&);

    virtual void layout() override;

    virtual void paint(PaintInfo&, const LayoutPoint&) override;

    void paintCollapsedBorders(PaintInfo&, const LayoutPoint&);
    void paintBackgroundsBehindCell(PaintInfo&, const LayoutPoint&, RenderElement* backgroundObject);

    LayoutUnit cellBaselinePosition() const;
    bool isBaselineAligned() const;

    void computeIntrinsicPadding(int rowHeight);
    void clearIntrinsicPadding() { setIntrinsicPadding(0, 0); }

    int intrinsicPaddingBefore() const { return m_intrinsicPaddingBefore; }
    int intrinsicPaddingAfter() const { return m_intrinsicPaddingAfter; }

    virtual LayoutUnit paddingTop() const override;
    virtual LayoutUnit paddingBottom() const override;
    virtual LayoutUnit paddingLeft() const override;
    virtual LayoutUnit paddingRight() const override;
    
    // FIXME: For now we just assume the cell has the same block flow direction as the table. It's likely we'll
    // create an extra anonymous RenderBlock to handle mixing directionality anyway, in which case we can lock
    // the block flow directionality of the cells to the table's directionality.
    virtual LayoutUnit paddingBefore() const override;
    virtual LayoutUnit paddingAfter() const override;

    void setOverrideLogicalContentHeightFromRowHeight(LayoutUnit);

    virtual void scrollbarsChanged(bool horizontalScrollbarChanged, bool verticalScrollbarChanged) override;

    bool cellWidthChanged() const { return m_cellWidthChanged; }
    void setCellWidthChanged(bool b = true) { m_cellWidthChanged = b; }

    static RenderTableCell* createAnonymousWithParentRenderer(const RenderObject*);
    virtual RenderBox* createAnonymousBoxWithSameTypeAs(const RenderObject* parent) const override { return createAnonymousWithParentRenderer(parent); }

    // This function is used to unify which table part's style we use for computing direction and
    // writing mode. Writing modes are not allowed on row group and row but direction is.
    // This means we can safely use the same style in all cases to simplify our code.
    // FIXME: Eventually this function should replaced by style() once we support direction
    // on all table parts and writing-mode on cells.
    const RenderStyle& styleForCellFlow() const { return row()->style(); }

    const BorderValue& borderAdjoiningTableStart() const;
    const BorderValue& borderAdjoiningTableEnd() const;
    const BorderValue& borderAdjoiningCellBefore(const RenderTableCell*);
    const BorderValue& borderAdjoiningCellAfter(const RenderTableCell*);

    using RenderBlockFlow::nodeAtPoint;
#ifndef NDEBUG
    bool isFirstOrLastCellInRow() const { return !table()->cellAfter(this) || !table()->cellBefore(this); }
#endif
    
    virtual LayoutRect clippedOverflowRectForRepaint(const RenderLayerModelObject* repaintContainer) const override;

    void invalidateHasEmptyCollapsedBorders();
    void setHasEmptyCollapsedBorder(CollapsedBorderSide, bool empty) const;

protected:
    virtual void styleDidChange(StyleDifference, const RenderStyle* oldStyle) override;
    virtual void computePreferredLogicalWidths() override;

private:
    virtual const char* renderName() const override { return (isAnonymous() || isPseudoElement()) ? "RenderTableCell (anonymous)" : "RenderTableCell"; }

    virtual bool isTableCell() const override { return true; }

    virtual void willBeRemovedFromTree() override;

    virtual void updateLogicalWidth() override;

    virtual void paintBoxDecorations(PaintInfo&, const LayoutPoint&) override;
    virtual void paintMask(PaintInfo&, const LayoutPoint&) override;

    virtual bool boxShadowShouldBeAppliedToBackground(BackgroundBleedAvoidance, InlineFlowBox*) const override;

    virtual LayoutSize offsetFromContainer(RenderElement&, const LayoutPoint&, bool* offsetDependsOnPoint = 0) const override;
    virtual void computeRectForRepaint(const RenderLayerModelObject* repaintContainer, LayoutRect&, bool fixed = false) const override;

    int borderHalfLeft(bool outer) const;
    int borderHalfRight(bool outer) const;
    int borderHalfTop(bool outer) const;
    int borderHalfBottom(bool outer) const;

    int borderHalfStart(bool outer) const;
    int borderHalfEnd(bool outer) const;
    int borderHalfBefore(bool outer) const;
    int borderHalfAfter(bool outer) const;

    void setIntrinsicPaddingBefore(int p) { m_intrinsicPaddingBefore = p; }
    void setIntrinsicPaddingAfter(int p) { m_intrinsicPaddingAfter = p; }
    void setIntrinsicPadding(int before, int after) { setIntrinsicPaddingBefore(before); setIntrinsicPaddingAfter(after); }

    bool hasStartBorderAdjoiningTable() const;
    bool hasEndBorderAdjoiningTable() const;

    CollapsedBorderValue collapsedStartBorder(IncludeBorderColorOrNot = IncludeBorderColor) const;
    CollapsedBorderValue collapsedEndBorder(IncludeBorderColorOrNot = IncludeBorderColor) const;
    CollapsedBorderValue collapsedBeforeBorder(IncludeBorderColorOrNot = IncludeBorderColor) const;
    CollapsedBorderValue collapsedAfterBorder(IncludeBorderColorOrNot = IncludeBorderColor) const;

    CollapsedBorderValue cachedCollapsedLeftBorder(const RenderStyle&) const;
    CollapsedBorderValue cachedCollapsedRightBorder(const RenderStyle&) const;
    CollapsedBorderValue cachedCollapsedTopBorder(const RenderStyle&) const;
    CollapsedBorderValue cachedCollapsedBottomBorder(const RenderStyle&) const;

    CollapsedBorderValue computeCollapsedStartBorder(IncludeBorderColorOrNot = IncludeBorderColor) const;
    CollapsedBorderValue computeCollapsedEndBorder(IncludeBorderColorOrNot = IncludeBorderColor) const;
    CollapsedBorderValue computeCollapsedBeforeBorder(IncludeBorderColorOrNot = IncludeBorderColor) const;
    CollapsedBorderValue computeCollapsedAfterBorder(IncludeBorderColorOrNot = IncludeBorderColor) const;

    Length logicalWidthFromColumns(RenderTableCol* firstColForThisCell, Length widthFromStyle) const;

    void updateColAndRowSpanFlags();

    unsigned parseRowSpanFromDOM() const;
    unsigned parseColSpanFromDOM() const;

    void nextSibling() const = delete;
    void previousSibling() const = delete;

    // Note MSVC will only pack members if they have identical types, hence we use unsigned instead of bool here.
    unsigned m_column : 25;
    unsigned m_cellWidthChanged : 1;
    unsigned m_hasColSpan: 1;
    unsigned m_hasRowSpan: 1;
    mutable unsigned m_hasEmptyCollapsedBeforeBorder: 1;
    mutable unsigned m_hasEmptyCollapsedAfterBorder: 1;
    mutable unsigned m_hasEmptyCollapsedStartBorder: 1;
    mutable unsigned m_hasEmptyCollapsedEndBorder: 1;
    int m_intrinsicPaddingBefore { 0 };
    int m_intrinsicPaddingAfter { 0 };
};

inline RenderTableCell* RenderTableCell::nextCell() const
{
    return downcast<RenderTableCell>(RenderBlockFlow::nextSibling());
}

inline RenderTableCell* RenderTableCell::previousCell() const
{
    return downcast<RenderTableCell>(RenderBlockFlow::previousSibling());
}

inline unsigned RenderTableCell::colSpan() const
{
    if (!m_hasColSpan)
        return 1;
    return parseColSpanFromDOM();
}

inline unsigned RenderTableCell::rowSpan() const
{
    if (!m_hasRowSpan)
        return 1;
    return parseRowSpanFromDOM();
}

inline void RenderTableCell::setCol(unsigned column)
{
    if (UNLIKELY(column > maxColumnIndex))
        CRASH();
    m_column = column;
}

inline unsigned RenderTableCell::col() const
{
    ASSERT(m_column != unsetColumnIndex);
    return m_column;
}

inline RenderTableSection* RenderTableCell::section() const
{
    RenderTableRow* row = this->row();
    if (!row)
        return nullptr;
    return downcast<RenderTableSection>(row->parent());
}

inline RenderTable* RenderTableCell::table() const
{
    RenderTableSection* section = this->section();
    if (!section)
        return nullptr;
    return downcast<RenderTable>(section->parent());
}

inline unsigned RenderTableCell::rowIndex() const
{
    // This function shouldn't be called on a detached cell.
    ASSERT(row());
    return row()->rowIndex();
}

inline Length RenderTableCell::styleOrColLogicalWidth() const
{
    Length styleWidth = style().logicalWidth();
    if (!styleWidth.isAuto())
        return styleWidth;
    if (RenderTableCol* firstColumn = table()->colElement(col()))
        return logicalWidthFromColumns(firstColumn, styleWidth);
    return styleWidth;
}

inline int RenderTableCell::logicalHeightForRowSizing() const
{
    // FIXME: This function does too much work, and is very hot during table layout!
    int adjustedLogicalHeight = pixelSnappedLogicalHeight() - (intrinsicPaddingBefore() + intrinsicPaddingAfter());
    int styleLogicalHeight = valueForLength(style().logicalHeight(), 0);
    // In strict mode, box-sizing: content-box do the right thing and actually add in the border and padding.
    // Call computedCSSPadding* directly to avoid including implicitPadding.
    if (!document().inQuirksMode() && style().boxSizing() != BORDER_BOX)
        styleLogicalHeight += (computedCSSPaddingBefore() + computedCSSPaddingAfter()).floor() + (borderBefore() + borderAfter()).floor();
    return std::max(styleLogicalHeight, adjustedLogicalHeight);
}

inline bool RenderTableCell::isBaselineAligned() const
{
    EVerticalAlign va = style().verticalAlign();
    return va == BASELINE || va == TEXT_BOTTOM || va == TEXT_TOP || va == SUPER || va == SUB || va == LENGTH;
}

inline const BorderValue& RenderTableCell::borderAdjoiningTableStart() const
{
    ASSERT(isFirstOrLastCellInRow());
    if (section()->hasSameDirectionAs(table()))
        return style().borderStart();

    return style().borderEnd();
}

inline const BorderValue& RenderTableCell::borderAdjoiningTableEnd() const
{
    ASSERT(isFirstOrLastCellInRow());
    if (section()->hasSameDirectionAs(table()))
        return style().borderEnd();

    return style().borderStart();
}

inline const BorderValue& RenderTableCell::borderAdjoiningCellBefore(const RenderTableCell* cell)
{
    ASSERT_UNUSED(cell, table()->cellAfter(cell) == this);
    // FIXME: https://webkit.org/b/79272 - Add support for mixed directionality at the cell level.
    return style().borderStart();
}

inline const BorderValue& RenderTableCell::borderAdjoiningCellAfter(const RenderTableCell* cell)
{
    ASSERT_UNUSED(cell, table()->cellBefore(cell) == this);
    // FIXME: https://webkit.org/b/79272 - Add support for mixed directionality at the cell level.
    return style().borderEnd();
}

inline RenderTableCell* RenderTableRow::firstCell() const
{
    return downcast<RenderTableCell>(RenderBox::firstChild());
}

inline RenderTableCell* RenderTableRow::lastCell() const
{
    return downcast<RenderTableCell>(RenderBox::lastChild());
}

inline void RenderTableCell::setHasEmptyCollapsedBorder(CollapsedBorderSide side, bool empty) const
{
    switch (side) {
    case CBSAfter: {
        m_hasEmptyCollapsedAfterBorder = empty;
        break;
    }
    case CBSBefore: {
        m_hasEmptyCollapsedBeforeBorder = empty;
        break;
    }
    case CBSStart: {
        m_hasEmptyCollapsedStartBorder = empty;
        break;
    }
    case CBSEnd: {
        m_hasEmptyCollapsedEndBorder = empty;
        break;
    }
    }
    if (empty)
        table()->collapsedEmptyBorderIsPresent();
}

inline void RenderTableCell::invalidateHasEmptyCollapsedBorders()
{
    m_hasEmptyCollapsedBeforeBorder = false;
    m_hasEmptyCollapsedAfterBorder = false;
    m_hasEmptyCollapsedStartBorder = false;
    m_hasEmptyCollapsedEndBorder = false;
}

} // namespace WebCore

SPECIALIZE_TYPE_TRAITS_RENDER_OBJECT(RenderTableCell, isTableCell())

#endif // RenderTableCell_h
