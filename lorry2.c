
#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#define TYPE_LORRY_BROWSER (lorry_browser_get_type ())
#define LORRY_BROWSER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_LORRY_BROWSER, LorryBrowser))
#define LORRY_BROWSER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_LORRY_BROWSER, LorryBrowserClass))
#define IS_LORRY_BROWSER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_LORRY_BROWSER))
#define IS_LORRY_BROWSER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_LORRY_BROWSER))
#define LORRY_BROWSER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_LORRY_BROWSER, LorryBrowserClass))

typedef struct _LorryBrowser LorryBrowser;
typedef struct _LorryBrowserClass LorryBrowserClass;
typedef struct _LorryBrowserPrivate LorryBrowserPrivate;
#define _g_regex_unref0(var) ((var == NULL) ? NULL : (var = (g_regex_unref (var), NULL)))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))

struct _LorryBrowser {
	GtkWindow parent_instance;
	LorryBrowserPrivate * priv;
};

struct _LorryBrowserClass {
	GtkWindowClass parent_class;
};

struct _LorryBrowserPrivate {
	GRegex* protocol_regex;
	WebKitWebView* web_view;
	GtkLabel* status_bar;
};


static gpointer lorry_browser_parent_class = NULL;

GType lorry_browser_get_type (void);
#define LORRY_BROWSER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_LORRY_BROWSER, LorryBrowserPrivate))
enum  {
	LORRY_BROWSER_DUMMY_PROPERTY
};
#define LORRY_BROWSER_TITLE "Lorry Browser"
#define LORRY_BROWSER_HOME_URL "http://images.google.co.uk/images?q=pictures%20of%20lorries&oe=utf-8&rls=com.ubuntu:en-GB:official&client=firefox-a&um=1&ie=UTF-8&sa=N&hl=en&tab=wi"
#define LORRY_BROWSER_DEFAULT_PROTOCOL "http"
static void lorry_browser_create_widgets (LorryBrowser* self);
static void lorry_browser_connect_signals (LorryBrowser* self);
LorryBrowser* lorry_browser_new (void);
LorryBrowser* lorry_browser_construct (GType object_type);
static void _gtk_main_quit_gtk_object_destroy (GtkObject* _sender, gpointer self);
static void _lambda0_ (WebKitWebView* source, WebKitWebFrame* frame, const char* title, LorryBrowser* self);
static void __lambda0__webkit_web_view_title_changed (WebKitWebView* _sender, WebKitWebFrame* p0, const char* p1, gpointer self);
void lorry_browser_start (LorryBrowser* self);
gint lorry_browser_main (char** args, int args_length1);
static void lorry_browser_finalize (GObject* obj);



LorryBrowser* lorry_browser_construct (GType object_type) {
	GError * _inner_error_;
	LorryBrowser * self;
	_inner_error_ = NULL;
	self = g_object_newv (object_type, 0, NULL);
	gtk_window_set_title ((GtkWindow*) self, LORRY_BROWSER_TITLE);
	gtk_window_set_default_size ((GtkWindow*) self, 800, 600);
	{
		GRegex* _tmp0_;
		GRegex* _tmp1_;
		_tmp0_ = g_regex_new (".*://.*", 0, 0, &_inner_error_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_REGEX_ERROR) {
				goto __catch0_g_regex_error;
			}
			goto __finally0;
		}
		self->priv->protocol_regex = (_tmp1_ = _tmp0_, _g_regex_unref0 (self->priv->protocol_regex), _tmp1_);
	}
	goto __finally0;
	__catch0_g_regex_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			g_critical ("lorry2.vala:24: %s", e->message);
			_g_error_free0 (e);
		}
	}
	__finally0:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	lorry_browser_create_widgets (self);
	lorry_browser_connect_signals (self);
	return self;
}


LorryBrowser* lorry_browser_new (void) {
	return lorry_browser_construct (TYPE_LORRY_BROWSER);
}


static void lorry_browser_create_widgets (LorryBrowser* self) {
	WebKitWebView* _tmp0_;
	GtkScrolledWindow* scrolled_window;
	GtkLabel* _tmp1_;
	GtkVBox* vbox;
	g_return_if_fail (self != NULL);
	self->priv->web_view = (_tmp0_ = g_object_ref_sink ((WebKitWebView*) webkit_web_view_new ()), _g_object_unref0 (self->priv->web_view), _tmp0_);
	scrolled_window = g_object_ref_sink ((GtkScrolledWindow*) gtk_scrolled_window_new (NULL, NULL));
	gtk_scrolled_window_set_policy (scrolled_window, GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add ((GtkContainer*) scrolled_window, (GtkWidget*) self->priv->web_view);
	self->priv->status_bar = (_tmp1_ = g_object_ref_sink ((GtkLabel*) gtk_label_new ("Welcome")), _g_object_unref0 (self->priv->status_bar), _tmp1_);
	g_object_set ((GtkMisc*) self->priv->status_bar, "xalign", (float) 0, NULL);
	vbox = g_object_ref_sink ((GtkVBox*) gtk_vbox_new (FALSE, 0));
	gtk_container_add ((GtkContainer*) vbox, (GtkWidget*) scrolled_window);
	gtk_box_pack_start ((GtkBox*) vbox, (GtkWidget*) self->priv->status_bar, FALSE, TRUE, (guint) 0);
	gtk_container_add ((GtkContainer*) self, (GtkWidget*) vbox);
	_g_object_unref0 (scrolled_window);
	_g_object_unref0 (vbox);
}


static void _gtk_main_quit_gtk_object_destroy (GtkObject* _sender, gpointer self) {
	gtk_main_quit ();
}


static void _lambda0_ (WebKitWebView* source, WebKitWebFrame* frame, const char* title, LorryBrowser* self) {
	char* _tmp0_;
	g_return_if_fail (source != NULL);
	g_return_if_fail (frame != NULL);
	g_return_if_fail (title != NULL);
	gtk_window_set_title ((GtkWindow*) self, _tmp0_ = g_strdup_printf ("%s - %s", title, LORRY_BROWSER_TITLE));
	_g_free0 (_tmp0_);
}


static void __lambda0__webkit_web_view_title_changed (WebKitWebView* _sender, WebKitWebFrame* p0, const char* p1, gpointer self) {
	_lambda0_ (_sender, p0, p1, self);
}


static void lorry_browser_connect_signals (LorryBrowser* self) {
	g_return_if_fail (self != NULL);
	g_signal_connect ((GtkObject*) self, "destroy", (GCallback) _gtk_main_quit_gtk_object_destroy, NULL);
	g_signal_connect_object (self->priv->web_view, "title-changed", (GCallback) __lambda0__webkit_web_view_title_changed, self, 0);
}


void lorry_browser_start (LorryBrowser* self) {
	g_return_if_fail (self != NULL);
	gtk_widget_show_all ((GtkWidget*) self);
	webkit_web_view_open (self->priv->web_view, LORRY_BROWSER_HOME_URL);
}


gint lorry_browser_main (char** args, int args_length1) {
	gint result;
	LorryBrowser* browser;
	gtk_init (&args_length1, &args);
	browser = g_object_ref_sink (lorry_browser_new ());
	lorry_browser_start (browser);
	gtk_main ();
	result = 0;
	_g_object_unref0 (browser);
	return result;
}


int main (int argc, char ** argv) {
	g_thread_init (NULL);
	g_type_init ();
	return lorry_browser_main (argv, argc);
}


static void lorry_browser_class_init (LorryBrowserClass * klass) {
	lorry_browser_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (LorryBrowserPrivate));
	G_OBJECT_CLASS (klass)->finalize = lorry_browser_finalize;
}


static void lorry_browser_instance_init (LorryBrowser * self) {
	self->priv = LORRY_BROWSER_GET_PRIVATE (self);
}


static void lorry_browser_finalize (GObject* obj) {
	LorryBrowser * self;
	self = LORRY_BROWSER (obj);
	_g_regex_unref0 (self->priv->protocol_regex);
	_g_object_unref0 (self->priv->web_view);
	_g_object_unref0 (self->priv->status_bar);
	G_OBJECT_CLASS (lorry_browser_parent_class)->finalize (obj);
}


GType lorry_browser_get_type (void) {
	static GType lorry_browser_type_id = 0;
	if (lorry_browser_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (LorryBrowserClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) lorry_browser_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (LorryBrowser), 0, (GInstanceInitFunc) lorry_browser_instance_init, NULL };
		lorry_browser_type_id = g_type_register_static (GTK_TYPE_WINDOW, "LorryBrowser", &g_define_type_info, 0);
	}
	return lorry_browser_type_id;
}




