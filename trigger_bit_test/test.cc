#include "TFile.h"

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"

#include "DataFormats/Common/interface/TriggerResults.h"

#include <iostream>

using namespace std;

//----------------------------------------------------------------------------------------------------

int main()
{
	// prepare input
	vector<string> input_files = {
		"root://cms-xrd-global.cern.ch///store/data/Run2017F/ZeroBias/RAW/v1/000/306/381/00000/DAA8B601-4DC5-E711-A04B-02163E01A3E0.root"
	};
	fwlite::ChainEvent event(input_files);

	printf("* events in input chain: %llu\n", event.size());

	// loop over the chain entries
	for (event.toBegin(); ! event.atEnd(); ++event)
	{
		cout << endl << "--------------------------------------------" << endl;
		cout << event.id() << endl;

		fwlite::Handle< edm::TriggerResults > trig;
		trig.getByLabel(event, "TriggerResults");

		cout << *trig << endl;

		cout << trig->accept(276) << endl;
	}

	// clean up
	return 0;
}
