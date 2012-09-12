#include <stdio.h>
#include <stdlib.h>

#include "font.h"

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
