/* Action.c generated by valac 0.12.0, the Vala compiler
 * generated from Action.vala, do not modify */

/* TODO: Superclass/Subclass*/

#include <glib.h>
#include <glib-object.h>
#include <gobject/gvaluecollector.h>


#define TYPE_TURN_ACTION (turn_action_get_type ())
#define TURN_ACTION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TURN_ACTION, TurnAction))
#define TURN_ACTION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TURN_ACTION, TurnActionClass))
#define IS_TURN_ACTION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TURN_ACTION))
#define IS_TURN_ACTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TURN_ACTION))
#define TURN_ACTION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TURN_ACTION, TurnActionClass))

typedef struct _TurnAction TurnAction;
typedef struct _TurnActionClass TurnActionClass;
typedef struct _TurnActionPrivate TurnActionPrivate;

#define TURN_ACTION_TYPE_TURN_ACTION_ENUM (turn_action_turn_action_enum_get_type ())

#define TYPE_TILE (tile_get_type ())
#define TILE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TILE, Tile))
#define TILE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TILE, TileClass))
#define IS_TILE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TILE))
#define IS_TILE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TILE))
#define TILE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TILE, TileClass))

typedef struct _Tile Tile;
typedef struct _TileClass TileClass;

#define TYPE_CALL (call_get_type ())
#define CALL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_CALL, Call))
#define CALL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_CALL, CallClass))
#define IS_CALL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_CALL))
#define IS_CALL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_CALL))
#define CALL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_CALL, CallClass))

typedef struct _Call Call;
typedef struct _CallClass CallClass;

#define TYPE_PON (pon_get_type ())
#define PON(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_PON, Pon))
#define PON_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_PON, PonClass))
#define IS_PON(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_PON))
#define IS_PON_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_PON))
#define PON_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_PON, PonClass))

typedef struct _Pon Pon;
typedef struct _PonClass PonClass;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _call_unref0(var) ((var == NULL) ? NULL : (var = (call_unref (var), NULL)))
typedef struct _ParamSpecTurnAction ParamSpecTurnAction;

#define TYPE_CALL_ACTION (call_action_get_type ())
#define CALL_ACTION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_CALL_ACTION, CallAction))
#define CALL_ACTION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_CALL_ACTION, CallActionClass))
#define IS_CALL_ACTION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_CALL_ACTION))
#define IS_CALL_ACTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_CALL_ACTION))
#define CALL_ACTION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_CALL_ACTION, CallActionClass))

typedef struct _CallAction CallAction;
typedef struct _CallActionClass CallActionClass;
typedef struct _CallActionPrivate CallActionPrivate;

#define CALL_ACTION_TYPE_CALL_ACTION_ENUM (call_action_call_action_enum_get_type ())
typedef struct _ParamSpecCallAction ParamSpecCallAction;

struct _TurnAction {
	GTypeInstance parent_instance;
	volatile int ref_count;
	TurnActionPrivate * priv;
};

struct _TurnActionClass {
	GTypeClass parent_class;
	void (*finalize) (TurnAction *self);
};

typedef enum  {
	TURN_ACTION_TURN_ACTION_ENUM_DISCARD,
	TURN_ACTION_TURN_ACTION_ENUM_CLOSED_KAN,
	TURN_ACTION_TURN_ACTION_ENUM_LATE_KAN,
	TURN_ACTION_TURN_ACTION_ENUM_RIICHI,
	TURN_ACTION_TURN_ACTION_ENUM_OPEN_RIICHI,
	TURN_ACTION_TURN_ACTION_ENUM_TSUMO
} TurnActionTurnActionEnum;

struct _TurnActionPrivate {
	TurnActionTurnActionEnum _action;
	Tile* _discard_tile;
	Tile* _late_kan_tile;
	Pon* _late_kan_pon;
	Tile** _kan_tiles;
	gint _kan_tiles_length1;
	gint __kan_tiles_size_;
};

struct _ParamSpecTurnAction {
	GParamSpec parent_instance;
};

struct _CallAction {
	GTypeInstance parent_instance;
	volatile int ref_count;
	CallActionPrivate * priv;
};

struct _CallActionClass {
	GTypeClass parent_class;
	void (*finalize) (CallAction *self);
};

typedef enum  {
	CALL_ACTION_CALL_ACTION_ENUM_NONE,
	CALL_ACTION_CALL_ACTION_ENUM_OPEN_KAN,
	CALL_ACTION_CALL_ACTION_ENUM_PON,
	CALL_ACTION_CALL_ACTION_ENUM_CHI,
	CALL_ACTION_CALL_ACTION_ENUM_RON
} CallActionCallActionEnum;

struct _CallActionPrivate {
	CallActionCallActionEnum _action;
	Tile** _tiles;
	gint _tiles_length1;
	gint __tiles_size_;
	Tile* _ron_tile;
};

struct _ParamSpecCallAction {
	GParamSpec parent_instance;
};


static gpointer turn_action_parent_class = NULL;
static gpointer call_action_parent_class = NULL;

gpointer turn_action_ref (gpointer instance);
void turn_action_unref (gpointer instance);
GParamSpec* param_spec_turn_action (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void value_set_turn_action (GValue* value, gpointer v_object);
void value_take_turn_action (GValue* value, gpointer v_object);
gpointer value_get_turn_action (const GValue* value);
GType turn_action_get_type (void) G_GNUC_CONST;
GType turn_action_turn_action_enum_get_type (void) G_GNUC_CONST;
GType tile_get_type (void) G_GNUC_CONST;
gpointer call_ref (gpointer instance);
void call_unref (gpointer instance);
GParamSpec* param_spec_call (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void value_set_call (GValue* value, gpointer v_object);
void value_take_call (GValue* value, gpointer v_object);
gpointer value_get_call (const GValue* value);
GType call_get_type (void) G_GNUC_CONST;
GType pon_get_type (void) G_GNUC_CONST;
#define TURN_ACTION_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_TURN_ACTION, TurnActionPrivate))
enum  {
	TURN_ACTION_DUMMY_PROPERTY
};
TurnAction* turn_action_new_discard (Tile* discard_tile);
TurnAction* turn_action_construct_discard (GType object_type, Tile* discard_tile);
static void turn_action_set_action (TurnAction* self, TurnActionTurnActionEnum value);
static void turn_action_set_discard_tile (TurnAction* self, Tile* value);
TurnAction* turn_action_new_closed_kan (Tile** kan, int kan_length1);
TurnAction* turn_action_construct_closed_kan (GType object_type, Tile** kan, int kan_length1);
static void turn_action_set_kan_tiles (TurnAction* self, Tile** value, int value_length1);
TurnAction* turn_action_new_late_kan (Tile* kan_tile, Pon* pon);
TurnAction* turn_action_construct_late_kan (GType object_type, Tile* kan_tile, Pon* pon);
static void turn_action_set_late_kan_tile (TurnAction* self, Tile* value);
static void turn_action_set_late_kan_pon (TurnAction* self, Pon* value);
TurnAction* turn_action_new_riichi (Tile* discard_tile);
TurnAction* turn_action_construct_riichi (GType object_type, Tile* discard_tile);
TurnAction* turn_action_new_open_riichi (Tile* discard_tile);
TurnAction* turn_action_construct_open_riichi (GType object_type, Tile* discard_tile);
TurnAction* turn_action_new_tsumo (void);
TurnAction* turn_action_construct_tsumo (GType object_type);
TurnAction* turn_action_new (void);
TurnAction* turn_action_construct (GType object_type);
TurnActionTurnActionEnum turn_action_get_action (TurnAction* self);
Tile* turn_action_get_discard_tile (TurnAction* self);
Tile* turn_action_get_late_kan_tile (TurnAction* self);
Pon* turn_action_get_late_kan_pon (TurnAction* self);
Tile** turn_action_get_kan_tiles (TurnAction* self, int* result_length1);
static Tile** _vala_array_dup1 (Tile** self, int length);
static void turn_action_finalize (TurnAction* obj);
gpointer call_action_ref (gpointer instance);
void call_action_unref (gpointer instance);
GParamSpec* param_spec_call_action (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void value_set_call_action (GValue* value, gpointer v_object);
void value_take_call_action (GValue* value, gpointer v_object);
gpointer value_get_call_action (const GValue* value);
GType call_action_get_type (void) G_GNUC_CONST;
GType call_action_call_action_enum_get_type (void) G_GNUC_CONST;
#define CALL_ACTION_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_CALL_ACTION, CallActionPrivate))
enum  {
	CALL_ACTION_DUMMY_PROPERTY
};
CallAction* call_action_new_none (void);
CallAction* call_action_construct_none (GType object_type);
static void call_action_set_action (CallAction* self, CallActionCallActionEnum value);
static void call_action_set_tiles (CallAction* self, Tile** value, int value_length1);
CallAction* call_action_new_ron (Tile* tile);
CallAction* call_action_construct_ron (GType object_type, Tile* tile);
static void call_action_set_ron_tile (CallAction* self, Tile* value);
CallAction* call_action_new (CallActionCallActionEnum action, Tile** tiles, int tiles_length1);
CallAction* call_action_construct (GType object_type, CallActionCallActionEnum action, Tile** tiles, int tiles_length1);
CallActionCallActionEnum call_action_get_action (CallAction* self);
Tile** call_action_get_tiles (CallAction* self, int* result_length1);
static Tile** _vala_array_dup2 (Tile** self, int length);
Tile* call_action_get_ron_tile (CallAction* self);
static void call_action_finalize (CallAction* obj);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);


GType turn_action_turn_action_enum_get_type (void) {
	static volatile gsize turn_action_turn_action_enum_type_id__volatile = 0;
	if (g_once_init_enter (&turn_action_turn_action_enum_type_id__volatile)) {
		static const GEnumValue values[] = {{TURN_ACTION_TURN_ACTION_ENUM_DISCARD, "TURN_ACTION_TURN_ACTION_ENUM_DISCARD", "discard"}, {TURN_ACTION_TURN_ACTION_ENUM_CLOSED_KAN, "TURN_ACTION_TURN_ACTION_ENUM_CLOSED_KAN", "closed-kan"}, {TURN_ACTION_TURN_ACTION_ENUM_LATE_KAN, "TURN_ACTION_TURN_ACTION_ENUM_LATE_KAN", "late-kan"}, {TURN_ACTION_TURN_ACTION_ENUM_RIICHI, "TURN_ACTION_TURN_ACTION_ENUM_RIICHI", "riichi"}, {TURN_ACTION_TURN_ACTION_ENUM_OPEN_RIICHI, "TURN_ACTION_TURN_ACTION_ENUM_OPEN_RIICHI", "open-riichi"}, {TURN_ACTION_TURN_ACTION_ENUM_TSUMO, "TURN_ACTION_TURN_ACTION_ENUM_TSUMO", "tsumo"}, {0, NULL, NULL}};
		GType turn_action_turn_action_enum_type_id;
		turn_action_turn_action_enum_type_id = g_enum_register_static ("TurnActionTurnActionEnum", values);
		g_once_init_leave (&turn_action_turn_action_enum_type_id__volatile, turn_action_turn_action_enum_type_id);
	}
	return turn_action_turn_action_enum_type_id__volatile;
}


TurnAction* turn_action_construct_discard (GType object_type, Tile* discard_tile) {
	TurnAction* self = NULL;
	g_return_val_if_fail (discard_tile != NULL, NULL);
	self = (TurnAction*) g_type_create_instance (object_type);
	turn_action_set_action (self, TURN_ACTION_TURN_ACTION_ENUM_DISCARD);
	turn_action_set_discard_tile (self, discard_tile);
	return self;
}


TurnAction* turn_action_new_discard (Tile* discard_tile) {
	return turn_action_construct_discard (TYPE_TURN_ACTION, discard_tile);
}


TurnAction* turn_action_construct_closed_kan (GType object_type, Tile** kan, int kan_length1) {
	TurnAction* self = NULL;
	Tile** _tmp0_;
	self = (TurnAction*) g_type_create_instance (object_type);
	turn_action_set_action (self, TURN_ACTION_TURN_ACTION_ENUM_CLOSED_KAN);
	_tmp0_ = kan;
	turn_action_set_kan_tiles (self, _tmp0_, kan_length1);
	return self;
}


TurnAction* turn_action_new_closed_kan (Tile** kan, int kan_length1) {
	return turn_action_construct_closed_kan (TYPE_TURN_ACTION, kan, kan_length1);
}


TurnAction* turn_action_construct_late_kan (GType object_type, Tile* kan_tile, Pon* pon) {
	TurnAction* self = NULL;
	g_return_val_if_fail (kan_tile != NULL, NULL);
	g_return_val_if_fail (pon != NULL, NULL);
	self = (TurnAction*) g_type_create_instance (object_type);
	turn_action_set_action (self, TURN_ACTION_TURN_ACTION_ENUM_LATE_KAN);
	turn_action_set_late_kan_tile (self, kan_tile);
	turn_action_set_late_kan_pon (self, pon);
	return self;
}


TurnAction* turn_action_new_late_kan (Tile* kan_tile, Pon* pon) {
	return turn_action_construct_late_kan (TYPE_TURN_ACTION, kan_tile, pon);
}


TurnAction* turn_action_construct_riichi (GType object_type, Tile* discard_tile) {
	TurnAction* self = NULL;
	g_return_val_if_fail (discard_tile != NULL, NULL);
	self = (TurnAction*) g_type_create_instance (object_type);
	turn_action_set_action (self, TURN_ACTION_TURN_ACTION_ENUM_RIICHI);
	turn_action_set_discard_tile (self, discard_tile);
	return self;
}


TurnAction* turn_action_new_riichi (Tile* discard_tile) {
	return turn_action_construct_riichi (TYPE_TURN_ACTION, discard_tile);
}


TurnAction* turn_action_construct_open_riichi (GType object_type, Tile* discard_tile) {
	TurnAction* self = NULL;
	g_return_val_if_fail (discard_tile != NULL, NULL);
	self = (TurnAction*) g_type_create_instance (object_type);
	turn_action_set_action (self, TURN_ACTION_TURN_ACTION_ENUM_OPEN_RIICHI);
	turn_action_set_discard_tile (self, discard_tile);
	return self;
}


TurnAction* turn_action_new_open_riichi (Tile* discard_tile) {
	return turn_action_construct_open_riichi (TYPE_TURN_ACTION, discard_tile);
}


TurnAction* turn_action_construct_tsumo (GType object_type) {
	TurnAction* self = NULL;
	self = (TurnAction*) g_type_create_instance (object_type);
	turn_action_set_action (self, TURN_ACTION_TURN_ACTION_ENUM_TSUMO);
	return self;
}


TurnAction* turn_action_new_tsumo (void) {
	return turn_action_construct_tsumo (TYPE_TURN_ACTION);
}


TurnAction* turn_action_construct (GType object_type) {
	TurnAction* self = NULL;
	self = (TurnAction*) g_type_create_instance (object_type);
	return self;
}


TurnAction* turn_action_new (void) {
	return turn_action_construct (TYPE_TURN_ACTION);
}


TurnActionTurnActionEnum turn_action_get_action (TurnAction* self) {
	TurnActionTurnActionEnum result;
	g_return_val_if_fail (self != NULL, 0);
	result = self->priv->_action;
	return result;
}


static void turn_action_set_action (TurnAction* self, TurnActionTurnActionEnum value) {
	g_return_if_fail (self != NULL);
	self->priv->_action = value;
}


Tile* turn_action_get_discard_tile (TurnAction* self) {
	Tile* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_discard_tile;
	return result;
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static void turn_action_set_discard_tile (TurnAction* self, Tile* value) {
	Tile* _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp0_ = _g_object_ref0 (value);
	_g_object_unref0 (self->priv->_discard_tile);
	self->priv->_discard_tile = _tmp0_;
}


Tile* turn_action_get_late_kan_tile (TurnAction* self) {
	Tile* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_late_kan_tile;
	return result;
}


static void turn_action_set_late_kan_tile (TurnAction* self, Tile* value) {
	Tile* _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp0_ = _g_object_ref0 (value);
	_g_object_unref0 (self->priv->_late_kan_tile);
	self->priv->_late_kan_tile = _tmp0_;
}


Pon* turn_action_get_late_kan_pon (TurnAction* self) {
	Pon* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_late_kan_pon;
	return result;
}


static gpointer _call_ref0 (gpointer self) {
	return self ? call_ref (self) : NULL;
}


static void turn_action_set_late_kan_pon (TurnAction* self, Pon* value) {
	Pon* _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp0_ = _call_ref0 (value);
	_call_unref0 (self->priv->_late_kan_pon);
	self->priv->_late_kan_pon = _tmp0_;
}


Tile** turn_action_get_kan_tiles (TurnAction* self, int* result_length1) {
	Tile** result;
	Tile** _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_kan_tiles;
	*result_length1 = self->priv->_kan_tiles_length1;
	result = _tmp0_;
	return result;
}


static Tile** _vala_array_dup1 (Tile** self, int length) {
	Tile** result;
	int i;
	result = g_new0 (Tile*, length + 1);
	for (i = 0; i < length; i++) {
		result[i] = _g_object_ref0 (self[i]);
	}
	return result;
}


static void turn_action_set_kan_tiles (TurnAction* self, Tile** value, int value_length1) {
	Tile** _tmp0_;
	Tile** _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp0_ = (_tmp1_ = value, (_tmp1_ == NULL) ? ((gpointer) _tmp1_) : _vala_array_dup1 (_tmp1_, value_length1));
	self->priv->_kan_tiles = (_vala_array_free (self->priv->_kan_tiles, self->priv->_kan_tiles_length1, (GDestroyNotify) g_object_unref), NULL);
	self->priv->_kan_tiles = _tmp0_;
	self->priv->_kan_tiles_length1 = value_length1;
	self->priv->__kan_tiles_size_ = value_length1;
}


static void value_turn_action_init (GValue* value) {
	value->data[0].v_pointer = NULL;
}


static void value_turn_action_free_value (GValue* value) {
	if (value->data[0].v_pointer) {
		turn_action_unref (value->data[0].v_pointer);
	}
}


static void value_turn_action_copy_value (const GValue* src_value, GValue* dest_value) {
	if (src_value->data[0].v_pointer) {
		dest_value->data[0].v_pointer = turn_action_ref (src_value->data[0].v_pointer);
	} else {
		dest_value->data[0].v_pointer = NULL;
	}
}


static gpointer value_turn_action_peek_pointer (const GValue* value) {
	return value->data[0].v_pointer;
}


static gchar* value_turn_action_collect_value (GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	if (collect_values[0].v_pointer) {
		TurnAction* object;
		object = collect_values[0].v_pointer;
		if (object->parent_instance.g_class == NULL) {
			return g_strconcat ("invalid unclassed object pointer for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		} else if (!g_value_type_compatible (G_TYPE_FROM_INSTANCE (object), G_VALUE_TYPE (value))) {
			return g_strconcat ("invalid object type `", g_type_name (G_TYPE_FROM_INSTANCE (object)), "' for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		}
		value->data[0].v_pointer = turn_action_ref (object);
	} else {
		value->data[0].v_pointer = NULL;
	}
	return NULL;
}


static gchar* value_turn_action_lcopy_value (const GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	TurnAction** object_p;
	object_p = collect_values[0].v_pointer;
	if (!object_p) {
		return g_strdup_printf ("value location for `%s' passed as NULL", G_VALUE_TYPE_NAME (value));
	}
	if (!value->data[0].v_pointer) {
		*object_p = NULL;
	} else if (collect_flags & G_VALUE_NOCOPY_CONTENTS) {
		*object_p = value->data[0].v_pointer;
	} else {
		*object_p = turn_action_ref (value->data[0].v_pointer);
	}
	return NULL;
}


GParamSpec* param_spec_turn_action (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags) {
	ParamSpecTurnAction* spec;
	g_return_val_if_fail (g_type_is_a (object_type, TYPE_TURN_ACTION), NULL);
	spec = g_param_spec_internal (G_TYPE_PARAM_OBJECT, name, nick, blurb, flags);
	G_PARAM_SPEC (spec)->value_type = object_type;
	return G_PARAM_SPEC (spec);
}


gpointer value_get_turn_action (const GValue* value) {
	g_return_val_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_TURN_ACTION), NULL);
	return value->data[0].v_pointer;
}


void value_set_turn_action (GValue* value, gpointer v_object) {
	TurnAction* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_TURN_ACTION));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, TYPE_TURN_ACTION));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
		turn_action_ref (value->data[0].v_pointer);
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		turn_action_unref (old);
	}
}


void value_take_turn_action (GValue* value, gpointer v_object) {
	TurnAction* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_TURN_ACTION));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, TYPE_TURN_ACTION));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		turn_action_unref (old);
	}
}


static void turn_action_class_init (TurnActionClass * klass) {
	turn_action_parent_class = g_type_class_peek_parent (klass);
	TURN_ACTION_CLASS (klass)->finalize = turn_action_finalize;
	g_type_class_add_private (klass, sizeof (TurnActionPrivate));
}


static void turn_action_instance_init (TurnAction * self) {
	self->priv = TURN_ACTION_GET_PRIVATE (self);
	self->ref_count = 1;
}


static void turn_action_finalize (TurnAction* obj) {
	TurnAction * self;
	self = TURN_ACTION (obj);
	_g_object_unref0 (self->priv->_discard_tile);
	_g_object_unref0 (self->priv->_late_kan_tile);
	_call_unref0 (self->priv->_late_kan_pon);
	self->priv->_kan_tiles = (_vala_array_free (self->priv->_kan_tiles, self->priv->_kan_tiles_length1, (GDestroyNotify) g_object_unref), NULL);
}


GType turn_action_get_type (void) {
	static volatile gsize turn_action_type_id__volatile = 0;
	if (g_once_init_enter (&turn_action_type_id__volatile)) {
		static const GTypeValueTable g_define_type_value_table = { value_turn_action_init, value_turn_action_free_value, value_turn_action_copy_value, value_turn_action_peek_pointer, "p", value_turn_action_collect_value, "p", value_turn_action_lcopy_value };
		static const GTypeInfo g_define_type_info = { sizeof (TurnActionClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) turn_action_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (TurnAction), 0, (GInstanceInitFunc) turn_action_instance_init, &g_define_type_value_table };
		static const GTypeFundamentalInfo g_define_type_fundamental_info = { (G_TYPE_FLAG_CLASSED | G_TYPE_FLAG_INSTANTIATABLE | G_TYPE_FLAG_DERIVABLE | G_TYPE_FLAG_DEEP_DERIVABLE) };
		GType turn_action_type_id;
		turn_action_type_id = g_type_register_fundamental (g_type_fundamental_next (), "TurnAction", &g_define_type_info, &g_define_type_fundamental_info, 0);
		g_once_init_leave (&turn_action_type_id__volatile, turn_action_type_id);
	}
	return turn_action_type_id__volatile;
}


gpointer turn_action_ref (gpointer instance) {
	TurnAction* self;
	self = instance;
	g_atomic_int_inc (&self->ref_count);
	return instance;
}


void turn_action_unref (gpointer instance) {
	TurnAction* self;
	self = instance;
	if (g_atomic_int_dec_and_test (&self->ref_count)) {
		TURN_ACTION_GET_CLASS (self)->finalize (self);
		g_type_free_instance ((GTypeInstance *) self);
	}
}


GType call_action_call_action_enum_get_type (void) {
	static volatile gsize call_action_call_action_enum_type_id__volatile = 0;
	if (g_once_init_enter (&call_action_call_action_enum_type_id__volatile)) {
		static const GEnumValue values[] = {{CALL_ACTION_CALL_ACTION_ENUM_NONE, "CALL_ACTION_CALL_ACTION_ENUM_NONE", "none"}, {CALL_ACTION_CALL_ACTION_ENUM_OPEN_KAN, "CALL_ACTION_CALL_ACTION_ENUM_OPEN_KAN", "open-kan"}, {CALL_ACTION_CALL_ACTION_ENUM_PON, "CALL_ACTION_CALL_ACTION_ENUM_PON", "pon"}, {CALL_ACTION_CALL_ACTION_ENUM_CHI, "CALL_ACTION_CALL_ACTION_ENUM_CHI", "chi"}, {CALL_ACTION_CALL_ACTION_ENUM_RON, "CALL_ACTION_CALL_ACTION_ENUM_RON", "ron"}, {0, NULL, NULL}};
		GType call_action_call_action_enum_type_id;
		call_action_call_action_enum_type_id = g_enum_register_static ("CallActionCallActionEnum", values);
		g_once_init_leave (&call_action_call_action_enum_type_id__volatile, call_action_call_action_enum_type_id);
	}
	return call_action_call_action_enum_type_id__volatile;
}


CallAction* call_action_construct_none (GType object_type) {
	CallAction* self = NULL;
	Tile** _tmp0_;
	self = (CallAction*) g_type_create_instance (object_type);
	call_action_set_action (self, CALL_ACTION_CALL_ACTION_ENUM_NONE);
	_tmp0_ = NULL;
	call_action_set_tiles (self, _tmp0_, 0);
	return self;
}


CallAction* call_action_new_none (void) {
	return call_action_construct_none (TYPE_CALL_ACTION);
}


CallAction* call_action_construct_ron (GType object_type, Tile* tile) {
	CallAction* self = NULL;
	g_return_val_if_fail (tile != NULL, NULL);
	self = (CallAction*) g_type_create_instance (object_type);
	call_action_set_action (self, CALL_ACTION_CALL_ACTION_ENUM_RON);
	call_action_set_ron_tile (self, tile);
	return self;
}


CallAction* call_action_new_ron (Tile* tile) {
	return call_action_construct_ron (TYPE_CALL_ACTION, tile);
}


CallAction* call_action_construct (GType object_type, CallActionCallActionEnum action, Tile** tiles, int tiles_length1) {
	CallAction* self = NULL;
	Tile** _tmp0_;
	self = (CallAction*) g_type_create_instance (object_type);
	call_action_set_action (self, action);
	_tmp0_ = tiles;
	call_action_set_tiles (self, _tmp0_, tiles_length1);
	return self;
}


CallAction* call_action_new (CallActionCallActionEnum action, Tile** tiles, int tiles_length1) {
	return call_action_construct (TYPE_CALL_ACTION, action, tiles, tiles_length1);
}


CallActionCallActionEnum call_action_get_action (CallAction* self) {
	CallActionCallActionEnum result;
	g_return_val_if_fail (self != NULL, 0);
	result = self->priv->_action;
	return result;
}


static void call_action_set_action (CallAction* self, CallActionCallActionEnum value) {
	g_return_if_fail (self != NULL);
	self->priv->_action = value;
}


Tile** call_action_get_tiles (CallAction* self, int* result_length1) {
	Tile** result;
	Tile** _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_tiles;
	*result_length1 = self->priv->_tiles_length1;
	result = _tmp0_;
	return result;
}


static Tile** _vala_array_dup2 (Tile** self, int length) {
	Tile** result;
	int i;
	result = g_new0 (Tile*, length + 1);
	for (i = 0; i < length; i++) {
		result[i] = _g_object_ref0 (self[i]);
	}
	return result;
}


static void call_action_set_tiles (CallAction* self, Tile** value, int value_length1) {
	Tile** _tmp0_;
	Tile** _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp0_ = (_tmp1_ = value, (_tmp1_ == NULL) ? ((gpointer) _tmp1_) : _vala_array_dup2 (_tmp1_, value_length1));
	self->priv->_tiles = (_vala_array_free (self->priv->_tiles, self->priv->_tiles_length1, (GDestroyNotify) g_object_unref), NULL);
	self->priv->_tiles = _tmp0_;
	self->priv->_tiles_length1 = value_length1;
	self->priv->__tiles_size_ = value_length1;
}


Tile* call_action_get_ron_tile (CallAction* self) {
	Tile* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_ron_tile;
	return result;
}


static void call_action_set_ron_tile (CallAction* self, Tile* value) {
	Tile* _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp0_ = _g_object_ref0 (value);
	_g_object_unref0 (self->priv->_ron_tile);
	self->priv->_ron_tile = _tmp0_;
}


static void value_call_action_init (GValue* value) {
	value->data[0].v_pointer = NULL;
}


static void value_call_action_free_value (GValue* value) {
	if (value->data[0].v_pointer) {
		call_action_unref (value->data[0].v_pointer);
	}
}


static void value_call_action_copy_value (const GValue* src_value, GValue* dest_value) {
	if (src_value->data[0].v_pointer) {
		dest_value->data[0].v_pointer = call_action_ref (src_value->data[0].v_pointer);
	} else {
		dest_value->data[0].v_pointer = NULL;
	}
}


static gpointer value_call_action_peek_pointer (const GValue* value) {
	return value->data[0].v_pointer;
}


static gchar* value_call_action_collect_value (GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	if (collect_values[0].v_pointer) {
		CallAction* object;
		object = collect_values[0].v_pointer;
		if (object->parent_instance.g_class == NULL) {
			return g_strconcat ("invalid unclassed object pointer for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		} else if (!g_value_type_compatible (G_TYPE_FROM_INSTANCE (object), G_VALUE_TYPE (value))) {
			return g_strconcat ("invalid object type `", g_type_name (G_TYPE_FROM_INSTANCE (object)), "' for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		}
		value->data[0].v_pointer = call_action_ref (object);
	} else {
		value->data[0].v_pointer = NULL;
	}
	return NULL;
}


static gchar* value_call_action_lcopy_value (const GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	CallAction** object_p;
	object_p = collect_values[0].v_pointer;
	if (!object_p) {
		return g_strdup_printf ("value location for `%s' passed as NULL", G_VALUE_TYPE_NAME (value));
	}
	if (!value->data[0].v_pointer) {
		*object_p = NULL;
	} else if (collect_flags & G_VALUE_NOCOPY_CONTENTS) {
		*object_p = value->data[0].v_pointer;
	} else {
		*object_p = call_action_ref (value->data[0].v_pointer);
	}
	return NULL;
}


GParamSpec* param_spec_call_action (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags) {
	ParamSpecCallAction* spec;
	g_return_val_if_fail (g_type_is_a (object_type, TYPE_CALL_ACTION), NULL);
	spec = g_param_spec_internal (G_TYPE_PARAM_OBJECT, name, nick, blurb, flags);
	G_PARAM_SPEC (spec)->value_type = object_type;
	return G_PARAM_SPEC (spec);
}


gpointer value_get_call_action (const GValue* value) {
	g_return_val_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_CALL_ACTION), NULL);
	return value->data[0].v_pointer;
}


void value_set_call_action (GValue* value, gpointer v_object) {
	CallAction* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_CALL_ACTION));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, TYPE_CALL_ACTION));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
		call_action_ref (value->data[0].v_pointer);
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		call_action_unref (old);
	}
}


void value_take_call_action (GValue* value, gpointer v_object) {
	CallAction* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_CALL_ACTION));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, TYPE_CALL_ACTION));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		call_action_unref (old);
	}
}


static void call_action_class_init (CallActionClass * klass) {
	call_action_parent_class = g_type_class_peek_parent (klass);
	CALL_ACTION_CLASS (klass)->finalize = call_action_finalize;
	g_type_class_add_private (klass, sizeof (CallActionPrivate));
}


static void call_action_instance_init (CallAction * self) {
	self->priv = CALL_ACTION_GET_PRIVATE (self);
	self->ref_count = 1;
}


static void call_action_finalize (CallAction* obj) {
	CallAction * self;
	self = CALL_ACTION (obj);
	self->priv->_tiles = (_vala_array_free (self->priv->_tiles, self->priv->_tiles_length1, (GDestroyNotify) g_object_unref), NULL);
	_g_object_unref0 (self->priv->_ron_tile);
}


GType call_action_get_type (void) {
	static volatile gsize call_action_type_id__volatile = 0;
	if (g_once_init_enter (&call_action_type_id__volatile)) {
		static const GTypeValueTable g_define_type_value_table = { value_call_action_init, value_call_action_free_value, value_call_action_copy_value, value_call_action_peek_pointer, "p", value_call_action_collect_value, "p", value_call_action_lcopy_value };
		static const GTypeInfo g_define_type_info = { sizeof (CallActionClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) call_action_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (CallAction), 0, (GInstanceInitFunc) call_action_instance_init, &g_define_type_value_table };
		static const GTypeFundamentalInfo g_define_type_fundamental_info = { (G_TYPE_FLAG_CLASSED | G_TYPE_FLAG_INSTANTIATABLE | G_TYPE_FLAG_DERIVABLE | G_TYPE_FLAG_DEEP_DERIVABLE) };
		GType call_action_type_id;
		call_action_type_id = g_type_register_fundamental (g_type_fundamental_next (), "CallAction", &g_define_type_info, &g_define_type_fundamental_info, 0);
		g_once_init_leave (&call_action_type_id__volatile, call_action_type_id);
	}
	return call_action_type_id__volatile;
}


gpointer call_action_ref (gpointer instance) {
	CallAction* self;
	self = instance;
	g_atomic_int_inc (&self->ref_count);
	return instance;
}


void call_action_unref (gpointer instance) {
	CallAction* self;
	self = instance;
	if (g_atomic_int_dec_and_test (&self->ref_count)) {
		CALL_ACTION_GET_CLASS (self)->finalize (self);
		g_type_free_instance ((GTypeInstance *) self);
	}
}


static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	_vala_array_destroy (array, array_length, destroy_func);
	g_free (array);
}



