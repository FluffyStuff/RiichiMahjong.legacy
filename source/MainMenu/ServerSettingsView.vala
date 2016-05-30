using Gee;

public class ServerSettingsView : View2D
{
    private OptionItemControl riichi_option;
    private OptionItemControl aka_option;
    private OptionItemControl multiple_ron_option;
    private OptionItemControl triple_ron_option;

    public signal void apply_clicked();
    public signal void back_clicked();

    public bool can_control;

    public ServerSettingsView(bool can_control, ServerSettings settings)
    {
        this.can_control = can_control;
        this.settings = new ServerSettings.from_settings(settings);
    }

    public override void added()
    {
        LabelControl label = new LabelControl();
        add_child(label);
        label.text = "Server Settings";
        label.font_size = 40;
        label.outer_anchor = Vec2(0.5f, 1);
        label.inner_anchor = Vec2(0.5f, 1);
        label.position = Vec2(0, -60);

        string[] enabled_disabled_choices = { "Disabled", "Enabled" };

        ArrayList<OptionItemControl> opts = new ArrayList<OptionItemControl>();

        riichi_option = new OptionItemControl(can_control, "Open riichi", enabled_disabled_choices, (int)settings.open_riichi);
        aka_option = new OptionItemControl(can_control, "Aka dora", enabled_disabled_choices, (int)settings.aka_dora);
        multiple_ron_option = new OptionItemControl(can_control, "Multiple ron", enabled_disabled_choices, (int)settings.multiple_ron);
        triple_ron_option = new OptionItemControl(can_control, "Triple ron draw", enabled_disabled_choices, (int)settings.triple_ron_draw);
        opts.add(riichi_option);
        opts.add(aka_option);
        opts.add(multiple_ron_option);
        opts.add(triple_ron_option);

        int padding = 30;

        Size2 size = Size2(600, 55);
        float start = label.size.height - label.position.y + padding;

        for (int i = 0; i < opts.size; i++)
        {
            OptionItemControl option = opts.get(i);
            add_child(option);
            option.size = size;
            option.outer_anchor = Vec2(0.5f, 1);
            option.inner_anchor = Vec2(0.5f, 1);
            option.position = Vec2(0, -(start + size.height * i));
        }

        if (can_control)
        {
            MenuTextButton apply_button = new MenuTextButton("MenuButton", "Apply");
            add_child(apply_button);
            apply_button.outer_anchor = Vec2(0.5f, 0);
            apply_button.inner_anchor = Vec2(1, 0);
            apply_button.position = Vec2(-padding, padding);
            apply_button.clicked.connect(apply);
        }

        MenuTextButton back_button = new MenuTextButton("MenuButton", "Back");
        add_child(back_button);
        back_button.outer_anchor = Vec2(0.5f, 0);
        back_button.inner_anchor = Vec2(can_control ? 0 : 0.5f, 0);
        back_button.position = Vec2(can_control ? padding : 0, padding);
        back_button.clicked.connect(back);
    }

    public override void do_render(RenderState state, RenderScene2D scene)
    {
        state.back_color = Color.black();
    }

    private void apply()
    {
        settings.open_riichi = (Options.OnOffEnum)riichi_option.index;
        settings.aka_dora = (Options.OnOffEnum)aka_option.index;
        settings.multiple_ron = (Options.OnOffEnum)multiple_ron_option.index;
        settings.triple_ron_draw = (Options.OnOffEnum)triple_ron_option.index;
        settings.save();

        apply_clicked();
    }

    private void back()
    {
        back_clicked();
    }

    public ServerSettings settings { get; private set; }
}
