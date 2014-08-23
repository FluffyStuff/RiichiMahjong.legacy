/* Button.c generated by valac 0.12.0, the Vala compiler
 * generated from Button.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <GL/glew.h>
#include <gobject/gvaluecollector.h>


#define TYPE_BUTTON (button_get_type ())
#define BUTTON(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_BUTTON, Button))
#define BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_BUTTON, ButtonClass))
#define IS_BUTTON(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_BUTTON))
#define IS_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_BUTTON))
#define BUTTON_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_BUTTON, ButtonClass))

typedef struct _Button Button;
typedef struct _ButtonClass ButtonClass;
typedef struct _ButtonPrivate ButtonPrivate;

#define TYPE_TEXTURE (texture_get_type ())
#define TEXTURE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TEXTURE, Texture))
#define TEXTURE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TEXTURE, TextureClass))
#define IS_TEXTURE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TEXTURE))
#define IS_TEXTURE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TEXTURE))
#define TEXTURE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TEXTURE, TextureClass))

typedef struct _Texture Texture;
typedef struct _TextureClass TextureClass;

#define TYPE_VECTOR (vector_get_type ())
#define VECTOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_VECTOR, Vector))
#define VECTOR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_VECTOR, VectorClass))
#define IS_VECTOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_VECTOR))
#define IS_VECTOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_VECTOR))
#define VECTOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_VECTOR, VectorClass))

typedef struct _Vector Vector;
typedef struct _VectorClass VectorClass;
#define _texture_unref0(var) ((var == NULL) ? NULL : (var = (texture_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
#define _vector_unref0(var) ((var == NULL) ? NULL : (var = (vector_unref (var), NULL)))
typedef struct _ParamSpecButton ParamSpecButton;

struct _Button {
	GTypeInstance parent_instance;
	volatile int ref_count;
	ButtonPrivate * priv;
};

struct _ButtonClass {
	GTypeClass parent_class;
	void (*finalize) (Button *self);
};

struct _ButtonPrivate {
	Texture* texture;
	gboolean press_down;
	gboolean hovering;
	gchar* _name;
	guint _color_id;
	Vector* _position;
	gfloat _size;
	gfloat _width;
	gfloat _height;
	gboolean _visible;
};

struct _ParamSpecButton {
	GParamSpec parent_instance;
};


static gpointer button_parent_class = NULL;

gpointer button_ref (gpointer instance);
void button_unref (gpointer instance);
GParamSpec* param_spec_button (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void value_set_button (GValue* value, gpointer v_object);
void value_take_button (GValue* value, gpointer v_object);
gpointer value_get_button (const GValue* value);
GType button_get_type (void) G_GNUC_CONST;
gpointer texture_ref (gpointer instance);
void texture_unref (gpointer instance);
GParamSpec* param_spec_texture (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void value_set_texture (GValue* value, gpointer v_object);
void value_take_texture (GValue* value, gpointer v_object);
gpointer value_get_texture (const GValue* value);
GType texture_get_type (void) G_GNUC_CONST;
gpointer vector_ref (gpointer instance);
void vector_unref (gpointer instance);
GParamSpec* param_spec_vector (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void value_set_vector (GValue* value, gpointer v_object);
void value_take_vector (GValue* value, gpointer v_object);
gpointer value_get_vector (const GValue* value);
GType vector_get_type (void) G_GNUC_CONST;
#define BUTTON_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_BUTTON, ButtonPrivate))
enum  {
	BUTTON_DUMMY_PROPERTY
};
Button* button_new (const gchar* name, guint color_id);
Button* button_construct (GType object_type, const gchar* name, guint color_id);
static void button_set_name (Button* self, const gchar* value);
Texture* texture_load_texture (const gchar* name);
static void button_set_color_id (Button* self, guint value);
Vector* vector_new_empty (void);
Vector* vector_construct_empty (GType object_type);
void button_set_position (Button* self, Vector* value);
void button_set_visible (Button* self, gboolean value);
void button_set_size (Button* self, gfloat value);
static void button_set_width (Button* self, gfloat value);
static void button_set_height (Button* self, gfloat value);
gboolean button_hover (Button* self, guint color_id);
guint button_get_color_id (Button* self);
gboolean button_click (Button* self, guint color_id, gboolean up);
void button_render (Button* self);
gboolean button_get_visible (Button* self);
Vector* button_get_position (Button* self);
gfloat vector_get_x (Vector* self);
gfloat vector_get_y (Vector* self);
gfloat vector_get_z (Vector* self);
GLuint texture_get_texture (Texture* self);
gfloat button_get_width (Button* self);
gfloat button_get_height (Button* self);
gfloat button_get_size (Button* self);
void button_render_selection (Button* self);
const gchar* button_get_name (Button* self);
static void button_finalize (Button* obj);


Button* button_construct (GType object_type, const gchar* name, guint color_id) {
	Button* self = NULL;
	gchar* _tmp0_;
	gchar* _tmp1_;
	Texture* _tmp2_ = NULL;
	Vector* _tmp3_ = NULL;
	Vector* _tmp4_;
	g_return_val_if_fail (name != NULL, NULL);
	self = (Button*) g_type_create_instance (object_type);
	button_set_name (self, name);
	_tmp0_ = g_strconcat ("interface/", name, NULL);
	_tmp1_ = _tmp0_;
	_tmp2_ = texture_load_texture (_tmp1_);
	_texture_unref0 (self->priv->texture);
	self->priv->texture = _tmp2_;
	_g_free0 (_tmp1_);
	button_set_color_id (self, color_id);
	_tmp3_ = vector_new_empty ();
	_tmp4_ = _tmp3_;
	button_set_position (self, _tmp4_);
	_vector_unref0 (_tmp4_);
	button_set_visible (self, FALSE);
	button_set_size (self, 0.1f);
	button_set_width (self, 0.5f);
	button_set_height (self, 0.5f);
	return self;
}


Button* button_new (const gchar* name, guint color_id) {
	return button_construct (TYPE_BUTTON, name, color_id);
}


gboolean button_hover (Button* self, guint color_id) {
	gboolean result = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	self->priv->hovering = self->priv->_color_id == color_id;
	if (!self->priv->hovering) {
		self->priv->press_down = FALSE;
	}
	result = self->priv->hovering;
	return result;
}


gboolean button_click (Button* self, guint color_id, gboolean up) {
	gboolean result = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	button_hover (self, color_id);
	if (!self->priv->hovering) {
		result = FALSE;
		return result;
	}
	if (!up) {
		self->priv->press_down = TRUE;
	} else {
		if (self->priv->press_down) {
			g_signal_emit_by_name (self, "press");
			self->priv->press_down = FALSE;
			result = TRUE;
			return result;
		}
	}
	result = FALSE;
	return result;
}


void button_render (Button* self) {
	gfloat _tmp0_;
	gfloat _tmp1_;
	gfloat _tmp2_;
	GLuint _tmp4_;
	g_return_if_fail (self != NULL);
	if (!self->priv->_visible) {
		return;
	}
	glPushMatrix ();
	glPushAttrib ((GLbitfield) GL_ALL_ATTRIB_BITS);
	_tmp0_ = vector_get_x (self->priv->_position);
	_tmp1_ = vector_get_y (self->priv->_position);
	_tmp2_ = vector_get_z (self->priv->_position);
	glTranslatef ((GLfloat) _tmp0_, (GLfloat) _tmp1_, (GLfloat) _tmp2_);
	if (self->priv->press_down) {
		glColor3f ((GLfloat) 0.5, (GLfloat) 0.5, (GLfloat) 0.5);
	} else {
		gfloat _tmp3_ = 0.0F;
		gfloat add;
		if (self->priv->hovering) {
			_tmp3_ = 0.25f;
		} else {
			_tmp3_ = (gfloat) 0;
		}
		add = _tmp3_;
		glSecondaryColor3f ((GLfloat) add, (GLfloat) add, (GLfloat) add);
	}
	_tmp4_ = texture_get_texture (self->priv->texture);
	glBindTexture ((GLenum) GL_TEXTURE_2D, _tmp4_);
	glTexParameteri ((GLenum) GL_TEXTURE_2D, (GLenum) GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri ((GLenum) GL_TEXTURE_2D, (GLenum) GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glScalef ((GLfloat) self->priv->_width, (GLfloat) self->priv->_height, (GLfloat) 1);
	glBegin ((GLenum) GL_QUADS);
	glTexCoord2f ((GLfloat) 0, (GLfloat) 1);
	glVertex3f (-((GLfloat) self->priv->_size), -((GLfloat) self->priv->_size), (GLfloat) 0);
	glTexCoord2f ((GLfloat) 1, (GLfloat) 1);
	glVertex3f ((GLfloat) self->priv->_size, -((GLfloat) self->priv->_size), (GLfloat) 0);
	glTexCoord2f ((GLfloat) 1, (GLfloat) 0);
	glVertex3f ((GLfloat) self->priv->_size, (GLfloat) self->priv->_size, (GLfloat) 0);
	glTexCoord2f ((GLfloat) 0, (GLfloat) 0);
	glVertex3f (-((GLfloat) self->priv->_size), (GLfloat) self->priv->_size, (GLfloat) 0);
	glEnd ();
	glPopAttrib ();
	glPopMatrix ();
}


void button_render_selection (Button* self) {
	gfloat _tmp0_;
	gfloat _tmp1_;
	gfloat _tmp2_;
	guint r;
	guint g;
	guint b;
	g_return_if_fail (self != NULL);
	if (!self->priv->_visible) {
		return;
	}
	glPushMatrix ();
	_tmp0_ = vector_get_x (self->priv->_position);
	_tmp1_ = vector_get_y (self->priv->_position);
	_tmp2_ = vector_get_z (self->priv->_position);
	glTranslatef ((GLfloat) _tmp0_, (GLfloat) _tmp1_, (GLfloat) _tmp2_);
	glDepthFunc ((GLenum) GL_LEQUAL);
	r = (self->priv->_color_id >> 16) % 256;
	g = (self->priv->_color_id >> 8) % 256;
	b = self->priv->_color_id % 256;
	glColor3f ((GLfloat) (r / 255.0f), (GLfloat) (g / 255.0f), (GLfloat) (b / 255.0f));
	glScalef ((GLfloat) self->priv->_width, (GLfloat) self->priv->_height, (GLfloat) 1);
	glBegin ((GLenum) GL_QUADS);
	glVertex3f (-((GLfloat) self->priv->_size), -((GLfloat) self->priv->_size), (GLfloat) 0);
	glVertex3f ((GLfloat) self->priv->_size, -((GLfloat) self->priv->_size), (GLfloat) 0);
	glVertex3f ((GLfloat) self->priv->_size, (GLfloat) self->priv->_size, (GLfloat) 0);
	glVertex3f (-((GLfloat) self->priv->_size), (GLfloat) self->priv->_size, (GLfloat) 0);
	glEnd ();
	glPopMatrix ();
}


const gchar* button_get_name (Button* self) {
	const gchar* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_name;
	return result;
}


static void button_set_name (Button* self, const gchar* value) {
	gchar* _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp0_ = g_strdup (value);
	_g_free0 (self->priv->_name);
	self->priv->_name = _tmp0_;
}


guint button_get_color_id (Button* self) {
	guint result;
	g_return_val_if_fail (self != NULL, 0U);
	result = self->priv->_color_id;
	return result;
}


static void button_set_color_id (Button* self, guint value) {
	g_return_if_fail (self != NULL);
	self->priv->_color_id = value;
}


Vector* button_get_position (Button* self) {
	Vector* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_position;
	return result;
}


static gpointer _vector_ref0 (gpointer self) {
	return self ? vector_ref (self) : NULL;
}


void button_set_position (Button* self, Vector* value) {
	Vector* _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp0_ = _vector_ref0 (value);
	_vector_unref0 (self->priv->_position);
	self->priv->_position = _tmp0_;
}


gfloat button_get_size (Button* self) {
	gfloat result;
	g_return_val_if_fail (self != NULL, 0.0F);
	result = self->priv->_size;
	return result;
}


void button_set_size (Button* self, gfloat value) {
	g_return_if_fail (self != NULL);
	self->priv->_size = value;
}


gfloat button_get_width (Button* self) {
	gfloat result;
	g_return_val_if_fail (self != NULL, 0.0F);
	result = self->priv->_width;
	return result;
}


static void button_set_width (Button* self, gfloat value) {
	g_return_if_fail (self != NULL);
	self->priv->_width = value;
}


gfloat button_get_height (Button* self) {
	gfloat result;
	g_return_val_if_fail (self != NULL, 0.0F);
	result = self->priv->_height;
	return result;
}


static void button_set_height (Button* self, gfloat value) {
	g_return_if_fail (self != NULL);
	self->priv->_height = value;
}


gboolean button_get_visible (Button* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	result = self->priv->_visible;
	return result;
}


void button_set_visible (Button* self, gboolean value) {
	g_return_if_fail (self != NULL);
	self->priv->_visible = value;
}


static void value_button_init (GValue* value) {
	value->data[0].v_pointer = NULL;
}


static void value_button_free_value (GValue* value) {
	if (value->data[0].v_pointer) {
		button_unref (value->data[0].v_pointer);
	}
}


static void value_button_copy_value (const GValue* src_value, GValue* dest_value) {
	if (src_value->data[0].v_pointer) {
		dest_value->data[0].v_pointer = button_ref (src_value->data[0].v_pointer);
	} else {
		dest_value->data[0].v_pointer = NULL;
	}
}


static gpointer value_button_peek_pointer (const GValue* value) {
	return value->data[0].v_pointer;
}


static gchar* value_button_collect_value (GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	if (collect_values[0].v_pointer) {
		Button* object;
		object = collect_values[0].v_pointer;
		if (object->parent_instance.g_class == NULL) {
			return g_strconcat ("invalid unclassed object pointer for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		} else if (!g_value_type_compatible (G_TYPE_FROM_INSTANCE (object), G_VALUE_TYPE (value))) {
			return g_strconcat ("invalid object type `", g_type_name (G_TYPE_FROM_INSTANCE (object)), "' for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		}
		value->data[0].v_pointer = button_ref (object);
	} else {
		value->data[0].v_pointer = NULL;
	}
	return NULL;
}


static gchar* value_button_lcopy_value (const GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	Button** object_p;
	object_p = collect_values[0].v_pointer;
	if (!object_p) {
		return g_strdup_printf ("value location for `%s' passed as NULL", G_VALUE_TYPE_NAME (value));
	}
	if (!value->data[0].v_pointer) {
		*object_p = NULL;
	} else if (collect_flags & G_VALUE_NOCOPY_CONTENTS) {
		*object_p = value->data[0].v_pointer;
	} else {
		*object_p = button_ref (value->data[0].v_pointer);
	}
	return NULL;
}


GParamSpec* param_spec_button (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags) {
	ParamSpecButton* spec;
	g_return_val_if_fail (g_type_is_a (object_type, TYPE_BUTTON), NULL);
	spec = g_param_spec_internal (G_TYPE_PARAM_OBJECT, name, nick, blurb, flags);
	G_PARAM_SPEC (spec)->value_type = object_type;
	return G_PARAM_SPEC (spec);
}


gpointer value_get_button (const GValue* value) {
	g_return_val_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_BUTTON), NULL);
	return value->data[0].v_pointer;
}


void value_set_button (GValue* value, gpointer v_object) {
	Button* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_BUTTON));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, TYPE_BUTTON));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
		button_ref (value->data[0].v_pointer);
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		button_unref (old);
	}
}


void value_take_button (GValue* value, gpointer v_object) {
	Button* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TYPE_BUTTON));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, TYPE_BUTTON));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		button_unref (old);
	}
}


static void button_class_init (ButtonClass * klass) {
	button_parent_class = g_type_class_peek_parent (klass);
	BUTTON_CLASS (klass)->finalize = button_finalize;
	g_type_class_add_private (klass, sizeof (ButtonPrivate));
	g_signal_new ("press", TYPE_BUTTON, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
}


static void button_instance_init (Button * self) {
	self->priv = BUTTON_GET_PRIVATE (self);
	self->priv->press_down = FALSE;
	self->priv->hovering = FALSE;
	self->ref_count = 1;
}


static void button_finalize (Button* obj) {
	Button * self;
	self = BUTTON (obj);
	_texture_unref0 (self->priv->texture);
	_g_free0 (self->priv->_name);
	_vector_unref0 (self->priv->_position);
}


GType button_get_type (void) {
	static volatile gsize button_type_id__volatile = 0;
	if (g_once_init_enter (&button_type_id__volatile)) {
		static const GTypeValueTable g_define_type_value_table = { value_button_init, value_button_free_value, value_button_copy_value, value_button_peek_pointer, "p", value_button_collect_value, "p", value_button_lcopy_value };
		static const GTypeInfo g_define_type_info = { sizeof (ButtonClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) button_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (Button), 0, (GInstanceInitFunc) button_instance_init, &g_define_type_value_table };
		static const GTypeFundamentalInfo g_define_type_fundamental_info = { (G_TYPE_FLAG_CLASSED | G_TYPE_FLAG_INSTANTIATABLE | G_TYPE_FLAG_DERIVABLE | G_TYPE_FLAG_DEEP_DERIVABLE) };
		GType button_type_id;
		button_type_id = g_type_register_fundamental (g_type_fundamental_next (), "Button", &g_define_type_info, &g_define_type_fundamental_info, 0);
		g_once_init_leave (&button_type_id__volatile, button_type_id);
	}
	return button_type_id__volatile;
}


gpointer button_ref (gpointer instance) {
	Button* self;
	self = instance;
	g_atomic_int_inc (&self->ref_count);
	return instance;
}


void button_unref (gpointer instance) {
	Button* self;
	self = instance;
	if (g_atomic_int_dec_and_test (&self->ref_count)) {
		BUTTON_GET_CLASS (self)->finalize (self);
		g_type_free_instance ((GTypeInstance *) self);
	}
}



