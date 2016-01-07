public abstract class RenderObject3D
{
    public RenderObject3D()
    {
        rotation = Vec3.empty();
        position = Vec3.empty();
        scale = Vec3(1, 1, 1);
        light_multiplier = 1;
        diffuse_color = Color.black();
    }

    public abstract RenderObject3D copy();

    public Vec3 rotation { get; set; }
    public Vec3 position { get; set; }
    public Vec3 scale { get; set; }
    public float light_multiplier { get; set; }
    public Color diffuse_color { get; set; }
}

public class RenderBody3D : RenderObject3D
{
    public RenderBody3D(RenderModel? model, RenderTexture? texture)
    {
        base();

        this.model = model;
        this.texture = texture;
    }

    public override RenderObject3D copy()
    {
        RenderBody3D obj = new RenderBody3D(model, texture);
        obj.rotation = rotation;
        obj.position = position;
        obj.scale = scale;
        obj.light_multiplier = light_multiplier;
        obj.diffuse_color = diffuse_color;

        return obj;
    }

    public RenderModel? model { get; set; }
    public RenderTexture? texture { get; set; }
}

public class RenderLabel3D : RenderObject3D
{
    private LabelResourceReference reference;
    private string _font_type;
    private float _font_size;
    private string _text;
    private bool _bold;

    public RenderLabel3D(uint handle, LabelResourceReference reference, RenderModel model)
    {
        base();

        this.handle = handle;
        this.reference = reference;
        this.model = model;

        _font_type = "Noto Sans CJK JP";
        _font_size = 40;
        _text = "";
        _bold = false;

        color = Color.white();
        size = 1;
    }

    ~RenderLabel3D()
    {
        reference.delete();
    }

    public override RenderObject3D copy()
    {
        RenderLabel3D img = new RenderLabel3D(handle, reference, model);
        img.info = info;
        img._font_type = _font_type;
        img._font_size = _font_size;
        img._text = _text;
        img._bold = _bold;
        img.size = size;

        img.rotation = rotation;
        img.position = position;
        img.scale = scale;
        img.light_multiplier = light_multiplier;
        img.diffuse_color = diffuse_color;

        return img;
    }

    private void update()
    {
        info = reference.update(font_type, font_size, text);
    }

    public uint handle { get; private set; }
    public LabelInfo? info { get; private set; }
    public RenderModel model { get; private set; }

    public string font_type
    {
        owned get
        {
            string font = _font_type;
            if (bold)
                font += " Bold";
            return font;
        }
        set
        {
            if (_font_type == value)
                return;

            _font_type = value;
            update();
        }
    }

    public float font_size
    {
        get { return _font_size; }
        set
        {
            if (_font_size == value)
                return;

            _font_size = value;
            update();
        }
    }

    public string text
    {
        get { return _text; }
        set
        {
            if (_text == value)
                return;

            _text = value;
            update();
        }
    }

    public bool bold
    {
        get { return _bold; }
        set
        {
            if (_bold == value)
                return;

            _bold = value;
            update();
        }
    }

    public Color color
    {
        get { return Color(diffuse_color.r + 1, diffuse_color.g + 1, diffuse_color.b + 1, diffuse_color.a); }
        set { diffuse_color = Color(value.r - 1, value.g - 1, value.b - 1, value.a); }
    }

    public Vec3 end_scale
    {
        get
        {
            return Vec3(scale.x * info.size.width / font_size * FONT_SIZE_MULTIPLIER * size, 1, scale.z * info.size.height / font_size * FONT_SIZE_MULTIPLIER * size);
        }
    }

    public Vec3 end_size
    {
        get
        {
            Vec3 scale = end_scale;
            return Vec3(model.size.x * scale.x, 0, model.size.z * scale.z);
        }
    }

    public float size { get; set; }

    private const float FONT_SIZE_MULTIPLIER = 0.2f;
}
