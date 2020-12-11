#include <gsl/gsl_machine.h>
#include <cstdio>
#include "classes/common_algorithms.hh"
#include "classes/common_event.hh"
#include "classes/common_init.hh"
#include "classes/Kinematics.hh"

//----------------------------------------------------------------------------------------------------

HitData Perturb(const HitData h_0, int rpi, int proji, double diff)
{
	HitData res(h_0);

	if (rpi == 0 && proji == 0) res.L_2_F.x += diff;
	if (rpi == 0 && proji == 1) res.L_2_F.y += diff;

	if (rpi == 1 && proji == 0) res.L_1_F.x += diff;
	if (rpi == 1 && proji == 1) res.L_1_F.y += diff;

	if (rpi == 2 && proji == 0) res.R_1_F.x += diff;
	if (rpi == 2 && proji == 1) res.R_1_F.y += diff;

	if (rpi == 3 && proji == 0) res.R_2_F.x += diff;
	if (rpi == 3 && proji == 1) res.R_2_F.y += diff;

	return res;
}

//----------------------------------------------------------------------------------------------------

int main()
{
	// run initialisation
	if (Init("config.py", "45b_56t") != 0)
		return 1;

	// uncertainties
	const double x_sh_unc = 150E-3;	// mm
	const double y_sh_unc = 500E-3;	// mm
	const double tilt_unc = 5E-3;	// rad
	
	const double x_sh_NF_unc = 10E-3;	// mm

	// central point
	HitData h_0;
	h_0.L_2_F.x = h_0.L_2_F.y = 0.;
	h_0.L_1_F.x = h_0.L_1_F.y = 0.;
	h_0.R_1_F.x = h_0.R_1_F.y = 0.;
	h_0.R_2_F.x = h_0.R_2_F.y = 0.;

	Kinematics k_0 = DoReconstruction(h_0, env);

	// propagate per-RP shift uncertainties
	{
		double unc_sq_th_x_L = 0, unc_sq_th_y_L = 0;
		double unc_sq_th_x_R = 0, unc_sq_th_y_R = 0;
		double unc_sq_th_x_G = 0, unc_sq_th_y_G = 0;

		for (int rpi = 0; rpi < 4; ++rpi)
		{
			for (int proji = 0; proji < 2; ++proji)
			{
				const double si_q = (proji == 0) ? x_sh_unc : y_sh_unc;

				const double epsilon = 1E-3; // mm
				const auto h_perturbed = Perturb(h_0, rpi, proji, epsilon);
				Kinematics k_perturbed = DoReconstruction(h_perturbed, env);

				const double der_th_x_L = (k_perturbed.th_x_L - k_0.th_x_L) / epsilon;
				const double der_th_y_L = (k_perturbed.th_y_L - k_0.th_y_R) / epsilon;

				const double der_th_x_R = (k_perturbed.th_x_R - k_0.th_x_R) / epsilon;
				const double der_th_y_R = (k_perturbed.th_y_R - k_0.th_y_R) / epsilon;

				const double der_th_x_G = (k_perturbed.th_x - k_0.th_x) / epsilon;
				const double der_th_y_G = (k_perturbed.th_y - k_0.th_y) / epsilon;

				unc_sq_th_x_L += pow(si_q * der_th_x_L, 2.);
				unc_sq_th_y_L += pow(si_q * der_th_y_L, 2.);

				unc_sq_th_x_R += pow(si_q * der_th_x_R, 2.);
				unc_sq_th_y_R += pow(si_q * der_th_y_R, 2.);

				unc_sq_th_x_G += pow(si_q * der_th_x_G, 2.);
				unc_sq_th_y_G += pow(si_q * der_th_y_G, 2.);
			}
		}

		printf("* per-RP shift uncertainties:\n");
		printf("    - left  : si(th_x) = %.1f murad, si(th_y) = %.1f murad\n", sqrt(unc_sq_th_x_L)*1E6, sqrt(unc_sq_th_y_L)*1E6);
		printf("    - right : si(th_x) = %.1f murad, si(th_y) = %.1f murad\n", sqrt(unc_sq_th_x_R)*1E6, sqrt(unc_sq_th_y_R)*1E6);
		printf("    - global: si(th_x) = %.1f murad, si(th_y) = %.1f murad\n", sqrt(unc_sq_th_x_G)*1E6, sqrt(unc_sq_th_y_G)*1E6);
	}

	// near-far shift uncertainty
	{
		const double epsilon = 1E-6;

		HitData h_perturbed(h_0);
		h_perturbed.L_1_F.x += epsilon/2.;
		h_perturbed.L_2_F.x -= epsilon/2.;
		h_perturbed.R_1_F.x += epsilon/2.;
		h_perturbed.R_2_F.x -= epsilon/2.;
		Kinematics k_perturbed = DoReconstruction(h_perturbed, env);
		const double der_L = (k_perturbed.th_x_L - k_0.th_x_L) / epsilon;
		const double der_R = (k_perturbed.th_x_R - k_0.th_x_R) / epsilon;

		printf("* N-F shift uncertainties:\n");
		printf("    - left  : si(th_x) = %.1f murad\n", fabs(der_L * x_sh_NF_unc)*1E6);
		printf("    - right : si(th_x) = %.1f murad\n", fabs(der_R * x_sh_NF_unc)*1E6);
	}

	// TODO: tilt estimate
	// in 2.5km notes:
	//	th*_x --> th*_x + C * th*_y
	//	th*_y --> th*_y + D * th*_x
}