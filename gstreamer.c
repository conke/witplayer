#include <gst/gst.h>
#include "gstreamer.h"

static gboolean cb_print_position(GstElement *pipeline)
{
	GstFormat fmt = GST_FORMAT_TIME;
	gint64 pos, len;

	if (gst_element_query_position(pipeline, &fmt, &pos)
			&& gst_element_query_duration(pipeline, &fmt, &len)) {
		g_print("Time:%" GST_TIME_FORMAT " / %" GST_TIME_FORMAT "\r",
				GST_TIME_ARGS(pos), GST_TIME_ARGS(len));
	}

	return TRUE;
}

static gboolean bus_call(GstBus *bus, GstMessage *msg, gpointer data)
{
	GMainLoop *loop = (GMainLoop *) data;

	switch (GST_MESSAGE_TYPE(msg)) {
		case GST_MESSAGE_EOS:
			g_print("End of stream\n");
			g_main_loop_quit(loop);
			break;

		case GST_MESSAGE_ERROR:
			{
				gchar *debug;
				GError *error;

				gst_message_parse_error(msg, &error, &debug);
				g_free(debug);
				g_printerr("ERROR:%s\n", error->message);
				g_error_free(error);
				g_main_loop_quit(loop);
			}
			break;

		default:
			break;
	}

	return TRUE;
}

int gstreamer_play(const char *path)
{
	GMainLoop *loop;
	GstElement *pipeline, *source, *decoder, *sink;
	GstBus *bus;

	gst_init(NULL, NULL);
	loop = g_main_loop_new(NULL, FALSE);

	pipeline = gst_pipeline_new("audio-player");
	if (!strncmp(path, HTTP_URL, HTTP_LEN))
		source = gst_element_make_from_uri(GST_URI_SRC, path, "source");
	else
		source = gst_element_factory_make("filesrc", "file-src");
	decoder = gst_element_factory_make("mad", "mad-decoder");
	sink = gst_element_factory_make("alsasink", "audio-output");
	if (!pipeline || !source || !decoder || !sink) {
		g_printerr("One element could not be created.Exiting.\n");
		return -1;
	}

	g_object_set(G_OBJECT(source), "location", path, NULL);
	bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));

	gst_bus_add_watch(bus, bus_call, loop);
	gst_object_unref(bus);
	gst_bin_add_many(GST_BIN(pipeline), source, decoder, sink, NULL);
	gst_element_link_many(source, decoder, sink, NULL);

	gst_element_set_state(pipeline, GST_STATE_PLAYING);
	g_print("Running\n");

	g_timeout_add(200, (GSourceFunc)cb_print_position, pipeline);
	g_main_loop_run(loop);
	g_print("Returned, stopping playback\n");
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(GST_OBJECT(pipeline));

	return 0;
}
