using Gee;

public abstract class RenderScene : Object {}

public class RenderScene3D : RenderScene
{
    ArrayList<RenderObject3D> objs = new ArrayList<RenderObject3D>();
    ArrayList<LightSource> _lights = new ArrayList<LightSource>();

    public RenderScene3D(Size2i size)
    {
        this.size = size;

        focal_length = 1;

        set_camera(new Camera());
    }

    public void add_object(RenderObject3D object)
    {
        objs.add(object.copy());
    }

    public void add_light_source(LightSource light)
    {
        _lights.add(light.copy());
    }

    public void set_camera(Camera camera)
    {
        view_transform = camera.get_view_transform(true);
        camera_position = camera.position;
        focal_length = camera.focal_length;
    }

    public ArrayList<RenderObject3D> objects { get { return objs; } }
    public ArrayList<LightSource> lights { get { return _lights; } }
    public Mat4 view_transform { get; set; }
    public Vec3 camera_position { get; set; }
    public float focal_length { get; set; }
    public Size2i size { get; private set; }
}
