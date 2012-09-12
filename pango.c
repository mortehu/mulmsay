#include "font.h"

void
pango_render_string (cairo_t *cairo,
                     int x, int y,
                     const char *font,
                     unsigned int size,
                     const char *string)
{
  PangoLayout *layout;
  PangoFontDescription *fontDescription;
  PangoRectangle ink, logical;

  layout = pango_cairo_create_layout (cairo);

  fontDescription = pango_font_description_new ();
  pango_font_description_set_family (fontDescription, font);
  pango_font_description_set_size (fontDescription, size * PANGO_SCALE);
  pango_layout_set_font_description (layout, fontDescription);
  pango_font_description_free (fontDescription);

  pango_layout_set_text (layout, string, -1);
  pango_layout_set_alignment (layout, PANGO_ALIGN_CENTER);
  pango_layout_set_width (layout, 242 * PANGO_SCALE);
  pango_layout_set_height (layout, 226 * PANGO_SCALE);

  pango_layout_get_extents (layout, &ink, &logical);

  cairo_move_to (cairo, 400, 340 - ink.height / PANGO_SCALE * 0.5);

  pango_cairo_update_layout (cairo, layout);
  pango_cairo_show_layout (cairo, layout);

  g_object_unref (layout);
}
