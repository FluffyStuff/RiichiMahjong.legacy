using GameServer;

public class JoinMenuView : View2D
{
    private IGameConnection? connection;
    private MenuTextButton join_button;
    private MenuTextButton back_button;
    private LabelControl info_label;
    private TextInputControl server_text;
    private TextInputControl name_text;
    private string name;
    private bool connecting = false;

    private DelayTimer timer = new DelayTimer();
    private int delay_time = 5;

    public signal void joined(IGameConnection connection, string name);
    public signal void back();

    protected override void added()
    {
        int padding = 60;

        LabelControl label = new LabelControl();
        add_child(label);
        label.text = "Join Server";
        label.font_size = 40;
        label.outer_anchor = Vec2(0.5f, 1);
        label.inner_anchor = Vec2(0.5f, 1);
        label.position = Vec2(0, -padding);

        info_label = new LabelControl();
        add_child(info_label);
        info_label.font_size = 40;
        info_label.outer_anchor = Vec2(0.5f, 1);
        info_label.inner_anchor = Vec2(0.5f, 1);
        info_label.position = Vec2(0, label.position.y - padding);

        server_text = new TextInputControl("Hostname", 50);
        add_child(server_text);
        server_text.position = Vec2(0, padding);

        name_text = new TextInputControl("Player name", Environment.MAX_NAME_LENGTH);
        add_child(name_text);
        name_text.position = Vec2(0, -padding);

        join_button = new MenuTextButton("MenuButton", "Join");
        add_child(join_button);
        join_button.outer_anchor = Vec2(0.5f, 0);
        join_button.inner_anchor = Vec2(1, 0);
        join_button.position = Vec2(-padding, padding);
        join_button.clicked.connect(join_clicked);
        join_button.enabled = false;

        back_button = new MenuTextButton("MenuButton", "Back");
        add_child(back_button);
        back_button.outer_anchor = Vec2(0.5f, 0);
        back_button.inner_anchor = Vec2(0, 0);
        back_button.position = Vec2(padding, padding);
        back_button.clicked.connect(back_clicked);

        name_text.text_changed.connect(name_changed);
    }

    protected override void do_process(DeltaArgs delta)
    {
        if (!connecting)
            return;

        if (timer.active(delta.time))
        {
            info_label.text = "Error: Failed to connect";
            join_button.enabled = true;
            connecting = false;
        }
    }

    private void name_changed()
    {
        join_button.enabled = !connecting && Environment.is_valid_name(name_text.text);
    }

    private void join_clicked()
    {
        join_button.enabled = false;
        info_label.text = "Connecting...";
        connecting = true;
        timer.set_time(delay_time);

        string host = server_text.text;
        name = name_text.text;

        Threading.start2(try_join, new Obj<string>(host), new Obj<string>(name));
    }

    private void try_join(Object host_obj, Object name_obj)
    {
        string host = ((Obj<string>)host_obj).obj;
        string name = ((Obj<string>)name_obj).obj;

        Connection? con = Networking.join(host, 1337);

        if (con == null)
        {
            info_label.text = "Error: Failed to connect";
            join_button.enabled = true;
            connecting = false;
        }
        else
        {
            info_label.text = "Connected";
            connection = new GameNetworkConnection(con);
            connection.received_message.connect(received_message);
            connection.disconnected.connect(disconnected);
            connection.send_message(new ClientMessageAuthenticate(name, Environment.version_info));
        }
    }

    private void received_message()
    {
        ServerMessage? message;

        while ((message = connection.dequeue_message()) != null)
        {
            ServerMessageAcceptJoin msg = message as ServerMessageAcceptJoin;
            if (msg == null)
                continue;

            if (msg.version_mismatch || !Environment.compatible(msg.version_info))
            {
                connection.disconnected.disconnect(disconnected);
                connection.close();
                connection = null;
                join_button.enabled = true;
                info_label.text = "Error: Version mismatch\n" + "Please get the latest version";
                connecting = false;
                return;
            }

            joined(connection, name);
            break;
        }
    }

    private void disconnected()
    {
        connection.close();
        connection = null;
        join_button.enabled = true;
        info_label.text = "Error: Connection closed";
        connecting = false;
        return;
    }

    private void back_clicked()
    {
        back();
    }
}
