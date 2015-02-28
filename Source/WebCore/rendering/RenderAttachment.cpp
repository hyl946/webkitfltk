/*
 * Copyright (C) 2015 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "RenderAttachment.h"

#if ENABLE(ATTACHMENT_ELEMENT)

#include "FloatRect.h"
#include "FloatRoundedRect.h"
#include "FrameSelection.h"
#include "HTMLAttachmentElement.h"
#include "Page.h"
#include "PaintInfo.h"
#include "RenderTheme.h"
#include "URL.h"

namespace WebCore {

using namespace HTMLNames;

RenderAttachment::RenderAttachment(HTMLAttachmentElement& element, Ref<RenderStyle>&& style)
    : RenderReplaced(element, WTF::move(style), LayoutSize())
{
}

HTMLAttachmentElement& RenderAttachment::attachmentElement() const
{
    return downcast<HTMLAttachmentElement>(nodeForNonAnonymous());
}

bool RenderAttachment::isSelected() const
{
    RefPtr<Range> selectionRange = frame().selection().selection().firstRange();
    return selectionRange && selectionRange->intersectsNode(&nodeForNonAnonymous(), ASSERT_NO_EXCEPTION);
}

void RenderAttachment::layout()
{
    setIntrinsicSize(document().page()->theme().attachmentIntrinsicSize(*this));

    RenderReplaced::layout();
}

void RenderAttachment::representedFileChanged()
{
    setNeedsLayout();
    repaint();
}

int RenderAttachment::baselinePosition(FontBaseline, bool, LineDirectionMode, LinePositionMode) const
{
    return document().page()->theme().attachmentBaseline(*this);
}

} // namespace WebCore

#endif
