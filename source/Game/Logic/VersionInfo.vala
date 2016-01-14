public class VersionInfo : Serializable
{
    public VersionInfo(int major, int minor, int patch, int revis)
    {
        this.major = major;
        this.minor = minor;
        this.patch = patch;
        this.revis = revis;
    }

    public int major { get; protected set; }
    public int minor { get; protected set; }
    public int patch { get; protected set; }
    public int revis { get; protected set; }
}
