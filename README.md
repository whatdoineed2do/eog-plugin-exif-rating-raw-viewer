# Gnome EOG plugin: EXIF rating & simple RAW image viewer

Simple set of addons for `gtk`, primarily/initially a `gdk pixbuf loader` for RAW files (loading by extracting embedded preview images via `exiv2`) and a `eog` rating plugin (also using `exiv2`).

Currently, pixbuf loader handles Nikon NEF and Canon CR2 and will examine the preview images available to use for display:  by default, it won't display anything larger than 12mpl and will internally scale a preview image to this size - this is to avoid a `cairo-xlib-surface-shm.c:619 mem pool exhausting bug` that would otherwise cause `eog` to crash.

The preview image size scaling limit can be controlled by the environment variable `EXIV2_PIXBUF_LOADER_SCALE_LIMIT` - set this to something large to avoid internal scaling and to observe the `cairo` bug.

## Intended Usage
Use when reviewing and making _first cut_ selections from RAW files from within a GNOME environment where spinning up a VM image with CaptureNX or Lightroom is not possible (ie travelling with a netbook).  Allows for review and later culls and RAW processing.

## Rating files
Using `eog`, open any files and use `r` key to toggle rating on the current image file - the rating is only saved when moving away from the current image;  if you toggle multiple times that leaves the file in the original _rated_ state, no rating update is written to the file.

Ratings are represented in the `XMP Rating` tag with a value of `5`.  Use `exiv2 -px foo.NEF` to validate rating flag is set on the file.

Current rating is displayed on the bottom right of the `eog` statusbar.

## Dependancies
Uses `eog`, `gdk-pixbuf`, `exiv2` and `image magick`.

