/*
 * Copyright (C) 2009 Collabora Ltd.
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

#ifndef webkitnewtorkresponse_h
#define webkitnewtorkresponse_h

#include <webkit/webkitdefines.h>

class WebKitNetworkResponse {
public:
	WebKitNetworkResponse(const char *uri);
	~WebKitNetworkResponse();

	void set_uri(const char *uri);
	const char *get_uri();
	// curl get_message();
	const char *get_suggested_filename();
private:
	const char *uri;
	const char *suggestedFilename;
	// curl something?
};

#endif
