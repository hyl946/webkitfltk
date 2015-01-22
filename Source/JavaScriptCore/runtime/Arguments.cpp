/*
 *  Copyright (C) 1999-2002 Harri Porten (porten@kde.org)
 *  Copyright (C) 2001 Peter Kelly (pmk@post.com)
 *  Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008, 2009 Apple Inc. All rights reserved.
 *  Copyright (C) 2007 Cameron Zwarich (cwzwarich@uwaterloo.ca)
 *  Copyright (C) 2007 Maks Orlovich
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 *
 */

#include "config.h"
#include "Arguments.h"

#include "CopyVisitorInlines.h"
#include "JSArgumentsIterator.h"
#include "JSFunction.h"
#include "JSGlobalObject.h"
#include "JSCInlines.h"
#include "JSLexicalEnvironment.h"

using namespace std;

namespace JSC {

STATIC_ASSERT_IS_TRIVIALLY_DESTRUCTIBLE(Arguments);

const ClassInfo Arguments::s_info = { "Arguments", &Base::s_info, 0, CREATE_METHOD_TABLE(Arguments) };

void Arguments::visitChildren(JSCell* cell, SlotVisitor& visitor)
{
    Arguments* thisObject = jsCast<Arguments*>(cell);

    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    JSObject::visitChildren(thisObject, visitor);

    if (thisObject->isTornOff())
        visitor.appendValues(&thisObject->registerArray(), thisObject->m_numArguments);

    if (thisObject->m_slowArgumentData) {
        visitor.copyLater(thisObject, ArgumentsSlowArgumentDataCopyToken,
            thisObject->m_slowArgumentData.get(), SlowArgumentData::sizeForNumArguments(thisObject->m_numArguments));
    }
    visitor.append(&thisObject->m_callee);
    visitor.append(&thisObject->m_lexicalEnvironment);
}

void Arguments::copyBackingStore(JSCell* cell, CopyVisitor& visitor, CopyToken token)
{
    Arguments* thisObject = jsCast<Arguments*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    

    switch (token) {
    case ArgumentsSlowArgumentDataCopyToken: {
        SlowArgumentData* slowArgumentData = thisObject->m_slowArgumentData.get();
        if (!slowArgumentData)
            return;

        if (visitor.checkIfShouldCopy(slowArgumentData)) {
            size_t bytes = SlowArgumentData::sizeForNumArguments(thisObject->m_numArguments);
            SlowArgumentData* newSlowArgumentData = static_cast<SlowArgumentData*>(visitor.allocateNewSpace(bytes));
            memcpy(newSlowArgumentData, slowArgumentData, bytes);
            thisObject->m_slowArgumentData.setWithoutWriteBarrier(newSlowArgumentData);
            visitor.didCopy(slowArgumentData, bytes);
        }
        return;
    }

    default:
        return;
    }
}
    
static EncodedJSValue JSC_HOST_CALL argumentsFuncIterator(ExecState*);

void Arguments::copyToArguments(ExecState* exec, CallFrame* callFrame, uint32_t copyLength, int32_t firstVarArgOffset)
{
    uint32_t length = copyLength + firstVarArgOffset;

    if (UNLIKELY(m_overrodeLength)) {
        length = min(get(exec, exec->propertyNames().length).toUInt32(exec), length);
        for (unsigned i = firstVarArgOffset; i < length; i++)
            callFrame->setArgument(i, get(exec, i));
        return;
    }
    ASSERT(length == this->length(exec));
    for (size_t i = firstVarArgOffset; i < length; ++i) {
        if (JSValue value = tryGetArgument(i))
            callFrame->setArgument(i - firstVarArgOffset, value);
        else
            callFrame->setArgument(i - firstVarArgOffset, get(exec, i));
    }
}

void Arguments::fillArgList(ExecState* exec, MarkedArgumentBuffer& args)
{
    if (UNLIKELY(m_overrodeLength)) {
        unsigned length = get(exec, exec->propertyNames().length).toUInt32(exec); 
        for (unsigned i = 0; i < length; i++) 
            args.append(get(exec, i)); 
        return;
    }
    uint32_t length = this->length(exec);
    for (size_t i = 0; i < length; ++i) {
        if (JSValue value = tryGetArgument(i))
            args.append(value);
        else
            args.append(get(exec, i));
    }
}

bool Arguments::getOwnPropertySlotByIndex(JSObject* object, ExecState* exec, unsigned i, PropertySlot& slot)
{
    Arguments* thisObject = jsCast<Arguments*>(object);
    if (JSValue value = thisObject->tryGetArgument(i)) {
        slot.setValue(thisObject, None, value);
        return true;
    }

    return JSObject::getOwnPropertySlot(thisObject, exec, Identifier::from(exec, i), slot);
}
    
void Arguments::createStrictModeCallerIfNecessary(ExecState* exec)
{
    if (m_overrodeCaller)
        return;

    VM& vm = exec->vm();
    m_overrodeCaller = true;
    PropertyDescriptor descriptor;
    descriptor.setAccessorDescriptor(globalObject()->throwTypeErrorGetterSetter(vm), DontEnum | DontDelete | Accessor);
    methodTable(exec->vm())->defineOwnProperty(this, exec, vm.propertyNames->caller, descriptor, false);
}

void Arguments::createStrictModeCalleeIfNecessary(ExecState* exec)
{
    if (m_overrodeCallee)
        return;

    VM& vm = exec->vm();
    m_overrodeCallee = true;
    PropertyDescriptor descriptor;
    descriptor.setAccessorDescriptor(globalObject()->throwTypeErrorGetterSetter(vm), DontEnum | DontDelete | Accessor);
    methodTable(exec->vm())->defineOwnProperty(this, exec, vm.propertyNames->callee, descriptor, false);
}

bool Arguments::getOwnPropertySlot(JSObject* object, ExecState* exec, PropertyName propertyName, PropertySlot& slot)
{
    Arguments* thisObject = jsCast<Arguments*>(object);
    if (Optional<uint32_t> index = propertyName.asIndex()) {
        if (JSValue value = thisObject->tryGetArgument(index.value())) {
            slot.setValue(thisObject, None, value);
            return true;
        }
    }

    if (propertyName == exec->propertyNames().length && LIKELY(!thisObject->m_overrodeLength)) {
        slot.setValue(thisObject, DontEnum, jsNumber(thisObject->m_numArguments));
        return true;
    }

    if (propertyName == exec->propertyNames().callee && LIKELY(!thisObject->m_overrodeCallee)) {
        if (!thisObject->m_isStrictMode) {
            slot.setValue(thisObject, DontEnum, thisObject->m_callee.get());
            return true;
        }
        thisObject->createStrictModeCalleeIfNecessary(exec);
    }

    if (propertyName == exec->propertyNames().caller && thisObject->m_isStrictMode)
        thisObject->createStrictModeCallerIfNecessary(exec);

    if (JSObject::getOwnPropertySlot(thisObject, exec, propertyName, slot))
        return true;
    if (propertyName == exec->propertyNames().iteratorPrivateName) {
        VM& vm = exec->vm();
        JSGlobalObject* globalObject = exec->lexicalGlobalObject();
        thisObject->JSC_NATIVE_FUNCTION(exec->propertyNames().iteratorPrivateName, argumentsFuncIterator, DontEnum, 0);
        if (JSObject::getOwnPropertySlot(thisObject, exec, propertyName, slot))
            return true;
    }
    return false;
}

void Arguments::getOwnPropertyNames(JSObject* object, ExecState* exec, PropertyNameArray& propertyNames, EnumerationMode mode)
{
    Arguments* thisObject = jsCast<Arguments*>(object);
    for (unsigned i = 0; i < thisObject->m_numArguments; ++i) {
        if (!thisObject->isArgument(i))
            continue;
        propertyNames.add(Identifier::from(exec, i));
    }
    if (shouldIncludeDontEnumProperties(mode)) {
        propertyNames.add(exec->propertyNames().callee);
        propertyNames.add(exec->propertyNames().length);
    }
    JSObject::getOwnPropertyNames(thisObject, exec, propertyNames, mode);
}

void Arguments::putByIndex(JSCell* cell, ExecState* exec, unsigned i, JSValue value, bool shouldThrow)
{
    Arguments* thisObject = jsCast<Arguments*>(cell);
    if (thisObject->trySetArgument(exec->vm(), i, value))
        return;

    PutPropertySlot slot(thisObject, shouldThrow);
    JSObject::put(thisObject, exec, Identifier::from(exec, i), value, slot);
}

void Arguments::put(JSCell* cell, ExecState* exec, PropertyName propertyName, JSValue value, PutPropertySlot& slot)
{
    Arguments* thisObject = jsCast<Arguments*>(cell);
    Optional<uint32_t> index = propertyName.asIndex();
    if (index && thisObject->trySetArgument(exec->vm(), index.value(), value))
        return;

    if (propertyName == exec->propertyNames().length && !thisObject->m_overrodeLength) {
        thisObject->m_overrodeLength = true;
        thisObject->putDirect(exec->vm(), propertyName, value, DontEnum);
        return;
    }

    if (propertyName == exec->propertyNames().callee && !thisObject->m_overrodeCallee) {
        if (!thisObject->m_isStrictMode) {
            thisObject->m_overrodeCallee = true;
            thisObject->putDirect(exec->vm(), propertyName, value, DontEnum);
            return;
        }
        thisObject->createStrictModeCalleeIfNecessary(exec);
    }

    if (propertyName == exec->propertyNames().caller && thisObject->m_isStrictMode)
        thisObject->createStrictModeCallerIfNecessary(exec);

    JSObject::put(thisObject, exec, propertyName, value, slot);
}

bool Arguments::deletePropertyByIndex(JSCell* cell, ExecState* exec, unsigned i) 
{
    Arguments* thisObject = jsCast<Arguments*>(cell);
    if (i < thisObject->m_numArguments) {
        if (!Base::deletePropertyByIndex(cell, exec, i))
            return false;
        if (thisObject->tryDeleteArgument(exec->vm(), i))
            return true;
    }
    return JSObject::deletePropertyByIndex(thisObject, exec, i);
}

bool Arguments::deleteProperty(JSCell* cell, ExecState* exec, PropertyName propertyName) 
{
    if (exec->vm().isInDefineOwnProperty())
        return Base::deleteProperty(cell, exec, propertyName);

    Arguments* thisObject = jsCast<Arguments*>(cell);
    Optional<uint32_t> index = propertyName.asIndex();
    if (index && index.value() < thisObject->m_numArguments) {
        if (!Base::deleteProperty(cell, exec, propertyName))
            return false;
        if (thisObject->tryDeleteArgument(exec->vm(), index.value()))
            return true;
    }

    if (propertyName == exec->propertyNames().length && !thisObject->m_overrodeLength) {
        thisObject->m_overrodeLength = true;
        return true;
    }

    if (propertyName == exec->propertyNames().callee && !thisObject->m_overrodeCallee) {
        if (!thisObject->m_isStrictMode) {
            thisObject->m_overrodeCallee = true;
            return true;
        }
        thisObject->createStrictModeCalleeIfNecessary(exec);
    }
    
    if (propertyName == exec->propertyNames().caller && thisObject->m_isStrictMode)
        thisObject->createStrictModeCallerIfNecessary(exec);

    return JSObject::deleteProperty(thisObject, exec, propertyName);
}

bool Arguments::defineOwnProperty(JSObject* object, ExecState* exec, PropertyName propertyName, const PropertyDescriptor& descriptor, bool shouldThrow)
{
    Arguments* thisObject = jsCast<Arguments*>(object);
    Optional<uint32_t> optionalIndex = propertyName.asIndex();
    if (optionalIndex && optionalIndex.value() < thisObject->m_numArguments) {
        // If the property is not yet present on the object, and is not yet marked as deleted, then add it now.
        uint32_t index = optionalIndex.value();
        PropertySlot slot(thisObject);
        if (!thisObject->isDeletedArgument(index) && !JSObject::getOwnPropertySlot(thisObject, exec, propertyName, slot)) {
            JSValue value = thisObject->tryGetArgument(index);
            ASSERT(value);
            object->putDirectMayBeIndex(exec, propertyName, value);
        }
        if (!Base::defineOwnProperty(object, exec, propertyName, descriptor, shouldThrow))
            return false;

        // From ES 5.1, 10.6 Arguments Object
        // 5. If the value of isMapped is not undefined, then
        if (thisObject->isArgument(index)) {
            // a. If IsAccessorDescriptor(Desc) is true, then
            if (descriptor.isAccessorDescriptor()) {
                // i. Call the [[Delete]] internal method of map passing P, and false as the arguments.
                thisObject->tryDeleteArgument(exec->vm(), index);
            } else { // b. Else
                // i. If Desc.[[Value]] is present, then
                // 1. Call the [[Put]] internal method of map passing P, Desc.[[Value]], and Throw as the arguments.
                if (descriptor.value())
                    thisObject->trySetArgument(exec->vm(), index, descriptor.value());
                // ii. If Desc.[[Writable]] is present and its value is false, then
                // 1. Call the [[Delete]] internal method of map passing P and false as arguments.
                if (descriptor.writablePresent() && !descriptor.writable())
                    thisObject->tryDeleteArgument(exec->vm(), index);
            }
        }
        return true;
    }

    if (propertyName == exec->propertyNames().length && !thisObject->m_overrodeLength) {
        thisObject->putDirect(exec->vm(), propertyName, jsNumber(thisObject->m_numArguments), DontEnum);
        thisObject->m_overrodeLength = true;
    } else if (propertyName == exec->propertyNames().callee && !thisObject->m_overrodeCallee) {
        thisObject->putDirect(exec->vm(), propertyName, thisObject->m_callee.get(), DontEnum);
        thisObject->m_overrodeCallee = true;
    } else if (propertyName == exec->propertyNames().caller && thisObject->m_isStrictMode)
        thisObject->createStrictModeCallerIfNecessary(exec);

    return Base::defineOwnProperty(object, exec, propertyName, descriptor, shouldThrow);
}

void Arguments::tearOff(CallFrame* callFrame)
{
    if (isTornOff())
        return;

    if (!m_numArguments)
        return;

    // Must be called for the same call frame from which it was created.
    ASSERT(bitwise_cast<WriteBarrier<Unknown>*>(callFrame) == m_registers);

    m_registers = &registerArray() - CallFrame::offsetFor(1) - 1;

    for (size_t i = 0; i < m_numArguments; ++i) {
        if (m_slowArgumentData && m_slowArgumentData->slowArguments()[i].status == SlowArgument::Captured) {
            m_registers[CallFrame::argumentOffset(i)].setUndefined();
            continue;
        }
        trySetArgument(callFrame->vm(), i, callFrame->argumentAfterCapture(i));
    }
}

void Arguments::tearOff(CallFrame* callFrame, InlineCallFrame* inlineCallFrame)
{
    RELEASE_ASSERT(!inlineCallFrame->baselineCodeBlock()->needsActivation());
    if (isTornOff())
        return;
    
    if (!m_numArguments)
        return;

    m_registers = &registerArray() - CallFrame::offsetFor(1) - 1;

    for (size_t i = 0; i < m_numArguments; ++i) {
        ValueRecovery& recovery = inlineCallFrame->arguments[i + 1];
        trySetArgument(callFrame->vm(), i, recovery.recover(callFrame));
    }
}
    
void Arguments::tearOffForCloning(CallFrame* callFrame)
{
    ASSERT(!isTornOff());
    
    if (!m_numArguments)
        return;
    
    // Must be called for the same call frame from which it was created.
    ASSERT(bitwise_cast<WriteBarrier<Unknown>*>(callFrame) == m_registers);
    
    m_registers = &registerArray() - CallFrame::offsetFor(1) - 1;
    
    ASSERT(!m_slowArgumentData);
    for (size_t i = 0; i < m_numArguments; ++i)
        m_registers[CallFrame::argumentOffset(i)].set(callFrame->vm(), this, callFrame->argument(i));
}
    
void Arguments::tearOffForCloning(CallFrame* callFrame, InlineCallFrame* inlineCallFrame)
{
    RELEASE_ASSERT(!inlineCallFrame->baselineCodeBlock()->needsActivation());
    ASSERT(!isTornOff());
    
    if (!m_numArguments)
        return;
    
    m_registers = &registerArray() - CallFrame::offsetFor(1) - 1;
    
    ASSERT(!m_slowArgumentData);
    for (size_t i = 0; i < m_numArguments; ++i) {
        ValueRecovery& recovery = inlineCallFrame->arguments[i + 1];
        m_registers[CallFrame::argumentOffset(i)].set(callFrame->vm(), this, recovery.recover(callFrame));
    }
}

EncodedJSValue JSC_HOST_CALL argumentsFuncIterator(ExecState* exec)
{
    JSObject* thisObj = exec->thisValue().toThis(exec, StrictMode).toObject(exec);
    Arguments* arguments = jsDynamicCast<Arguments*>(thisObj);
    if (!arguments)
        return JSValue::encode(throwTypeError(exec, ASCIILiteral("Attempted to use Arguments iterator on non-Arguments object")));
    return JSValue::encode(JSArgumentsIterator::create(exec->vm(), exec->callee()->globalObject()->argumentsIteratorStructure(), arguments));
}


} // namespace JSC
