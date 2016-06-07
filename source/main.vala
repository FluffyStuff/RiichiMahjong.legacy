public static int main(string[] args)
{
    Environment.init();

    Engine engine = new Engine();
    if (!engine.init())
        return -1;

    while (true)
    {
        Options options = new Options.from_disk();
        engine.set_multisampling(options.anti_aliasing == Options.OnOffEnum.ON ? 2 : 0);

        bool fullscreen = options.fullscreen == Options.OnOffEnum.ON;
        var wnd = engine.create_window("RiichiMahjong", 1280, 720, fullscreen);
        if (wnd == null)
        {
            Environment.log(LogType.ERROR, "Main", "Could not create window");
            return -1;
        }

        var context = engine.create_context(wnd);
        if (context == null)
        {
            Environment.log(LogType.ERROR, "Main", "Could not create graphics context");
            return -1;
        }

        SDLWindowTarget sdlWindow = new SDLWindowTarget((owned)wnd, (owned)context, fullscreen);
        OpenGLRenderer renderer = new OpenGLRenderer(sdlWindow);
        MainWindow window = new MainWindow(sdlWindow, renderer);

        if (!renderer.start())
        {
            Environment.log(LogType.ERROR, "Main", "Could not start renderer");
            return -1;
        }

        window.show();

        if (!window.do_restart)
            break;
    }

    Environment.log(LogType.INFO, "Main", "Application stopped normally");

    return 0;
}
