/*
 * Copyright (C) 2011 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef AccessibilitySpinButton_h
#define AccessibilitySpinButton_h

#include "AccessibilityMockObject.h"

#include "SpinButtonElement.h"

namespace WebCore {
    
class AccessibilitySpinButton : public AccessibilityMockObject {
public:
    static PassRefPtr<AccessibilitySpinButton> create();
    virtual ~AccessibilitySpinButton();
    
    void setSpinButtonElement(SpinButtonElement* spinButton) { m_spinButtonElement = spinButton; }
    
    AccessibilityObject* incrementButton();
    AccessibilityObject* decrementButton();

    void step(int amount);
    
private:
    AccessibilitySpinButton();

    virtual AccessibilityRole roleValue() const override { return SpinButtonRole; }
    virtual bool isSpinButton() const override { return true; }
    virtual bool isNativeSpinButton() const override { return true; }
    virtual void addChildren() override;
    virtual LayoutRect elementRect() const override;
    
    SpinButtonElement* m_spinButtonElement;
}; 
   
class AccessibilitySpinButtonPart : public AccessibilityMockObject {
public:
    static PassRefPtr<AccessibilitySpinButtonPart> create();
    virtual ~AccessibilitySpinButtonPart() { }
    
    bool isIncrementor() const { return m_isIncrementor; }
    void setIsIncrementor(bool value) { m_isIncrementor = value; }
    
private:
    AccessibilitySpinButtonPart();
    bool m_isIncrementor : 1;
    
    virtual bool press() override;
    virtual AccessibilityRole roleValue() const override { return ButtonRole; }
    virtual bool isSpinButtonPart() const override { return true; }
    virtual LayoutRect elementRect() const override;
};
    
} // namespace WebCore

SPECIALIZE_TYPE_TRAITS_ACCESSIBILITY(AccessibilitySpinButton, isNativeSpinButton())
SPECIALIZE_TYPE_TRAITS_ACCESSIBILITY(AccessibilitySpinButtonPart, isSpinButtonPart())

#endif // AccessibilitySpinButton_h
