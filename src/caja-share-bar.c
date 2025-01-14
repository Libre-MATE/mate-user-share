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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "caja-share-bar.h"

#include <glib/gi18n-lib.h>
#include <gtk/gtk.h>

typedef struct {
  GtkWidget *label;
} CajaShareBarPrivate;

enum { PROP_0, PROP_LABEL };

G_DEFINE_TYPE_WITH_PRIVATE(CajaShareBar, caja_share_bar, GTK_TYPE_INFO_BAR)

static void caja_share_bar_set_property(GObject *object, guint prop_id,
                                        const GValue *value,
                                        GParamSpec *pspec) {
  CajaShareBarPrivate *priv;

  priv = caja_share_bar_get_instance_private(CAJA_SHARE_BAR(object));

  switch (prop_id) {
    case PROP_LABEL: {
      gtk_label_set_text(GTK_LABEL(priv->label), g_value_get_string(value));
      break;
    }
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

static void caja_share_bar_class_init(CajaShareBarClass *klass) {
  GObjectClass *object_class = G_OBJECT_CLASS(klass);

  object_class->set_property = caja_share_bar_set_property;

  g_object_class_install_property(
      G_OBJECT_CLASS(klass), PROP_LABEL,
      g_param_spec_string("label", "label", "The widget's main label", NULL,
                          G_PARAM_WRITABLE));
}

static void caja_share_bar_init(CajaShareBar *bar) {
  GtkWidget *content_area;
  GtkWidget *action_area;
  GtkWidget *label;
  GtkWidget *vbox;
  GtkWidget *button;
  PangoAttrList *attrs;
  CajaShareBarPrivate *priv;

  priv = caja_share_bar_get_instance_private(bar);

  content_area = gtk_info_bar_get_content_area(GTK_INFO_BAR(bar));
  action_area = gtk_info_bar_get_action_area(GTK_INFO_BAR(bar));
  gtk_button_box_set_layout(GTK_BUTTON_BOX(action_area), GTK_BUTTONBOX_CENTER);

  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
  gtk_container_add(GTK_CONTAINER(content_area), vbox);

  attrs = pango_attr_list_new();
  pango_attr_list_insert(attrs, pango_attr_weight_new(PANGO_WEIGHT_BOLD));
  label = gtk_label_new(_("Personal File Sharing"));
  gtk_label_set_attributes(GTK_LABEL(label), attrs);
  pango_attr_list_unref(attrs);

  gtk_label_set_xalign(GTK_LABEL(label), 0.0);
  gtk_label_set_yalign(GTK_LABEL(label), 0.5);
  gtk_widget_show(label);
  gtk_container_add(GTK_CONTAINER(vbox), label);

  priv->label = gtk_label_new(NULL);
  gtk_label_set_xalign(GTK_LABEL(priv->label), 0.0);
  gtk_label_set_yalign(GTK_LABEL(priv->label), 0.5);
  gtk_widget_show(priv->label);
  gtk_container_add(GTK_CONTAINER(vbox), priv->label);

  button = gtk_info_bar_add_button(GTK_INFO_BAR(bar), _("Preferences"),
                                   CAJA_SHARE_BAR_RESPONSE_PREFERENCES);

  gtk_widget_set_tooltip_text(button,
                              _("Launch Personal File Sharing Preferences"));

  gtk_widget_show_all(vbox);
}

GtkWidget *caja_share_bar_new(const char *label) {
  return g_object_new(CAJA_TYPE_SHARE_BAR, "message-type", GTK_MESSAGE_QUESTION,
                      "label", label, NULL);
}
