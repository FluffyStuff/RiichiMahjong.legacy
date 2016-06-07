using GameServer;

public class ServerMenuView : View2D
{
    private ServerController? server = null;
    private IGameConnection? connection = null;
    private Mutex mutex = Mutex();
    private string name;
    private bool host = false;
    private bool can_control;
    private ServerSettings settings = new ServerSettings.from_disk();

    private ServerSettingsView settings_view;
    private ServerPlayerFieldView[] players = new ServerPlayerFieldView[4];
    private MenuTextButton start_button;
    private MenuTextButton settings_button;
    private MenuTextButton back_button;
    private LabelControl label;

    public signal void start(GameStartInfo info, ServerSettings settings, IGameConnection connection, int player_index);
    public signal void back();

    public ServerMenuView.create_server(string name)
    {
        host = true;
        this.name = name;
        can_control = true;
    }

    public ServerMenuView.join_server(IGameConnection? connection, bool can_control)
    {
        this.connection = connection;
        this.connection.disconnected.connect(disconnected);
        this.connection.received_message.connect(received_message);
        this.can_control = can_control;
    }

    ~ServerMenuView()
    {
        connection = null; // Fixes warnings because of reasons
    }

    private void start_server()
    {
        server = new ServerController();

        ServerPlayerLocalConnection server_connection = new ServerPlayerLocalConnection();
        GameLocalConnection game_connection = new GameLocalConnection();

        server_connection.set_connection(game_connection);
        game_connection.set_connection(server_connection);

        connection = game_connection;
        connection.disconnected.connect(disconnected);
        connection.received_message.connect(received_message);

        ServerHumanPlayer player = new ServerHumanPlayer(server_connection, name);
        server.add_player(player);

        server.start_listening(1337);

        send_settings(settings);
    }

    protected override void added()
    {
        label = new LabelControl();
        add_child(label);
        label.text = "Server";
        label.font_size = 40;
        label.outer_anchor = Vec2(0.5f, 1);
        label.inner_anchor = Vec2(0.5f, 1);
        label.position = Vec2(0, -60);

        int padding = 50;

        settings_button = new MenuTextButton("MenuButton", "Settings");
        add_child(settings_button);
        settings_button.outer_anchor = Vec2(0.5f, 0);
        settings_button.inner_anchor = Vec2(0.5f, 0);
        settings_button.position = Vec2(0, padding);
        settings_button.clicked.connect(settings_clicked);
        settings_button.enabled = false; // Disable until we receive the settings from the server

        if (can_control)
        {
            start_button = new MenuTextButton("MenuButton", "Start");
            add_child(start_button);
            start_button.outer_anchor = Vec2(0.5f, 0);
            start_button.inner_anchor = Vec2(1, 0);
            start_button.position = Vec2(-padding - settings_button.size.width / 2, padding);
            start_button.clicked.connect(start_clicked);
            start_button.enabled = false;
        }

        back_button = new MenuTextButton("MenuButton", "Back");
        add_child(back_button);
        back_button.outer_anchor = Vec2(0.5f, 0);
        back_button.inner_anchor = Vec2(0, 0);
        back_button.position = Vec2(padding + settings_button.size.width / 2, padding);
        back_button.clicked.connect(back_clicked);

        for (int i = 3; i >= 0; i--)
        {
            ServerPlayerFieldView player = new ServerPlayerFieldView(can_control, i);
            add_child(player);
            player.size = Size2(300, 40);
            player.position = Vec2(0, -(i - 1.5f) * 60);
            player.kick.connect(kick_slot);
            player.add_bot.connect(add_bot);
            players[i] = player;
        }

        if (host)
            start_server();
        else if (can_control)
            send_settings(settings);
    }

    private void kick_slot(int slot)
    {
        connection.send_message(new ClientMessageMenuKickPlayer(slot));
    }

    private void add_bot(string name, int slot)
    {
        connection.send_message(new ClientMessageMenuAddBot(name, slot));
    }

    private void start_clicked()
    {
        connection.send_message(new ClientMessageMenuGameStart());
    }

    private void settings_clicked()
    {
        if (settings == null)
            return;

        toggle_elements(false);

        settings_view = new ServerSettingsView(can_control, settings);
        settings_view.apply_clicked.connect(apply_server_settings);
        settings_view.back_clicked.connect(settings_finished);

        add_child(settings_view);
    }

    private void back_clicked()
    {
        if (host && server != null)
            server.kill();
        back();
    }

    private void apply_server_settings()
    {
        send_settings(settings_view.settings);
        settings_finished();
    }

    private void settings_finished()
    {
        remove_child(settings_view);
        toggle_elements(true);
        settings_view = null;
    }

    private void send_settings(ServerSettings settings)
    {
        string s = FileLoader.array_to_string(settings.to_string());
        connection.send_message(new ClientMessageMenuSettings(s));
    }

    private void toggle_elements(bool visible)
    {
        for (int i = 0; i < players.length; i++)
            players[i].visible = visible;
        if (start_button != null)
            start_button.visible = visible;
        settings_button.visible = visible;
        back_button.visible = visible;
        label.visible = visible;
    }

    private void disconnected()
    {
        back();
    }

    public void received_message()
    {
        mutex.lock();
        ServerMessage? message;

        while ((message = connection.dequeue_message()) != null)
        {
            if (message is ServerMessageGameStart)
                start_message(message as ServerMessageGameStart);
            else if (message is ServerMessageMenuSlotAssign)
                assign_message(message as ServerMessageMenuSlotAssign);
            else if (message is ServerMessageMenuSlotClear)
                clear_message(message as ServerMessageMenuSlotClear);
            else if (message is ServerMessageMenuSettings)
                settings_message(message as ServerMessageMenuSettings);
        }
        mutex.unlock();
    }

    private void start_message(ServerMessageGameStart message)
    {
        connection.received_message.disconnect(received_message);
        start(message.info, settings, connection, message.player_index);
    }

    private void assign_message(ServerMessageMenuSlotAssign message)
    {
        players[message.slot].assign(message.name);
        check_can_start();
    }

    private void clear_message(ServerMessageMenuSlotClear message)
    {
        players[message.slot].unassign();
        check_can_start();
    }

    private void settings_message(ServerMessageMenuSettings message)
    {
        settings.load_string(message.settings);
        settings_button.enabled = true;
    }

    private void check_can_start()
    {
        if (!can_control)
            return;

        for (int i = 0; i < players.length; i++)
        {
            if (!players[i].assigned)
            {
                start_button.enabled = false;
                return;
            }
        }

        start_button.enabled = true;
    }
}
