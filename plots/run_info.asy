import patterns;

//----------------------------------------------------------------------------------------------------

transform swToHours = scale(1/3600, 1);
transform swToMinutes = scale(1/60, 1);

//----------------------------------------------------------------------------------------------------

int runs[];
string run_datasets[];
real run_ts_from[], run_ts_to[];
pen run_colors[];

void AddRun(string ds, int r, real f, real t, pen p = yellow + opacity(0.3))
{
	run_datasets.push(ds);
	runs.push(r);
	run_ts_from.push(f);
	run_ts_to.push(t);
	run_colors.push(p);
}

//----------------------------------------------------------------------------------------------------

string excl_datasets[];
real excl_ts_from[], excl_ts_to[];

void AddExcl(string ds, real f, real t)
{
	excl_datasets.push(ds);
	excl_ts_from.push(f);
	excl_ts_to.push(t);
}

pen p_excl = black + opacity(0.4);

//----------------------------------------------------------------------------------------------------

// fill 7280
AddRun("7280", 324458, 78681, 84964);
AddRun("7280", 324460, 85249, 89040);
AddExcl("7280", 78680, 79250);
AddExcl("7280", 80640, 80660);
AddExcl("7280", 80670, 80820);
AddExcl("7280", 80850, 81050);
AddExcl("7280", 84840, 84970);

// fill 7281
AddRun("7281", 324461, 92934, 93580);
AddRun("7281", 324462, 93631, 101598);
AddExcl("7281", 93364, 93434);
AddExcl("7281", 93464, 93474);
AddExcl("7281", 94444, 94454);
AddExcl("7281", 95804, 101574);

// fill 7282
AddRun("7282", 324464, 105700, 107544);
AddRun("7282", 324465, 107684, 116740);
AddExcl("7282", 105700, 105900);
AddExcl("7282", 107520, 107550);
AddExcl("7282", 112100, 112320);
AddExcl("7282", 112520, 112560);
AddExcl("7282", 115000, 116730);

// fill 7283
AddRun("7283", 324467, 120518, 120652);
AddRun("7283", 324469, 121303, 122682);
AddRun("7283", 324471, 123007, 126492);
AddExcl("7283", 120518, 120658);

// fill 7284
AddRun("7284", 324485, 130750, 143443);
AddExcl("7284", 131310, 131340);
AddExcl("7284", 133920, 134180);
AddExcl("7284", 137740, 137760);
AddExcl("7284", 141420, 141460);

// fill 7285
AddRun("7285", 324498, 148551, 150577);
AddRun("7285", 324509, 150745, 152385);
AddRun("7285", 324513, 153219, 159046);
AddExcl("7285", 150480, 150580);
AddExcl("7285", 152340, 152390);

// fill 7289
AddRun("7289", 324532, 206071, 218141);
AddExcl("7289", 206070, 206090);
AddExcl("7289", 215290, 218120);

// fill 7291
AddRun("7291", 324536, 233085, 244931);
AddExcl("7291", 233084, 233094);
AddExcl("7291", 241454, 244914);


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
			x_min = min(x_min, run_ts_from[i]/3600);
			x_max = max(x_max, run_ts_to[i]/3600);
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

			real x_min = run_ts_from[i]/3600, x_max = run_ts_to[i]/3600;
			filldraw((x_min, y_min)--(x_max, y_min)--(x_max, y_max)--(x_min, y_max)--cycle, run_colors[i], nullpen);
		}
	}

	// draw exclusions
	{
		for (int i : excl_datasets.keys)
		{
			if (excl_datasets[i] == filter)
			{
				real x_min = excl_ts_from[i]/3600, x_max = excl_ts_to[i]/3600;
				filldraw((x_min, y_min)--(x_max, y_min)--(x_max, y_max)--(x_min, y_max)--cycle, p_excl, nullpen);
			}
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

			real x_min = run_ts_from[i]/3600, x_max = run_ts_to[i]/3600;
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

		yaxis(XEquals(run_ts_from[i]/3600, false), dashed);
		yaxis(XEquals(run_ts_to[i]/3600, false), dashed);
	}
}
