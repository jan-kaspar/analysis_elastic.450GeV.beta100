#include "TFile.h"
#include "TGraph.h"
#include "TH1D.h"

#include <string>

using namespace std;

//----------------------------------------------------------------------------------------------------

int CompareGraphs(const TGraph *g1, const TGraph *g2)
{
    if (g1->GetN() != g2->GetN())
    {
        printf("* number of points is different\n");
        return 1;
    }

    for (int i = 0; i < g1->GetN(); ++i)
    {
        const double x1 = g1->GetX()[i];
        const double y1 = g1->GetY()[i];
        const double x2 = g2->GetX()[i];
        const double y2 = g2->GetY()[i];

        if (x1 != x2 || y1 != y2)
        {
            printf("* difference in point %i: (1) = (%.3E, %.3E), (2) = (%.3E, %.3E)\n", i, x1, y1, x2, y2);
            return 2;
        }
    }

    return 0;
}

//----------------------------------------------------------------------------------------------------

int CompareHistograms(const TH1 *h1, const TH1 *h2)
{
    printf("* CompareHistograms\n");

    if (h1->GetNbinsX() != h2->GetNbinsX())
    {
        printf("* number of bins is different\n");
        return 1;
    }

    bool error = false;
    for (int bi = 1; bi <= h1->GetNbinsX(); ++bi)
    {
        const double c1 = h1->GetBinCenter(bi);
        const double w1 = h1->GetBinWidth(bi);
        const double v1 = h1->GetBinContent(bi);

        const double c2 = h2->GetBinCenter(bi);
        const double w2 = h2->GetBinWidth(bi);
        const double v2 = h2->GetBinContent(bi);

        if (c1 != c2)
        {
            printf("* bin %i: difference in bin center: (1) = %.3E, (2) = %.3E\n", bi, c1, c2);
            error = true;
        }

        if (w1 != w2)
        {
            printf("* bin %i: difference in bin width: (1) = %.3E, (2) = %.3E\n", bi, w1, w2);
            error = true;
        }

        if (v1 != v2)
        {
            printf("* bin %i: difference in bin content: (1) = %.3E, (2) = %.3E\n", bi, v1, v2);
            error = true;
        }
    }

    if (error)
        return 2;

    return 0;
}

//----------------------------------------------------------------------------------------------------

int main(int argc, const char **argv)
{
    if (argc < 5)
    {
        printf("ERROR: insufficient input.");
        return 1;
    }

    string n_file1 = argv[1];
    string n_obj1 = argv[2];
    string n_file2 = argv[3];
    string n_obj2 = argv[4];

    printf("comparing (1) to (2):\n");
    printf("    (1): %s from %s\n", n_obj1.c_str(), n_file1.c_str());
    printf("    (2): %s from %s\n", n_obj2.c_str(), n_file2.c_str());

    // load data
    TFile *file1 = TFile::Open(n_file1.c_str());
    if (!file1)
    {
        printf("ERROR: cannot open file '%s'.\n", n_file1.c_str());
        return 2;
    }

    TObject *obj1 = file1->Get(n_obj1.c_str());
    if (!obj1)
    {
        printf("ERROR: cannot load object '%s'.\n", n_obj1.c_str());
        return 3;
    }

    TFile *file2 = TFile::Open(n_file2.c_str());
    if (!file2)
    {
        printf("ERROR: cannot open file '%s'.\n", n_file2.c_str());
        return 4;
    }

    TObject *obj2 = file2->Get(n_obj2.c_str());
    if (!obj2)
    {
        printf("ERROR: cannot load object '%s'.\n", n_obj2.c_str());
        return 5;
    }

    // do comparison
    const bool obj1_graph = obj1->InheritsFrom("TGraph");
    const bool obj1_histogram = obj1->InheritsFrom("TH1");

    const bool obj2_graph = obj2->InheritsFrom("TGraph");
    const bool obj2_histogram = obj2->InheritsFrom("TH1");

    if (obj1_graph && obj2_graph)
        return CompareGraphs((TGraph *) obj1, (TGraph *) obj2);

    if (obj1_histogram && obj2_histogram)
        return CompareHistograms((TH1 *) obj1, (TH1 *) obj2);

    printf("ERROR: don't know how to compare objects of types %s (1) and %s (2).\n", obj1->ClassName(), obj2->ClassName());

    return 0;
}
