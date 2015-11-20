using Gee;

public class ClientRoundState
{
    private Tile[] tiles = new Tile[136];
    private int player_index;
    private Wind round_wind;
    private int dealer;
    private ClientRoundStatePlayer[] players = new ClientRoundStatePlayer[4];
    private ClientRoundStateWall wall = new ClientRoundStateWall();

    private bool flow_interrupted = false;
    private int turn_counter = -52; // TODO: seperate out initial tile draw
    private bool rinshan = false;

    public ClientRoundState(int player_index, Wind round_wind, int dealer, bool[] can_riichi)
    {
        this.player_index = player_index;
        this.round_wind = round_wind;
        this.dealer = dealer;
        discard_tile = null;

        for (int i = 0; i < players.length; i++)
            players[i] = new ClientRoundStatePlayer(i, i == dealer, (Wind)((i - dealer + 4) % 4), can_riichi[i]);

        for (int i = 0; i < tiles.length; i++)
            tiles[i] = new Tile(i, TileType.BLANK, false);
    }

    public void tile_assign(Tile tile)
    {
        Tile t = tiles[tile.ID];
        t.tile_type = tile.tile_type;
        t.dora = tile.dora;
    }

    public void tile_draw(int player_index, int tile_ID)
    {
        if (discard_tile != null)
            foreach (var player in players)
                player.check_temporary_furiten(discard_tile);

        turn_counter++;
        Tile tile = tiles[tile_ID];
        wall.draw_tile(tile);
        players[player_index].draw(tile);
    }

    public void tile_discard(int player_index, int tile_ID)
    {
        Tile tile = tiles[tile_ID];
        ClientRoundStatePlayer player = players[player_index];
        player.discard(tile);

        discard_tile = tile;
        discard_player = player;
        rinshan = false;
    }

    public void flip_dora(int tile_ID)
    {
        Tile tile = tiles[tile_ID];
        wall.flip_dora(tile);
    }

    public void flip_ura_dora(int tile_ID)
    {
        Tile tile = tiles[tile_ID];
        wall.flip_ura_dora(tile);
    }

    public void riichi(int player_index)
    {
        ClientRoundStatePlayer player = get_player(player_index);
        player.do_riichi();
    }

    public void late_kan(int player_index, int tile_ID)
    {
        ClientRoundStatePlayer player = get_player(player_index);
        player.do_late_kan(get_tile(tile_ID));
        rinshan = true;
    }

    public void closed_kan(int player_index, TileType tile_type)
    {
        ClientRoundStatePlayer player = get_player(player_index);
        player.do_closed_kan(tile_type);

        interrupt_flow(); // TODO: Find out whether this is correct
        rinshan = true;
    }

    public void open_kan(int player_index, int discarding_player_index, int tile_ID, int tile_1_ID, int tile_2_ID, int tile_3_ID)
    {
        ClientRoundStatePlayer player = get_player(player_index);
        ClientRoundStatePlayer discarder = get_player(discarding_player_index);

        Tile tile = get_tile(tile_ID);
        Tile tile_1 = get_tile(tile_1_ID);
        Tile tile_2 = get_tile(tile_2_ID);
        Tile tile_3 = get_tile(tile_3_ID);
        discarder.rob_tile(tile);

        player.do_open_kan(tile, tile_1, tile_2, tile_3);

        interrupt_flow();
        rinshan = true;
    }

    public void pon(int player_index, int discarding_player_index, int tile_ID, int tile_1_ID, int tile_2_ID)
    {
        ClientRoundStatePlayer player = get_player(player_index);
        ClientRoundStatePlayer discarder = get_player(discarding_player_index);

        Tile tile = get_tile(tile_ID);
        Tile tile_1 = get_tile(tile_1_ID);
        Tile tile_2 = get_tile(tile_2_ID);
        discarder.rob_tile(tile);

        player.do_pon(tile, tile_1, tile_2);

        interrupt_flow();
    }

    public void chii(int player_index, int discarding_player_index, int tile_ID, int tile_1_ID, int tile_2_ID)
    {
        ClientRoundStatePlayer player = get_player(player_index);
        ClientRoundStatePlayer discarder = get_player(discarding_player_index);

        Tile tile = get_tile(tile_ID);
        Tile tile_1 = get_tile(tile_1_ID);
        Tile tile_2 = get_tile(tile_2_ID);
        discarder.rob_tile(tile);

        player.do_chii(tile, tile_1, tile_2);

        interrupt_flow();
    }

    public Scoring get_ron_score(ClientRoundStatePlayer player, Tile tile)
    {
        return player.get_ron_score(create_context(true, tile));
    }

    public Scoring get_tsumo_score(ClientRoundStatePlayer player)
    {
        return player.get_tsumo_score(create_context(false, player.last_drawn_tile));
    }

    public bool can_ron(ClientRoundStatePlayer player, Tile tile)
    {
        return player.can_ron(create_context(true, tile));
    }

    public bool can_tsumo(ClientRoundStatePlayer player)
    {
        return player.can_tsumo(create_context(false, player.last_drawn_tile));
    }

    public bool can_chii(Tile tile, ClientRoundStatePlayer player, ClientRoundStatePlayer discard_player)
    {
        return ((discard_player.seat + 1) % 4 == player.seat) && TileRules.can_chii(player.hand, tile);
    }

    public ArrayList<Tile> get_tenpai_tiles(ClientRoundStatePlayer player)
    {
        return TileRules.tenpai_tiles(player.hand);
    }

    public ClientRoundStatePlayer get_player(int player_index)
    {
        return players[player_index];
    }

    public Tile get_tile(int tile_ID)
    {
        return tiles[tile_ID];
    }

    private void interrupt_flow()
    {
        foreach (ClientRoundStatePlayer player in players)
            player.flow_interrupted();
        flow_interrupted = true;
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
            flow_interrupted,
            turn_counter <= players.length && !flow_interrupted
        );
    }

    public ClientRoundStatePlayer self { get { return players[player_index]; } }

    public Tile? discard_tile { get; private set; }
    public ClientRoundStatePlayer? discard_player { get; private set; }
}

public class ClientRoundStatePlayer
{
    private bool double_riichi = true;
    private bool do_riichi_discard = false;
    private bool ippatsu = false;
    private bool dealer;
    private Wind wind;
    private bool tiles_called_on = false;
    private bool temporary_furiten = false;
    private bool _can_riichi;

    public ClientRoundStatePlayer(int seat, bool dealer, Wind wind, bool can_riichi)
    {
        this.seat = seat;
        this.dealer = dealer;
        this.wind = wind;
        _can_riichi = can_riichi;

        hand = new ArrayList<Tile>();
        pond = new ArrayList<Tile>();
        calls = new ArrayList<RoundStateCall>();
        in_riichi = false;
    }

    public bool has_tile(Tile tile)
    {
        foreach (Tile t in hand)
            if (t.ID == tile.ID)
                return true;
        return false;
    }

    public void draw(Tile tile)
    {
        hand.add(tile);
        last_drawn_tile = tile;

        if (!in_riichi)
            temporary_furiten = false;
    }

    public void discard(Tile tile)
    {
        hand.remove(tile);
        pond.add(tile);

        if (!in_riichi)
            double_riichi = false;

        if (do_riichi_discard)
            do_riichi_discard = false;
        else
            ippatsu = false;
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
        if (!in_riichi)
            double_riichi = false;
        ippatsu = false;
    }

    public void do_riichi()
    {
        in_riichi = true;
        ippatsu = true;
        do_riichi_discard = true;
    }

    public void do_late_kan(Tile tile)
    {
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

        calls.add(new RoundStateCall(RoundStateCall.CallType.LATE_KAN, tiles));
    }

    public void do_closed_kan(TileType type)
    {
        ArrayList<Tile> tiles = new ArrayList<Tile>();
        for (int i = 0; i < hand.size; i++)
            if (hand[i].tile_type == type)
                tiles.add(hand.remove_at(i--));

        calls.add(new RoundStateCall(RoundStateCall.CallType.CLOSED_KAN, tiles));
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

        calls.add(new RoundStateCall(RoundStateCall.CallType.OPEN_KAN, tiles));
    }

    public void do_pon(Tile discard_tile, Tile tile_1, Tile tile_2)
    {
        hand.remove(tile_1);
        hand.remove(tile_2);

        ArrayList<Tile> tiles = new ArrayList<Tile>();
        tiles.add(discard_tile);
        tiles.add(tile_1);
        tiles.add(tile_2);

        calls.add(new RoundStateCall(RoundStateCall.CallType.PON, tiles));
    }

    public void do_chii(Tile discard_tile, Tile tile_1, Tile tile_2)
    {
        hand.remove(tile_1);
        hand.remove(tile_2);

        ArrayList<Tile> tiles = new ArrayList<Tile>();
        tiles.add(discard_tile);
        tiles.add(tile_1);
        tiles.add(tile_2);

        calls.add(new RoundStateCall(RoundStateCall.CallType.CHII, tiles));
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

    public Scoring get_ron_score(RoundStateContext context)
    {
        return TileRules.get_score(create_context(false), context);
    }

    public Scoring get_tsumo_score(RoundStateContext context)
    {
        return TileRules.get_score(create_context(true), context);
    }

    public bool can_ron(RoundStateContext context)
    {
        return !temporary_furiten && !TileRules.in_furiten(hand, pond) && TileRules.can_ron(create_context(false), context);
    }

    public bool can_tsumo(RoundStateContext context)
    {
        return TileRules.can_tsumo(create_context(true), context);
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
        if (in_riichi)
            return false;

        return TileRules.can_late_kan(hand, calls);
    }

    public bool can_closed_kan()
    {
        // TODO: Fix
        if (in_riichi)
            return false;

        return TileRules.can_closed_kan(hand);
    }

    private PlayerStateContext create_context(bool tsumo)
    {
        ArrayList<Tile> hand = new ArrayList<Tile>();
        hand.add_all(this.hand);
        if (tsumo)
            hand.remove(last_drawn_tile);

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
            tiles_called_on
        );
    }

    public int seat { get; private set; }
    public ArrayList<Tile> hand { get; private set; }
    public ArrayList<Tile> pond { get; private set; }
    public ArrayList<RoundStateCall> calls { get; private set; }
    public bool in_riichi { get; private set; }
    public Tile? last_drawn_tile { get; private set; }
}

public class ClientRoundStateWall
{
    private int tile_count = 136;

    public ClientRoundStateWall()
    {
        dora = new ArrayList<Tile>();
        ura_dora = new ArrayList<Tile>();
    }

    public void draw_tile(Tile tile)
    {
        tile_count--;
    }

    public void flip_dora(Tile tile)
    {
        dora.add(tile);
    }

    public void flip_ura_dora(Tile tile)
    {
        ura_dora.add(tile);
    }

    public ArrayList<Tile> dora { get; private set; }
    public ArrayList<Tile> ura_dora { get; private set; }
    public bool empty { get { return tile_count <= 14; } }
}
