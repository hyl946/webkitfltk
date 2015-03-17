# - Try to find OpenWebRTC.
# Once done, this will define
#
#  OPENWEBRTC_FOUND - system has OpenWebRTC.
#  OPENWEBRTC_INCLUDE_DIRS - the OpenWebRTC include directories
#  OPENWEBRTC_LIBRARIES - link these to use OpenWebRTC.
#
# Copyright (C) 2015 Igalia S.L.
# Copyright (C) 2015 Metrological.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1.  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
# 2.  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND ITS CONTRIBUTORS ``AS
# IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR ITS
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

find_package(PkgConfig)
pkg_check_modules(OPENWEBRTC openwebrtc-0.1)

set(VERSION_OK TRUE)
if (OPENWEBRTC_VERSION)
    if (OPENWEBRTC_FIND_VERSION_EXACT)
        if (NOT("${OPENWEBRTC_FIND_VERSION}" VERSION_EQUAL "${OPENWEBRTC_VERSION}"))
            set(VERSION_OK FALSE)
        endif ()
    else ()
        if ("${OPENWEBRTC_VERSION}" VERSION_LESS "${OPENWEBRTC_FIND_VERSION}")
            set(VERSION_OK FALSE)
        endif ()
    endif ()
endif ()

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OPENWEBRTC DEFAULT_MSG OPENWEBRTC_INCLUDE_DIRS OPENWEBRTC_LIBRARIES VERSION_OK)
