#include "TFile.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TH2D.h"

#include <string>
#include <tuple>

using namespace std;

//----------------------------------------------------------------------------------------------------

std::tuple<double, bool, bool> CompareValues(const double v1, const double v2)
{
    const double rel_diff = (v1 == 0. && v2 == 0.) ? 0. : (v2 - v1) / (v2 + v1) * 2.;
    const bool diff_minor = (fabs(rel_diff) > 1E-6);
    const bool diff_major = (fabs(rel_diff) > 1E-3);

    return {rel_diff, diff_major, diff_minor};
}

//----------------------------------------------------------------------------------------------------

int CompareGraphs(const TGraph *g1, const TGraph *g2)
{
    if (g1->GetN() != g2->GetN())
    {
        printf("* number of points is different\n");
        return 1;
    }

    bool diff_major = false;
    bool diff_minor = false;

    for (int i = 0; i < g1->GetN(); ++i)
    {
        const double x_1 = g1->GetX()[i];
        const double y_1 = g1->GetY()[i];

        const double x_2 = g2->GetX()[i];
        const double y_2 = g2->GetY()[i];

        auto [x_rel_diff, x_diff_major, x_diff_minor] = CompareValues(x_1, x_2);
        diff_major |= x_diff_major;
        diff_minor |= x_diff_minor;
        if (x_diff_minor != 0)
            printf("* point %i: difference in x: (1) = %.3E, (2) = %.3E --> rel. diff. = %.1E\n", i, x_1, x_2, x_rel_diff);

        auto [y_rel_diff, y_diff_major, y_diff_minor] = CompareValues(y_1, y_2);
        diff_major |= y_diff_major;
        diff_minor |= y_diff_minor;
        if (y_diff_minor != 0)
            printf("* point %i: difference in x: (1) = %.3E, (2) = %.3E --> rel. diff. = %.1E\n", i, y_1, y_2, y_rel_diff);
    }

    if (diff_major)
        return 2;

    if (diff_minor)
        return 3;

    return 0;
}

//----------------------------------------------------------------------------------------------------

int CompareHistograms1D(const TH1 *h1, const TH1 *h2)
{
    if (h1->GetNbinsX() != h2->GetNbinsX())
    {
        printf("* number of bins is different\n");
        return 1;
    }

    bool diff_major = false;
    bool diff_minor = false;

    for (int bi = 1; bi <= h1->GetNbinsX(); ++bi)
    {
        const double c_1 = h1->GetBinCenter(bi);
        const double w_1 = h1->GetBinWidth(bi);
        const double v_1 = h1->GetBinContent(bi);

        const double c_2 = h2->GetBinCenter(bi);
        const double w_2 = h2->GetBinWidth(bi);
        const double v_2 = h2->GetBinContent(bi);

        auto [c_rel_diff, c_diff_major, c_diff_minor] = CompareValues(c_1, c_2);
        diff_major |= c_diff_major;
        diff_minor |= c_diff_minor;
        if (c_diff_minor != 0)
            printf("* bin %i: difference in bin center: (1) = %.3E, (2) = %.3E --> rel. diff. = %.1E\n", bi, c_1, c_2, c_rel_diff);

        auto [w_rel_diff, w_diff_major, w_diff_minor] = CompareValues(w_1, w_2);
        diff_major |= w_diff_major;
        diff_minor |= w_diff_minor;
        if (w_diff_minor != 0)
            printf("* bin %i: difference in bin width: (1) = %.3E, (2) = %.3E --> rel. diff. = %.1E\n", bi, w_1, w_2, w_rel_diff);

        auto [v_rel_diff, v_diff_major, v_diff_minor] = CompareValues(v_1, v_2);
        diff_major |= v_diff_major;
        diff_minor |= v_diff_minor;
        if (v_diff_minor != 0)
            printf("* bin %i: difference in bin content: (1) = %.3E, (2) = %.3E --> rel. diff. = %.1E\n", bi, v_1, v_2, v_rel_diff);
    }

    if (diff_major)
        return 2;

    if (diff_minor)
        return 3;

    return 0;
}

//----------------------------------------------------------------------------------------------------

int CompareHistograms2D(const TH2 *h1, const TH2 *h2)
{
    if (h1->GetNbinsX() != h2->GetNbinsX() || h1->GetNbinsY() != h2->GetNbinsY())
    {
        printf("* number of bins is different\n");
        return 1;
    }

    bool diff_major = false;
    bool diff_minor = false;

    for (int bi_x = 1; bi_x <= h1->GetNbinsX(); ++bi_x)
    {
        for (int bi_y = 1; bi_y <= h1->GetNbinsY(); ++bi_y)
        {
            const int bi = h1->GetBin(bi_x, bi_y);

            const double c_1 = h1->GetBinCenter(bi);
            const double w_1 = h1->GetBinWidth(bi);
            const double v_1 = h1->GetBinContent(bi);

            const double c_2 = h2->GetBinCenter(bi);
            const double w_2 = h2->GetBinWidth(bi);
            const double v_2 = h2->GetBinContent(bi);

            auto [c_rel_diff, c_diff_major, c_diff_minor] = CompareValues(c_1, c_2);
            diff_major |= c_diff_major;
            diff_minor |= c_diff_minor;
            if (c_diff_minor != 0)
                printf("* bin x %i, bin y %i: difference in bin center: (1) = %.3E, (2) = %.3E --> rel. diff. = %.1E\n", bi_x, bi_y, c_1, c_2, c_rel_diff);

            auto [w_rel_diff, w_diff_major, w_diff_minor] = CompareValues(w_1, w_2);
            diff_major |= w_diff_major;
            diff_minor |= w_diff_minor;
            if (w_diff_minor != 0)
                printf("* bin x %i, bin y %i: difference in bin width: (1) = %.3E, (2) = %.3E --> rel. diff. = %.1E\n", bi_x, bi_y, w_1, w_2, w_rel_diff);

            auto [v_rel_diff, v_diff_major, v_diff_minor] = CompareValues(v_1, v_2);
            diff_major |= v_diff_major;
            diff_minor |= v_diff_minor;
            if (v_diff_minor != 0)
                printf("* bin x %i, bin y %i: difference in bin content: (1) = %.3E, (2) = %.3E --> rel. diff. = %.1E\n", bi_x, bi_y, v_1, v_2, v_rel_diff);
        }
    }

    if (diff_major)
        return 2;

    if (diff_minor)
        return 3;

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
    const bool obj1_histogram_2d = obj1->InheritsFrom("TH2");

    const bool obj2_graph = obj2->InheritsFrom("TGraph");
    const bool obj2_histogram = obj2->InheritsFrom("TH1");
    const bool obj2_histogram_2d = obj2->InheritsFrom("TH2");

    if (obj1_graph && obj2_graph)
        return CompareGraphs((TGraph *) obj1, (TGraph *) obj2);

    if (obj1_histogram_2d && obj2_histogram_2d)
        return CompareHistograms2D((TH2 *) obj1, (TH2 *) obj2);

    if (obj1_histogram && obj2_histogram)
        return CompareHistograms1D((TH1 *) obj1, (TH1 *) obj2);

    printf("ERROR: don't know how to compare objects of types %s (1) and %s (2).\n", obj1->ClassName(), obj2->ClassName());

    return 0;
}
