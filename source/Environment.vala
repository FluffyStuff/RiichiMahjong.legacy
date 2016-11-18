using Gee;

public class Environment
{
    private static const int VERSION_MAJOR = 0;
    private static const int VERSION_MINOR = 1;
    private static const int VERSION_PATCH = 2;
    private static const int VERSION_REVIS = 0;

    public static const int MIN_NAME_LENGTH =  2;
    public static const int MAX_NAME_LENGTH = 12;

    public static const uint16 GAME_PORT     = 1337;
    public static const uint16 LOBBY_PORT    = 1337;
    public static const string LOBBY_ADDRESS = "riichi.fluffy.is";

    private static bool initialized = false;

    private static Logger logger;
    private static LogCallback engine_logger;

    private Environment() {}

    public static void init(bool do_debug)
    {
        if (initialized)
            return;
        initialized = true;
        debug = do_debug;

        version_info = new VersionInfo(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVIS);

        logger = new Logger("application/");
        engine_logger = new LogCallback();
        engine_logger.log.connect(engine_log);
        EngineLog.set_log_callback(engine_logger);
        log(LogType.INFO, "Environment", "Logging started");
        log(LogType.DEBUG, "Environment", "Logging debug information");

        set_working_dir();
        reflection_bug_fix();
    }

    private static void engine_log(EngineLogType log_type, string origin, string message)
    {
        LogType t;

        switch (log_type)
        {
        case EngineLogType.NETWORK:
            t = LogType.NETWORK;
            break;
        case EngineLogType.DEBUG:
            t = LogType.DEBUG;
            break;
        default:
            t = LogType.SYSTEM;
            break;
        }

        log(t, origin, message);
    }

    // TODO: Find better way to fix class reflection bug
    private static void reflection_bug_fix()
    {
        typeof(Serializable).class_ref();
        typeof(SerializableList).class_ref();
        //typeof(SerializableListItem).class_ref();
        typeof(ObjInt).class_ref();
        typeof(GamePlayer).class_ref();

        typeof(ServerMessage).class_ref();
        typeof(ServerMessageRoundStart).class_ref();
        typeof(ServerMessageAcceptJoin).class_ref();
        typeof(ServerMessageMenuSlotAssign).class_ref();
        typeof(ServerMessageMenuSlotClear).class_ref();
        typeof(ServerMessageMenuSettings).class_ref();
        typeof(ServerMessageMenuGameLog).class_ref();
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

        typeof(GameLog).class_ref();
        typeof(GameLogRound).class_ref();
        typeof(GameLogLine).class_ref();
        typeof(DefaultTileDiscardGameLogLine).class_ref();
        typeof(DefaultCallActionGameLogLine).class_ref();
        typeof(ClientTileDiscardGameLogLine).class_ref();
        typeof(ClientNoCallGameLogLine).class_ref();
        typeof(ClientRonGameLogLine).class_ref();
        typeof(ClientTsumoGameLogLine).class_ref();
        typeof(ClientVoidHandGameLogLine).class_ref();
        typeof(ClientRiichiGameLogLine).class_ref();
        typeof(ClientLateKanGameLogLine).class_ref();
        typeof(ClientClosedKanGameLogLine).class_ref();
        typeof(ClientOpenKanGameLogLine).class_ref();
        typeof(ClientPonGameLogLine).class_ref();
        typeof(ClientChiiGameLogLine).class_ref();

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

    public static GameLogger open_game_log(GameStartInfo start_info, ServerSettings settings)
    {
        return new GameLogger(start_info, settings);
    }

    public static GameLog? load_game_log(string name)
    {
        uint8[]? data = FileLoader.load_data(name);
        return (GameLog?)Serializable.deserialize(data);
    }

    public static string[] get_game_log_names()
    {
        ArrayList<string> logs = new ArrayList<string>();

        foreach (string log in FileLoader.get_files_in_dir(game_log_dir))
        {
            string extension = log_extension;
            if (log.last_index_of(extension) == log.length - extension.length)
                logs.add(log.substring(0, log.length - extension.length));
        }

        return logs.to_array();
    }

    public static bool debug { get; private set; }
    public static VersionInfo version_info { get; private set; }
    public static string log_dir { owned get { return Environment.get_user_dir() + "logs/"; } }
    public static string game_log_dir { owned get { return log_dir + "game/"; } }
    public static string log_extension { owned get { return ".log"; } }
}

public class GameLogger
{
    private Mutex log_lock;
    private GameLog game_log;
    private string name;

    public GameLogger(GameStartInfo start_info, ServerSettings settings)
    {
        log_lock = Mutex();
        game_log = new GameLog(Environment.version_info, start_info, settings);
        name = Environment.game_log_dir + Environment.get_datetime_string() + Environment.log_extension;
    }

    private void write()
    {
        FileWriter file = FileLoader.open(name);
        file.write_data(game_log.serialize());
    }

    public void log(GameLogLine line)
    {
        log_lock.lock();
        game_log.add_line(line);
        write();
        log_lock.unlock();
    }

    public void log_round(RoundStartInfo info, Tile[] tiles)
    {
        log_lock.lock();
        game_log.start_round(info, tiles);
        write();
        log_lock.unlock();
    }
}

public class Logger
{
    private const string NEWLINE = "\r\n";

    private Mutex log_lock;
    private FileWriter log_stream;

    public Logger(string name)
    {
        log_stream = FileLoader.open(Environment.log_dir + name + Environment.get_datetime_string() + Environment.log_extension);
        log_lock = Mutex();

        log_stream.write("%VersionInfo:" + Environment.version_info.to_string() + NEWLINE);
    }

    public void log(LogType log_type, string origin, string message)
    {
        if (log_type == LogType.DEBUG && !Environment.debug)
            return;

        log_lock.lock();
        string m = message.replace("\r", "").replace("\n", " ").replace("\"", "|").strip();
        string line = "[" + Environment.get_datetime_string() + "] " + log_type.to_string().substring(9) + " from " + origin + ": \"" + m + "\"" + NEWLINE;
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
