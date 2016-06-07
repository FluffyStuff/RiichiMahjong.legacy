public class Environment
{
    private static const int VERSION_MAJOR = 0;
    private static const int VERSION_MINOR = 1;
    private static const int VERSION_PATCH = 2;
    private static const int VERSION_REVIS = 0;

    public static const int MIN_NAME_LENGTH =  2;
    public static const int MAX_NAME_LENGTH = 12;

    private static bool initialized = false;

    private static Logger logger;

    private Environment() {}

    public static void init()
    {
        if (initialized)
            return;
        initialized = true;

        version_info = new VersionInfo(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVIS);

        logger = new Logger("application/");
        log(LogType.INFO, "Environment", "Logging started");

        set_working_dir();
        reflection_bug_fix();
    }

    // TODO: Find better way to fix class reflection bug
    private static void reflection_bug_fix()
    {
        typeof(Serializable).class_ref();
        typeof(SerializableList).class_ref();
        typeof(SerializableListItem).class_ref();
        typeof(ObjInt).class_ref();
        typeof(GamePlayer).class_ref();

        typeof(ServerMessage).class_ref();
        typeof(ServerMessageRoundStart).class_ref();
        typeof(ServerMessageAcceptJoin).class_ref();
        typeof(ServerMessageMenuSlotAssign).class_ref();
        typeof(ServerMessageMenuSlotClear).class_ref();
        typeof(ServerMessageMenuSettings).class_ref();
        typeof(ServerMessageDraw).class_ref();

        typeof(Lobby.LobbyInformation).class_ref();
        typeof(Lobby.ServerLobbyMessage).class_ref();
        typeof(Lobby.ServerLobbyMessageCloseTunnel).class_ref();
        typeof(Lobby.ServerLobbyMessageVersionMismatch).class_ref();
        typeof(Lobby.ServerLobbyMessageVersionInfo).class_ref();
        typeof(Lobby.ServerLobbyMessageAuthenticationResult).class_ref();
        typeof(Lobby.ServerLobbyMessageLobbyEnumerationResult).class_ref();
        typeof(Lobby.ServerLobbyMessageEnterLobbyResult).class_ref();
        typeof(Lobby.ServerLobbyMessageEnterGameResult).class_ref();
        typeof(Lobby.ServerLobbyMessageLeaveGameResult).class_ref();
        typeof(Lobby.ServerLobbyMessageUserEnteredLobby).class_ref();
        typeof(Lobby.ServerLobbyMessageUserLeftLobby).class_ref();
        typeof(Lobby.ServerLobbyMessageCreateGameResult).class_ref();
        typeof(Lobby.ServerLobbyMessageGameAdded).class_ref();
        typeof(Lobby.ServerLobbyMessageUserEnteredGame).class_ref();
        typeof(Lobby.ServerLobbyMessageUserLeftGame).class_ref();

        typeof(Lobby.ClientLobbyMessage).class_ref();
        typeof(Lobby.ClientLobbyMessageCloseTunnel).class_ref();
        typeof(Lobby.ClientLobbyMessageVersionInfo).class_ref();
        typeof(Lobby.ClientLobbyMessageGetLobbies).class_ref();
        typeof(Lobby.ClientLobbyMessageAuthenticate).class_ref();
        typeof(Lobby.ClientLobbyMessageEnterLobby).class_ref();
        typeof(Lobby.ClientLobbyMessageLeaveLobby).class_ref();
        typeof(Lobby.ClientLobbyMessageEnterGame).class_ref();
        typeof(Lobby.ClientLobbyMessageLeaveGame).class_ref();
        typeof(Lobby.ClientLobbyMessageCreateGame).class_ref();

        typeof(NullBot).class_ref();
        typeof(SimpleBot).class_ref();
    }

    private static void set_working_dir()
    {
	// This makes relative paths work by changing directory to the Resources folder inside the .app bundle
	#if MAC
        void *mainBundle = CFBundleGetMainBundle();
        void *resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
        char path[PATH_MAX];
        if (!CFURLGetFileSystemRepresentation(resourcesURL, true, (uint8*)path, PATH_MAX))
        {
            // error!
        }
        CFRelease(resourcesURL);

        GLib.Environment.set_current_dir((string)path);
	#endif
    }

    public static bool compatible(VersionInfo version)
    {
        return
            version.major == version_info.major &&
            version.minor == version_info.minor &&
            version.patch >= version_info.patch &&
            version.revis >= version_info.revis;
    }

    public static string sanitize_name(string input)
    {
        return Helper.sanitize_string(input).strip();
    }

    public static bool is_valid_name(string name)
    {
        int chars = sanitize_name(name).char_count();
        return chars >= MIN_NAME_LENGTH && chars <= MAX_NAME_LENGTH;
    }

    public static string get_user_dir()
    {
        return GLib.Environment.get_user_config_dir() + "/RiichiMahjong/";
    }

    public static string get_datetime_string()
    {
        return new DateTime.now_local().format("%F_%H-%M-%S");
    }

    public static void log(LogType log_type, string origin, string message)
    {
        logger.log(log_type, origin, message);
    }

    public static Logger open_game_log()
    {
        return new Logger("game/");
    }

    public static VersionInfo version_info { get; private set; }
}

public class Logger
{
    private const string NEWLINE = "\r\n";

    private Mutex log_lock;
    private FileWriter log_stream;

    public Logger(string name)
    {
        log_stream = FileLoader.open(Environment.get_user_dir() + "/logs/" + name + Environment.get_datetime_string() + ".log");
        log_lock = Mutex();

        log_stream.write("%VersionInfo:" + Environment.version_info.to_string() + NEWLINE);
    }

    public void log(LogType log_type, string origin, string message)
    {
        log_lock.lock();
        string line = "[" + Environment.get_datetime_string() + "] " + log_type.to_string().substring(9) + " from " + origin + ": \"" + message + "\"" + NEWLINE;
        print(line);
        log_stream.write(line);
        log_lock.unlock();
    }
}

public enum LogType
{
    ERROR,
    SYSTEM,
    INFO,
    GAME,
    NETWORK,
    DEBUG
}

#if MAC
static extern const int PATH_MAX;
static extern void* CFBundleGetMainBundle();
static extern void* CFBundleCopyResourcesDirectoryURL(void *bundle);
static extern bool CFURLGetFileSystemRepresentation(void *url, bool b, uint8 *path, int max_path);
static extern void CFRelease(void *url);
#endif
