set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 11)
set(PROJECT_VERSION_MICRO 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_MICRO})

add_definitions(-DBUILDING_EFL__=1)

set(ENABLE_WEBKIT OFF)
set(ENABLE_WEBKIT2 ON)

# FIXME: Disable WERROR in clang build because of many warnings.
if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(ADDITIONAL_COMPILER_FLAGS ENABLE_WERROR)
endif ()

find_package(Cairo 1.10.2 REQUIRED)
find_package(Fontconfig 2.8.0 REQUIRED)
find_package(Sqlite REQUIRED)
find_package(LibXml2 2.8.0 REQUIRED)
find_package(LibXslt 1.1.7 REQUIRED)
find_package(ICU REQUIRED)
find_package(Threads REQUIRED)
find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)
find_package(ZLIB REQUIRED)

set(glib_components gio gobject gthread)
if (ENABLE_GEOLOCATION)
    list(APPEND glib_components gio-unix)
endif ()
find_package(GLIB 2.38.0 REQUIRED COMPONENTS ${glib_components})
find_package(LibSoup 2.42.0 REQUIRED)

set(WTF_USE_SOUP 1)
set(WTF_USE_UDIS86 1)

add_definitions(-DWTF_USE_GLIB=1)
add_definitions(-DWTF_USE_SOUP=1)
add_definitions(-DWTF_USE_CAIRO=1)
add_definitions(-DWTF_USE_CROSS_PLATFORM_CONTEXT_MENUS=1)

set(WTF_LIBRARY_TYPE STATIC)
set(WTF_OUTPUT_NAME wtf_efl)
set(JavaScriptCore_OUTPUT_NAME javascriptcore_efl)
set(WebCore_OUTPUT_NAME webcore_efl)
set(WebKit2_OUTPUT_NAME ewebkit2)

set(DATA_INSTALL_DIR "share/${WebKit2_OUTPUT_NAME}-${PROJECT_VERSION_MAJOR}" CACHE PATH "Installation path for theme data")
set(THEME_BINARY_DIR ${CMAKE_BINARY_DIR}/WebCore/platform/efl/DefaultTheme)
file(MAKE_DIRECTORY ${THEME_BINARY_DIR})

add_definitions(-DDATA_DIR="${CMAKE_INSTALL_PREFIX}/${DATA_INSTALL_DIR}"
                -DTEST_THEME_DIR="${THEME_BINARY_DIR}")

WEBKIT_OPTION_BEGIN()

if (DEVELOPER_MODE)
    set(ENABLE_TOOLS ON)
    WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_API_TESTS ON)
else ()
    set(ENABLE_TOOLS OFF)
    WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_API_TESTS OFF)

    set(WEBKIT2_VERSION_SCRIPT "-Wl,--version-script,${CMAKE_MODULE_PATH}/eflsymbols.filter")
endif ()

WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_3D_RENDERING ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_ACCESSIBILITY ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_BATTERY_STATUS ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS3_CONDITIONAL_RULES ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS3_TEXT ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS_DEVICE_ADAPTATION ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS_GRID_LAYOUT OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS_IMAGE_SET ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS_REGIONS ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS_SELECTORS_LEVEL4 ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CUSTOM_SCHEME_HANDLER ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_DATALIST_ELEMENT ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_DOM4_EVENTS_CONSTRUCTOR ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_DOWNLOAD_ATTRIBUTE ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_DRAG_SUPPORT ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_ENCRYPTED_MEDIA OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_ENCRYPTED_MEDIA_V2 ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_FILTERS ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_FULLSCREEN_API ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_GAMEPAD OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_GAMEPAD_DEPRECATED ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_GEOLOCATION ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_INDEXED_DATABASE OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_INDEXED_DATABASE_IN_WORKERS OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_INPUT_TYPE_COLOR ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_LINK_PREFETCH ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MEDIA_CAPTURE ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MEDIA_CONTROLS_SCRIPT ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MEMORY_SAMPLER ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MHTML ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MOUSE_CURSOR_SCALE ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_NAVIGATOR_CONTENT_UTILS ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_NAVIGATOR_HWCONCURRENCY ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_NETSCAPE_PLUGIN_API ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_NETWORK_PROCESS ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_NOSNIFF ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_PICTURE_SIZES ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_RESOLUTION_MEDIA_QUERY ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_REQUEST_ANIMATION_FRAME ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_SECCOMP_FILTERS OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_SHARED_WORKERS ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_SPEECH_SYNTHESIS ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_SPELLCHECK ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_TEMPLATE_ELEMENT ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_TOUCH_EVENTS ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_TOUCH_SLIDER ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_USERSELECT_ALL ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_VIBRATION ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_VIDEO ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_VIDEO_TRACK ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_VIEW_MODE_CSS_MEDIA ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_WEB_AUDIO ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_WEB_TIMING ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_WEBGL ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_XHR_TIMEOUT ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(WTF_USE_TILED_BACKING_STORE ON)

if (ENABLE_LLINT_C_LOOP)
    message(STATUS "Force enabling LLINT C LOOP.")
    WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_JIT OFF)
    WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_DFG_JIT OFF)
    WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_FTL_JIT OFF)
endif ()

WEBKIT_OPTION_END()

option(ENABLE_ECORE_X "Enable Ecore_X specific usage (cursor, bell)" ON)
if (ENABLE_ECORE_X)
    # We need Xext.h to disable Xlib error messages  when running WTR on Xvfb.
    # These errors are dumped on stderr and makes the test driver thinks that
    # the test case has failed.
    find_package(X11 REQUIRED)

    list(APPEND ECORE_ADDITIONAL_COMPONENTS X)
    add_definitions(-DHAVE_ECORE_X)
    add_definitions(-DWTF_PLATFORM_X11=1)
    add_definitions(-DMOZ_X11)
endif ()

find_package(Eo QUIET)
if (EO_FOUND)
    add_definitions(-DWTF_USE_EO=1)

    # EFL 1.8 provides FooConfig.cmake and it is preferred because FindFoo.cmake's
    # tricky check routine for version is not availiable on EFL 1.8.
    # But FindFoo.cmake is still required to support EFL 1.7 and config mode of CMake
    # is supported after CMake 2.8.8.
    # So, just disabled version requirement if CMake version is lower than 2.8.8 to
    # build with EFL 1.8. Eo probably guarantee their version.
    if (NOT (CMAKE_VERSION VERSION_LESS 2.8.8))
       set(EFL_CONFIG_MODE CONFIG)
       set(EFL_REQUIRED_VERSION 1.8)
    endif ()
else ()
    set(EFL_REQUIRED_VERSION 1.7)
endif ()

find_package(Eina ${EFL_REQUIRED_VERSION} REQUIRED ${EFL_CONFIG_MODE})
find_package(Evas ${EFL_REQUIRED_VERSION} REQUIRED ${EFL_CONFIG_MODE})
find_package(Ecore ${EFL_REQUIRED_VERSION} COMPONENTS Evas File Input Imf Imf_Evas ${ECORE_ADDITIONAL_COMPONENTS} ${EFL_CONFIG_MODE})
find_package(Edje ${EFL_REQUIRED_VERSION} REQUIRED ${EFL_CONFIG_MODE})
find_package(Eet ${EFL_REQUIRED_VERSION} REQUIRED ${EFL_CONFIG_MODE})
find_package(Eeze ${EFL_REQUIRED_VERSION} REQUIRED ${EFL_CONFIG_MODE})
find_package(Efreet ${EFL_REQUIRED_VERSION} REQUIRED ${EFL_CONFIG_MODE})

find_package(Freetype2 2.4.2 REQUIRED)
find_package(HarfBuzz 0.9.2 REQUIRED)
add_definitions(-DWTF_USE_FREETYPE=1)
add_definitions(-DWTF_USE_HARFBUZZ=1)

if (ENABLE_GEOLOCATION)
    find_package(GeoClue2 2.1.5)
    if (GEOCLUE2_FOUND)
      set(WTF_USE_GEOCLUE2 1)
    else ()
      find_package(GeoClue)
      set(WTF_USE_GEOCLUE2 0)
    endif ()
endif ()

if (ENABLE_NETSCAPE_PLUGIN_API)
    set(ENABLE_PLUGIN_PROCESS 1)
endif ()

if (WTF_OS_UNIX)
    set(ENABLE_X11_TARGET ON)
    add_definitions(-DXP_UNIX)
endif (WTF_OS_UNIX)

if (ENABLE_BATTERY_STATUS OR (EFL_REQUIRED_VERSION VERSION_LESS 1.8))
    find_package(DBus REQUIRED)
    find_package(E_DBus 1.7 COMPONENTS EUKit)
endif ()

if (ENABLE_VIDEO OR ENABLE_WEB_AUDIO)
    set(GSTREAMER_COMPONENTS app mpegts pbutils)
    set(WTF_USE_GSTREAMER 1)
    add_definitions(-DWTF_USE_GSTREAMER=1)

    if (ENABLE_VIDEO)
        list(APPEND GSTREAMER_COMPONENTS video tag)
    endif ()

    if (ENABLE_WEB_AUDIO)
        list(APPEND GSTREAMER_COMPONENTS audio fft)
        add_definitions(-DWTF_USE_WEBAUDIO_GSTREAMER=1)
    endif ()

    find_package(GStreamer 1.0.5 REQUIRED COMPONENTS ${GSTREAMER_COMPONENTS})

    if (PC_GSTREAMER_MPEGTS_FOUND)
        add_definitions(-DWTF_USE_GSTREAMER_MPEGTS)
        set(USE_GSTREAMER_MPEGTS TRUE)
    endif ()
endif ()

add_definitions(-DWTF_USE_COORDINATED_GRAPHICS=1)

add_definitions(-DWTF_USE_TEXTURE_MAPPER=1)

set(WTF_USE_3D_GRAPHICS 1)
add_definitions(-DWTF_USE_3D_GRAPHICS=1)

set(ENABLE_3D_RENDERING 1)
add_definitions(-DENABLE_3D_RENDERING=1)

add_definitions(-DWTF_USE_GRAPHICS_SURFACE=1)

option(ENABLE_GLES2 "Enable GLES Support")
if (ENABLE_GLES2)
    find_package(GLES REQUIRED)

    set(WTF_USE_OPENGL_ES_2 1)
    add_definitions(-DWTF_USE_OPENGL_ES_2=1)
else ()
    find_package(OpenGL REQUIRED)

    set(WTF_USE_OPENGL 1)
    add_definitions(-DWTF_USE_OPENGL=1)
endif ()

option(ENABLE_EGL "Enable EGL Support")
if (ENABLE_EGL)
    find_package(EGL REQUIRED)
    set(WTF_USE_EGL 1)
    add_definitions(-DWTF_USE_EGL=1)
else ()
    CHECK_INCLUDE_FILES("GL/glx.h" OPENGLX_FOUND)
    add_definitions(-DWTF_USE_GLX=1)
endif ()

if (ENABLE_WEBGL AND OPENGLX_FOUND)
    if (NOT X11_Xcomposite_FOUND OR NOT X11_Xrender_FOUND)
        # FIXME: Add support for NOT X11_Xcomposite for GLX
        message(FATAL_ERROR "To use WebGL with GLX support requires X11_Xcomposite.")
    endif ()
endif ()

if (ENABLE_INSPECTOR)
    set(WEB_INSPECTOR_DIR "${DATA_INSTALL_DIR}/inspector")
    set(WEBINSPECTORUI_DIR "${CMAKE_SOURCE_DIR}/Source/WebInspectorUI")
    add_definitions(-DWEB_INSPECTOR_DIR=\"${CMAKE_BINARY_DIR}/${WEB_INSPECTOR_DIR}\")
    add_definitions(-DWEB_INSPECTOR_INSTALL_DIR=\"${CMAKE_INSTALL_PREFIX}/${WEB_INSPECTOR_DIR}\")
endif ()

if (ENABLE_SECCOMP_FILTERS)
    find_package(LibSeccomp REQUIRED)
endif ()

set(CPACK_SOURCE_GENERATOR TBZ2)

# Optimize binary size for release builds by removing dead sections on unix/gcc.
# Push of rbp is needed after JSC JIT uses CStack.
if (CMAKE_COMPILER_IS_GNUCC AND UNIX AND NOT APPLE)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffunction-sections -fdata-sections -fno-omit-frame-pointer -fno-tree-dce")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ffunction-sections -fdata-sections -fno-rtti -fno-omit-frame-pointer -fno-tree-dce")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -Wl,--gc-sections")
endif ()

# FIXME: Consider to use linker script
if (NOT SHARED_CORE AND NOT DEVELOPER_MODE)
    set(CMAKE_C_FLAGS_RELEASE "-fvisibility=hidden ${CMAKE_C_FLAGS_RELEASE}")
    set(CMAKE_CXX_FLAGS_RELEASE "-fvisibility=hidden ${CMAKE_CXX_FLAGS_RELEASE}")
endif ()

if (ENABLE_SPELLCHECK)
    find_package(Enchant REQUIRED)
endif ()

if (ENABLE_ACCESSIBILITY)
    find_package(ATK 2.10.0 REQUIRED)
else ()
    add_definitions(-DHAVE_ACCESSIBILITY=0)
endif ()

if (ENABLE_SPEECH_SYNTHESIS)
    find_package(Espeak REQUIRED)
    add_definitions(-DENABLE_SPEECH_SYNTHESIS=1)
endif ()

if (ENABLE_FTL_JIT)
    find_package(LLVM REQUIRED)
    find_package(LIBCXXABI REQUIRED)
    set(HAVE_LLVM ON)
endif ()

# [E]WebKit2 tests need a hint to find out where processes such as WebProcess are located at.
add_definitions(-DWEBKIT_EXEC_PATH=\"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}\")
