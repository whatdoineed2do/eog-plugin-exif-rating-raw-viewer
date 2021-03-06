#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <strings.h>
#include <limits.h>

#include <string>
#include <sstream>
#include <iostream>
#include <cassert>

using namespace  std;

#include <Magick++.h>


int main(int argc, char* const argv[])
{
    int  ret = 0;
    try
    {
	ostringstream  os;
	os << "text\nwith\nnewline breaks";

	Magick::Image  magick(argc == 2 ? argv[1] : "600x400", "blue");

	Magick::Image  info(Magick::Geometry(magick.columns(), magick.rows()), "grey");
	info.borderColor("grey");
	if (argc == 3) {
	    // ttf - needs full path: "@/usr/share/fonts/google-noto/NotoSans-Regular.ttf"
	    // xserver font: NimbusSans-Regular
	    // see fc-list
	    info.font(argv[2]);
	}
	info.fontPointsize(28);
	info.annotate(os.str(), Magick::Geometry("+10+10"), Magick::WestGravity);
	info.trim();
	info.border();
#if MagickLibInterface == 5  // IM 6.x
        info.opacity(65535/3.0);
        info.transparent("grey");
#elif MagickLibInterface == 6  // IM 7
	// TODO - no transparency
        info.opaque(Magick::Color("none"), Magick::Color("grey"));
	info.backgroundColor(Magick::Color("grey"));
#endif

	cout << "composite size=" << info.columns() << "x" << info.rows() << endl;

	if (info.columns() > magick.columns()-10) {
	    ostringstream  os;
	    os << magick.columns()-10 << "x";
	    info.resize(os.str());
	}


	magick.composite(info,
			    Magick::Geometry(info.columns(), info.rows(), 10, magick.rows()-info.rows()-10),
			    Magick::DissolveCompositeOp);

	magick.write("magick-label-composite.jpg");
    }
    catch (const std::exception& ex)
    {
	cerr << "failed to magick - " << ex.what() << endl;
	ret = 1;
    }

    return ret;
}
