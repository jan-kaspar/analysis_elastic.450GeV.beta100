#include <cmath>

struct Environment
{
    double v_x_N, v_x_F;
    double L_x_N, L_x_F;

    double L_y_N, L_y_F;

    double la_xy_N, la_xy_F;
    double la_yx_N, la_yx_F;

    void Init()
    {
        v_x_N = -2.22676133379662;
        v_x_F = -1.90985828033614;

        L_x_N = 36.5451226794256E3;   // mm
        L_x_F = 28.2017100011691E3;   // mm

        L_y_N = 170.970215192752E3; // mm
        L_y_F = 191.571488403204E3; // mm

        la_xy_N = la_xy_F = 0;
        la_yx_N = la_yx_F = 0.;
    }
};

struct Kinematics
{
    double vtx_x;
    double th_x, th_y;
};

struct Event
{
    double x_N, x_F;
    double y_N, y_F;
};

Event Propagate(const Kinematics &k, const Environment &env)
{
    Event e;
    e.x_N = env.L_x_N * k.th_x + env.v_x_N * k.vtx_x + env.la_xy_N * k.th_y;
    e.x_F = env.L_x_F * k.th_x + env.v_x_F * k.vtx_x + env.la_xy_F * k.th_y;

    e.y_N = env.L_y_N * k.th_y + env.la_yx_N * k.th_x;
    e.y_F = env.L_y_F * k.th_y + env.la_yx_F * k.th_x;

    return e;
}

Kinematics Reconstruct(const Event &ev, const Environment &env)
{
    const double D = env.v_x_F * env.L_x_N - env.v_x_N * env.L_x_F;

    Kinematics k;
    k.th_x = (env.v_x_F * ev.x_N - env.v_x_N * ev.x_F) / D;
    k.vtx_x = (ev.x_F * env.L_x_N - ev.x_N * env.L_x_F) / D;

    k.th_y = (ev.y_F / env.L_y_F + ev.y_N / env.L_y_N) / 2.;

    return k;
}

//----------------------------------------------------------------------------------------------------

Environment GetBiasedEnvironment(const Environment &env, double la_xy_sym, double la_xy_asym, double la_yx_sym, double la_yx_asym)
{
    Environment env_p = env;

    env_p.la_xy_N = la_xy_sym + la_xy_asym;
    env_p.la_xy_F = la_xy_sym - la_xy_asym;

    env_p.la_yx_N = la_yx_sym + la_yx_asym;
    env_p.la_yx_F = la_yx_sym - la_yx_asym;

    return env_p;
}