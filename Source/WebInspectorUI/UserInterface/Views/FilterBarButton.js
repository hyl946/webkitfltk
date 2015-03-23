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

WebInspector.FilterBarButton = function(identifier, filterFunction, activatedByDefault, defaultToolTip, activatedToolTip, image, imageWidth, imageHeight, suppressEmboss, role)
{
    WebInspector.ActivateButtonNavigationItem.call(this, identifier, defaultToolTip, activatedToolTip, image, imageWidth, imageHeight, suppressEmboss, role);

    this._filterFunction = filterFunction;

    this._activatedSetting = new WebInspector.Setting(identifier, activatedByDefault);

    this.activated = !!this._activatedSetting.value;
};

WebInspector.FilterBarButton.StyleClassName = "filter-bar-button";

WebInspector.FilterBarButton.Event = {
    ActivatedStateToggled: "filter-bar-activated-state-toggled"
};

WebInspector.FilterBarButton.prototype = {
    constructor: WebInspector.FilterBarButton,
    __proto__: WebInspector.ActivateButtonNavigationItem.prototype,

    // Public

    get filterFunction()
    {
        return this._filterFunction;
    },

    toggle: function()
    {
        this.activated = !this.activated;
        this._activatedSetting.value = this.activated;
        this.dispatchEventToListeners(WebInspector.FilterBarButton.Event.ActivatedStateToggled);
    }
};
