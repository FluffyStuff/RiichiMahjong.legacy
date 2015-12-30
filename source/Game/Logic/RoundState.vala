using Gee;

public class RoundState : Object
{
    private int current_index;
    private int player_index;
    private RoundStatePlayer[] players = new RoundStatePlayer[4];
    private RoundStateWall wall;

    private bool flow_interrupted = false;
    private int turn_counter = 0;
    private bool rinshan = false;

    public RoundState(int player_index, Wind round_wind, int dealer, int wall_index, bool[] can_riichi)
    {
        init(false, player_index, round_wind, dealer, wall_index, null, can_riichi);
    }

    public RoundState.server(Wind round_wind, int dealer, int wall_index, Rand rnd, bool[] can_riichi)
    {
        init(true, -1, round_wind, dealer, wall_index, rnd, can_riichi);
    }

    private void init(bool shuffled, int player_index, Wind round_wind, int dealer, int wall_index, Rand? rnd, bool[] can_riichi)
    {
        this.player_index = player_index;
        this.round_wind = round_wind;
        this.dealer = current_index = dealer;
        if (shuffled)
            wall = new RoundStateWall.shuffled(dealer, wall_index, rnd);
        else
            wall = new RoundStateWall(dealer, wall_index);
        discard_tile = null;

        for (int i = 0; i < players.length; i++)
            players[i] = new RoundStatePlayer(i, i == dealer, (Wind)((i - dealer + 4) % 4), can_riichi[i]);

        game_draw_type = GameDrawType.NONE;
    }

    public void start()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int p = 0; p < 4; p++)
            {
                RoundStatePlayer player = current_player;

                for (int t = 0; t < 4; t++)
                {
                    Tile tile = wall.draw_wall();
                    player.draw_initial(tile);
                }

                current_index = (current_index + 1) % players.length;
            }
        }

        for (int p = 0; p < 4; p++)
        {
            RoundStatePlayer player = current_player;
            Tile tile = wall.draw_wall();
            player.draw_initial(tile);

            if (p < 3)
                current_index = (current_index + 1) % players.length;
        }
    }

    public void tile_assign(Tile tile)
    {
        Tile t = get_tile(tile.ID);
        t.tile_type = tile.tile_type;
        t.dora = tile.dora;
    }

    public void calls_finished()
    {
        if (wall.empty)
        {
            game_over = true;
            game_draw_type = GameDrawType.EMPTY_WALL;
            return;
        }

        bool four_riichi = true;
        bool diff = false;
        int count = 0;

        foreach (RoundStatePlayer player in players)
        {
            if (!player.in_riichi)
                four_riichi = false;

            if ((count += player.get_kan_count()) != 4)
                diff = true;
        }

        if (count == 4 && diff) // Four kans game draw
        {
            game_over = true;
            game_draw_type = GameDrawType.FOUR_KANS;
            return;
        }

        if (four_riichi) // Four riichi game draw
        {
            game_over = true;
            game_draw_type = GameDrawType.FOUR_RIICHI;
            return;
        }

        if (turn_counter == 4 && !flow_interrupted)
        {
            bool four_winds = true;
            for (int i = 0; i < players.length; i++)
            {
                if (players[i].pond.size != 1 ||
                   !players[i].pond[0].is_wind_tile() ||
                    players[i].pond[0].tile_type != players[0].pond[0].tile_type)
                {
                    four_winds = false;
                    break;
                }
            }

            if (four_winds) // Four winds game draw
            {
                game_over = true;
                game_draw_type = GameDrawType.FOUR_WINDS;
                return;
            }
        }
    }

    public void void_hand()
    {
        game_over = true;
        game_draw_type = GameDrawType.VOID_HAND;
        return;
    }

    public Tile tile_draw()
    {
        if (discard_tile != null)
            foreach (var player in players)
                player.check_temporary_furiten(discard_tile);

        current_index = (current_index + 1) % players.length;
        turn_counter++;
        Tile tile = wall.draw_wall();
        current_player.draw(tile);

        return tile;
    }

    public Tile tile_draw_dead_wall()
    {
        Tile tile = wall.draw_dead_wall();
        current_player.draw(tile);

        return tile;
    }

    public bool tile_discard(int tile_ID)
    {
        Tile tile = get_tile(tile_ID);
        RoundStatePlayer player = current_player;
        if (!player.discard(tile))
            return false;

        discard_tile = tile;
        rinshan = false;

        return true;
    }

    public void flip_dora()
    {
        wall.flip_dora();
    }

    public void ron(int player_index)
    {
        game_over = true;
        current_index = player_index;
    }

    public void tsumo()
    {
        game_over = true;
    }

    public bool riichi()
    {
        if (!can_riichi())
            return false;

        current_player.do_riichi();
        return true;
    }

    public ArrayList<Tile>? late_kan(int tile_ID)
    {
        if (!can_late_kan_with(tile_ID))
            return null;

        Tile tile = get_tile(tile_ID);

        var kan_tiles = current_player.do_late_kan(tile);
        kan();
        return kan_tiles;
    }

    public ArrayList<Tile>? closed_kan(TileType tile_type)
    {
        if (!can_closed_kan_with(tile_type))
            return null;

        var tiles = current_player.do_closed_kan(tile_type);
        kan();
        //interrupt_flow(); // TODO: Find out whether this is correct

        return tiles;
    }

    public void open_kan(int player_index, int tile_1_ID, int tile_2_ID, int tile_3_ID)
    {
        RoundStatePlayer player = get_player(player_index);
        RoundStatePlayer discarder = current_player;

        Tile tile = discard_tile;
        Tile tile_1 = get_tile(tile_1_ID);
        Tile tile_2 = get_tile(tile_2_ID);
        Tile tile_3 = get_tile(tile_3_ID);
        discarder.rob_tile(tile);

        player.do_open_kan(tile, tile_1, tile_2, tile_3);

        current_index = player_index;
        kan();
    }

    public void pon(int player_index, int tile_1_ID, int tile_2_ID)
    {
        RoundStatePlayer player = get_player(player_index);
        RoundStatePlayer discarder = current_player;

        Tile tile = discard_tile;
        Tile tile_1 = get_tile(tile_1_ID);
        Tile tile_2 = get_tile(tile_2_ID);
        discarder.rob_tile(tile);

        player.do_pon(tile, tile_1, tile_2);

        interrupt_flow();
        current_index = player_index;
    }

    public void chii(int player_index, int tile_1_ID, int tile_2_ID)
    {
        RoundStatePlayer player = get_player(player_index);
        RoundStatePlayer discarder = current_player;

        Tile tile = discard_tile;
        Tile tile_1 = get_tile(tile_1_ID);
        Tile tile_2 = get_tile(tile_2_ID);
        discarder.rob_tile(tile);

        player.do_chii(tile, tile_1, tile_2);

        interrupt_flow();
        current_index = player_index;
    }

    public Scoring get_ron_score()
    {
        RoundStatePlayer player = current_player;
        return player.get_ron_score(create_context(true, discard_tile));
    }

    public Scoring get_tsumo_score()
    {
        RoundStatePlayer player = current_player;
        return player.get_tsumo_score(create_context(false, player.newest_tile));
    }

    public bool can_void_hand()
    {
        return !flow_interrupted && turn_counter <= 4 && TileRules.can_void_hand(current_player.hand);
    }

    public bool can_ron(RoundStatePlayer player)
    {
        return player != current_player && player.can_ron(create_context(true, discard_tile));
    }

    public bool can_tsumo()
    {
        RoundStatePlayer player = current_player;
        return player.can_tsumo(create_context(false, player.newest_tile));
    }

    public bool can_riichi()
    {
        return wall.can_riichi && current_player.can_riichi();
    }

    public bool can_late_kan_with(int tile_ID)
    {
        return wall.can_call && wall.can_kan && current_player.can_late_kan_with(get_tile(tile_ID));
    }

    public bool can_closed_kan_with(TileType type)
    {
        return wall.can_call && wall.can_kan && current_player.can_closed_kan_with(type);
    }

    public bool can_late_kan()
    {
        return wall.can_call && wall.can_kan && current_player.can_late_kan();
    }

    public bool can_closed_kan()
    {
        return wall.can_call && wall.can_kan && current_player.can_closed_kan();
    }

    public bool can_open_kan(RoundStatePlayer player)
    {
        return wall.can_call && wall.can_kan && !player.in_riichi && player != current_player && TileRules.can_open_kan(player.hand, discard_tile);
    }

    public bool can_pon(RoundStatePlayer player)
    {
        return wall.can_call && !player.in_riichi && player != current_player && TileRules.can_pon(player.hand, discard_tile);
    }

    public bool can_chii(RoundStatePlayer player)
    {
        return wall.can_call && ((current_player.index + 1) % 4 == player.index) && player.can_chii(discard_tile);
    }

    public bool can_chii_with(RoundStatePlayer player, Tile tile_1, Tile tile_2)
    {
        return ((current_player.index + 1) % 4 == player.index) && player.can_chii_with(tile_1, tile_2, discard_tile);
    }

    public ArrayList<ArrayList<Tile>> get_chii_groups(RoundStatePlayer player)
    {
        return player.get_chii_groups(discard_tile);
    }

    public ArrayList<Tile> get_tenpai_tiles(RoundStatePlayer player)
    {
        return TileRules.tenpai_tiles(player.hand);
    }

    public RoundStatePlayer get_player(int player_index)
    {
        return players[player_index];
    }

    public Tile get_tile(int tile_ID)
    {
        return wall.get_tile(tile_ID);
    }

    public int[] get_nagashi_indices()
    {
        ArrayList<int> indices = new ArrayList<int>();

        if (game_over && game_draw_type == GameDrawType.EMPTY_WALL)
        {
            foreach (RoundStatePlayer player in players)
                if (player.has_nagashi_mangan())
                    indices.add(player.index);
        }

        return indices.to_array();
    }

    public ArrayList<RoundStatePlayer> get_tenpai_players()
    {
        ArrayList<RoundStatePlayer> players = new ArrayList<RoundStatePlayer>();

        foreach (RoundStatePlayer player in this.players)
            if (player.in_tenpai())
                players.add(player);

        return players;
    }

    private void interrupt_flow()
    {
        foreach (RoundStatePlayer player in players)
            player.flow_interrupted();
        flow_interrupted = true;
    }

    private void kan()
    {
        rinshan = true;
        wall.flip_dora();
        tile_draw_dead_wall();
        interrupt_flow();

    }

    private RoundStateContext create_context(bool ron, Tile win_tile)
    {
        bool last_tile = wall.empty;
        bool chankan = false;

        return new RoundStateContext
        (
            round_wind,
            wall.dora,
            wall.ura_dora,
            ron,
            win_tile,
            last_tile,
            rinshan && !ron,
            chankan,
            flow_interrupted
        );
    }

    public RoundStatePlayer self { get { return players[player_index]; } }
    public Tile? discard_tile { get; private set; }
    public RoundStatePlayer current_player { get { return players[current_index]; } }
    public int dealer { get; private set; }
    public Wind round_wind { get; private set; }
    public bool game_over { get; private set; }
    public GameDrawType game_draw_type { get; private set; }
    public Tile newest_dora { get { return wall.newest_dora; } }
    public ArrayList<Tile> ura_dora { get { return wall.ura_dora; } }
    public bool tiles_empty { get { return wall.empty; } }
}

public class RoundStatePlayer
{
    private bool double_riichi = false;
    private bool do_riichi_discard = false;
    private bool do_chii_discard = false;
    private bool do_pon_discard = false;
    private bool ippatsu = false;
    private bool dealer;
    private bool tiles_called_on = false;
    private bool temporary_furiten = false;
    private bool _can_riichi;

    public RoundStatePlayer(int index, bool dealer, Wind wind, bool can_riichi)
    {
        this.index = index;
        this.dealer = dealer;
        this.wind = wind;
        _can_riichi = can_riichi;

        hand = new ArrayList<Tile>();
        pond = new ArrayList<Tile>();
        calls = new ArrayList<RoundStateCall>();
        in_riichi = false;
        first_turn = true;
    }

    public bool has_tile(Tile tile)
    {
        foreach (Tile t in hand)
            if (t.ID == tile.ID)
                return true;
        return false;
    }

    public void draw_initial(Tile tile)
    {
        hand.add(tile);
    }

    public void draw(Tile tile)
    {
        hand.add(tile);

        if (!in_riichi)
            temporary_furiten = false;
    }

    public bool discard(Tile tile)
    {
        if (!can_discard(tile))
            return false;

        hand.remove(tile);
        pond.add(tile);

        if (do_riichi_discard)
            do_riichi_discard = false;
        else
            ippatsu = false;

        first_turn = false;
        do_chii_discard = false;
        do_pon_discard = false;
        return true;
    }

    public void rob_tile(Tile tile)
    {
        //pond.remove(tile); // Don't need to do this
        tiles_called_on = true;
    }

    public void check_temporary_furiten(Tile tile)
    {
        ArrayList<Tile> hand = new ArrayList<Tile>();
        hand.add_all(this.hand);
        hand.add(tile);

        if (TileRules.winning_hand(hand))
            temporary_furiten = true;
    }

    public void flow_interrupted()
    {
        ippatsu = false;
        first_turn = false;
    }

    public void do_riichi()
    {
        in_riichi = true;
        ippatsu = true;
        do_riichi_discard = true;

        if (first_turn)
            double_riichi = true;
    }

    public ArrayList<Tile>? do_late_kan(Tile tile)
    {
        if (!can_late_kan_with(tile))
            return null;

        hand.remove(tile);

        ArrayList<Tile> tiles = new ArrayList<Tile>();
        tiles.add(tile);

        foreach (RoundStateCall call in calls)
        {
            if (call.call_type == RoundStateCall.CallType.PON)
                if (call.tiles[0].tile_type == tile.tile_type)
                {
                    calls.remove(call);
                    tiles.add_all(call.tiles);
                    break;
                }
        }

        calls.add(new RoundStateCall(RoundStateCall.CallType.LATE_KAN, tiles, tile));
        return tiles;
    }

    public ArrayList<Tile>? do_closed_kan(TileType type)
    {
        if (!can_closed_kan_with(type))
            return null;

        ArrayList<Tile> tiles = get_closed_kan_tiles(type);

        foreach (Tile tile in tiles)
            hand.remove(tile);

        calls.add(new RoundStateCall(RoundStateCall.CallType.CLOSED_KAN, tiles, null));
        return tiles;
    }

    public void do_open_kan(Tile discard_tile, Tile tile_1, Tile tile_2, Tile tile_3)
    {
        hand.remove(tile_1);
        hand.remove(tile_2);
        hand.remove(tile_3);

        ArrayList<Tile> tiles = new ArrayList<Tile>();
        tiles.add(discard_tile);
        tiles.add(tile_1);
        tiles.add(tile_2);
        tiles.add(tile_3);

        calls.add(new RoundStateCall(RoundStateCall.CallType.OPEN_KAN, tiles, discard_tile));
    }

    public void do_pon(Tile discard_tile, Tile tile_1, Tile tile_2)
    {
        hand.remove(tile_1);
        hand.remove(tile_2);

        ArrayList<Tile> tiles = new ArrayList<Tile>();
        tiles.add(discard_tile);
        tiles.add(tile_1);
        tiles.add(tile_2);

        calls.add(new RoundStateCall(RoundStateCall.CallType.PON, tiles, discard_tile));
        do_pon_discard = true;
    }

    public void do_chii(Tile discard_tile, Tile tile_1, Tile tile_2)
    {
        hand.remove(tile_1);
        hand.remove(tile_2);

        ArrayList<Tile> tiles = new ArrayList<Tile>();
        tiles.add(discard_tile);
        tiles.add(tile_1);
        tiles.add(tile_2);

        calls.add(new RoundStateCall(RoundStateCall.CallType.CHII, tiles, discard_tile));
        do_chii_discard = true;
    }

    public ArrayList<Tile> get_discard_tiles()
    {
        ArrayList<Tile> tiles = new ArrayList<Tile>();
        if (in_riichi)
        {
            tiles.add(newest_tile);
            return tiles;
        }

        foreach (Tile tile in hand)
            if (can_discard(tile))
                tiles.add(tile);

        return tiles;
    }

    public ArrayList<Tile> get_late_kan_tiles(Tile tile)
    {
        ArrayList<Tile> tiles = new ArrayList<Tile>();

        for (int i = 0; i < calls.size; i++)
        {
            RoundStateCall call = calls[i];

            if (call.call_type == RoundStateCall.CallType.PON)
            {
                if (call.tiles[0].tile_type == tile.tile_type)
                {
                    tiles.add_all(call.tiles);
                    break;
                }
            }
        }

        return tiles;
    }

    public ArrayList<Tile>? get_closed_kan_tiles(TileType type)
    {
        ArrayList<Tile> tiles = new ArrayList<Tile>();
        foreach (Tile tile in hand)
            if (tile.tile_type == type)
                tiles.add(tile);

        if (tiles.size != 4)
            return null;
        return tiles;
    }

    public Scoring get_ron_score(RoundStateContext context)
    {
        return TileRules.get_score(create_context(false), context);
    }

    public Scoring get_tsumo_score(RoundStateContext context)
    {
        return TileRules.get_score(create_context(true), context);
    }

    public bool can_discard(Tile tile)
    {
        if (!has_tile(tile) ||
            (in_riichi && !do_riichi_discard && tile.ID != newest_tile.ID))
            return false;

        // Kuikae check
        if (do_chii_discard)
        {
            ArrayList<Tile> open_tiles = new ArrayList<Tile>();
            open_tiles.add_all(newest_call.tiles);
            open_tiles.remove(newest_call.call_tile);

            if (TileRules.can_chii(open_tiles, tile))
                return false;
        }
        else if (do_pon_discard)
        {
            if (tile.tile_type == newest_call.tiles[0].tile_type)
                return false;
        }

        return true;
    }

    public bool can_ron(RoundStateContext context)
    {
        return !temporary_furiten && !TileRules.in_furiten(hand, pond) && TileRules.can_ron(create_context(false), context);
    }

    public bool can_tsumo(RoundStateContext context)
    {
        return !do_chii_discard && !do_pon_discard && TileRules.can_tsumo(create_context(true), context);
    }

    public bool can_riichi()
    {
        if (!_can_riichi || in_riichi)
            return false;

        foreach (RoundStateCall call in calls)
            if (call.call_type != RoundStateCall.CallType.CLOSED_KAN)
                return false;

        return TileRules.tenpai_tiles(hand).size > 0;
    }

    public bool can_late_kan()
    {
        if (do_chii_discard || do_pon_discard || in_riichi)
            return false;

        return TileRules.can_late_kan(hand, calls);
    }

    public bool can_late_kan_with(Tile tile)
    {
        return can_late_kan() && get_late_kan_tiles(tile).size > 0;
    }

    public bool can_closed_kan()
    {
        if (do_chii_discard || do_pon_discard)
            return false;

        return TileRules.can_closed_kan(hand, in_riichi);
    }

    public bool can_closed_kan_with(TileType type)
    {
        return can_closed_kan() && get_closed_kan_tiles(type).size > 0;
    }

    public bool can_chii(Tile discard_tile)
    {
        if (in_riichi)
            return false;

        return get_chii_groups(discard_tile).size > 0;
    }

    public bool can_chii_with(Tile tile_1, Tile tile_2, Tile discard_tile)
    {
        if (in_riichi)
            return false;

        ArrayList<Tile> tiles = new ArrayList<Tile>();
        tiles.add(tile_1);
        tiles.add(tile_2);

        if (!TileRules.can_chii(tiles, discard_tile))
            return false;

        foreach (Tile tile in hand)
        {
            if (tile == tile_1 || tile == tile_2)
                continue;

            if (!TileRules.can_chii(tiles, tile))
                return true;
        }

        return false;
    }

    public ArrayList<ArrayList<Tile>> get_chii_groups(Tile discard_tile)
    {
        ArrayList<ArrayList<Tile>> groups = TileRules.get_chii_groups(hand, discard_tile);

        for (int i = 0; i < groups.size; i++)
        {
            ArrayList<Tile> group = groups[i];
            if (!can_chii_with(group[0], group[1], discard_tile))
                groups.remove_at(i--);
        }

        return groups;
    }

    public ArrayList<ArrayList<Tile>> get_closed_kan_groups()
    {
        return TileRules.get_closed_kan_groups(hand, in_riichi);
    }

    public int get_kan_count()
    {
        int count = 0;
        foreach (RoundStateCall call in calls)
            if (call.call_type == RoundStateCall.CallType.OPEN_KAN ||
                call.call_type == RoundStateCall.CallType.CLOSED_KAN ||
                call.call_type == RoundStateCall.CallType.LATE_KAN)
                count++;

        return count;
    }

    public Tile get_default_discard_tile()
    {
        ArrayList<Tile> tiles = get_discard_tiles();
        return tiles[tiles.size - 1];
    }

    public bool has_nagashi_mangan()
    {
        return !tiles_called_on && calls.size == 0 && TileRules.is_nagashi_mangan(pond);
    }

    public bool in_tenpai()
    {
        return TileRules.in_tenpai(hand);
    }

    private PlayerStateContext create_context(bool tsumo)
    {
        ArrayList<Tile> hand = new ArrayList<Tile>();
        hand.add_all(this.hand);
        if (tsumo)
            hand.remove(newest_tile);

        return new PlayerStateContext
        (
            hand,
            pond,
            calls,
            wind,
            dealer,
            in_riichi,
            double_riichi,
            ippatsu,
            tiles_called_on,
            first_turn
        );
    }

    public int index { get; private set; }
    public Wind wind { get; private set; }
    public ArrayList<Tile> hand { get; private set; }
    public ArrayList<Tile> pond { get; private set; }
    public ArrayList<RoundStateCall> calls { get; private set; }
    public bool in_riichi { get; private set; }
    public bool first_turn { get; private set; }
    public Tile newest_tile { owned get { return hand[hand.size - 1]; } }
    public RoundStateCall newest_call { owned get { return calls[calls.size - 1]; } }
}

class RoundStateWall
{
    private ArrayList<Tile> wall_tiles = new ArrayList<Tile>();
    private ArrayList<Tile> dead_wall_tiles = new ArrayList<Tile>();
    private int dora_index = 4;

    public RoundStateWall(int dealer, int wall_index)
    {
        init(dealer, wall_index, null, false);
    }

    public RoundStateWall.shuffled(int dealer, int wall_index, Rand rnd)
    {
        init(dealer, wall_index, rnd, true);
    }

    private void init(int dealer, int wall_index, Rand? rnd, bool shuffled)
    {
        tiles = new Tile[136];
        dora = new ArrayList<Tile>();
        ura_dora = new ArrayList<Tile>();

        for (int i = 0; i < tiles.length; i++)
        {
            TileType type = shuffled ? (TileType)((i / 4) + 1) : TileType.BLANK;
            tiles[i] = new Tile(-1, type, false);
        }

        int start_wall = (4 - dealer) % 4;
        int index = start_wall * 34 + wall_index * 2;

        if (shuffled)
            shuffle(tiles, rnd);

        for (int i = 0; i < tiles.length; i++)
            tiles[i].ID = i;

        for (int i = 0; i < 122; i++)
        {
            int t = (index + i) % 136;
            wall_tiles.add(tiles[t]);
        }

        for (int i = 0; i < 14; i++)
        {
            int t = (index + i + 122) % 136;
            if (i % 2 == 0)
                t++;
            else
                t--;

            dead_wall_tiles.insert(0, tiles[t]);
        }

        flip_dora();
    }

    public Tile flip_dora()
    {
        Tile tile = dead_wall_tiles[dora_index];
        dora.add(tile);
        ura_dora.add(dead_wall_tiles[dora_index + 1]);

        dora_index += 2;

        newest_dora = tile;
        return tile;
    }

    public Tile draw_wall()
    {
        return wall_tiles.remove_at(0);
    }

    public Tile draw_dead_wall()
    {
        Tile tile = dead_wall_tiles.remove_at(0);
        dead_tile_add();
        dora_index--;
        return tile;
    }

    public Tile dead_tile_add()
    {
        Tile tile = wall_tiles.remove_at(wall_tiles.size - 1);
        dead_wall_tiles.insert(dead_wall_tiles.size, tile);
        return tile;
    }

    public Tile? get_tile(int tile_ID)
    {
        foreach (Tile tile in tiles)
            if (tile.ID == tile_ID)
                return tile;
        return null;
    }

    private static void shuffle(Tile[] tiles, Rand rnd)
    {
        for (int i = 0; i < tiles.length; i++)
        {
            int tmp = rnd.int_range(0, tiles.length);
            Tile t = tiles[i];
            tiles[i] = tiles[tmp];
            tiles[tmp] = t;
        }
    }

    public bool empty { get { return wall_tiles.size == 0; } }
    public bool can_kan { get { return dora.size < 5; } }
    public bool can_call { get { return wall_tiles.size > 0; } }
    public bool can_riichi { get { return wall_tiles.size >= 4; } }
    public Tile newest_dora { get; private set; }
    public ArrayList<Tile> dora { get; private set; }
    public ArrayList<Tile> ura_dora { get; private set; }
    public Tile[] tiles { get; private set; }
}

public enum GameDrawType
{
    NONE,
    EMPTY_WALL,
    FOUR_WINDS,
    FOUR_KANS,
    FOUR_RIICHI,
    VOID_HAND,
    // TODO: Implement multiple ron
    TRIPLE_RON
}
