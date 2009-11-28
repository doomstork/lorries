using Gtk;
using WebKit;

public class LorryBrowser : Window {

    private const string TITLE = "Lorry Browser";
    private const string HOME_URL = "http://images.google.co.uk/images?q=pictures%20of%20lorries&oe=utf-8&rls=com.ubuntu:en-GB:official&client=firefox-a&um=1&ie=UTF-8&sa=N&hl=en&tab=wi";
    private const string DEFAULT_PROTOCOL = "http";

    private Regex protocol_regex;


    private WebView web_view;
    private Label status_bar;


    public LorryBrowser () {
        this.title = LorryBrowser.TITLE;
        set_default_size (800, 600);

        try {
            this.protocol_regex = new Regex (".*://.*");
        } catch (RegexError e) {
            critical ("%s", e.message);
        }

        create_widgets ();
        connect_signals ();

    }


    private void create_widgets () {
/* But don't have too many widgets because it 
   will distract the user from the pictures of lorries  */


        this.web_view = new WebView ();
        var scrolled_window = new ScrolledWindow (null, null);
        scrolled_window.set_policy (PolicyType.AUTOMATIC, PolicyType.AUTOMATIC);
        scrolled_window.add (this.web_view);
        this.status_bar = new Label ("Welcome");
        this.status_bar.xalign = 0;
        var vbox = new VBox (false, 0);
        vbox.add (scrolled_window);
        vbox.pack_start (this.status_bar, false, true, 0);
        add (vbox);
    }

    private void connect_signals () {
        this.destroy.connect (Gtk.main_quit);
        this.web_view.title_changed.connect ((source, frame, title) => {
            this.title = "%s - %s".printf (title, LorryBrowser.TITLE);
        });
    }


    public void start () {
        show_all ();
        this.web_view.open (LorryBrowser.HOME_URL);
    }

    public static int main (string[] args) {
        Gtk.init (ref args);

        var browser = new LorryBrowser ();
        browser.start ();

        Gtk.main ();

        return 0;
    }
}
