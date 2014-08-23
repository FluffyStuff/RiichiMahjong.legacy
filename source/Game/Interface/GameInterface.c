/* GameInterface.c generated by valac 0.12.0, the Vala compiler
 * generated from GameInterface.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gee.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <GL/glew.h>
#include <gobject/gvaluecollector.h>


#define TYPE_GAME_INTERFACE (game_interface_get_type ())
#define GAME_INTERFACE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_GAME_INTERFACE, GameInterface))
#define GAME_INTERFACE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_GAME_INTERFACE, GameInterfaceClass))
#define IS_GAME_INTERFACE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_GAME_INTERFACE))
#define IS_GAME_INTERFACE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_GAME_INTERFACE))
#define GAME_INTERFACE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_GAME_INTERFACE, GameInterfaceClass))

typedef struct _GameInterface GameInterface;
typedef struct _GameInterfaceClass GameInterfaceClass;
typedef struct _GameInterfacePrivate GameInterfacePrivate;

#define TYPE_BUTTON (button_get_type ())
#define BUTTON(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_BUTTON, Button))
#define BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_BUTTON, ButtonClass))
#define IS_BUTTON(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_BUTTON))
#define IS_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_BUTTON))
#define BUTTON_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_BUTTON, ButtonClass))

typedef struct _Button Button;
typedef struct _ButtonClass ButtonClass;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _button_unref0(var) ((var == NULL) ? NULL : (var = (button_unref (var), NULL)))

#define TYPE_VECTOR (vector_get_type ())
#define VECTOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_VECTOR, Vector))
#define VECTOR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_VECTOR, VectorClass))
#define IS_VECTOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_VECTOR))
#define IS_VECTOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_VECTOR))
#define VECTOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_VECTOR, VectorClass))

typedef struct _Vector Vector;
typedef struct _VectorClass VectorClass;
#define _vector_unref0(var) ((var == NULL) ? NULL : (var = (vector_unref (var), NULL)))
typedef struct _ParamSpecGameInterface ParamSpecGameInterface;

struct _GameInterface {
	GTypeInstance parent_instance;
	volatile int ref_count;
	GameInterfacePrivate * priv;
};

struct _GameInterfaceClass {
	GTypeClass parent_class;
	void (*finalize) (GameInterface *self);
};

struct _GameInterfacePrivate {
	GeeArrayList* buttons;
	Button* continue_button;
	Button* pon_button;
	Button* kan_button;
	Button* chi_button;
	Button* riichi_button;
	Button* tsumo_button;
	Button* ron_button;
	gboolean _visible;
};

struct _ParamSpecGameInterface {
	GParamSpec parent_instance;
};


static gpointer game_interface_parent_class = NULL;

gpointer game_interface_ref (gpointer instance);
void game_interface_unref (gpointer instance);
GParamSpec* param_spec_game_interface (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void value_set_game_interface (GValue* value, gpointer v_object);
void value_take_game_interface (GValue* value, gpointer v_object);
gpointer value_get_game_interface (const GValue* value);
GType game_interface_get_type (void) G_GNUC_CONST;
gpointer button_ref (gpointer instance);
void button_unref (gpointer instance);
GParamSpec* param_spec_button (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void value_set_button (GValue* value, gpointer v_object);
void value_take_button (GValue* value, gpointer v_object);
gpointer value_get_button (const GValue* value);
GType button_get_type (void) G_GNUC_CONST;
#define GAME_INTERFACE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_GAME_INTERFACE, GameInterfacePrivate))
enum  {
	GAME_INTERFACE_DUMMY_PROPERTY
};
Button* button_new (const gchar* name, guint color_id);
Button* button_construct (GType object_type, const gchar* name, guint color_id);
GameInterface* game_interface_new (void);
GameInterface* game_interface_construct (GType object_type);
gfloat button_get_size (Button* self);
gfloat button_get_height (Button* self);
Vector* vector_new (gfloat x, gfloat y, gfloat z);
Vector* vector_construct (GType object_type, gfloat x, gfloat y, gfloat z);
gpointer vector_ref (gpointer instance);
void vector_unref (gpointer instance);
GParamSpec* param_spec_vector (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void value_set_vector (GValue* value, gpointer v_object);
void value_take_vector (GValue* value, gpointer v_object);
gpointer value_get_vector (const GValue* value);
GType vector_get_type (void) G_GNUC_CONST;
void button_set_position (Button* self, Vector* value);
gfloat button_get_width (Button* self);
void button_set_visible (Button* self, gboolean value);
void game_interface_render (GameInterface* self);
gboolean game_interface_get_visible (GameInterface* self);
void button_render (Button* self);
void game_interface_render_selection (GameInterface* self);
void button_render_selection (Button* self);
gboolean game_interface_hover (GameInterface* self, gint x, gint y, guint color_id);
gboolean button_hover (Button* self, guint color_id);
guint button_get_color_id (Button* self);
Button* game_interface_click (GameInterface* self, gint x, gint y, guint color_id, gboolean state);
gboolean button_click (Button* self, guint color_id, gboolean up);
void game_interface_set_visible (GameInterface* self, gboolean value);
gboolean game_interface_get_show_continue (GameInterface* self);
gboolean button_get_visible (Button* self);
void game_interface_set_show_continue (GameInterface* self, gboolean value);
gboolean game_interface_get_show_pon (GameInterface* self);
void game_interface_set_show_pon (GameInterface* self, gboolean value);
gboolean game_interface_get_show_kan (GameInterface* self);
void game_interface_set_show_kan (GameInterface* self, gboolean value);
gboolean game_interface_get_show_chi (GameInterface* self);
void game_interface_set_show_chi (GameInterface* self, gboolean value);
gboolean game_interface_get_show_riichi (GameInterface* self);
void game_interface_set_show_riichi (GameInterface* self, gboolean value);
gboolean game_interface_get_show_tsumo (GameInterface* self);
void game_interface_set_show_tsumo (GameInterface* self, gboolean value);
gboolean game_interface_get_show_ron (GameInterface* self);
void game_interface_set_show_ron (GameInterface* self, gboolean value);
static void game_interface_finalize (GameInterface* obj);


GameInterface* game_interface_construct (GType object_type) {
	GameInterface* self = NULL;
	gfloat _tmp0_;
	gfloat _tmp1_;
	Vector* _tmp2_ = NULL;
	Vector* _tmp3_;
	gfloat _tmp4_;
	gfloat _tmp5_;
	gfloat _tmp6_;
	gfloat _tmp7_;
	Vector* _tmp8_ = NULL;
	Vector* _tmp9_;
	gfloat _tmp10_;
	gfloat _tmp11_;
	gfloat _tmp12_;
	gfloat _tmp13_;
	Vector* _tmp14_ = NULL;
	Vector* _tmp15_;
	gfloat _tmp16_;
	gfloat _tmp17_;
	gfloat _tmp18_;
	gfloat _tmp19_;
	Vector* _tmp20_ = NULL;
	Vector* _tmp21_;
	gfloat _tmp22_;
	gfloat _tmp23_;
	gfloat _tmp24_;
	gfloat _tmp25_;
	Vector* _tmp26_ = NULL;
	Vector* _tmp27_;
	gfloat _tmp28_;
	gfloat _tmp29_;
	gfloat _tmp30_;
	gfloat _tmp31_;
	Vector* _tmp32_ = NULL;
	Vector* _tmp33_;
	gfloat _tmp34_;
	gfloat _tmp35_;
	gfloat _tmp36_;
	gfloat _tmp37_;
	Vector* _tmp38_ = NULL;
	Vector* _tmp39_;
	self = (GameInterface*) g_type_create_instance (object_type);
	_tmp0_ = button_get_size (self->priv->continue_button);
	_tmp1_ = button_get_height (self->priv->continue_button);
	_tmp2_ = vector_new ((gfloat) 0, (-1) + (_tmp0_ * _tmp1_), (gfloat) 0);
	_tmp3_ = _tmp2_;
	button_set_position (self->priv->continue_button, _tmp3_);
	_vector_unref0 (_tmp3_);
	_tmp4_ = button_get_size (self->priv->continue_button);
	_tmp5_ = button_get_width (self->priv->continue_button);
	_tmp6_ = button_get_size (self->priv->continue_button);
	_tmp7_ = button_get_height (self->priv->continue_button);
	_tmp8_ = vector_new ((_tmp4_ * _tmp5_) * 2, (-1) + (_tmp6_ * _tmp7_), (gfloat) 0);
	_tmp9_ = _tmp8_;
	button_set_position (self->priv->pon_button, _tmp9_);
	_vector_unref0 (_tmp9_);
	_tmp10_ = button_get_size (self->priv->continue_button);
	_tmp11_ = button_get_width (self->priv->continue_button);
	_tmp12_ = button_get_size (self->priv->continue_button);
	_tmp13_ = button_get_height (self->priv->continue_button);
	_tmp14_ = vector_new ((_tmp10_ * _tmp11_) * 4, (-1) + (_tmp12_ * _tmp13_), (gfloat) 0);
	_tmp15_ = _tmp14_;
	button_set_position (self->priv->kan_button, _tmp15_);
	_vector_unref0 (_tmp15_);
	_tmp16_ = button_get_size (self->priv->continue_button);
	_tmp17_ = button_get_width (self->priv->continue_button);
	_tmp18_ = button_get_size (self->priv->continue_button);
	_tmp19_ = button_get_height (self->priv->continue_button);
	_tmp20_ = vector_new ((_tmp16_ * _tmp17_) * 6, (-1) + (_tmp18_ * _tmp19_), (gfloat) 0);
	_tmp21_ = _tmp20_;
	button_set_position (self->priv->chi_button, _tmp21_);
	_vector_unref0 (_tmp21_);
	_tmp22_ = button_get_size (self->priv->continue_button);
	_tmp23_ = button_get_width (self->priv->continue_button);
	_tmp24_ = button_get_size (self->priv->continue_button);
	_tmp25_ = button_get_height (self->priv->continue_button);
	_tmp26_ = vector_new ((_tmp22_ * _tmp23_) * 6, (-1) + (_tmp24_ * _tmp25_), (gfloat) 0);
	_tmp27_ = _tmp26_;
	button_set_position (self->priv->riichi_button, _tmp27_);
	_vector_unref0 (_tmp27_);
	_tmp28_ = button_get_size (self->priv->continue_button);
	_tmp29_ = button_get_width (self->priv->continue_button);
	_tmp30_ = button_get_size (self->priv->continue_button);
	_tmp31_ = button_get_height (self->priv->continue_button);
	_tmp32_ = vector_new ((_tmp28_ * _tmp29_) * 8, (-1) + (_tmp30_ * _tmp31_), (gfloat) 0);
	_tmp33_ = _tmp32_;
	button_set_position (self->priv->tsumo_button, _tmp33_);
	_vector_unref0 (_tmp33_);
	_tmp34_ = button_get_size (self->priv->continue_button);
	_tmp35_ = button_get_width (self->priv->continue_button);
	_tmp36_ = button_get_size (self->priv->continue_button);
	_tmp37_ = button_get_height (self->priv->continue_button);
	_tmp38_ = vector_new ((_tmp34_ * _tmp35_) * 10, (-1) + (_tmp36_ * _tmp37_), (gfloat) 0);
	_tmp39_ = _tmp38_;
	button_set_position (self->priv->ron_button, _tmp39_);
	_vector_unref0 (_tmp39_);
	button_set_visible (self->priv->continue_button, TRUE);
	gee_abstract_collection_add ((GeeAbstractCollection*) self->priv->buttons, self->priv->continue_button);
	gee_abstract_collection_add ((GeeAbstractCollection*) self->priv->buttons, self->priv->pon_button);
	gee_abstract_collection_add ((GeeAbstractCollection*) self->priv->buttons, self->priv->kan_button);
	gee_abstract_collection_add ((GeeAbstractCollection*) self->priv->buttons, self->priv->chi_button);
	gee_abstract_collection_add ((GeeAbstractCollection*) self->priv->buttons, self->priv->riichi_button);
	gee_abstract_collection_add ((GeeAbstractCollection*) self->priv->buttons, self->priv->tsumo_button);
	gee_abstract_collection_add ((GeeAbstractCollection*) self->priv->buttons, self->priv->ron_button);
	return self;
}


GameInterface* game_interface_new (void) {
	return game_interface_construct (TYPE_GAME_INTERFACE);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


void game_interface_render (GameInterface* self) {
	g_return_if_fail (self != NULL);
	if (!self->priv->_visible) {
		return;
	}
	glDisable (GL_DEPTH_TEST);
	glDisable (GL_CULL_FACE);
	glDisable ((GLenum) GL_LIGHTING);
	glEnable ((GLenum) GL_TEXTURE_2D);
	glEnable ((GLenum) GL_COLOR_SUM);
	glDepthFunc ((GLenum) GL_LEQUAL);
	{
		GeeArrayList* _tmp0_;
		GeeArrayList* _b_list;
		gint _tmp1_;
		gint _b_size;
		gint _b_index;
		_tmp0_ = _g_object_ref0 (self->priv->buttons);
		_b_list = _tmp0_;
		_tmp1_ = gee_collection_get_size ((GeeCollection*) _b_list);
		_b_size = _tmp1_;
		_b_index = -1;
		while (TRUE) {
			gpointer _tmp2_ = NULL;
			Button* b;
			_b_index = _b_index + 1;
			if (!(_b_index < _b_size)) {
				break;
			}
			_tmp2_ = gee_abstract_list_get ((GeeAbstractList*) _b_list, _b_index);
			b = (Button*) _tmp2_;
			button_render (b);
			_button_unref0 (b);
		}
		_g_object_unref0 (_b_list);
	}
	glDisable ((GLenum) GL_TEXTURE_2D);
}


void game_interface_render_selection (GameInterface* self) {
	g_return_if_fail (self != NULL);
	if (!self->priv->_visible) {
		return;
	}
	glDisable (GL_DEPTH_TEST);
	glDisable (GL_CULL_FACE);
	glDisable ((GLenum) GL_LIGHTING);
	glDisable ((GLenum) GL_TEXTURE_2D);
	{
		GeeArrayList* _tmp0_;
		GeeArrayList* _b_list;
		gint _tmp1_;
		gint _b_size;
		gint _b_index;
		_tmp0_ = _g_object_ref0 (self->priv->buttons);
		_b_list = _tmp0_;
		_tmp1_ = gee_collection_get_size ((GeeCollection*) _b_list);
		_b_size = _tmp1_;
		_b_index = -1;
		while (TRUE) {
			gpointer _tmp2_ = NULL;
			Button* b;
			_b_index = _b_index + 1;
			if (!(_b_index < _b_size)) {
				break;
			}
			_tmp2_ = gee_abstract_list_get ((GeeAbstractList*) _b_list, _b_index);
			b = (Button*) _tmp2_;
			button_render_selection (b);
			_button_unref0 (b);
		}
		_g_object_unref0 (_b_list);
	}
}


gboolean game_interface_hover (GameInterface* self, gint x, gint y, guint color_id) {
	gboolean result = FALSE;
	gboolean hovering;
	g_return_val_if_fail (self != NULL, FALSE);
	hovering = FALSE;
	{
		GeeArrayList* _tmp0_;
		GeeArrayList* _b_list;
		gint _tmp1_;
		gint _b_size;
		gint _b_index;
		_tmp0_ = _g_object_ref0 (self->priv->buttons);
		_b_list = _tmp0_;
		_tmp1_ = gee_collection_get_size ((GeeCollection*) _b_list);
		_b_size = _tmp1_;
		_b_index = -1;
		while (TRUE) {
			gpointer _tmp2_ = NULL;
			Button* b;
			gboolean _tmp3_ = FALSE;
			gboolean _tmp4_;
			_b_index = _b_index + 1;
			if (!(_b_index < _b_size)) {
				break;
			}
			_tmp2_ = gee_abstract_list_get ((GeeAbstractList*) _b_list, _b_index);
			b = (Button*) _tmp2_;
			_tmp4_ = button_hover (b, color_id);
			if (_tmp4_) {
				guint _tmp5_;
				_tmp5_ = button_get_color_id (b);
				_tmp3_ = _tmp5_ == color_id;
			} else {
				_tmp3_ = FALSE;
			}
			if (_tmp3_) {
				hovering = TRUE;
			}
			_button_unref0 (b);
		}
		_g_object_unref0 (_b_list);
	}
	result = hovering;
	return result;
}


static gpointer _button_ref0 (gpointer self) {
	return self ? button_ref (self) : NULL;
}


Button* game_interface_click (GameInterface* self, gint x, gint y, guint color_id, gboolean state) {
	Button* result = NULL;
	Button* button;
	g_return_val_if_fail (self != NULL, NULL);
	button = NULL;
	{
		GeeArrayList* _tmp0_;
		GeeArrayList* _b_list;
		gint _tmp1_;
		gint _b_size;
		gint _b_index;
		_tmp0_ = _g_object_ref0 (self->priv->buttons);
		_b_list = _tmp0_;
		_tmp1_ = gee_collection_get_size ((GeeCollection*) _b_list);
		_b_size = _tmp1_;
		_b_index = -1;
		while (TRUE) {
			gpointer _tmp2_ = NULL;
			Button* b;
			gboolean _tmp3_;
			_b_index = _b_index + 1;
			if (!(_b_index < _b_size)) {
				break;
			}
			_tmp2_ = gee_abstract_list_get ((GeeAbstractList*) _b_list, _b_index);
			b = (Button*) _tmp2_;
			_tmp3_ = button_click (b, color_id, state);
			if (_tmp3_) {
				Button* _tmp4_;
				_tmp4_ = _button_ref0 (b);
				_button_unref0 (button);
				button = _tmp4_;
			}
			_button_unref0 (b);
		}
		_g_object_unref0 (_b_list);
	}
	result = button;
	return result;
}


gboolean game_interface_get_visible (GameInterface* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	result = self->priv->_visible;
	return result;
}


void game_interface_set_visible (GameInterface* self, gboolean value) {
	g_return_if_fail (self != NULL);
	self->priv->_visible = value;
}


gboolean game_interface_get_show_continue (GameInterface* self) {
	gboolean result;
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = button_get_visible (self->priv->continue_button);
	result = _tmp0_;
	return result;
}


void game_interface_set_show_continue (GameInterface* self, gboolean value) {
	g_return_if_fail (self != NULL);
	button_set_visible (self->priv->continue_button, value);
}


gboolean game_interface_get_show_pon (GameInterface* self) {
	gboolean result;
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = button_get_visible (self->priv->pon_button);
	result = _tmp0_;
	return result;
}


void game_interface_set_show_pon (GameInterface* self, gboolean value) {
	g_return_if_fail (self != NULL);
	button_set_visible (self->priv->pon_button, value);
}


gboolean game_interface_get_show_kan (GameInterface* self) {
	gboolean result;
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = button_get_visible (self->priv->kan_button);
	result = _tmp0_;
	return result;
}


void game_interface_set_show_kan (GameInterface* self, gboolean value) {
	g_return_if_fail (self != NULL);
	button_set_visible (self->priv->kan_button, value);
}


gboolean game_interface_get_show_chi (GameInterface* self) {
	gboolean result;
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = button_get_visible (self->priv->chi_button);
	result = _tmp0_;
	return result;
}


void game_interface_set_show_chi (GameInterface* self, gboolean value) {
	g_return_if_fail (self != NULL);
	button_set_visible (self->priv->chi_button, value);
}


gboolean game_interface_get_show_riichi (GameInterface* self) {
	gboolean result;
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = button_get_visible (self->priv->riichi_button);
	result = _tmp0_;
	return result;
}


void game_interface_set_show_riichi (GameInterface* self, gboolean value) {
	g_return_if_fail (self != NULL);
	button_set_visible (self->priv->riichi_button, value);
}


gboolean game_interface_get_show_tsumo (GameInterface* self) {
	gboolean result;
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = button_get_visible (self->priv->tsumo_button);
	result = _tmp0_;
	return result;
}


void game_interface_set_show_tsumo (GameInterface* self, gboolean value) {
	g_return_if_fail (self != NULL);
	button_set_visible (self->priv->tsumo_button, value);
}


gboolean game_interface_get_show_ron (GameInterface* self) {
	gboolean result;
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = button_get_visible (self->priv->ron_button);
	result = _tmp0_;
	return result;
}


void game_interface_set_show_ron (GameInterface* self, gboolean value) {
	g_return_if_fail (self != NULL);
	button_set_visible (self->priv->ron_button, value);
}


static void value_game_interface_init (GValue* value) {
	value->data[0].v_pointer = NULL;
}


static void value_game_interface_free_value (GValue* value) {
	if (value->data[0].v_pointer) {
		game_interface_unref (value->data[0].v_pointer);
	}
}


static void value_game_interface_copy_value (const GValue* src_value, GValue* dest_value) {
	if (src_value->data[0].v_pointer) {
		dest_value->data[0].v_pointer = game_interface_ref (src_value->data[0].v_pointer);
	} else {
		dest_value->data[0].v_pointer = NULL;
	}
}


static gpointer value_game_interface_peek_pointer (const GValue* value) {
	return value->data[0].v_pointer;
}


static gchar* value_game_interface_collect_value (GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	if (collect_values[0].v_pointer) {
		GameInterface* object;
		object = collect_values[0].v_pointer;
		if (object->parent_instance.g_class == NULL) {
			return g_strconcat ("invalid unclassed object pointer for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		} else if (!g_value_type_compatible (G_TYPE_FROM_INSTANCE (object), G_VALUE_TYPE (value))) {
			return g_strconcat ("invalid object type `", g_type_name (G_TYPE_FROM_INSTANCE (object)), "' for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		}
		value->data[0].v_pointer = game_interface_ref (object);
	} else {
		value->data[0].v_pointer = NULL;
	}
	return NULL;
}


static gchar* value_game_interface_lcopy_value (const GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	GameInterface** object_p;
	object_p = collect_values[0].v_pointer;
	if (!object_p) {
		return g_strdup_printf ("value location for `%s' passed as NULL", G_VALUE_TYPE_NAME (value));
	}
	if (!value->data[0].v_pointer) {
		*object_p = NULL;
	} else if (collect_flags & G_VALUE_NOCOPY_CONTENTS) {
		*object_p = value->data[0].v_pointer;
	} else {
		*object_p = game_interface_ref (value->data[0].v_pointer);
	}
	return NULL;
}


GParamSpec* param_spec_game_interface (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags) {
	ParamSpecGameInterface* spec;
	g_return_val_if_fail (g_type_is_a (object_type, TYPE_GAME_INTERFACE), NULL);
	spec = g_param_spec_internal (G_TYPE_PARAM_OBJECT, name, nick, blurb, flags);
	G_PARAM_SPEC (spec)->value_type = object_type;
	return G_PARAM_SPEC (spec);
}


gpointer value_get_game_interface (const GValue* value) {
	g_return_val_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_GAME_INTERFACE), NULL);
	return value->data[0].v_pointer;
}


void value_set_game_interface (GValue* value, gpointer v_object) {
	GameInterface* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_GAME_INTERFACE));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, TYPE_GAME_INTERFACE));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
		game_interface_ref (value->data[0].v_pointer);
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		game_interface_unref (old);
	}
}


void value_take_game_interface (GValue* value, gpointer v_object) {
	GameInterface* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_GAME_INTERFACE));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, TYPE_GAME_INTERFACE));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		game_interface_unref (old);
	}
}


static void game_interface_class_init (GameInterfaceClass * klass) {
	game_interface_parent_class = g_type_class_peek_parent (klass);
	GAME_INTERFACE_CLASS (klass)->finalize = game_interface_finalize;
	g_type_class_add_private (klass, sizeof (GameInterfacePrivate));
}


static void game_interface_instance_init (GameInterface * self) {
	GeeArrayList* _tmp0_ = NULL;
	Button* _tmp1_ = NULL;
	Button* _tmp2_ = NULL;
	Button* _tmp3_ = NULL;
	Button* _tmp4_ = NULL;
	Button* _tmp5_ = NULL;
	Button* _tmp6_ = NULL;
	Button* _tmp7_ = NULL;
	self->priv = GAME_INTERFACE_GET_PRIVATE (self);
	_tmp0_ = gee_array_list_new (TYPE_BUTTON, (GBoxedCopyFunc) button_ref, button_unref, NULL);
	self->priv->buttons = _tmp0_;
	_tmp1_ = button_new ("Continue", (guint) 256);
	self->priv->continue_button = _tmp1_;
	_tmp2_ = button_new ("Pon", (guint) 257);
	self->priv->pon_button = _tmp2_;
	_tmp3_ = button_new ("Kan", (guint) 258);
	self->priv->kan_button = _tmp3_;
	_tmp4_ = button_new ("Chi", (guint) 259);
	self->priv->chi_button = _tmp4_;
	_tmp5_ = button_new ("Riichi", (guint) 260);
	self->priv->riichi_button = _tmp5_;
	_tmp6_ = button_new ("Tsumo", (guint) 261);
	self->priv->tsumo_button = _tmp6_;
	_tmp7_ = button_new ("Ron", (guint) 262);
	self->priv->ron_button = _tmp7_;
	self->ref_count = 1;
}


static void game_interface_finalize (GameInterface* obj) {
	GameInterface * self;
	self = GAME_INTERFACE (obj);
	_g_object_unref0 (self->priv->buttons);
	_button_unref0 (self->priv->continue_button);
	_button_unref0 (self->priv->pon_button);
	_button_unref0 (self->priv->kan_button);
	_button_unref0 (self->priv->chi_button);
	_button_unref0 (self->priv->riichi_button);
	_button_unref0 (self->priv->tsumo_button);
	_button_unref0 (self->priv->ron_button);
}


GType game_interface_get_type (void) {
	static volatile gsize game_interface_type_id__volatile = 0;
	if (g_once_init_enter (&game_interface_type_id__volatile)) {
		static const GTypeValueTable g_define_type_value_table = { value_game_interface_init, value_game_interface_free_value, value_game_interface_copy_value, value_game_interface_peek_pointer, "p", value_game_interface_collect_value, "p", value_game_interface_lcopy_value };
		static const GTypeInfo g_define_type_info = { sizeof (GameInterfaceClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) game_interface_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GameInterface), 0, (GInstanceInitFunc) game_interface_instance_init, &g_define_type_value_table };
		static const GTypeFundamentalInfo g_define_type_fundamental_info = { (G_TYPE_FLAG_CLASSED | G_TYPE_FLAG_INSTANTIATABLE | G_TYPE_FLAG_DERIVABLE | G_TYPE_FLAG_DEEP_DERIVABLE) };
		GType game_interface_type_id;
		game_interface_type_id = g_type_register_fundamental (g_type_fundamental_next (), "GameInterface", &g_define_type_info, &g_define_type_fundamental_info, 0);
		g_once_init_leave (&game_interface_type_id__volatile, game_interface_type_id);
	}
	return game_interface_type_id__volatile;
}


gpointer game_interface_ref (gpointer instance) {
	GameInterface* self;
	self = instance;
	g_atomic_int_inc (&self->ref_count);
	return instance;
}


void game_interface_unref (gpointer instance) {
	GameInterface* self;
	self = instance;
	if (g_atomic_int_dec_and_test (&self->ref_count)) {
		GAME_INTERFACE_GET_CLASS (self)->finalize (self);
		g_type_free_instance ((GTypeInstance *) self);
	}
}



