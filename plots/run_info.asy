//----------------------------------------------------------------------------------------------------

transform swToHours = scale(1/3600, 1);
transform swToMinutes = scale(1/60, 1);

//----------------------------------------------------------------------------------------------------

string run_datasets[];
int runs[];
real ts_from[], ts_to[];
pen run_colors[];

void AddRun(string ds, int r, real f, real t, pen p = yellow + opacity(0.3))
{
	run_datasets.push(ds);
	runs.push(r);
	ts_from.push(f);
	ts_to.push(t);
	run_colors.push(p);
}

pen p_unused = black + opacity(0.2);

// fill 7280
AddRun("7280", 324458, 78681, 84964);
AddRun("7280", 324460, 85249, 89040);

// fill 7281
AddRun("7281", 324461, 92934, 93580);
AddRun("7281", 324462, 93631, 101598);

// fill 7282
AddRun("7282", 324464, 105700, 107544);
AddRun("7282", 324465, 107684, 116740);

// fill 7283
AddRun("7283", 324467, 120518, 120652);
AddRun("7283", 324469, 121303, 122682);
AddRun("7283", 324471, 123007, 126492);

// fill 7284
AddRun("7284", 324485, 130750, 143443);

// fill 7285
AddRun("7285", 324498, 148551, 150577);
AddRun("7285", 324509, 150745, 152385);
AddRun("7285", 324513, 153219, 159046);

// fill 7289
AddRun("7289", 324532, 206071, 218141);

// fill 7291
AddRun("7291", 324536, 233085, 244931);

// in hours
real time_min = 0;
real time_max = 5;

//----------------------------------------------------------------------------------------------------

void DrawBands(string filter="", string bands="ds", string labels="ds", real y_min=0, real y_max=0)
{
	// determine min and max of x for the selection
	real x_min = 1e100, x_max = -1e100;
	for (int i : runs.keys)
	{
		if (run_datasets[i] == filter)
		{
			x_min = min(x_min, ts_from[i]/3600);
			x_max = max(x_max, ts_to[i]/3600);
		}
	}

	// draw bands
	if (bands == "ds")
	{
		pen p = yellow+opacity(0.3);

		filldraw((x_min, y_min)--(x_max, y_min)--(x_max, y_max)--(x_min, y_max)--cycle, p, nullpen);
	}

	if (bands == "run")
	{
		for (int i : runs.keys)
		{
			if (run_datasets[i] != filter)
				continue;

			real x_min = ts_from[i]/3600, x_max = ts_to[i]/3600;
			filldraw((x_min, y_min)--(x_max, y_min)--(x_max, y_max)--(x_min, y_max)--cycle, run_colors[i], nullpen);
		}
	}

	// draw labels
	if (labels == "ds")
	{
		label("{\SmallerFonts " + filter + "}", ((x_min + x_max)/2, y_max), S);
	}

	if (labels == "run")
	{
		for (int i : runs.keys)
		{
			if (run_datasets[i] != filter)
				continue;

			real x_min = ts_from[i]/3600, x_max = ts_to[i]/3600;
			label(format("{\SmallerFonts %u}", runs[i]), ((x_min + x_max)/2, y_max), S);
		}
	}
}

//----------------------------------------------------------------------------------------------------

void DrawFillBands(string filter="", real y_min=0, real y_max=0, bool details=true)
{
	DrawBands(filter, bands="ds", labels=(details) ? "ds" : "", y_min, y_max);
}

//----------------------------------------------------------------------------------------------------

void DrawRunBands(string filter="", real y_min=0, real y_max=0, bool details=true)
{
	DrawBands(filter, bands="run", labels=(details) ? "run" : "", y_min, y_max);
}

//----------------------------------------------------------------------------------------------------

void DrawRunBoundaries(string filter="")
{
	for (int i : runs.keys)
	{
		if (filter != "")
			if (run_datasets[i] != filter)
				continue;

		yaxis(XEquals(ts_from[i]/3600, false), dashed);
		yaxis(XEquals(ts_to[i]/3600, false), dashed);
	}
}
