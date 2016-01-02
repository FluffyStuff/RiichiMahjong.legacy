public class RenderTable
{
    private RenderObject3D table;
    private RenderObject3D field;
    private Vec3 tile_size;
    private float field_rotation;

    public RenderTable(IResourceStore store, string extension, Vec3 tile_size, float field_rotation)
    {
        this.tile_size = tile_size;
        this.field_rotation = field_rotation;
        reload(store, extension);
    }

    public void render(RenderScene3D scene)
    {
        scene.add_object(table);
        scene.add_object(field);
    }

    public void reload(IResourceStore store, string extension)
    {
        table = store.load_object_3D("table_" + extension);

        string dir = FileLoader.get_user_dir() + "Custom/";

        RenderModel? model = null;
        RenderTexture? texture = null;

        texture = store.load_texture_dir(dir, "field", true);
        if (texture != null)
            model = store.load_model_dir(dir, "field", false);
        else
            texture = store.load_texture("field_" + extension, true);

        if (model == null)
            model = store.load_model("field", false);

        field = new RenderObject3D(model, texture);

        table.position = Vec3(0, -0.163f, 0);
        table.scale = Vec3(10, 10, 10);
        field.position = Vec3(0, 0, 0);
        field.scale = Vec3(9.6f, 1, 9.6f);
        field.rotation = Vec3(0, field_rotation, 0);

        center = Vec3(0, field.position.y, 0);
        player_offset = field.scale.z - 1.0f - (tile_size.x + tile_size.z) / 2;
    }

    public Vec3 center { get; private set; }
    public float player_offset { get; private set; }
    //public float wall_offset { get; private set; }
}
