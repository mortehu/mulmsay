#include <stdio.h>
#include <stdlib.h>

#include <cairo/cairo.h>
#include <pango/pangocairo.h>

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

int
main (int argc, char **argv)
{
  cairo_t *cairo;
  cairo_surface_t *surface, *hair, *outline;
  const char *text;

  if (argc >= 2)
    text = argv[1];
  else
    text = "Hallo!";

  surface = cairo_image_surface_create (CAIRO_FORMAT_RGB24, 696, 707);
  hair = cairo_image_surface_create_from_png ("/usr/local/share/mulmsay/mulm-hair.png");
  outline = cairo_image_surface_create_from_png ("/usr/local/share/mulmsay/mulm.png");

  cairo = cairo_create (surface);

  cairo_set_source_rgba (cairo, 1.0f, 1.0f, 1.0f, 1.0f);
  cairo_rectangle (cairo, 0, 0, 696, 707);
  cairo_fill (cairo);

  cairo_set_source_rgba (cairo, 0.0f, 0.0f, 0.0f, 1.0f);
  pango_render_string (cairo, 0, 0, "Droid", 22, text);


  if (argc >= 3)
    {
      long haircolor;

      haircolor = strtol (argv[2], 0, 0);

      cairo_set_source_rgba (cairo, ((haircolor >> 16) & 0xff) / 255.0, ((haircolor >> 8) & 0xff) / 255.0, (haircolor & 0xff) / 255.0, 1.0f);
      cairo_mask_surface (cairo, hair, 0.0, 0.0);
    }

  cairo_set_source_rgba (cairo, 0.0f, 0.0f, 0.0f, 1.0f);
  cairo_mask_surface (cairo, outline, 0.0, 0.0);

  cairo_surface_write_to_png (surface, "/proc/self/fd/1");

  return EXIT_SUCCESS;
}
