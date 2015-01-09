/*
 * Copyright (C) 2014 Apple Inc. All rights reserved.
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
#include "ContentExtensionsManager.h"

#if ENABLE(CONTENT_EXTENSIONS)

#include "ContentExtensionRule.h"
#include "ContentExtensionsBackend.h"
#include <JavaScriptCore/IdentifierInlines.h>
#include <JavaScriptCore/JSCJSValueInlines.h>
#include <JavaScriptCore/JSGlobalObject.h>
#include <JavaScriptCore/JSONObject.h>
#include <JavaScriptCore/StructureInlines.h>
#include <JavaScriptCore/VM.h>
#include <wtf/text/WTFString.h>

using namespace JSC;

namespace WebCore {

namespace ContentExtensions {

namespace ExtensionsManager {

static bool loadTrigger(ExecState& exec, JSObject& ruleObject, ContentExtensionRule::Trigger& trigger)
{
    JSValue triggerObject = ruleObject.get(&exec, Identifier(&exec, "trigger"));
    if (!triggerObject || exec.hadException() || !triggerObject.isObject()) {
        WTFLogAlways("Invalid trigger object.");
        return false;
    }

    JSValue urlFilterObject = triggerObject.get(&exec, Identifier(&exec, "url-filter"));
    if (!urlFilterObject || exec.hadException() || !urlFilterObject.isString()) {
        WTFLogAlways("Invalid url-filter object.");
        return false;
    }

    String urlFilter = urlFilterObject.toWTFString(&exec);
    if (urlFilter.isEmpty()) {
        WTFLogAlways("Invalid url-filter object. The url is empty.");
        return false;
    }

    trigger.urlFilter = urlFilter;
    return true;
}

static bool loadAction(ExecState& exec, JSObject& ruleObject, ContentExtensionRule::Action& action)
{
    JSValue actionObject = ruleObject.get(&exec, Identifier(&exec, "action"));
    if (!actionObject || exec.hadException() || !actionObject.isObject()) {
        WTFLogAlways("Invalid action object.");
        return false;
    }

    JSValue typeObject = actionObject.get(&exec, Identifier(&exec, "type"));
    if (!typeObject || exec.hadException() || !typeObject.isString()) {
        WTFLogAlways("Invalid url-filter object.");
        return false;
    }

    String actionType = typeObject.toWTFString(&exec);
    if (actionType != "block") {
        WTFLogAlways("Unrocognized action: \"%s\"", actionType.utf8().data());
        return false;
    }

    action.type = ExtensionActionType::BlockLoad;

    return true;
}

static void loadRule(ExecState& exec, JSObject& ruleObject, Vector<ContentExtensionRule>& ruleList)
{
    ContentExtensionRule::Trigger trigger;
    if (!loadTrigger(exec, ruleObject, trigger))
        return;

    ContentExtensionRule::Action action;
    if (!loadAction(exec, ruleObject, action))
        return;

    ruleList.append(ContentExtensionRule(trigger, action));
}

void loadExtension(const String& identifier, const String& rules)
{
    Vector<ContentExtensionRule> ruleList;

    RefPtr<VM> vm = VM::create();

    JSLockHolder locker(vm.get());
    JSGlobalObject* globalObject = JSGlobalObject::create(*vm, JSGlobalObject::createStructure(*vm, jsNull()));

    ExecState* exec = globalObject->globalExec();
    JSValue decodedRules = JSONParse(exec, rules);
    if (decodedRules.isObject()) {
        JSObject* topLevelObject = decodedRules.toObject(exec);
        if (!topLevelObject || exec->hadException()) {
            WTFLogAlways("Invalid input, the top level structure is not an object.");
            return;
        }

        if (!isJSArray(topLevelObject)) {
            WTFLogAlways("Invalid input, the top level object is not an array.");
            return;
        }

        JSArray* topLevelArray = jsCast<JSArray*>(topLevelObject);

        unsigned length = topLevelArray->length();
        for (unsigned i = 0; i < length; ++i) {
            JSValue value = topLevelArray->getIndex(exec, i);
            if (exec->hadException() || !value) {
                WTFLogAlways("Invalid object in the array.");
                continue;
            }

            JSObject* ruleObject = value.toObject(exec);
            if (!ruleObject || exec->hadException()) {
                WTFLogAlways("Invalid rule");
                continue;
            }
            loadRule(*exec, *ruleObject, ruleList);
        }
    }

    vm.clear();

    if (ruleList.isEmpty()) {
        WTFLogAlways("Empty extension.");
        return;
    }

    ContentExtensionsBackend::sharedInstance().setRuleList(identifier, ruleList);
}

} // namespace ExtensionsManager
} // namespace ContentExtensions
} // namespace WebCore

#endif // ENABLE(CONTENT_EXTENSIONS)
