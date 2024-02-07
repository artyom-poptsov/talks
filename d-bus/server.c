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

enum { MAX_STRING_LENGTH = 256 };
static gchar JOKES[][MAX_STRING_LENGTH] = {
  "Основные изменения в новой версии программы: исправлены старые баги, добавлены новые.",
  "Опытный разработчик всегда посмотрит направо и налево, даже если переходит улицу с односторонним движением.",
  "Сколько программистов надо, чтобы вкрутить одну лампочку? – Ни одного. В этом случае отсутствие света – проблема на стороне железа.",
  "Существует два вида языков программирования: одни – все ругают, другими не пользуются.",
  "Перед тем, как удалять файлы, убедитесь, что они не ваши.",
  "На самом деле большинство багов – это фичи, просто не задокументированные.",
  "Если никто не знает ответ на вопрос, пора начать читать документацию.",
  "Программист звонит в библиотеку.\n\
  — Здравствуйте, Катю можно?\n\
  — Она в архиве.\n\
  — Разархивируйте ее пожалуйста. Она мне срочно нужна!"
};

/* Introspection data for the service we are exporting */
static const gchar INTROSPECTION_XML[] =
  "<node>"
  "  <interface name='com.example.server.interface'>"
  "    <method name='getRandomJoke'>"
  "      <arg name='request' type='s' direction='out'/>"
  "    </method>"
  "  </interface>"
  "  <interface name='org.freedesktop.DBus.Properties'>"
  "    <method name='Get'>"
  "      <arg name='interface_name' type='s' direction='in'/>"
  "      <arg name='property_name' type='s' direction='in'/>"
  "      <arg name='value' type='v' direction='out'/>"
  "    </method>"
  "    <method name='Set'>"
  "      <arg name='interface_name' type='s' direction='in'/>"
  "      <arg name='property_name' type='s' direction='in'/>"
  "      <arg name='value' type='v' direction='in'/>"
  "    </method>"
  "    <method name='GetAll'>"
  "      <arg name='interface_name' type='s' direction='in'/>"
  "      <arg name='values' type='a{sv}' direction='out'/>"
  "    </method>"
  "  </interface>"
  "  <interface name='org.freedesktop.DBus.Introspectable'>"
  "    <method name='Introspect'>"
  "      <arg name='xml_data' type='s' direction='out'/>"
  "    </method>"
  "  </interface>"
  "</node>";

static GDBusNodeInfo *introspection_data = NULL;

static GVariant* get_random_joke() {
  int n = rand() % sizeof(JOKES) / sizeof(JOKES[0]);
  return g_variant_new ("(s)", JOKES[n]);
}

static void handle_method_call(GDBusConnection       *connection,
                               const gchar           *sender,
                               const gchar           *object_path,
                               const gchar           *interface_name,
                               const gchar           *method_name,
                               GVariant              *parameters,
                               GDBusMethodInvocation *invocation,
                               gpointer               user_data)
{
	const gchar *uniquebusname = g_dbus_connection_get_unique_name (connection);
	g_printf ("server: Inside Handle Method Call -- sender %s -- bus %s --- %s\n",
            sender,
            uniquebusname,
            method_name);

	if ( g_strcmp0 (method_name, "getRandomJoke") == 0 ) {
    GVariant* value = get_random_joke();
    g_dbus_method_invocation_return_value (invocation, value);
  } else {
		g_warning ("server: Oh noes! No method registered for \"%s\"\n",
               method_name);
		g_dbus_method_invocation_return_error (invocation,
                                           g_quark_from_string ("bugdemoserver"),
                                           99,
                                           "server does not know method \"%s\"",
                                           method_name);
	}
}

static const GDBusInterfaceVTable interface_vtable = {
  handle_method_call, /* method call*/
  NULL, /* get_prop */
  NULL /* set_prop */
};

static void on_bus_acquired (GDBusConnection *connection,
                             const gchar     *name,
                             gpointer         user_data)
{
	GError *error = NULL;
	g_printf ("\n Inside on_bus_acquired \n");

	guint registration_id;

	registration_id = g_dbus_connection_register_object (connection,
	                                                     "/com/example/server/obj", /* object path */
	                                                     introspection_data->interfaces[0],/*pick the first interface*/
	                                                     &interface_vtable,
	                                                     NULL,  /* user_data */
	                                                     NULL,  /* user_data_free_func */
	                                                     &error); /* GError** */
	g_printf("object registered to id %u\n", registration_id);
	g_assert(!error);
}

static void on_name_acquired (GDBusConnection *connection,
                              const gchar     *name,
                              gpointer         user_data)
{
	g_printf("name: %s\n", name);
}

static void on_name_lost (GDBusConnection *connection,
                          const gchar     *name,
                          gpointer         user_data)
{
	g_warning ("lost name ownership! leave sinking ship\n");
	exit (1);
}

int main (int argc, char *argv[])
{
#if OLD_GLIB
	g_type_init ();
#endif

	GError *error = NULL;
	guint owner_id;
	GMainLoop *loop = g_main_loop_new (NULL, FALSE);

  srand( time(0) );

	introspection_data = g_dbus_node_info_new_for_xml (INTROSPECTION_XML, NULL);
	g_assert (introspection_data);

	owner_id = g_bus_own_name (G_BUS_TYPE_SESSION,
	                           "com.example.server",
	                           G_BUS_NAME_OWNER_FLAGS_NONE,
	                           on_bus_acquired,
	                           on_name_acquired,
	                           on_name_lost,
	                           NULL,
	                           (GDestroyNotify) NULL);
	g_assert (!error);

	g_printf ("\n Owner id is %d ", owner_id);

	g_main_loop_run (loop);

	g_bus_unown_name (owner_id);

	g_dbus_node_info_unref (introspection_data);

	return EXIT_SUCCESS;
}
