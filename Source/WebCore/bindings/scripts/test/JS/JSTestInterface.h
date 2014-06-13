/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef JSTestInterface_h
#define JSTestInterface_h

#if ENABLE(Condition1) || ENABLE(Condition2)

#include "JSDOMBinding.h"
#include "TestInterface.h"
#include <runtime/JSGlobalObject.h>
#include <runtime/JSObject.h>
#include <runtime/ObjectPrototype.h>

namespace WebCore {

class JSTestInterface : public JSDOMWrapper {
public:
    typedef JSDOMWrapper Base;
    static JSTestInterface* create(JSC::Structure* structure, JSDOMGlobalObject* globalObject, PassRefPtr<TestInterface> impl)
    {
        JSTestInterface* ptr = new (NotNull, JSC::allocateCell<JSTestInterface>(globalObject->vm().heap)) JSTestInterface(structure, globalObject, impl);
        ptr->finishCreation(globalObject->vm());
        return ptr;
    }

    static JSC::JSObject* createPrototype(JSC::VM&, JSC::JSGlobalObject*);
    static bool getOwnPropertySlot(JSC::JSObject*, JSC::ExecState*, JSC::PropertyName, JSC::PropertySlot&);
    static void put(JSC::JSCell*, JSC::ExecState*, JSC::PropertyName, JSC::JSValue, JSC::PutPropertySlot&);
    static void putByIndex(JSC::JSCell*, JSC::ExecState*, unsigned propertyName, JSC::JSValue, bool shouldThrow);
    bool putDelegate(JSC::ExecState*, JSC::PropertyName, JSC::JSValue, JSC::PutPropertySlot&);
    static void destroy(JSC::JSCell*);
    ~JSTestInterface();
    DECLARE_INFO;

    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

    static JSC::JSValue getConstructor(JSC::VM&, JSC::JSGlobalObject*);

    // Custom attributes
#if ENABLE(Condition22) || ENABLE(Condition23)
    JSC::JSValue implementsStr3(JSC::ExecState*) const;
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
    void setImplementsStr3(JSC::ExecState*, JSC::JSValue);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    JSC::JSValue supplementalStr3(JSC::ExecState*) const;
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    void setSupplementalStr3(JSC::ExecState*, JSC::JSValue);
#endif

    // Custom functions
#if ENABLE(Condition22) || ENABLE(Condition23)
    JSC::JSValue implementsMethod3(JSC::ExecState*);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    JSC::JSValue supplementalMethod3(JSC::ExecState*);
#endif
    TestInterface& impl() const { return *m_impl; }
    void releaseImpl() { m_impl->deref(); m_impl = 0; }

    void releaseImplIfNotNull()
    {
        if (m_impl) {
            m_impl->deref();
            m_impl = 0;
        }
    }

private:
    TestInterface* m_impl;
protected:
    JSTestInterface(JSC::Structure*, JSDOMGlobalObject*, PassRefPtr<TestInterface>);

    void finishCreation(JSC::VM& vm)
    {
        Base::finishCreation(vm);
        ASSERT(inherits(info()));
    }

    static const unsigned StructureFlags = JSC::InterceptsGetOwnPropertySlotByIndexEvenWhenLengthIsNotZero | JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
};

class JSTestInterfaceOwner : public JSC::WeakHandleOwner {
public:
    virtual bool isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown>, void* context, JSC::SlotVisitor&);
    virtual void finalize(JSC::Handle<JSC::Unknown>, void* context);
};

inline JSC::WeakHandleOwner* wrapperOwner(DOMWrapperWorld&, TestInterface*)
{
    DEPRECATED_DEFINE_STATIC_LOCAL(JSTestInterfaceOwner, jsTestInterfaceOwner, ());
    return &jsTestInterfaceOwner;
}

inline void* wrapperContext(DOMWrapperWorld& world, TestInterface*)
{
    return &world;
}

JSC::JSValue toJS(JSC::ExecState*, JSDOMGlobalObject*, TestInterface*);
TestInterface* toTestInterface(JSC::JSValue);

class JSTestInterfacePrototype : public JSC::JSNonFinalObject {
public:
    typedef JSC::JSNonFinalObject Base;
    static JSC::JSObject* self(JSC::VM&, JSC::JSGlobalObject*);
    static JSTestInterfacePrototype* create(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestInterfacePrototype* ptr = new (NotNull, JSC::allocateCell<JSTestInterfacePrototype>(vm.heap)) JSTestInterfacePrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    void finishCreation(JSC::VM&);
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestInterfacePrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure) : JSC::JSNonFinalObject(vm, structure) { }
protected:
    static const unsigned StructureFlags = Base::StructureFlags;
};

class JSTestInterfaceConstructor : public DOMConstructorObject {
private:
    JSTestInterfaceConstructor(JSC::Structure*, JSDOMGlobalObject*);
    void finishCreation(JSC::VM&, JSDOMGlobalObject*);

public:
    typedef DOMConstructorObject Base;
    static JSTestInterfaceConstructor* create(JSC::VM& vm, JSC::Structure* structure, JSDOMGlobalObject* globalObject)
    {
        JSTestInterfaceConstructor* ptr = new (NotNull, JSC::allocateCell<JSTestInterfaceConstructor>(vm.heap)) JSTestInterfaceConstructor(structure, globalObject);
        ptr->finishCreation(vm, globalObject);
        return ptr;
    }

    DECLARE_INFO;
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }
protected:
    static const unsigned StructureFlags = JSC::OverridesGetOwnPropertySlot | JSC::ImplementsHasInstance | DOMConstructorObject::StructureFlags;
    static JSC::EncodedJSValue JSC_HOST_CALL constructJSTestInterface(JSC::ExecState*);
#if ENABLE(TEST_INTERFACE)
    static JSC::ConstructType getConstructData(JSC::JSCell*, JSC::ConstructData&);
#endif // ENABLE(TEST_INTERFACE)
};

// Functions

#if ENABLE(Condition22) || ENABLE(Condition23)
JSC::EncodedJSValue JSC_HOST_CALL jsTestInterfacePrototypeFunctionImplementsMethod1(JSC::ExecState*);
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
JSC::EncodedJSValue JSC_HOST_CALL jsTestInterfacePrototypeFunctionImplementsMethod2(JSC::ExecState*);
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
JSC::EncodedJSValue JSC_HOST_CALL jsTestInterfacePrototypeFunctionImplementsMethod3(JSC::ExecState*);
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
JSC::EncodedJSValue JSC_HOST_CALL jsTestInterfaceConstructorFunctionImplementsMethod4(JSC::ExecState*);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
JSC::EncodedJSValue JSC_HOST_CALL jsTestInterfacePrototypeFunctionSupplementalMethod1(JSC::ExecState*);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
JSC::EncodedJSValue JSC_HOST_CALL jsTestInterfacePrototypeFunctionSupplementalMethod2(JSC::ExecState*);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
JSC::EncodedJSValue JSC_HOST_CALL jsTestInterfacePrototypeFunctionSupplementalMethod3(JSC::ExecState*);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
JSC::EncodedJSValue JSC_HOST_CALL jsTestInterfaceConstructorFunctionSupplementalMethod4(JSC::ExecState*);
#endif
// Attributes

#if ENABLE(Condition22) || ENABLE(Condition23)
JSC::EncodedJSValue jsTestInterfaceConstructorImplementsStaticReadOnlyAttr(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
JSC::EncodedJSValue jsTestInterfaceConstructorImplementsStaticAttr(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
void setJSTestInterfaceConstructorImplementsStaticAttr(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
JSC::EncodedJSValue jsTestInterfaceImplementsStr1(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
JSC::EncodedJSValue jsTestInterfaceImplementsStr2(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
void setJSTestInterfaceImplementsStr2(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
JSC::EncodedJSValue jsTestInterfaceImplementsStr3(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
void setJSTestInterfaceImplementsStr3(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
JSC::EncodedJSValue jsTestInterfaceImplementsNode(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
void setJSTestInterfaceImplementsNode(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
JSC::EncodedJSValue jsTestInterfaceConstructorSupplementalStaticReadOnlyAttr(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
JSC::EncodedJSValue jsTestInterfaceConstructorSupplementalStaticAttr(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
void setJSTestInterfaceConstructorSupplementalStaticAttr(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
JSC::EncodedJSValue jsTestInterfaceSupplementalStr1(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
JSC::EncodedJSValue jsTestInterfaceSupplementalStr2(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
void setJSTestInterfaceSupplementalStr2(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
JSC::EncodedJSValue jsTestInterfaceSupplementalStr3(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
void setJSTestInterfaceSupplementalStr3(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
JSC::EncodedJSValue jsTestInterfaceSupplementalNode(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
void setJSTestInterfaceSupplementalNode(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::EncodedJSValue);
#endif
JSC::EncodedJSValue jsTestInterfaceConstructor(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
// Constants

#if ENABLE(Condition22) || ENABLE(Condition23)
JSC::EncodedJSValue jsTestInterfaceIMPLEMENTSCONSTANT1(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
#endif
#if ENABLE(Condition22) || ENABLE(Condition23)
JSC::EncodedJSValue jsTestInterfaceIMPLEMENTSCONSTANT2(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
JSC::EncodedJSValue jsTestInterfaceSUPPLEMENTALCONSTANT1(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
JSC::EncodedJSValue jsTestInterfaceSUPPLEMENTALCONSTANT2(JSC::ExecState*, JSC::JSObject*, JSC::EncodedJSValue, JSC::PropertyName);
#endif

} // namespace WebCore

#endif // ENABLE(Condition1) || ENABLE(Condition2)

#endif
