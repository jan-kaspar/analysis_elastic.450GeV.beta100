import root;
import pad_layout;

string f = "fit_details.root";

NewPad("$\De^{R-L} \th^*_x\ung{\mu rad}$");
scale(Linear, Log);
draw(scale(1e6, 1), RootGetObject(f, "h_x_in"), "vl,eb", black);
draw(scale(1e6, 1), RootGetObject(f, "h_x_in|gaus"), blue);
draw(scale(1e6, 1), RootGetObject(f, "h_x_in|ff"), red);
limits((-150, 1e5), (+150, 2e9), Crop);

NewPad("$\De^{R-L} \th^*_y\ung{\mu rad}$");
scale(Linear, Log);
draw(scale(1e6, 1), RootGetObject(f, "h_y_in"), "vl,eb", black);
draw(scale(1e6, 1), RootGetObject(f, "h_y_in|gaus"), blue);
draw(scale(1e6, 1), RootGetObject(f, "h_y_in|ff"), red);
limits((-40, 2e6), (+40, 8e9), Crop);
