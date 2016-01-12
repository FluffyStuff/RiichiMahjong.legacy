using Gee;

public class GameMenuView : View2D
{
    private ScoringView? score_view = null;
    private ArrayList<MenuTextButton> buttons = new ArrayList<MenuTextButton>();

    private int player_index;
    private int decision_time;
    private int round_time;
    private int hanchan_time;
    private int game_time;

    private Sound hint_sound;
    private float start_time;
    private LabelControl timer;
    private LabelControl furiten;

    private MenuTextButton chii;
    private MenuTextButton pon;
    private MenuTextButton kan;
    private MenuTextButton riichi;
    private MenuTextButton open_riichi;
    private MenuTextButton tsumo;
    private MenuTextButton ron;
    private MenuTextButton conti;
    private MenuTextButton void_hand;

    public signal void chii_pressed();
    public signal void pon_pressed();
    public signal void kan_pressed();
    public signal void riichi_pressed(bool open);
    public signal void tsumo_pressed();
    public signal void ron_pressed();
    public signal void continue_pressed();
    public signal void void_hand_pressed();
    public signal void display_score_pressed();

    private void press_chii() { chii_pressed(); }
    private void press_pon() { pon_pressed(); }
    private void press_kan() { kan_pressed(); }
    private void press_riichi() { riichi_pressed(false); }
    private void press_open_riichi() { riichi_pressed(true); }
    private void press_tsumo() { tsumo_pressed(); }
    private void press_ron() { ron_pressed(); }
    private void press_continue() { continue_pressed(); }
    private void press_void_hand() { void_hand_pressed(); }

    public GameMenuView(int player_index, int decision_time, int round_time, int hanchan_time, int game_time)
    {
        this.player_index = player_index;
        this.decision_time = decision_time;
        this.round_time = round_time;
        this.hanchan_time = hanchan_time;
        this.game_time = game_time;
    }

    public override void added()
    {
        hint_sound = store.audio_player.load_sound("hint");

        int padding = 30;
        timer = new LabelControl();
        add_child(timer);
        timer.inner_anchor = Vec2(1, 0);
        timer.outer_anchor = Vec2(1, 0);
        timer.position = Vec2(-padding, padding / 2);
        timer.font_size = 60;
        timer.visible = false;

        furiten = new LabelControl();
        add_child(furiten);
        furiten.inner_anchor = Vec2(0, 0);
        furiten.outer_anchor = Vec2(0, 0);
        furiten.position = Vec2(padding, padding / 2);
        furiten.font_size = 30;
        furiten.visible = false;
        furiten.text = "Furiten";
        furiten.color = Color.red();

        chii = new MenuTextButton("MenuButtonSmall", "Chii");
        pon = new MenuTextButton("MenuButtonSmall", "Pon");
        kan = new MenuTextButton("MenuButtonSmall", "Kan");
        riichi = new MenuTextButton("MenuButtonSmall", "Riichi");
        open_riichi = new MenuTextButton("MenuButtonSmall", "Open Riichi");
        tsumo = new MenuTextButton("MenuButtonSmall", "Tsumo");
        ron = new MenuTextButton("MenuButtonSmall", "Ron");
        conti = new MenuTextButton("MenuButtonSmall", "Continue");
        void_hand = new MenuTextButton("MenuButtonSmall", "Void Hand");

        chii.clicked.connect(press_chii);
        pon.clicked.connect(press_pon);
        kan.clicked.connect(press_kan);
        riichi.clicked.connect(press_riichi);
        open_riichi.clicked.connect(press_open_riichi);
        tsumo.clicked.connect(press_tsumo);
        ron.clicked.connect(press_ron);
        conti.clicked.connect(press_continue);
        void_hand.clicked.connect(press_void_hand);

        buttons.add(chii);
        buttons.add(pon);
        buttons.add(kan);
        buttons.add(riichi);
        buttons.add(open_riichi);
        buttons.add(tsumo);
        buttons.add(ron);
        buttons.add(conti);
        buttons.add(void_hand);

        foreach (var button in buttons)
        {
            add_child(button);
            button.enabled = false;
            button.inner_anchor = Vec2(0.5f, 0);
            button.outer_anchor = Vec2(0.5f, 0);
            button.font_size = 24;
        }

        void_hand.visible = false;
        open_riichi.visible = false; // Disable open riichi for now
        position_buttons();
    }

    private void position_buttons()
    {
        float p = 0;
        float width = 0;

        foreach (var button in buttons)
            if (button.visible)
                width += button.size.width / 2;

        foreach (var button in buttons)
        {
            if (!button.visible)
                continue;

            button.position = Vec2(button.size.width / 2 - width + p, 0);
            p += button.size.width;
        }
    }

    protected override void do_key_press(KeyArgs key)
    {
        if (key.handled)
            return;

        key.handled = true;

        if (key.scancode == ScanCode.TAB && !key.repeat)
        {
            if (key.down)
                display_score_pressed();
            else
                hide_score();
        }
        else
            key.handled = false;
    }

    public void set_chii(bool enabled)
    {
        chii.enabled = enabled;
    }

    public void set_pon(bool enabled)
    {
        pon.enabled = enabled;
    }

    public void set_kan(bool enabled)
    {
        kan.enabled = enabled;
    }

    public void set_riichi(bool enabled)
    {
        riichi.enabled = enabled;
        open_riichi.enabled = enabled;
    }

    public void set_tsumo(bool enabled)
    {
        tsumo.enabled = enabled;
    }

    public void set_ron(bool enabled)
    {
        ron.enabled = enabled;
    }

    public void set_continue(bool enabled)
    {
        if (enabled)
            hint_sound.play();
        conti.enabled = enabled;
    }

    public void set_void_hand(bool enabled)
    {
        void_hand.visible = enabled;
        void_hand.enabled = enabled;
        position_buttons();
    }

    public void set_furiten(bool enabled)
    {
        furiten.visible = enabled;
    }

    public void set_timer(bool enabled)
    {
        if (timer.visible && enabled)
            return;

        start_time = 0;
        timer.visible = enabled;
    }

    public void display_score(RoundScoreState score, bool timer)
    {
        if (score_view != null)
        {
            if (score_view.score != score)
                remove_child(score_view);
            else
            {
                score_view.visible = true;
                return;
            }
        }

        score_view = new ScoringView(score, player_index, timer, round_time, hanchan_time, game_time);
        add_child(score_view);
    }

    public void hide_score()
    {
        if (score_view != null)
            score_view.visible = false;
    }

    protected override void do_process(DeltaArgs delta)
    {
        if (start_time == 0)
            start_time = delta.time;

        if (!timer.visible)
            return;

        int t = int.max((int)(start_time + decision_time - delta.time), 0);
        if (t == decision_time)
            t--;

        timer.color = t < 3 ? Color.red() : Color.white();

        string str = t.to_string();

        if (str != timer.text)
            timer.text = str;
    }
}
