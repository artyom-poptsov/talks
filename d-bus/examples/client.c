/* Copyright (C) 2024 Artyom V. Poptsov <poptsov.artyom@gmail.com>
 *
 * To the extent possible under law, the person who associated CC0 with
 * this work has waived all copyright and related or neighboring rights
 * to this work.  See
 * <https://creativecommons.org/publicdomain/zero/1.0/>
 */

#include <glib.h>
#include <glib/gprintf.h>
#include <gio/gio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
#if OLD_GLIB
	g_type_init ();
#endif

	GError *error = NULL;
	GDBusConnection *con = g_bus_get_sync (G_BUS_TYPE_SESSION, NULL, &error);

	if (error) {
		g_printf ("Failed to get bus access - %i : %s\n", error->code, error->message);
		g_error_free (error);
    error = NULL;
		return EXIT_FAILURE;
	}

  GDBusMessage *msg = g_dbus_message_new_method_call ("com.example.server",
                                                      "/com/example/server/obj",
                                                      "com.example.server.interface",
                                                      "getRandomJoke");
  GDBusMessage *resp = g_dbus_connection_send_message_with_reply_sync (con,
                                                                       msg,
                                                                       G_DBUS_SEND_MESSAGE_FLAGS_NONE,
                                                                       -1,
                                                                       NULL,
                                                                       NULL,
                                                                       &error);

  gchar* value;
  g_variant_get(g_dbus_message_get_body(resp),
                "(s)",
                &value);

  printf("%s\n", value);

	if (error) {
		g_printf ("Failed to call remote method - %i : %s\n",
              error->code,
              error->message);
		g_error_free (error);
    error = NULL;
		g_object_unref (con);
		return EXIT_FAILURE;
	}

	g_object_unref (con);
	return EXIT_SUCCESS;
}
