/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2005 William Jon McCann <mccann@jhu.edu>
 * Copyright (C) 2012-2021 MATE Developers
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Authors: William Jon McCann <mccann@jhu.edu>
 *
 */

#ifndef __CAJA_SHARE_BAR_H
#define __CAJA_SHARE_BAR_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define CAJA_TYPE_SHARE_BAR (caja_share_bar_get_type())
G_DECLARE_DERIVABLE_TYPE(CajaShareBar, caja_share_bar, CAJA, SHARE_BAR,
                         GtkInfoBar)

#define CAJA_SHARE_BAR_RESPONSE_PREFERENCES 1

struct _CajaShareBarClass {
  GtkInfoBarClass parent_class;

  void (*activate)(CajaShareBar *bar);
};

GtkWidget *caja_share_bar_new(const char *label);

GtkWidget *caja_share_bar_get_button(CajaShareBar *bar);

G_END_DECLS

#endif /* __GS_SHARE_BAR_H */
